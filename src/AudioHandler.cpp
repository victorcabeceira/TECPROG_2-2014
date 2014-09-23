#include "AudioHandler.h"
#include "Game.h"
#include "Logger.h"

AudioHandler::AudioHandler() :

	currentMusic(nullptr),
	currentEffects()

{

}

AudioHandler::~AudioHandler(){

	if(this->currentMusic != nullptr){

		Mix_FreeMusic(this->currentMusic);
		this->currentMusic = nullptr;

	}

	// Log(DEBUG) << "Still had " << this->currentEffects.size() << " sfx on vector.";

	for(auto sfx : this->currentEffects){

		Mix_FreeChunk(sfx.effect);

	}

	this->currentEffects.clear();

}

void AudioHandler::setCurrentMusic(const std::string& path_){

	if(this->currentMusic != nullptr){

		Mix_FreeMusic(this->currentMusic);
		this->currentMusic = nullptr;

	}

	this->currentMusic = Mix_LoadMUS(path_.c_str());

}

void AudioHandler::playMusic(const int times_){

	if(this->currentMusic){

		Mix_PlayMusic(this->currentMusic, times_);

	}
	else{

		Log(WARN) << "There is no song loaded.";

	}
}

void AudioHandler::stopMusic(){

	Mix_HaltMusic();	

}

void AudioHandler::setMusicVolume(const unsigned int percent_){

	const int value = percent_ * MIX_MAX_VOLUME/100;
	Mix_VolumeMusic(value);

}

void AudioHandler::addSoundEffect(const std::string& path_){

	Mix_Chunk* effect = Mix_LoadWAV(path_.c_str());
	SoundEffect sfx = {effect, -1};

	if(effect == nullptr){

		Log(DEBUG) << "Loaded null chunk " << path_ << " " << Mix_GetError();

	}

	/// @todo Resource manager for audio.
	this->currentEffects.push_back(sfx);

	playEffect(0);

}

void AudioHandler::playEffect(const int times_){

	const int playedChannel = Mix_PlayChannel(-1, this->currentEffects.back().effect, times_);

	if(playedChannel == -1){

		Log(ERROR) << "Failed to play sound effect on channel " << playedChannel << ". " << Mix_GetError();

	}

	this->currentEffects.back().channel = playedChannel;

	Mix_ChannelFinished(AudioHandler::notifyChannelDone);

}

void AudioHandler::setEffectVolume(const unsigned int percent_){

	const int value = percent_ * MIX_MAX_VOLUME/100;
	Mix_Volume(-1, value);

}

void AudioHandler::changeMusic(const std::string& path_){

	stopMusic();
	setCurrentMusic(path_);
	playMusic(MIX_LOOP);

}

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
	// Log(DEBUG) << "Channel [" << channel_ << "] done. (CALLBACK)";

	Game::instance().getAudioHandler().clearChannel(channel_);
	
}
