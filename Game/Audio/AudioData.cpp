#include "AudioData.h"

AudioData::AudioData()
{}

AudioData::AudioData(string relativePathToAudioFile)
{
	LoadSound(relativePathToAudioFile);
}

AudioData::~AudioData()
{
}

void AudioData::LoadSound(string relativePathToAudioFile)
{
	buffer.loadFromFile(relativePathToAudioFile);

	sound.setBuffer(buffer);
}

void AudioData::Play()
{
	sound.play();
}

void AudioData::Stop()
{
	sound.stop();
}

sf::SoundBuffer & AudioData::GetBuffer()
{
	return buffer;
}