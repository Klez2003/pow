#!/bin/bash

# Update package list and install required utilities
sudo apt update
sudo apt install -y gcc make golang ruby python3 argon2

# Compile C
gcc -o solver_c solver.c -lm

# Compile Go
go build -o solver_go solver.go

# Check Ruby script
ruby -c solver.rb

# Python doesn't require compilation
echo "Python script (solver.py) does not require compilation."

echo "All files have been processed."
