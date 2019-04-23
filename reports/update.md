# Marauder’s Map in C
### Mid-Project Update
## Ashley Swanson, Jane Sieving, Emma Pan (The Marauders)

---

## Project Goals

The goal of this project is to create a Marauder’s Map application. The program would allow users to log into a network and track and report their whereabouts using proximity to wifi routers throughout Olin’s campus. As a minimum viable product, we hope to create an application which can report the location of a single user in a text-based format within the terminal. Our stretch goals include tracking multiple users at once and visualizing the output graphically. As discussed in depth below, we are very close to achieving our MVP, we are confident that we can make it work for multiple users, and we are now looking into visualizing the output.

## Learning Goals

One of our learning goals was to learn about networks, how to work with them in C, and how to obtain useful, physical information from the WiFi networks Olin has in place. We definitely have learned a lot about networks already, and have already used C programs to establish client-server connections, and obtain useful information on MAC addresses and connection strength of nearby WiFi routers. <br>

We also wanted to learn about the process of implementing a project with little background knowledge, and this project has already covered many areas that we previously unknown to us. We have split our meetings into research and implementation, and tried various learning techniques like peer-programming and peer-teaching. We have learned a lot from working towards our MVP. In pursuit of one of our stretch goals, we will be learning about and implementing visualization in C, which is another field that we were interested in exploring. <br>

Our last learning goal was to learn about creating well-organized, reader-friendly code. This is an ongoing process, and one of our immediate next tasks is to document our code more thoroughly.


## Progress

Thus far, we have created many of the building blocks for our MVP. We implemented a client and server that can send and receive information to one another using TCP protocol, which will allow us to send the calculated location to the server and disperse the locations to all of the clients. <br>

We implemented a script that parses a file containing Olin’s router MAC addresses (just for West Hall right now - we didn’t want Mike to hate us), along with their room numbers and (eventually) coordinates, and puts them into a hash table. This table will be used to map from MAC addresses to coordinates, at which point we can implement triangulation and send the location back to the server. <br>

We also have a script that gathers the MAC addresses of the strongest wifi routers in the vicinity, along with their respective strengths. This script creates a fork that uses system() to call `nmcli`, which pipes the information back to the parent. They are translated to rooms using the mapping we obtained from Mike, and prints a specified number of nearest rooms. <br>

Here is a picture of that script being run in West Hall, with different numbers of specified outputs:

![image of screenshot](https://github.com/jsieving/SoftSysMarauders/blob/master/Screenshot%20from%202019-04-21%2018-59-26.png)

<br>

While triangulation has not yet been implemented, we have determined the algorithm we will use to calculate approximate location. This consists of adding up the signal strength of all three routers and dividing each strength by this total, giving each router a scale factor proportional to its relative strength. We can then take the X coordinates of each router and multiply them by their respective scale factors. Adding up these three products yields the X coordinate of a user’s location. Then we do the same to find the Y coordinate. Because the strongest routers tend to be in a relatively narrow range of strengths, we may have to scale the scale factors by an experimentally determined value to be more accurate.  <br>


We are in the process of creating a client script which gets the nearest rooms and sends them to the server, integrating the progress described above. It is very close to being complete. In the end, clients will triangulate their location and just send that, rather than the list of nearby rooms. <br>

Lastly, we are in the process of researching and sketching out how we might visualize our Marauder’s Map. We have taken some inspiration from the previous Marauder’s Map, but have decided to implement our own UI, because theirs is implemented in PHP, and we’d like to learn more about graphics in C given that we seem to have time to work towards this stretch goal. So far, we have looked into OpenGL, Kore, and SDL, and are leaning towards CSFML. We chose this development library because it is similar to pygame, a library that we are familiar with, and the C++ version, SFML, has a good amount of documentation and was implemented by a SoftSys team in their final project last year.

## Next Steps

- Document our code more thoroughly. This is done when someone could look at our code, be able to run it, and understand what each function is doing. (Jane, Emma & Ashley)
- Finish the client-side location reporter & transport it to Ashley’s better-scaffolded server-client program. Done when the combined programs compile and produce the expected output. (Jane w/ help from friends)
- Get an image of the map of West Hall with the placements of routers, develop a coordinate system and add the coordinates of routers to each room mapping. Done when the text file of rooms and MAC addresses also has coordinates. (Emma has asked for the image.)
- Write a function which can triangulate between the coordinates of WiFi routers so the output of the room listing program can be converted to a physical location. Done when this function compiles and works. (Ashley)
- Choose a visualization library and get familiar with it. Done when team agrees on library, and tasks have been added to Trello for implementing the visualization. (Emma)

## Resources Used

- [Here](https://docs.google.com/document/d/1idELToCDq5wX1h-5r3yL-W4tlr2yUxLwAVgkMUuoz4s/edit?usp=sharing) is a link to the list of resources we found for network connections and finding MAC addresses in the first phase of our project.
- [Here](https://docs.google.com/document/d/1Z-yXkrT_hlOyFl2hj6lLLfkZ74O_Ei0_TwBZ1cZhOnA/edit?usp=sharing) is a link to the list of resources we found for visualization research.
