import os
import base64
import random

def generate_salt(length=16):
    """Generate a URL-safe base64-encoded random salt."""
    salt = os.urandom(length)  # Generate random bytes
    return "SALTE" + base64.urlsafe_b64encode(salt).decode('utf-8')[:12]  # Prefix "SALTE" and limit the length

def generate_pow_code():
    """Generate a proof of work challenge code."""
    memory_cost = 262144  # Example memory cost (64 MB)
    time_cost = 1  # Example time cost
    salt = generate_salt()  # Generate the salt
    difficulty = random.randint(1000, 2000)  # Random difficulty between 1000 and 2000
    
    # Format the proof of work code
    pow_code = f"{memory_cost}:{time_cost}:{salt}:{difficulty}"
    return pow_code

if __name__ == "__main__":
    pow_code = generate_pow_code()
    print("Generated Proof of Work Code:", pow_code)
