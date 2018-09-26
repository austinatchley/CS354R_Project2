# Project 2 for CS 354R Game Technology

------------------------------------------
## Outdated info


## Information
### Build instructions
Navigate to the `build/` dir and run the command `cmake ..` then `make` to build the project. Then, run the executable with `./Project1`.

### Contents
This project serves as my introduction to Ogre. The assignment was just to create a ball bouncing in a room, but my project contains a few extras:
- Event System
	- For this project, I wrote the beginnings of an event sending/receiving system in the pursuit of decoupling any dependencies between classes
	- Subscribers can use the `connect` function to subscribe to any incoming events of a certain type
	- Events can be sent with arbitrary datasets, and they are handled by each connected subscriber's `receive` function
	- Events are queued up during the course of a frame and dispatched at its end
	- The source is located in `include/ECS/EventManager.h` for more details
	- Planned features include:
		- Full-fledged Entity-Component system
		- `broadcast` vs `event` using an ID system (could be based on Entity or Component ID)
		- Use more efficient data structure for storing queued events (e.g., ring buffer)
- Camera controls
	- Use WASD to control forward/backward and strafe
	- Use PgUp and PgDn/End (for some reason the Ogre bindings for PgDn maps to End on my keyboard)
	- Up left/right/up/down arrow keys to rotate the camera (DOOM-style :) )
- Textured walls and balls
	- The walls use the provided BeachStones example material
	- The balls use the provided SphereMappedRustySteel material
- Sound effects
	- SDL2\_mixer is used to play a sound effect every time a ball hits a wall
- Address Sanitizer
    - If your C++ compiler supports it, setting the mode to DEBUG in CMakeLists will enable AddressSanitizer and detect memory issues

Most of the 'event-driven' code that is present in the game uses my event system (e.g., camera movement, triggering audio, etc.).
