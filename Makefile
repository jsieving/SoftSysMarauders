make_room_lookup: make_room_lookup.c
	gcc make_room_lookup.c -Wall -I/usr/local/include/glib-2.0 -I/usr/local/lib/x86_64-linux-gnu/glib-2.0/include -L/usr/local/lib/x86_64-linux-gnu -lglib-2.0 -o make_room_lookup
