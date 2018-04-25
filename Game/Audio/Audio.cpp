#include "Audio.h"

Audio::Audio(EventManager * eventManager) :
	Subsystem("Audio", Event::AUDIO, eventManager)
{
	// Create function map using lambdas to handle events.
	eventMap[Event::AUDIO_PLAY_SOUND] = [this](Event * e) { HandlePlaySoundEvent(e); };
	eventMap[Event::AUDIO_STOP_SOUND] = [this](Event * e) { HandlePlaySoundEvent(e); };
	//eventMap[Event::AUDIO_PLAY_MUSIC] = [this](Event * e) { HandlePlayMusicEvent(e); };
	//eventMap[Event::AUDIO_STOP_MUSIC] = [this](Event * e) { HandleStopMusicEvent(e); };
}

Audio::~Audio()
{}

void Audio::HandlePlaySoundEvent(Event * e)
{
	cout << "Hey?";
	//PlaySoundEvent * pse = static_cast<PlaySoundEvent *>(e);

	//try {
	//	if (pse->canStack)
	//	{
	//		sounds.at(pse->relativePathToAudioFile).Play();
	//	}

	//} catch (out_of_range e)
	//{
	//	// Create a sound buffer.
	//	AudioData ad(pse->relativePathToAudioFile);
	//	
	//	// TODO: Clean
	//	//if (!buffer.loadFromFile(pse->relativePathToAudioFile))
	//	//{
	//	//	logger.Error("Could not open audio file " + pse->relativePathToAudioFile);
	//	//}

	//	// Play it.
	//	ad.Play();

	//	// And add it to map.
	//	sounds[pse->relativePathToAudioFile] = ad;
	//}

	
}

void Audio::HandleStopSoundEvent(Event * e)
{
	//StopSoundEvent * sse = static_cast<StopSoundEvent *>(e);

	//try {
	//	sounds.at(sse->relativePathToAudioFile).Stop();
	//}
	//catch (out_of_range e)
	//{
	//	logger.Warn("Attempting to stop a sound that does not exist: " + sse->relativePathToAudioFile);
	//}
}

//void Audio::StopAllSounds()
//{
//	for (map<string, sf::Sound>::iterator it = sounds.begin(); it != sounds.end(); ++it)
//	{
//		it->second.stop();
//	}
//}
