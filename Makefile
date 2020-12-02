all:
	gcc bctest.c  binder.c -o bctest
	gcc service_manager.c binder.c -o servicemanager
	gcc test/rpi/client.c binder.c -o client -I.
	gcc test/rpi/service.c binder.c -o service -I.

clean:
	bctest servicemanager client service cpu

