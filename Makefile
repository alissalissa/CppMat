#Master project makefile
default: all

all:
	$(MAKE) -C build/

tests:
	$(MAKE) -C tests/

clean:
	$(MAKE) -C build/ clean