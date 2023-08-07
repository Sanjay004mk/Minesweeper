#!/bin/bash

isPackageNotInstalled() {

    dpkg --status $1 &> /dev/null

    if [ $? -eq 0 ]; then
        echo "$1: Already installed"
    else
        sudo apt-get install -y $1
    fi
}

sdl=libsdl2-dev

isPackageNotInstalled $sdl

./premake5 gmake2;

make