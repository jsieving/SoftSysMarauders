message_create_test: mac_mapping.h mac_mapping.c message_create_test.c
	gcc mac_mapping.h mac_mapping.c message_create_test.c -Wall -I/usr/local/include/glib-2.0 -I/usr/local/lib/x86_64-linux-gnu/glib-2.0/include -L/usr/local/lib/x86_64-linux-gnu -lglib-2.0 -o message_create_test

client: mac_mapping.h mac_mapping.c client_reporter.c
	gcc mac_mapping.h mac_mapping.c client_reporter.c -Wall -I/usr/local/include/glib-2.0 -I/usr/local/lib/x86_64-linux-gnu/glib-2.0/include -L/usr/local/lib/x86_64-linux-gnu -lglib-2.0 -o client
	gcc server_multi.c -o server

get_locs: mac_mapping.h mac_mapping.c get_locs.c
	gcc mac_mapping.h mac_mapping.c get_locs.c -Wall -I/usr/local/include/glib-2.0 -I/usr/local/lib/x86_64-linux-gnu/glib-2.0/include -L/usr/local/lib/x86_64-linux-gnu -lglib-2.0 -o get_locs

room_lookup: mac_mapping.h mac_mapping.c room_lookup.c
	gcc mac_mapping.h mac_mapping.c room_lookup.c -Wall -I/usr/local/include/glib-2.0 -I/usr/local/lib/x86_64-linux-gnu/glib-2.0/include -L/usr/local/lib/x86_64-linux-gnu -lglib-2.0 -o room_lookup

get_macs: mac_mapping.h mac_mapping.c get_macs.c
	gcc mac_mapping.h mac_mapping.c get_macs.c -Wall -I/usr/local/include/glib-2.0 -I/usr/local/lib/x86_64-linux-gnu/glib-2.0/include -L/usr/local/lib/x86_64-linux-gnu -lglib-2.0 -o get_macs

clean:
	rm -f get_macs room_lookup get_locs server client message_create_test
