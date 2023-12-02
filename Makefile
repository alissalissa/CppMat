#Master project makefile
default: compile

compile:
	$(MAKE) -C build/

clean:
	$(MAKE) -C build/ clean