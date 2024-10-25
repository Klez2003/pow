# Proof of Work Challenge Solver

This document provides instructions for compiling and running the Proof of Work Challenge Solver implemented in C and Ruby.

## Requirements

Before running the scripts, ensure you have the following utilities installed on your system:

- **argon2**: A secure hashing algorithm for password hashing.
- **xxd**: A tool for creating a hex dump from a binary file and vice versa.
- **bc**: An arbitrary precision calculator language.

### Install Required Utilities

On Ubuntu/Debian-based systems, you can install the required utilities using:

```bash
sudo apt update
sudo apt install argon2 xxd bc
```
```bash
gcc -o solver solver.c -lm
./proof_of_work "262144:1:SALTe7e590c2f902:1500"
```
```bash
ruby proof_of_work.rb "262144:1:SALTe7e590c2f902:1500"
```
```bash
chmod +x solver.sh
./solver.sh "262144:1:SALTe7e590c2f902:1500"
```
### Summary of the Markdown Content

- **Requirements**: Lists required utilities and how to install them.
- **C Version**: Instructions for compiling and running the C program, including example output.
- **Ruby Version**: Instructions for running the Ruby script, including example output.
- **Conclusion**: Encourages the user to follow the instructions for successful execution.

You can save the above content in a file named `README.md`. Let me know if you need any further modifications!