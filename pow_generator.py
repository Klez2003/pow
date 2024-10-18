import os
import base64
import random

def generate_salt(length=16):
    """Generate a URL-safe base64-encoded random salt."""
    salt = os.urandom(length)  # Generate random bytes
    return "SALTE" + base64.urlsafe_b64encode(salt).decode('utf-8')[:12]  # Prefix "SALTE" and limit the length

def generate_pow_code():
    """Generate a proof of work challenge code with randomized parameters."""
    # Randomize memory cost (between 1 and 262144 bytes)
    memory_cost = random.randint(1, 262144)  # in bytes
    # Set time cost to 1
    time_cost = 1
    # Generate a random salt
    salt = generate_salt()  # Generate the salt
    # Randomize difficulty (between 1000 and 1500)
    difficulty = random.randint(1000, 1500)  # Random difficulty
    
    # Format the proof of work code
    pow_code = f"{memory_cost}:{time_cost}:{salt}:{difficulty}"
    return pow_code

if __name__ == "__main__":
    pow_code = generate_pow_code()
    print("Generated Proof of Work Code:", pow_code)
