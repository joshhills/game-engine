#include <nclgl/Window.h>

#include "Core.h"

int main() {
	// Create engine and game.
	Core c = Core();

	// TODO: More sophisticated conditions
	// e.g. game logic not finished or window not finished.
	// Main game loop.
	while (true)
	{
		c.Step();
	}
}