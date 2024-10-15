# Proof of Work Script

This bash script implements a Proof of Work (PoW) algorithm using the Argon2 hashing function. It is designed to solve a mining challenge based on given parameters, making it suitable for educational purposes or testing PoW implementations.

## Table of Contents

- [Features](#features)
- [Requirements](#requirements)
- [Usage](#usage)
- [Script Details](#script-details)
- [License](#license)

## Features

- Checks for required utilities (`argon2`, `xxd`, `bc`).
- Accepts a challenge code as input, either via command line or prompt.
- Iteratively generates and hashes candidate passwords until a valid solution is found.
- Displays the solution once it meets the required difficulty.

## Requirements

Ensure the following utilities are installed on your system:

- `argon2`: A secure hashing algorithm for password hashing.
- `xxd`: A tool for creating a hex dump from a binary file and vice versa.
- `bc`: An arbitrary precision calculator language.

You can install these utilities on Debian/Ubuntu-based systems with:

```bash
sudo apt-get install argon2 xxd bc
```
```bash
git clone https://github.com/TiredFromTelehack/proof-of-work.git
cd proof-of-work
```
```bash
chmod +x proof_of_work.sh
```
```bash
./proof_of_work.sh "262144:1:SALTe7e590c2f902:1500"
```
