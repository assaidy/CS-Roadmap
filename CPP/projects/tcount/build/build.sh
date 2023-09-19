#!/bin/bash

# preparing data
mkdir -p ~/.local/share/tcount
cp ansi_regular.flf ~/.local/share/tcount/ansi_regular.flf
cp mixkit-positive-notification-951.wav ~/.local/share/tcount/mixkit-positive-notification-951.wav

# building
g++ -o ../tcount ../tcount.cpp -Wall
sudo cp ../tcount /usr/bin/tcount
