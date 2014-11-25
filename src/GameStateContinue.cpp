#include "GameStateContinue.h"
#include "LuaScript.h"
#include "Game.h"
#include "Util.h"
#include <string>
#include "SafeDeallocation.h"


GameStateContinue::GameStateContinue() :

	background(nullptr),
	selector(nullptr),
	passedTime(0.0),
	currentSelection(Selection::SLOT_1),
	selectorXPosition(562),
	selectorYPosition {500,610,723}

{

	this->slot1 = new Text(615.0, 520.0, "res/fonts/maturasc.ttf", 45, "Empty Slot");
	this->slot2 = new Text(615.0, 630.0, "res/fonts/maturasc.ttf", 45, "Empty Slot");
	this->slot3 = new Text(615.0, 730.0, "res/fonts/maturasc.ttf", 45, "Empty Slot");

}

GameStateContinue::~GameStateContinue(){

	SAFE_DELETE(this->slot1);
	SAFE_DELETE(this->slot2);
	SAFE_DELETE(this->slot3);
	
}

void GameStateContinue::load(){
	
	Log(DEBUG) << "Loading Continue Screen...";
	
	bool game_instance_save_slot1 = Game::instance().getSaves().isSaved(SLOT_1);

	if(game_instance_save_slot1){
		
		const int levelFromSave = game_instance_save_slot1;

		const std::string currentLevel = "Level " + Util::toString(levelFromSave);
		
		if(levelFromSave == -1)
	
			this->slot1->changeText("Empty Slot");
	
		else
	
			this->slot1->changeText(currentLevel.c_str());
	
	}

	else{
	
		this->slot1->changeText("Empty Slot");
	
	}

	bool game_instance_save_slot2 = Game::instance().getSaves().isSaved(SLOT_2);

	if(game_instance_save_slot2){
		
		const int levelFromSave = game_instance_save_slot2;

		const std::string currentLevel = "Level " + Util::toString(levelFromSave);
		
		if(levelFromSave == -1)
	
			this->slot2->changeText("Empty Slot");
	
		else
	
			this->slot2->changeText(currentLevel.c_str());
	
	}
	else{
	
		this->slot2->changeText("Empty Slot");
	
	}

	bool game_instance_save_slot3 = Game::instance().getSaves().isSaved(SLOT_3);

	if(game_instance_save_slot3){
		
		const int levelFromSave = game_instance_save_slot3;

		const std::string currentLevel = "Level " + Util::toString(levelFromSave);
			
		if(levelFromSave == -1)
	
			this->slot3->changeText("Empty Slot");
	
		else
	
			this->slot3->changeText(currentLevel.c_str());
	
	}
	else{
	
		this->slot3->changeText("Empty Slot");
	
	}

	std::string imageBackground ("continue.images.background");
	std::string imageSelector ("continue.images.selector");

	LuaScript luaMenu("lua/Continue.lua");
	const std::string pathBackground = luaMenu.unlua_get<std::string>(imageBackground);
	const std::string pathSelector = luaMenu.unlua_get<std::string>(imageSelector);

	this->background = Game::instance().getResources().get(pathBackground);
    this->selector = Game::instance().getResources().get(pathSelector);

	this->selector->setWidth(410);
	this->selector->setHeight(102);

    this->currentSelection = Selection::SLOT_1;

    Game::instance().getFade().fadeOut(0, 0.002);

}

void GameStateContinue::unload(){

	Log(DEBUG) << "\tUnloading menu...";
	cleanEntities();

}

void GameStateContinue::update(const double deltaTime_){

	this->passedTime += deltaTime_;

	handleSelectorMenu();

	std::array<bool, GameKeys::MAX> keyStates = Game::instance().getInput();

	if(keyStates[GameKeys::ESCAPE] == true){

		Game::instance().setState(Game::GameStates::MENU);

	}

}

void GameStateContinue::render(){

	if(this->background != nullptr){

		this->background->render(0, 0, nullptr, true);
		this->selector->render(selectorXPosition, selectorYPosition[currentSelection],
							   nullptr, false, 0.0, nullptr, SDL_FLIP_NONE);
	
		this->slot1->render(0, 0);
		this->slot2->render(0, 0);
		this->slot3->render(0, 0);
	}
	else{

		Log(WARN) << "No image set to display on the menu!";

	}
}

