#!/bin/bash
g++ main.cpp player/Player.cpp -o game $(pkg-config --cflags --libs raylib)
./game
