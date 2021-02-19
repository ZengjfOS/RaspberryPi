all:
	# add `-static` for static link
	gcc bctest.c  binder.c -o bctest
	gcc service_manager.c binder.c -o servicemanager
	gcc test/rpi/client.c binder.c -o client -I.
	gcc test/rpi/service.c binder.c -o service -I.

clean:
	rm bctest servicemanager client service

