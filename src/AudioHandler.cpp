#include "AudioHandler.h"
#include "Game.h"
#include "Logger.h"

// Method that creates de Audio Handler of the game.
AudioHandler::AudioHandler() :

	currentMusic(nullptr),
	currentEffects()

{

}

// Destructor method, runs when the class is deallocated.
AudioHandler::~AudioHandler(){

	if(this->currentMusic != nullptr){

		Mix_FreeMusic(this->currentMusic);
		this->currentMusic = nullptr;

	}

	for(auto sfx : this->currentEffects){

		Mix_FreeChunk(sfx.effect);

	}

	this->currentEffects.clear();

}

// Change the current music.
void AudioHandler::setCurrentMusic(const std::string& path_){

	if(this->currentMusic != nullptr){
	
		// Free the current music running.
		Mix_FreeMusic(this->currentMusic);
		this->currentMusic = nullptr;

	}

	// Loads the new music.
	this->currentMusic = Mix_LoadMUS(path_.c_str());

}

// Play the current music, a determined number of times.
void AudioHandler::playMusic(const int times_){

	if(this->currentMusic){

		Mix_PlayMusic(this->currentMusic, times_);

	}
	else{

		Log(WARN) << "There is no song loaded.";

	}
}

// Stop the current music.
void AudioHandler::stopMusic(){

	Mix_HaltMusic();	

}

// Change the volume of the music running.
void AudioHandler::setMusicVolume(const unsigned int percent_){

	const int value = percent_ * MIX_MAX_VOLUME/100;
	Mix_VolumeMusic(value);

}

// Add a new sound effect.
void AudioHandler::addSoundEffect(const std::string& path_){

	// Loads the new sound effect.
	Mix_Chunk* effect = Mix_LoadWAV(path_.c_str());
	SoundEffect sfx = {effect, -1};

	// Gives it a error if the effect didn't load.
	if(effect == nullptr){

		Log(DEBUG) << "Loaded null chunk " << path_ << " " << Mix_GetError();

	}

	/// @todo Resource manager for audio.
	
	// Put the effect in the vector of effects, and plays it.
	this->currentEffects.push_back(sfx);
	playEffect(0);

}

// Plays the effects.
void AudioHandler::playEffect(const int times_){

	const int playedChannel = Mix_PlayChannel(-1, this->currentEffects.back().effect, times_);

	if(playedChannel == -1){

		Log(ERROR) << "Failed to play sound effect on channel " << playedChannel << ". " << Mix_GetError();

	}

	this->currentEffects.back().channel = playedChannel;

	Mix_ChannelFinished(AudioHandler::notifyChannelDone);

}

// Change the effect volume.
void AudioHandler::setEffectVolume(const unsigned int percent_){

	const int value = percent_ * MIX_MAX_VOLUME/100;
	Mix_Volume(-1, value);

}

// Change the volume.
void AudioHandler::changeMusic(const std::string& path_){

	stopMusic();
	setCurrentMusic(path_);
	playMusic(MIX_LOOP);

}

// Deletes all the sound playing.
void AudioHandler::clearChannel(const int channel_){

	std::vector<SoundEffect>::iterator it;

	for(it = this->currentEffects.begin(); it != this->currentEffects.end();){

		if(it->channel == channel_){

			Mix_FreeChunk(it->effect);
			it->effect = nullptr;
			this->currentEffects.erase(it);

		}
		else{

			it++;

		}
	}
}

void AudioHandler::notifyChannelDone(int channel_){

	Game::instance().getAudioHandler().clearChannel(channel_);
	
}
