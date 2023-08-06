#!/bin/bash

if [ "$(id -u)" != "0" ]; then
    echo "Run as sudo!"
    exit 1
fi

sdl=libsdl2-dev

sudo apt-get update; sudo apt-get install "$sdl"

#failed to install sdl2
if [ "$?" != "0" ]; then
    exit 1
fi

#build project using premake5 if available 
#else use makefile, if it exists
if [ -x "$(command -v premake5)" ]; then
   premake5 gmake2
fi

if [ -f "Makefile" ]; then
    make
else
    echo -n "SDL2 installed. Project not build."
fi