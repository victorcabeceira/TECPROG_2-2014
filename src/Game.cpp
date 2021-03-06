#include "Game.h"
#include "FramesPerSecondWrapper.h"
#include "Configuration.h"
#include <cassert>
#include "Util.h"

#include "GameStateSplash.h"
#include "LevelOne.h"
#include "LevelTwo.h"
#include "LevelThree.h"
#include "LevelFour.h"
#include "LevelFive.h"
#include "LevelBoss.h"
#include "GameStateMenu.h"
#include "GameStateNewGame.h"
#include "GameStateContinue.h"
#include "GameStateOptions.h"
#include "GameStateCredits.h"
#include "GameStateGameOver.h"
#include "GameStateTransition.h"
#include "GameStateVictory.h"
#include "Sprite.h"
#include "SafeDeallocation.h"

#include "Logger.h"

#define ADD_STATE_EMPLACE(stateEnum, stateClass) this->statesMap.emplace(stateEnum, new stateClass())
#define ADD_STATE_INSERT(stateEnum, stateClass) this->statesMap.insert(std::make_pair<GameStates, StateGame*>(stateEnum, new stateClass()))
/*
*
* Main structure class for the game.
* Contains all the necessary functionalities to loop and update the game.
* 	Is the state machine (controls current state), contains all the different possible states.
*/

/**
* Singleton imeplementation for Game.
* @return The instance for a Game.
*/
Game& Game::instance(){

	static Game* instance = new Game();
	return *instance;

}

Game::Game() :

	isCutscene(false),
	isPaused(false),
	currentLine(0),
	transitionTo(LEVEL_ONE),
	window(nullptr),
	isRunning(false),
	pauseImage(nullptr),
	pauseSelector(nullptr),
	audioHandler(new AudioHandler()),
	inputHandler(new InputHandler()),
	resourceManager(new ResourceManager()),
	gameSave(new GameSave()),
	fadeScreen(nullptr),
	currentState(nullptr),
	statesMap(),
	passedTime(0.0),
	currentSelection(PSelection::RESUME),
	selectorXPositionLeft {550, 550},
	selectorYPositionLeft {400, 470},
	selectorXPositionRight {930, 930},
	selectorYPositionRight {400, 470}

{

	this->window = new Window(Configuration::getScreenWidth(),
		Configuration::getScreenHeight(), Configuration::getWindowTitle());

	assert(this->window != nullptr && "The window should not be null!");

	initializEnemyStates();

	std::string path = "res/images/Dialog/dialog";
	std::string extension = ".png";	

	for(int dialogIterator = 0; dialogIterator < numLines; dialogIterator++){

		this->dialog[dialogIterator] = nullptr;
		this->dialog[dialogIterator] = getResources().get(path + Util::toString(dialogIterator) + extension);
	
		if(this->dialog[dialogIterator] == nullptr){

			Log(ERROR) << "Invalid dialog image.";

		}
	}

	this->pauseImage = getResources().get("res/images/pause_overlay.png");
	this->pauseSelector = getResources().get("res/images/cursor_regular.png");
	this->pauseSelector->setWidth(50);

	this->isRunning = true;
	FramesPerSecondWrapper::initialize(this->fpsManager);

}

/**
* The destructor.
* Destroys the game's Window and states, and unloads current state.
*/
Game::~Game(){

	SAFE_UNLOAD(this->currentState);
	destroyStates();
	SAFE_DELETE(this->audioHandler);
	SAFE_DELETE(this->inputHandler);
	SAFE_DELETE(this->resourceManager);
	SAFE_DELETE(this->fadeScreen);
	SAFE_DELETE(this->window);
	
}

