# JETPLANE-SIMULATOR-GAME

# DEVELOPER
	PURU GUPTA

# RUNNING THE GAME
* To build the game enter these command:
	* mkdir output
    * cd output
    * cmake ..
    * make all

* To run the game enter these command in the output/ directory:
	* run	./graphics_asgn1 in build directory

# RULES
* Your health and fuel is your lifeline.
* Your game is over if:-
    * your health or fuel reaches zero 
    * you crash into the water
    * you crash into the super volcanoes
* Random checkpoints are generated throughout the game denoted by a shiny red arrow, you have to kill the enemy cannon at the checkpoint to mark it.
* You can use missiles and bombs to kill enemy cannons.
* The enemy cannons follow your movement and  fires missiles at you in a certain range, avoid them or lose health and score.
* Some smoke rings appear in the sky, pass through them for extra score.
* A powerup in the form of a 
    * Fuel Barrel, if taken gives extra fuel.
    * Health Refill, if taken gives extra health.
* You can also kill enemy parachutes for extra score using missiles only.
* There is a dashboard to aid you in the game with:-
    * Compass
    * SpeedoMeter
    * AltiMeter
    * HealthMeter
    * FueloMeter
    * Map
    * Segment Score Display
* Sounds are added to make it more fun.
* To win the game, mark all the checkpoints clear.

# CAMERA VIEWS
* Plane View
* Top View
* Tower View
* Follow-Cam View
* Helicopter View

# POINT SCHEME
* Fuel Barrel -> 10
* Health Refill -> 10
* Passing through Ring -> 10
* Parachute -> 30
* Marking a Checkpoint -> 20
* Hit a Cannon -> 50
* Got hit by a cannon ball -> -10

# CONTROLS:

|      Moves          |      Keyboard input     |
|:-------------------:|:-----------------------:|
| Move Left  	      |     Left Arrow Key      | 
| Move Right 	      |     Right Arrow key     |
| Nose Up     	      |      Up Arrow Key       |
| Nose Down           |     Down Arrow Key      |
| Move Forward        |         W Key           |
| Move Backward       |         S Key           |
| Tilt Right          |         D Key           |
| Tilt Left           |         A Key           |
| Ascent              |         G Key           |
| Descent             |         H Key           |
| Missile             | M Key/Left Mouse Button |
| Bomb                | B Key/Right Mouse Button|
| Zoom In/Out         |      Mouse Scroll       |
| Control Camera(Heli)|       Mouse Drag        |


#								GOOD LUCK