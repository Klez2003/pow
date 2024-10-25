#!/bin/bash

# Check if required utilities are installed
for utils in argon2 xxd bc; do
    if ! command -v $utils &> /dev/null; then
        echo "$utils is not installed. Please install it and try again."
        exit 1
    fi
done

# Read the challenge code from argument or prompt user
if [ $# -lt 1 ]; then
    read -p "Enter Challenge Code: " challenge
else
    challenge=$1
fi 

# Trim whitespace
challenge=$(echo "$challenge" | xargs)

# Validate the challenge format
if ! [[ $challenge =~ ^([0-9]+):([0-9]+):([A-Za-z0-9]+):([0-9]+)$ ]]; then
    echo "Invalid challenge format. Expected format: memory_cost:time_cost:salt:difficulty"
    exit 2
fi

# Parse challenge code
IFS=':' read -r memory_cost time_cost salt difficulty <<< "$challenge"

# Trim whitespace
memory_cost=$(echo "$memory_cost" | xargs)
time_cost=$(echo "$time_cost" | xargs)
salt=$(echo "$salt" | xargs)
difficulty=$(echo "$difficulty" | xargs)

# Debugging output
echo "Memory Cost: $memory_cost"
echo "Time Cost: $time_cost"
echo "Salt: $salt"
echo "Difficulty: $difficulty"

# Generate prefix for the password
pw_prefix="UNBLOCK-$(head /dev/urandom | tr -dc A-Z0-9 | head -c 8)-"
difficulty_raw=$(echo "scale=10; e(l(256) * (4 - l($difficulty) / l(256))) / 1" | bc -l | xargs printf %.0f)	

echo "Estimated iterations: $difficulty"
echo "Time Cost: $time_cost"
echo

n=1
start_time=$(date +%s)

# Function to display elapsed time
elapsed_time() {
    current_time=$(date +%s)
    elapsed_time=$((current_time - start_time))
    echo -ne "\rElapsed Time: $elapsed_time seconds."
}

# Main loop to find the solution
while true; do
    pw="$pw_prefix$n"
    hash=$(echo -n "$pw" | argon2 "$salt" -t "$time_cost" -k "$memory_cost" -p 1 -id -v 13 -r)
    hash_bytes=${hash:0:8}
 
    if [ $((16#$hash_bytes)) -lt "$difficulty_raw" ]; then
        echo
        echo "SOLUTION FOUND"
        echo "Your unblock code is: $pw"
        echo "This is the code you enter into the site to pass the challenge."
        echo
        exit 0
    else
        elapsed_time
        n=$((n + 1)) 
    fi
done