/**
* The main game loop.
* Orders the game structure, such as inputs, updates, and rendering.
*/
void Game::runGame(){

	this->fadeScreen = new FadeScreen();

	this->currentState = this->statesMap.at(GameStates::SPLASH);
	this->currentState->load();

	// Get the first game time.
	double totalGameTime = 0.0;
	const double deltaTime = 1.0 / 60.0;
	double accumulatedTime = 0.0;

	// This is the main game loop.
	while(this->isRunning){

		const double frameTime = FramesPerSecondWrapper::delay(this->fpsManager);
		accumulatedTime += frameTime;

		// Update.
		while(accumulatedTime >= deltaTime){

			this->inputHandler->handleInput();

			// Check for an exit signal from input.
			if(this->inputHandler->isQuitFlag() == true){

				stop();
				return;
			
			}

			std::array<bool, GameKeys::MAX> keyStates = Game::instance().getInput();

			if(keyStates[GameKeys::ESCAPE] && isPauseable()){
		
				this->currentSelection = PSelection::RESUME;
				this->isPaused = true;
		
			}

			if(!this->isPaused){
		
				this->currentState->update(deltaTime);
		
			}
		
			else if(!this->isCutscene){
		
				this->passedTime += deltaTime;
				updatePause();
		
			}
			else{
		
				this->passedTime += deltaTime;
				updateDialog();
		
			}

			this->fadeScreen->update(deltaTime);

			accumulatedTime -= deltaTime;
			totalGameTime += deltaTime;
		}

		// Render.
		window->clear();
		
		this->currentState->render();				    
		
		if(this->isPaused){
		
			renderPause();
		
		}
		
		else if(this->isCutscene){
		
			if(currentLine < numLines)
				renderDialog();	
			else{
		
				currentLine = 0;
				isCutscene = false;
			
			}
		}

		this->fadeScreen->render();

		window->render();
	
	}
}

/**
* Sets the current game state.
* @see StateGame::load()
* @see StateGame::unload()
* @param state_ : The state you want to be changed into.
*/
void Game::setState(const GameStates state_){

	/// @todo Implement the transition between states.
	this->currentState->unload();
	this->currentState = this->statesMap.at(state_);
	this->currentState->load();

}

/**
* Loads all the states.
* Every new state implemented should be initialized here.
*/
void Game::initializEnemyStates(){

	ADD_STATE_INSERT(SPLASH, GameStateSplash);
	ADD_STATE_INSERT(MENU, GameStateMenu);
	ADD_STATE_INSERT(NEW_GAME, GameStateNewGame);
	ADD_STATE_INSERT(LEVEL_ONE, LevelOne);
	ADD_STATE_INSERT(LEVEL_TWO, LevelTwo);
	ADD_STATE_INSERT(LEVEL_THREE, LevelThree);
	ADD_STATE_INSERT(LEVEL_FOUR, LevelFour);
	ADD_STATE_INSERT(LEVEL_FIVE, LevelFive);
	ADD_STATE_INSERT(LEVEL_BOSS, LevelBoss);
	ADD_STATE_INSERT(CONTINUE, GameStateContinue);
	ADD_STATE_INSERT(OPTIONS, GameStateOptions);
	ADD_STATE_INSERT(CREDITS, GameStateCredits);
	ADD_STATE_INSERT(GAMEOVER, GameStateGameOver);
	ADD_STATE_INSERT(TRANSITION, GameStateTransition);
	ADD_STATE_INSERT(VICTORY, GameStateVictory);

}

void Game::renderDialog(){

	if(currentLine > numLines){

		currentLine = 0;
		return;

	}

	if(this->dialog[currentLine])
		this->dialog[currentLine]->render(0,0,nullptr,true);
		
}

void Game::handleDialog(){

	std::array<bool, GameKeys::MAX> keyStates = Game::instance().getInput();

	const double selectorDelayTime = 0.2;

	if(keyStates[GameKeys::SPACE] == true ){

		if(this->passedTime >= selectorDelayTime){

			currentLine++;

		}
	}
}

void Game::updateDialog(){

	handleDialog();

}

