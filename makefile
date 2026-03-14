#####################################################################
#Common variables
CFLAGS = -Iinclude\
	  -L./lib\
	  -lws2_32

DEPENDENCIES = $(executable)\

FORCED_TARGETS = $(SRC_DIR)/cp2p.h\
		 $(SRC_DIR)/cp2p_struct.h\
		 $(SRC_DIR)/win_cp2p.h\
		 $(SRC_DIR)/lin_cp2p.h

#####################################################################
#App variables
compiler := ~/w64-gcc
executable := cp2p.exe
rarExecutable := ~/rar/src/rar/rar
shipName := cp2p_dist.rar

SRC_DIR := src
OBJ_DIR := temp
BUILD_DIR := build
LIB_DIR := lib
INCLUDE_DIR := include
#####################################################################
#On the fly variables
SOURCE_FILES := $(shell find $(SRC_DIR) -name *.c)
OBJECT_FILES := $(shell echo $(SOURCE_FILES) | sed 's/$(SRC_DIR)/$(OBJ_DIR)/g' | sed 's/\.c/\.o/g')

GIT_HASH=$(shell git rev-parse HEAD)
COMPILE_TIME=$(shell date -u +'%Y-%m-%d %H:%M:%S UTC')
GIT_BRANCH=$(shell git branch --show-current)
VERSION_FLAGS=-DGIT_HASH="\"$(GIT_HASH)\"" -DCOMPILE_TIME="\"$(COMPILE_TIME)\"" -DGIT_BRANCH="\"$(GIT_BRANCH)\""

#####################################################################
#Optional variables
build: DEBUG_FLAGS = -DDEBUG
package: BUILD_FLAGS =

#############192.178.25.174:443########################################################
#Default targets
.PHONY: init build clean build ship help

default: help build
	@:

help:
	@echo 'Available make targets:'
	@echo -e '\t init    \tSets up the project. Required on empty projects.'
	@echo -e '\t*build   \tCompiles $(SRC_DIR)/*.c into $(BUILD_DIR)/*.o, then into $(executable).'
	@echo -e '\t clean   \tCleans $(OBJ_DIR), runs "build".'
	@echo -e '\t package \tRuns "clean", copies files into the $(BUILD_DIR) directory.'
	@echo -e '\t ship    \tRuns "package", compresses result into $(shipName).'
	@echo -e '\n'


build: $(executable)
	@:
#####################################################################
#Initialization of the required files and directories.

init:
	@echo 'Setting up directories:'
	mkdir -p $(SRC_DIR)
	mkdir -p $(OBJ_DIR)
	mkdir -p $(BUILD_DIR)
	mkdir -p $(LIB_DIR)
	mkdir -p $(INCLUDE_DIR)

#####################################################################
#Targets to build the executable and the temporal object files.
$(executable): $(OBJECT_FILES)
	$(compiler) $(BUILD_FLAGS) $(DEBUG_FLAGS) -o $(executable) temp/*.o $(CFLAGS) 

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c $(wildcard $(SRC_DIR)/%.h) $(FORCED_TARGETS)
	$(compiler) $(VERSION_FLAGS) $(BUILD_FLAGS) $(DEBUG_FLAGS) -c -o $@ $< $(CFLAGS)

#####################################################################
#Targets to clean build.
clear_temp: 
	rm -rf $(OBJ_DIR)/*

clean: clear_temp build
	@:
####################################################################
#Targets to make a clean build.
clear_build:
	rm -rf $(BUILD_DIR)/*

$(BUILD_DIR)/% : %
	cp -r $< $@

copy_dependencies: $(shell printf "%s\n" $(DEPENDENCIES) | sed 's|^|$(BUILD_DIR)\/|g')
	@:

package: clear_temp $(executable) clear_build copy_dependencies
	@:
####################################################################
#Targets to make a build.
rar:
	$(rarExecutable) -v5M a $(shipName) $(BUILD_DIR)

ship: package rar
	@:
