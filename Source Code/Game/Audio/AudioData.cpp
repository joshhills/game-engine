#include "AudioData.h"

AudioData::AudioData()
{}

AudioData::AudioData(string relativePathToAudioFile)
{
	LoadSound(relativePathToAudioFile);
}

AudioData::~AudioData()
{
	delete buffer;
}

void AudioData::LoadSound(string relativePathToAudioFile)
{
	if (buffer != nullptr)
	{
		delete buffer;
	}

	buffer = new sf::SoundBuffer;
	buffer->loadFromFile(relativePathToAudioFile);

	sound.setBuffer(*buffer);
}

void AudioData::Play(float x, float y)
{
	sound.setPosition(x, y, 0);
	sound.play();
}

void AudioData::Stop()
{
	sound.stop();
}