# MAC address mapping
### Authors: Jane Sieving
### For the Marauders' Map project

These are the files which pertain to getting nearby MAC addresses, mapping them to rooms, and showing the results (so far in plain text).

## Quick demo

Building this code depends on GLib.

Download `mac_mapping.c`, `mac_mapping.h`, `Makefile`, and either `message_create_test.c` or the server and client code.

Message creation only: `$ make && ./message_create_test`

Client & server demo:

    $ make client
    $ ./server

    (New terminal)

    $ ./client [server_IP]

## Files

`mac_mapping.c` provides functions for getting nearby MAC addresses and creating a lookup table to translate MAC addresses to room numbers. Its functions are described in `mac_mapping.h` for use in the rest of the code.

`get_macs.c` tests one component of that process: getting nearby MAC addresses, parsing them, and displaying addresses with signal strength.

`room_lookup.c` tests another component, which is building a lookup table between MAC addresses and rooms by parsing a text file, and printing that table. It takes one optional command line argument, which is the name of an alternate text file to create the table from.

`MAC_rooms.txt` is the text file used by default to create a table in `room_lookup.c`.

`get_locs.c` puts all the functionality of `mac_mapping.c` together to get find the routers with the strongest signals and print their rooms with signal strength. It takes one optional command line argument, which is an integer specifying the number of routers to show. By default, it is the top 3.

`message_create_test.c` tests the function `create_message`, which takes a text buffer and its size and fills it with formatted results of room finding. It takes one optional command line argument, which is the size of the buffer to test with.

`client_reporter.c` is a simple client program which connects to a server and reports its location once, in the form produced by `create_message`. It takes one optional command line argument, which is the IP address of the server.

`server_multi.c` is a server program capable of connecting to multiple clients by using `select` to switch between sockets. When run, it will wait for client messages and then print them.

## Building

The Makefile provides several options for building and testing the code contained here:

`make` or `make message_create_test` will compile `message_create_test.c` and the code it relies on into an executable called `message_create_test`. To use it, enter `$ ./message_create_test [buffer_size]`.

`make client` will compile `client_reporter.c`, `server_multi.c` and the code they rely on into executables called `client` and `server`, respectively. To use them, run `$ ./server` in one terminal tab, followed by `$ ./client [server_IP]` in another.

`make get_locs` will compile `get_locs.c` and the code it relies on into an executable called `get_locs`. To use it, enter `$ ./get_locs [max_results]`.

`make get_macs` will compile `get_macs.c` and the code it relies on into an executable called `get_macs`. To use it, enter `$ ./get_macs`.

`make room_lookup` will compile `room_lookup.c` and the code it relies on into an executable called `room_lookup`. To use it, enter `$ ./room_lookup [mapping_filename]`.

`make clean` deletes executable files created by make.

## Known Issues

When `get_locs` is run with a high number of results to display (10 in my experience), it will print an error message as described in `get_locs.c`, `get_near_rooms()`, ~ line 22. This claims that a key was not found. However, 10 results are returned, and the previous line, which prints the key that allegedly couldn't be found, does not execute.
