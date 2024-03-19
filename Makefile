CC=gcc
CFLAGS=-Wall -Wextra -std=c99 -g3

BUILD_DIR=build
SRC_DIR=src

EXE=segregated_free_lists
SOURCES+=$(wildcard $(SRC_DIR)/*.c)
HEADERS+= $(addprefix -I,$(wildcard $(SRC_DIR)))

.PHONY: build
build:
	$(CC) $(CFLAGS) $(HEADERS) $(SOURCES) -o $(BUILD_DIR)/$(EXE) -lm

pack:
	zip -FSr 312CA_ZegheruMihai_Tema3.zip $(SOURCES) $(HEADERS) $(EXTRAS)

clean:
	rm $(BUILD_DIR)/$(EXE)
