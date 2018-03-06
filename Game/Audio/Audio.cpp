#include "Audio.h"

Audio::Audio(EventManager * eventManager, vector<Entity *> * entities) :
	Subsystem("Audio", Event::AUDIO, eventManager),
	entities(entities)
{
	// Create function map using lambdas to handle events.
	eventMap[Event::PLAY_SOUND] = [this](Event * e) { PlaySound(e); };
}

Audio::~Audio()
{
}

void Audio::Update()
{
	Subsystem::Update();

	// Update the audio objects based of their entity (physics, currently -) data.
	// TODO: Decouple this..
	for (auto entity : *entities)
	{
		// If there is graphics data to enact upon.
		if (entity->GetAudioData() != nullptr)
		{
			GameObject * gameObject = entity->GetGameObject();
			AudioData * audioData = entity->GetAudioData();

			// Set the audio data accordingly.
			audioData->GetSound().setPosition(
				-gameObject->x,
				-gameObject->y,
				1.0f
			);
		}
	}
}

void Audio::PlaySound(Event * e)
{
	e->entities[0]->GetAudioData()->Play();
}
