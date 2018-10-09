# Project 2 for CS 354R Game Technology

## Design
### Game Overview
Game mechanics:
- Defend your escort as it moves across the level
- Block projectiles by rotating around the escort with the mouse
- Raise and lower the paddle height with keyboard
- Projectiles flying at you from every direction (360 degrees around a single axis)
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

### Software Architecture

At a high level, we will have a single Game class that drives the game, and each of the game objects will be split into their own class, inheriting from the generic GameObject. The game loop, rendering loop, simulation loop, etc will be contained in the Game class, which will invoke updates on singleton instances of each game system. We will use the EventManager, Event, and EventSubscriber patterns to send events between (entirely decoupled) GameObjects and GameSystems.

We will keep track of game state with different State classes stored in a stack of states. The current top of the stack will be shown on the screen. At the state exit, we will pop it off and resume the previous state.

- GUI - 5 man hours
- Physics - 20 man hours
- Sound - 5 man hours
- Gameplay - 20 man hours
- Level design - 15 man hours
- Camera control - 5 man hours

If we won't be able to meet the deadline, we will scrap the stretch goals and some of the different game states. Namely, moving the shield to different height slots and having projectiles behind the player. Also, we will scale back the level design in favor of getting the tech up and running.

### Division of Labor
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

### Week 2 Update:

GUI: Currently initialized, but is not displaying on the rendered window, code should be good to go when display issue is found. (Behind)
Physics: Objects are not being acted upon by forces thus we can't move on to gameplay (very behind)
Sound: Working as Intended. (Done)
Level Design: Wasn't needed for demo, time constraints have made it so design is being severely cut if not nonexistant. (N/A)
Gameplay: Nonexistant until physics is working.
Cameral Control: Working as intended. (Done)

Notes: The rendering loop is now contained in each individual state with the game class calling the update method on the active state. Workload is the same.
