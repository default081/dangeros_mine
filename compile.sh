#!/bin/bash

echo "begin"
g++ main.cpp -o main menu.cpp menu.h view.h -lsfml-graphics -lsfml-window -lsfml-system -ltinyxml -lsfml-audio
echo "end"