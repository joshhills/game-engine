#pragma once

#include <SFML/Audio.hpp>

#include <string>

using namespace std;

class AudioData {
public:
	AudioData();
	AudioData(string relativePathToAudioFile);
	~AudioData();

	sf::SoundBuffer & GetBuffer();

	/**
	* Shortcut method to set the buffer
	* for the current audio source.
	*
	* @param relativePathToAudioFile The audio buffer to load.
	*/
	void LoadSound(string relativePathToAudioFile);

	/**
	* Shortcut method to play the sound
	* loaded into the audio source.
	*/
	void Play();

	/**
	 * Shortcut method to stop the
	 * sound loaded into the audio source.
	 */
	void Stop();
private:

	// The positional audio source.
	sf::Sound sound;

	// The current sound as a buffer.
	sf::SoundBuffer buffer;
};