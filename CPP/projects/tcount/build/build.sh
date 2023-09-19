#!/bin/bash

# preparing data
mkdir -p ~/.local/share/tcount
cp ansi_regular.flf ~/.local/share/tcount/ansi_regular.flf
# TODO: NOTIFICATION SOUND

# building
g++ -o ../tcount ../tcount.cpp -Wall
sudo cp ../tcount /usr/bin/tcount
