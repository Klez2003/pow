import subprocess
import sys
import time
import re
import os
import random
import math

# Check if required utilities are installed
required_utils = ['argon2', 'xxd', 'bc']

for utils in required_utils:
    if subprocess.call(f"command -v {utils}", shell=True) != 0:
            print(f"{utils} is not installed. Please install it and try again.")
                    sys.exit(1)

                    # Read the challenge code from argument or prompt user
                    if len(sys.argv) < 2:
                        challenge = input("Enter Challenge Code: ")
                        else:
                            challenge = sys.argv[1].strip()

                            # Validate the challenge format
                            if not re.match(r'^([0-9]+):([0-9]+):([A-Za-z0-9]+):([0-9]+)$', challenge):
                                print("Invalid challenge format. Expected format: memory_cost:time_cost:salt:difficulty")
                                    sys.exit(2)

                                    # Parse challenge code
                                    memory_cost, time_cost, salt, difficulty = challenge.split(':')
                                    memory_cost = memory_cost.strip()
                                    time_cost = time_cost.strip()
                                    salt = salt.strip()
                                    difficulty = difficulty.strip()

                                    # Debugging output
                                    print(f"Memory Cost: {memory_cost}")
                                    print(f"Time Cost: {time_cost}")
                                    print(f"Salt: {salt}")
                                    print(f"Difficulty: {difficulty}")

                                    # Generate prefix for the password
                                    pw_prefix = f"UNBLOCK-{''.join(random.choices('ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789', k=8))}-"
                                    difficulty_raw = int(math.exp(math.log(256) * (4 - math.log(int(difficulty), 256))))  # Calculate difficulty threshold

                                    print(f"Estimated iterations: {difficulty}")
                                    print(f"Time Cost: {time_cost}\n")

                                    n = 1
                                    start_time = time.time()

                                    # Main loop to find the solution
                                    while True:
                                        pw = f"{pw_prefix}{n}"
                                            # Create hash using argon2
                                                hash_result = subprocess.check_output(
                                                        f"echo -n '{pw}' | argon2 {salt} -t {time_cost} -k {memory_cost} -p 1 -id -v 13 -r",
                                                                shell=True, text=True, stderr=subprocess.DEVNULL
                                                                    )
                                                                        hash_bytes = hash_result.split('$')[3][:8]  # Extract the first 8 characters of the hash

                                                                            if int(hash_bytes, 16) < difficulty_raw:
                                                                                    print(f"\nSOLUTION FOUND")
                                                                                            print(f"Your unblock code is: {pw}")
                                                                                                    print("This is the code you enter into the site to pass the challenge.\n")
                                                                                                            break
                                                                                                                else:
                                                                                                                        elapsed_time = int(time.time() - start_time)
                                                                                                                                print(f"\rElapsed Time: {elapsed_time} seconds.", end="")
                                                                                                                                        n += 1