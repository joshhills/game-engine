#include "AudioData.h"

AudioData::AudioData()
{
}

AudioData::~AudioData()
{
	delete this->buffer;
}

sf::Sound & AudioData::GetSound()
{
	return sound;
}

void AudioData::SetSoundBuffer(sf::SoundBuffer * buffer)
{
	if (this->buffer != nullptr)
	{
		delete this->buffer;
	}

	this->buffer = buffer;

	sound.setBuffer(*buffer);
}

void AudioData::Play()
{
	sound.play();
}