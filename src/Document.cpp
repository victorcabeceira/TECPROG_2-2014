#include "Document.h"
#include "Logger.h"
#include "Game.h"

Document::Document(const double x_, const double y_, const std::string& path_, const std::string& pathDocumentText_) :

	Entity(x_, y_, path_),
	shouldRender(false),
	documentText(Game::instance().getResources().get(pathDocumentText_))

{

	if(documentText == nullptr){

		Log(ERROR) << "Could not load document text sprite.";

	}
}

Document::~Document(){
}

void Document::update(const double deltaTime_){

	((void)deltaTime_); // Unused;

}

void Document::render(const double cameraX_, const double cameraY_){

	const double dx = this->x - cameraX_;
	const double dy = this->y - cameraY_;

	if(this->sprite != nullptr){

		this->sprite->render(dx, dy);

	}
	else{

		Log(ERROR) << "Failed to render document sprite.";
	
	}
}

void Document::renderDocumentText(){

	this->documentText->render(0, 0, nullptr, true);
	
}