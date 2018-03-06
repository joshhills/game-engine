#pragma once

#include <SFML/Audio.hpp>

class AudioData {
public:
	AudioData();
	~AudioData();

	sf::Sound & GetSound();

	/**
	 * Shortcut method to set the buffer
	 * for the current audio source.
	 *
	 * @param buffer The audio buffer to load.
	 */
	void SetSoundBuffer(sf::SoundBuffer * buffer);

	/**
	 * Shortcut method to play the sound
	 * loaded into the audio source.
	 */
	void Play();
private:

	// The positional audio source.
	sf::Sound sound;
	
	// The current sound as a buffer.
	sf::SoundBuffer * buffer; 
};