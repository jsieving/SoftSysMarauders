# An Olin Marauder’s Map in C:
## Utilizing Networks to Find, Share & Visualize Location
### Ashley Swanson, Jane Sieving, Emma Pan (The Marauders)

---

## Project Goals

The goal of this project was to create a Marauder’s Map application. The program allows users to log into a network and track and report their whereabouts using proximity to wifi routers throughout Olin’s campus. As a minimum viable product, we created an application which could report the location of a single user in a text-based format within the terminal. We extended this locator to handle multiple client connections and render users’ positions on a map of West Hall.

## Accomplishments

Our project consists of an SDL2 visualization framework that displays a map for the user of all the people currently logged into the program, a client program which calculates and reports its location, then renders the locations of other users on a map, and a server program which receives and sends out the locations of all users.

Here's an image of our process diagram for the client. The client does most of the work, and the server mainly just parrots back information, so it is not included.

![](https://github.com/jsieving/SoftSysMarauders/blob/master/client_diagram.png)

### Server/Client Communication

The clients and server communicate use TCP, and the server handles multiple clients by checking on which clients have had activity using the select() function. We selected TCP over other network protocols like UDP to ensure that all information packets were sent reliably and received in order. We used select() rather than threads or forking because managing several clients in the same address space with threads would be too error-prone from sharing data, and forking a process for each client seemed like unnecessary work for the CPU.

Here's a diagram of the client-server protocol:

![](https://github.com/jsieving/SoftSysMarauders/blob/master/client_server_diagram.png)
<br>

### Location from Wifi Routers

We created a script that gathers the MAC addresses of the strongest Wi-Fi routers in the vicinity, along with their respective strengths. This script creates a fork that uses system() to call `nmcli`, which outputs the addresses and strengths.

`system("nmcli -f BSSID,SIGNAL -t -e no dev wifi")`

The fork then pipes this information back to the parent process. The addresses are translated to room numbers and coordinates using the router mapping we obtained from Mike. The mapping data is in a text file, which is parsed and used to create a lookup table (specifically a GLib Hashtable). After looking up the nearby rooms, the client uses their coordinates to triangulate the user’s location.

Here are the results of mapping nearby routers to rooms:

![](https://github.com/jsieving/SoftSysMarauders/blob/master/router_mapping.jpg)
<br>

### Triangulation

The triangulation algorithm adds up the signal strength of all three routers and divides each strength by this total, giving each router a scale factor proportional to its relative strength. We then take the X coordinates of each router and multiply them by their respective scale factors. Adding up these three products yields the X coordinate of a user’s location. Then we do the same to find the Y coordinate. The floor number is just the floor number of the router with the strongest signal.

Because signal strengths and found routers can change unpredictably, we maintain a rolling average of the most recent triangulated locations. In order to make users move more smoothly on the map and make the location more consistent, each update from the client sends the average of the last 20 locations. This is maintained by a rolling queue which keeps track of the total x and y values for efficient recalculation. The floor number is just the number determined in the most recent report.

Here is the output from tracking one user's location:

![](https://github.com/jsieving/SoftSysMarauders/blob/master/location_reports.jpg)
<br>

### Reporting

The map is an image of a floor plan of West Hall at Olin College. There are buttons to change which floor is being displayed. After scanning the nearby routers, mapping these to rooms, triangulating location and updating the rolling average, the client reports its latest location to the server, along with the user’s name. The server reports each location update as they are received to all the clients. Each client then renders all the location updates it received as characters on the map. <br>

### Visualization

![](https://github.com/jsieving/SoftSysMarauders/blob/master/screencap_map.png)

To visualize our Marauder’s Map, we decided to implement our own UI, in order to learn more about graphics in C. We looked into the C visualization frameworks OpenGL, Kore, SDL2, and CSFML, and settled on SDL2. We chose this development library because it is similar to Pygame, a library that we are familiar with, it was simpler than OpenGL and Kore, and had the most documentation in C. The link to the tutorial we learned from can be found [here](https://www.parallelrealities.co.uk/tutorials/#ppp). <br>

When creating the visualization framework, we followed a similar organization structure to the tutorials, and simplified it greatly to fit our needs and make it easier to read. We split the code into different files based on functionality, gave each its own header file to keep track of dependencies, and imported a `common.h` header file to all of them, to store the essential imports and header files. Two other essential header files were `defs.h`, which defined the global variables, and `structs.h`, which defined all the structs we created for our visualization program. The `app` is stored in one shared struct called `App`, and each player’s information is stored in an `Entity` struct, which are all stored in a linked list. The head of the linked list is stored in the `App` struct. This architecture allows us to update the shared entities and app from different code files, quickly find the functions we’re looking for, and isolate where visualization-related errors are coming from. <br>

There is a lot of code supporting the visualization, so here is a list describing the most important files and their functionalities:

`init.c`: Initializes the framework and necessary components, then creates and opens a window. This also includes cleanup functions for ending the program.

`input.c`: Monitors user input. Registers when the mouse moves/is clicked, and when the window is closed.

`draw.c`: Includes the functions related to displaying graphics on the screen, and does all the scaling and translating necessary to render things in the right place.

`entities.c`: Includes code for initializing an entity when a new player joins, removing and updating players, changing the background based on mouse clicks for different floors, and calling draw functions to show the relevant players on the screen.

`main.c`: Runs the program. Creates a client thread, calls the initialization functions, and then calls the functions that run the GUI in a while loop.

## Current State

We achieved the basic functionality of multi-client location reporting early on in our project and got each of the components described above working. Here is a link to a video demo of the program: [Demo](https://youtu.be/tULAqdishBw)

As you can see, we also created a beautiful visualizer with the ability to render multiple users and switch between floors. We got successful demos of the visualizer for 2 cases: hard-coded users, and one user calculating and rendering its own location.

However, when trying to integrate the visualizer with the multi-threaded client code, we ran into issues involving how SDL2 handles threads. Aside from having to re-factor parts of our code to use SDL2's threading protocol, we ran into an issue which is internal to Xlib (a dependency of SDL2) which takes a variable amount of time to cause a segfault (in our experience, a few seconds). Despite doing a lot of research and trying a lot of things to fix the bug, we were not able to troubleshoot it in the time available. Therefore, we are currently not able to visualize data based on communication between the clients and server; we can only render data that is locally available. We're still very satisfied with all that we learned and got working. <br>


## What we Learned

Over the course of this project, we have learned about networks, threading, forking, piping, system calls, header files, system architecture, manipulating strings in C, working with large, complex C libraries, graphics, debugging segmentation faults, and writing tolerable technical reports. <br>

Our use of threads and forks in the client and the select() function in the server reinforced our understanding of how to use these tools and challenged us to think critically about which was the right tool for handling multiple tasks or activities. Accordingly, we learned methods for sharing data across threads and forks and how the implementations differs. Additionally, the number of moving parts involved in our entire program afforded us the opportunity to learn about system architecture in a project with multiple types of functionality and multi-threading.

The project also allowed our team to learn how to approach a large project where we knew very little about the subject at the start. We researched, sought guidance, and experimented throughout the process, taking on new tasks one at a time. For the especially daunting holes in our knowledge (such as Wi-Fi routers in general), we learned to start early and Google lots.


## Resources Used

[Here](https://docs.google.com/document/d/1idELToCDq5wX1h-5r3yL-W4tlr2yUxLwAVgkMUuoz4s/edit?usp=sharing) is a link to the list of resources we found for network connections and finding MAC addresses in the first phase of our project.
[Here](https://docs.google.com/document/d/1Z-yXkrT_hlOyFl2hj6lLLfkZ74O_Ei0_TwBZ1cZhOnA/edit?usp=sharing) is a link to the list of resources we found for visualization research.
