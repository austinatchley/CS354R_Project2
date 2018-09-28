# Project 2 for CS 354R Game Technology

##Design
###Game Overview
Game mechanics:
- Defend your escort as it moves across the level
- Block projectiles by rotating around the escort with the mouse
- Raise and lower the paddle height with keyboard
- Projectiles flying at you around 180 degrees at a time
- Projectiles can start coming from behind, forcing you to flip the camera 
- Anti-bullet hell

Scoring:
- Three lives per level
- Time based score

Look:
- Obstacles scattered around the map
- Can be simple visually
- Alert that projectiles are coming from behind

GUI display/control:
- Time
- Score
- Alert that projectiles are coming from behind

Stretch goals:
- Powerups?
- Rhythm based?

###Software Architecture

At a high level, we will have a single Game class that drives the game, and each of the game objects will be split into their own class, inheriting from the generic GameObject. The game loop, rendering loop, simulation loop, etc will be contained in the Game class, which will invoke updates on singleton instances of each game system. We will use the EventManager, Event, and EventSubscriber patterns to send events between (entirely decoupled) GameObjects and GameSystems.

We will keep track of game state with different State classes stored in a stack of states. The current top of the stack will be shown on the screen. At the state exit, we will pop it off and resume the previous state.

GUI - 5 man hours
Physics - 20 man hours
Sound - 5 man hours
Gameplay - 20 man hours
Level design - 15 man hours
Camera control - 5 man hours

If we won't be able to meet the deadline, we will scrap the stretch goals and some of the different game states. Namely, moving the shield to different height slots and having projectiles behind the player. Also, we will scale back the level design in favor of getting the tech up and running.

###Division of Labor
- GUI
    - Todd
- Physics
    - Billy
    - Austin
- Sound
    - Austin
- Level design
    - Todd
- Gameplay
    - Billy
    - Austin
    - Todd
- Camera control
    - Billy

We're using GitHub, and we will pair program whenever possible.
We're going to meet Thursdays, Sundays, and whenever else possible.

------------------------------------------
## Info from Project 1


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
