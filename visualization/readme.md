## To run: 

cd into visualization/themap <br>
Type: <br>
`./test_sdl`
<br>

Main Files: In visualization/themap/src

`init.c`: Initializes the framework and necessary components, then creates and opens a window. This also includes cleanup functions for ending the program.

`input.c`: Monitors user input. Registers when the mouse moves/is clicked, and when the window is closed.

`draw.c`: Includes the functions related to displaying graphics on the screen, and does all the scaling and translating necessary to render things in the right place.

`entities.c`: Includes code for initializing an entity when a new player joins, removing and updating players, changing the background based on mouse clicks for different floors, and calling draw functions to show the relevant players on the screen.

`main.c`: Runs the program. Creates a client thread, calls the initialization functions, and then calls the functions that run the GUI in a while loop.
