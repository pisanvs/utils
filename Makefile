CARGS := "-Werror"
BINROOT := "/usr/local/bin/"

build:
	@echo "Building..."
	$(foreach f, $(wildcard src/*.c), $(shell gcc -o ./dist/$(subst .c,,$(notdir $(f))) $(CARGS) $(f)))
	@echo "Done."

install:
	$(shell mkdir -p $(BINROOT))
	$(shell cp dist/* $(BINROOT))

clean:
	$(shell rm -rf dist/*)
	$(shell rm -rf $(BINROOT)/*)