void Game::renderPause(){
	
	if(this->pauseImage != nullptr){
	
		this->pauseImage->render(0, 0, nullptr, true);

		this->pauseSelector->render(selectorXPositionLeft[currentSelection],
			selectorYPositionLeft[currentSelection], nullptr, false, 0.0, nullptr, SDL_FLIP_NONE);

		this->pauseSelector->render(selectorXPositionRight[currentSelection],
			selectorYPositionRight[currentSelection], nullptr, false, 0.0, nullptr, SDL_FLIP_HORIZONTAL);
	
	}
	else{
	
		Log(WARN) << "No image set to display on the menu!";
	
	}
}

void Game::updatePause(){

	handleSelectorMenu();

}

void Game::handleSelectorMenu(){

	std::array<bool, GameKeys::MAX> keyStates = Game::instance().getInput();

	const double selectorDelayTime = 0.2;

	if(keyStates[GameKeys::DOWN] == true || keyStates[GameKeys::RIGHT] == true){

		if(this->passedTime >= selectorDelayTime){

			if(currentSelection < (PSelection::TOTAL - 1)){

				currentSelection++;

			}
			else{

				currentSelection = PSelection::RESUME;
			}

			this->passedTime = 0.0;
		}
	}

	else if(keyStates[GameKeys::UP] == true || keyStates[GameKeys::LEFT] == true){

		if(this->passedTime >= selectorDelayTime){
			
			if(currentSelection > PSelection::RESUME){
			
				currentSelection--;
			
			}
			else{
			
				currentSelection = (PSelection::TOTAL - 1);
			
			}
			
			this->passedTime = 0.0;
		
		}
	}

	else if(currentSelection == PSelection::RESUME && keyStates[GameKeys::SPACE] == true){

		this->isPaused = false;

	}

	else if(currentSelection == PSelection::EXIT && keyStates[GameKeys::SPACE] == true){

		Game::instance().setState(Game::GameStates::MENU);
		this->isPaused = false;

	}
}

/**
* Deletes all the loaded states.
* Every new state implemented should be deleted here.
*/
void Game::destroyStates(){

	std::map<GameStates, StateGame*>::const_iterator it;

    for(it = this->statesMap.begin(); it != this->statesMap.end(); it++){

        delete it->second;

    }
}

/**
* @return The Game audioHandler.
*/
AudioHandler& Game::getAudioHandler(){

	return (*(this->audioHandler));

}

/**
* @return The boolean array recieved from the InputHandler.
*/
std::array<bool, GameKeys::MAX> Game::getInput(){

	return this->inputHandler->getKeyStates();

}

/**
* @return The resource manager.
*/
ResourceManager& Game::getResources(){

	return (*(this->resourceManager));

}

GameSave& Game::getSaves(){

	return (*(this->gameSave));

}

/**
* Stops execution and closes the game.
*/
void Game::stop(){

	this->isRunning = false;

}

void Game::clearKeyFromInput(const GameKeys key_){

	this->inputHandler->clearKey(key_);

}

FadeScreen& Game::getFade(){

	return (*(this->fadeScreen));

}

void Game::resizeWindow(const unsigned int width_, const unsigned int height_){

	this->window->resize(width_, height_);

}

bool Game::isPauseable(){

	if(this->currentState == this->statesMap.at(Game::GameStates::LEVEL_ONE))

		return true;

	if(this->currentState == this->statesMap.at(Game::GameStates::LEVEL_TWO))

		return true;

	if(this->currentState == this->statesMap.at(Game::GameStates::LEVEL_THREE))

		return true;

	if(this->currentState == this->statesMap.at(Game::GameStates::LEVEL_FOUR))

		return true;

	if(this->currentState == this->statesMap.at(Game::GameStates::LEVEL_FIVE))

		return true;

	if(this->currentState == this->statesMap.at(Game::GameStates::LEVEL_BOSS))

		return true;

	return false;
}