void GameStateContinue::handleSelectorMenu(){

	std::array<bool, GameKeys::MAX> keyStates = Game::instance().getInput();

	const double selectorDelayTime = 0.2;

	if(keyStates[GameKeys::LATTACK] == true){

		if(this->passedTime >= selectorDelayTime){

			Game::instance().setState(Game::GameStates::MENU);

		}
	}
	if(keyStates[GameKeys::DOWN] == true || keyStates[GameKeys::RIGHT] == true){

		if(this->passedTime >= selectorDelayTime){

			if(currentSelection < (Selection::TOTAL - 1)){

				currentSelection++;

			}
			else{

				currentSelection = Selection::SLOT_1;

			}

			this->passedTime = 0.0;

		}
	}

	else if(keyStates[GameKeys::UP] == true || keyStates[GameKeys::LEFT] == true){

		if(this->passedTime >= selectorDelayTime){

			if(currentSelection > Selection::SLOT_1){

				currentSelection--;

			}
			else{

				currentSelection = (Selection::TOTAL - 1);

			}

			this->passedTime = 0.0;

		}
	}


	else if(currentSelection == Selection::SLOT_1 && keyStates[GameKeys::SPACE] == true){

		Game::instance().currentSlot = SLOT_1;

		switch(Game::instance().getSaves().getSavedLevel(Selection::SLOT_1)){

			Game::instance().currentSlot = Selection::SLOT_1;

			case 1:
				Game::instance().transitionTo = Game::GameStates::LEVEL_ONE;
				Game::instance().setState(Game::instance().transitionTo);

				break;

			case 2:
				Game::instance().transitionTo = Game::GameStates::LEVEL_TWO;
				Game::instance().setState(Game::instance().transitionTo);

				break;

			case 3:
				Game::instance().transitionTo = Game::GameStates::LEVEL_THREE;
				Game::instance().setState(Game::instance().transitionTo);

				break;

			case 4:
				Game::instance().transitionTo = Game::GameStates::LEVEL_FOUR;
				Game::instance().setState(Game::instance().transitionTo);

				break;

			case 5:
				Game::instance().transitionTo = Game::GameStates::LEVEL_FIVE;
				Game::instance().setState(Game::instance().transitionTo);

				break;

			case 6:
				Game::instance().transitionTo = Game::GameStates::LEVEL_BOSS;
				Game::instance().setState(Game::instance().transitionTo);

				break;

			default:

				break;

		}

	}

	else if(currentSelection == Selection::SLOT_2 && keyStates[GameKeys::SPACE] == true){

		Game::instance().currentSlot = SLOT_2;

		switch(Game::instance().getSaves().getSavedLevel(Selection::SLOT_2)){
			
			Game::instance().currentSlot = Selection::SLOT_2;

			case 1:
				Game::instance().transitionTo = Game::GameStates::LEVEL_ONE;
				Game::instance().setState(Game::instance().transitionTo);
	
				break;
	
			case 2:
				Game::instance().transitionTo = Game::GameStates::LEVEL_TWO;
				Game::instance().setState(Game::instance().transitionTo);
	
				break;
	
			case 3:
				Game::instance().transitionTo = Game::GameStates::LEVEL_THREE;
				Game::instance().setState(Game::instance().transitionTo);
	
				break;
	
			case 4:
				Game::instance().transitionTo = Game::GameStates::LEVEL_FOUR;
				Game::instance().setState(Game::instance().transitionTo);
	
				break;
	
			case 5:
				//CHANGE THIS AFTER CREATING FIFTH LEVEL
				Game::instance().transitionTo = Game::GameStates::LEVEL_FIVE;
				Game::instance().setState(Game::instance().transitionTo);
	
				break;
	
			case 6:
				Game::instance().transitionTo = Game::GameStates::LEVEL_BOSS;
				Game::instance().setState(Game::instance().transitionTo);
	
				break;
	
			default:
	
				break;
	
		}

	}
	
	else if(currentSelection == Selection::SLOT_3 && keyStates[GameKeys::SPACE] == true){
	
		Game::instance().currentSlot = SLOT_3;

		switch(Game::instance().getSaves().getSavedLevel(Selection::SLOT_3)){
	
			Game::instance().currentSlot = Selection::SLOT_3;
	
			case 1:
				Game::instance().transitionTo = Game::GameStates::LEVEL_ONE;
				Game::instance().setState(Game::instance().transitionTo);
			
				break;
			
			case 2:
				Game::instance().transitionTo = Game::GameStates::LEVEL_TWO;
				Game::instance().setState(Game::instance().transitionTo);
			
				break;
			
			case 3:
				Game::instance().transitionTo = Game::GameStates::LEVEL_THREE;
				Game::instance().setState(Game::instance().transitionTo);
			
				break;
			
			case 4:
				Game::instance().transitionTo = Game::GameStates::LEVEL_FOUR;
				Game::instance().setState(Game::instance().transitionTo);
			
				break;
			
			case 5:
				//CHANGE THIS AFTER CREATING FIFTH LEVEL
				Game::instance().transitionTo = Game::GameStates::LEVEL_FIVE;
				Game::instance().setState(Game::instance().transitionTo);
			
				break;
			
			case 6:
				Game::instance().transitionTo = Game::GameStates::LEVEL_BOSS;
				Game::instance().setState(Game::instance().transitionTo);
			
				break;
			
			default:
			
				break;
		
		}

	}

}
