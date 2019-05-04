client: mac_mapping.h mac_mapping.c client.c
	gcc mac_mapping.h mac_mapping.c client.c -Wall -pthread `pkg-config --cflags glib-2.0` `pkg-config --libs glib-2.0` -o client
	gcc server.c -Wall -o server

message_create_test: mac_mapping.h mac_mapping.c message_create_test.c
	gcc mac_mapping.h mac_mapping.c message_create_test.c -Wall `pkg-config --cflags glib-2.0` `pkg-config --libs glib-2.0` -o message_create_test

get_locs: mac_mapping.h mac_mapping.c get_locs.c
	gcc mac_mapping.h mac_mapping.c get_locs.c -Wall `pkg-config --cflags glib-2.0` `pkg-config --libs glib-2.0` -lglib-2.0 -o get_locs

room_lookup: mac_mapping.h mac_mapping.c room_lookup.c
	gcc mac_mapping.h mac_mapping.c room_lookup.c -Wall `pkg-config --cflags glib-2.0` `pkg-config --libs glib-2.0` -lglib-2.0 -o room_lookup

get_macs: mac_mapping.h mac_mapping.c get_macs.c
	gcc mac_mapping.h mac_mapping.c get_macs.c -Wall `pkg-config --cflags glib-2.0` `pkg-config --libs glib-2.0` -o get_macs

triangulate: mac_mapping.h mac_mapping.c triangulate.c
	gcc mac_mapping.h mac_mapping.c triangulate.c -Wall `pkg-config --cflags glib-2.0` `pkg-config --libs glib-2.0` -o triangulate

clean:
	rm -f get_macs room_lookup get_locs server client message_create_test triangulate
