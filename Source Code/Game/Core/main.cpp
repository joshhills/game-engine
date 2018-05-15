#include <nclgl/Window.h>

#include "Core.h"

int main() {
	// Create engine and attached game.
	Core c = Core();

	// Run game until it is finished.
	while (c.Step()) {}
}