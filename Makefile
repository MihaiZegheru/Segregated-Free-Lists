#
#   Copyright (c) 2023-2024 | Mihai Zegheru | 312CAb
#

CC=gcc
CFLAGS=-Wall -Wextra -std=c99 -g3 -g

BUILD_DIR=build
SRC_DIR=src
INC_DIR=include

EXE=sfl
SOURCES+=$(wildcard $(SRC_DIR)/*.c)
HEADERS+= $(addprefix -I,$(wildcard $(INC_DIR)))

EXTRAS=Makefile README.md

.PHONY: build
build:
	$(CC) $(CFLAGS) $(HEADERS) $(SOURCES) -o $(BUILD_DIR)/$(EXE) -lm

run_sfl:
	./build/sfl

pack:
	zip -FSr 312CA_ZegheruMihai_Tema1.zip $(SRC_DIR) $(INC_DIR) $(BUILD_DIR) $(EXTRAS)

clean:
	rm $(BUILD_DIR)/$(EXE)
