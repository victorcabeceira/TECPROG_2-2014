#include "Document.h"
#include "Logger.h"
#include "Game.h"

//The Constructor of Document
Document::Document(const double x_, const double y_, const std::string& path_, const std::string& pathDocumentText_) :

	Entity(x_, y_, path_),
	shouldRender(false),
	documentText(Game::instance().getResources().get(pathDocumentText_))

{

	if(documentText == nullptr){

		std::string error_DocumentText("Could not load document text sprite.");

		Log(ERROR) << error_DocumentText;

	}
}

//Empty constructor
Document::~Document(){
}

//Updates the Document
void Document::update(const double deltaTime_){

	((void)deltaTime_); // Unused;

}

//Renders the document
void Document::render(const double cameraX_, const double cameraY_){

	const double dx = this->x - cameraX_;
	const double dy = this->y - cameraY_;

	if(this->sprite != nullptr){

		this->sprite->render(dx, dy);

	}
	else{

		std::string error_render_document ("Failed to render document sprite.");

		Log(ERROR) << error_render_document;
	
	}
}

//Renders the Text of the Document
void Document::renderDocumentText(){

	this->documentText->render(0, 0, nullptr, true);
	
}