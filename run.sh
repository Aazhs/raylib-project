#!/bin/bash
g++ main.cpp player/Player.cpp -o game $(pkg-config --cflags --libs raylib)
if [ $? -eq 0 ]; then
	./game 1>/dev/null
fi
