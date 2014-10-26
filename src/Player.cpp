#include "Player.h"
#include "Game.h"
#include "Logger.h"
#include "Configuration.h"
#include "LuaScript.h"
#include <cmath>
#include <cfloat>

#include "PlayerStateIdle.h"
#include "PlayerStateAerial.h"
#include "PlayerStateMoving.h"
#include "PlayerStateRolling.h"
#include "PlayerStateCrouching.h"
#include "PlayerStateAiming.h"
#include "PlayerStateMovingCrouch.h"
#include "PlayerStateAttack.h"
#include "PlayerStateAttackMoving.h"
#include "PlayerStateAttackJumping.h"
#include "PlayerStateHit.h"
#include "PlayerStateClimbing.h"
#include "PlayerStateDead.h"

#include "Window.h"

#define ADD_STATE_EMPLACE(stateEnum, stateClass) this->statesMap.emplace(stateEnum, new stateClass(this))
#define ADD_STATE_INSERT(stateEnum, stateClass) this->statesMap.insert(std::make_pair<PlayerStates, StatePlayer*>(stateEnum, new stateClass(this)));

Player::Player(const double x_, const double y_, const std::string& path_) :
    DynamicEntity(x_, y_, path_),
    potionsLeft(3),
    maxPotions(3),
    crosshair(new Crosshair(0.0, 0.0, "res/images/alvo.png")),
    life(3),
    attackStrength(50),
    canAttack(true),
    currentItem(PItems::POTION),
    closestEnemyIsRight(true),
    isVulnerable(true),
    invulnerableTime(0),
    canMove(true),
    animation(nullptr),
    currentState(nullptr)
{
    initializEnemyStates();

    LuaScript luaPlayer("lua/Player.lua");
    this->width = luaPlayer.unlua_get<int>("player.dimensions.width");
    this->height = luaPlayer.unlua_get<int>("player.dimensions.height");

    // Shouldn't be here?
    this->animation = new Animation(0, 3, this->width, this->height, 11, false);

    if(this->sprite != nullptr){
	
        this->currentState = this->statesMap.at(IDLE);
        this->currentState->enter();
		
    }
    else{
	
        Log(WARN) << "No sprite set for the player! Null sprite.";
		
    }

}

Player::~Player(){
    if(this->currentState != nullptr){
	
        this->currentState->exit();
        this->currentState = nullptr;
		
    }

    if(this->animation != nullptr){
	
        delete this->animation;
        this->animation = nullptr;
		
    }
	
    destroyStates();
}

void Player::update(const double deltaTime_){
    std::array<bool, GameKeys::MAX> keyStates = Game::instance().getInput();

    if(this->canMove){
	
        this->currentState->handleInput(keyStates);
		
    }

    Game::instance().clearKeyFromInput(GameKeys::ACTION);

    scoutPosition(deltaTime_);

    updateBoundingBox();

    const std::array<bool, CollisionSide::SOLID_TOTAL> detections = detectCollision();
    handleCollision(detections);

    updatePosition(deltaTime_);

    this->animation->update(this->animationClip, deltaTime_);

    for(auto potion : this->potions){
	
        if(!potion->activated){
            // Delete potion.
			
        }
        potion->update(deltaTime_);
    }

    if(!this->isVulnerable){
	
        this->invulnerableTime += deltaTime_;
        if(this->invulnerableTime >= 1){
		
            this->invulnerableTime = 0;
            this->isVulnerable = true;
            this->canAttack = true;
			
        }
    }

    if(this->isClimbing && !isCurrentState(PlayerStates::CLIMBING)){
	
        changEnemyState(PlayerStates::CLIMBING);
		
    }

}

