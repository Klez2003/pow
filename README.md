# Proof of Work Script

This repository contains scripts for implementing a Proof of Work (PoW) algorithm using the Argon2 hashing function. It is designed to solve a mining challenge based on given parameters, making it suitable for educational purposes or testing PoW implementations.

## Table of Contents

- [Features](#Features)
- [Requirements](#Requirements)
- [Installation](#Installation)
- [Usage](#Usage)
- [Examples](#Examples)

## Features

- Checks for required utilities (`argon2`, `xxd`, `bc`).
- Accepts a challenge code as input, either via command line or prompt.
- Iteratively generates and hashes candidate passwords until a valid solution is found.
- Displays the solution once it meets the required difficulty.
- **Python Salt Generator**: A Python script to generate random salt values and PoW challenge codes, with configurable parameters.

## Requirements

Ensure the following utilities are installed on your system:

- `argon2`: A secure hashing algorithm for password hashing.
- `xxd`: A tool for creating a hex dump from a binary file and vice versa.
- `bc`: An arbitrary precision calculator language.

## Installation

You can install the required utilities on Debian/Ubuntu-based systems using the following command:

```bash
sudo apt-get install argon2 xxd bc
```
If you're using a different Linux distribution, please consult your package manager's documentation.

## Usage

1. Clone the repository to your local machine:

```bash
git clone https://github.com/Klez2003/pow.git
cd pow/
```

2. Make the script executable:

```bash
chmod +x solver.sh
```

3. Run the script with a challenge code:

```bash
./solver.sh "262144:1:SALTe7e590c2f902:1500"
```

1. Make sure you have Python installed (Python 3 is recommended).


2. Run the generator script to create a random Proof of Work challenge code:

```bash
python3 pow_generator.py
```


## Examples

Run the Bash script with a specific challenge code:

```bash
./proof_of_work.sh "262144:1:SALTe7e590c2f902:1500"
```
Output Example:

Estimated iterations: 1500
Time Cost: 1
Elapsed Time: 700 seconds.
SOLUTION FOUND
Your unblock code is: UNBLOCK-X7J2L9D5
This is the code you enter into the site to pass the challenge.

- **Python Salt Generator Example**:

Run the Python salt generator to create a random challenge code:

```bash
python3 pow_generator.py
```
Output Example:

Generated Proof of Work Code: 262144:1:SALTe7e590c2f902:1500

The generated code includes:

Memory Cost: Always Set To 262,144 bytes.

Time Cost: Always set to 1.

Salt: Randomized, prefixed with "SALT".

Difficulty: Always Set To 1500.

