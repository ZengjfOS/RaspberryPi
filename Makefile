all:
	gcc bctest.c  binder.c -o bctest
	gcc service_manager.c binder.c -o service_manager

clean:
	bctest service_manager