void Player::handleCollision(std::array<bool, CollisionSide::SOLID_TOTAL> detections_){
    if(detections_.at(CollisionSide::SOLID_TOP)){ 
	
        Log(DEBUG) << "COLLIDED_TOP";
        this->vy = 0.0;
		
    }
    if(detections_.at(CollisionSide::SOLID_BOTTOM)){
	
        if(isCurrentState(PlayerStates::AERIAL) || isCurrentState(PlayerStates::ATTACKJUMPING) 
            || isCurrentState(PlayerStates::HITED)  || isCurrentState(PlayerStates::CLIMBING) ||  
            isCurrentState(PlayerStates::DEAD)){
			
            const double magic = 32.0;
            const double aerialToIdleCorrection = 8.0;

            this->nextY -= fmod(this->nextY, 64.0) - magic + aerialToIdleCorrection;
            this->vy = 0.0;
            if(!isCurrentState(PlayerStates::DEAD)){
			
                changEnemyState(PlayerStates::IDLE);
				
            }
        }
    }
    else{
        if(!isCurrentState(PlayerStates::AERIAL) && !isCurrentState(PlayerStates::ATTACKJUMPING)
            && !isCurrentState(PlayerStates::CLIMBING) && !isCurrentState(PlayerStates::DEAD)){
			
            changEnemyState(PlayerStates::AERIAL);
			
        }
    }
    if(detections_.at(CollisionSide::SOLID_LEFT)){
	
        this->nextX = this->x;
        this->vx = 0.0;
		
    }
    if(detections_.at(CollisionSide::SOLID_RIGHT)){
	
        this->nextX = this->x;
        this->vx = -0.001;
		
    }

}

void Player::render(const double cameraX_, const double cameraY_){

    const double dx = this->x - cameraX_;
    const double dy = this->y - cameraY_;

    if(this->sprite != nullptr){
	
        SDL_RendererFlip flip = getFlip();

        if(flip == SDL_FLIP_HORIZONTAL){
		
            this->sprite->render(dx - 100, dy, &this->animationClip, false, 0.0, nullptr, flip);
			
			}
        else{
		
            this->sprite->render(dx, dy, &this->animationClip, false, 0.0, nullptr, flip);
			
			}
    }

    if(this->crosshair != nullptr){
	
        this->crosshair->render(cameraX_, cameraY_);
		
    }

    for (auto potion : this->potions) {
	
        potion->render(cameraX_, cameraY_);
		
    }

}

void Player::usePotion(const int strength_, const int distance_){
    if(this->potionsLeft > 0){
	
        this->potionsLeft--;
        const double potionX = ((this->isRight) ? this->boundingBox.x + this->boundingBox.w : this->boundingBox.x);
        Potion* potion = new Potion(potionX , this->y, "res/images/explosion_with_potion.png", strength_, this->vx, distance_, this->isRight);
        this->potions.push_back(potion);
		
    }
}

void Player::addPotions(const unsigned int quantity_){
    if(this->potionsLeft + quantity_ > this->maxPotions){
	
        this->potionsLeft = this->maxPotions;
		
    }
    else{
	
        this->potionsLeft += quantity_;
		
    }
}

void Player::initializEnemyStates(){
    // Initialize all the states in Player here.
    ADD_STATE_INSERT(IDLE,         PlayerStateIdle);
    ADD_STATE_INSERT(MOVING,       PlayerStateMoving);
    ADD_STATE_INSERT(AERIAL,       PlayerStateAerial);
    ADD_STATE_INSERT(ROLLING,      PlayerStateRolling);
    ADD_STATE_INSERT(CROUCHING,    PlayerStateCrouching);
    ADD_STATE_INSERT(AIMING,       PlayerStateAiming);
    ADD_STATE_INSERT(MOVINGCROUCH, PlayerStateMovingCrouch);
    ADD_STATE_INSERT(ATTACK,       PlayerStateAttack);
    ADD_STATE_INSERT(ATTACKMOVING, PlayerStateAttackMoving);
    ADD_STATE_INSERT(ATTACKJUMPING,PlayerStateAttackJumping);
    ADD_STATE_INSERT(HITED,        PlayerStateHit);
    ADD_STATE_INSERT(CLIMBING,     PlayerStateClimbing);
    ADD_STATE_INSERT(DEAD,         PlayerStateDead);
}

void Player::destroyStates(){
    // Delete all the states in Player here.
    std::map<PlayerStates, StatePlayer*>::const_iterator it;
    for(it = this->statesMap.begin(); it != this->statesMap.end(); it++){
	
        delete it->second;
		
    }
}

void Player::changEnemyState(const PlayerStates state_){
    this->currentState->exit();
    this->currentState = this->statesMap.at(state_);
    this->currentState->enter();
}

Animation* Player::getAnimation(){
    return (this->animation);
}

bool Player::isCurrentState(const PlayerStates state_){
    return (this->currentState == this->statesMap.at(state_));
}

void Player::updateBoundingBox(){
    this->boundingBox.x = (int) this->nextX + this->currentState->box.x;
    this->boundingBox.y = (int) this->nextY + this->currentState->box.y;
    this->boundingBox.w = this->currentState->box.w;
    this->boundingBox.h = this->currentState->box.h;
}

bool Player::isDead(){
    return (this->life <= 0);
}
