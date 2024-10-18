import hashlib
import random
import time

def generate_salt(length=16):
    """Generates a random salt."""
    return ''.join(random.choices('abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789', k=length))

def proof_of_work(difficulty, nonce_limit, salt):
    """Generates a proof of work."""
    for nonce in range(nonce_limit):
        # Combine salt and nonce to create a unique input
        input_str = f"{salt}:{nonce}"
        # Calculate the SHA-256 hash
        hash_result = hashlib.sha256(input_str.encode()).hexdigest()
        # Check if the hash meets the difficulty
        if hash_result.startswith('0' * difficulty):
            return nonce, hash_result
    return None, None

def generate_proof_of_work(difficulty=6, nonce_limit=10000):
    """Generates a proof of work string."""
    salt = generate_salt()
    nonce, hash_result = proof_of_work(difficulty, nonce_limit, salt)

    if nonce is not None:
        # Format the proof of work
        proof_of_work_string = f"{nonce}:{1}:{salt}:{nonce}"
        return proof_of_work_string
    else:
        return "No valid proof of work found"

# Example usage
if __name__ == "__main__":
    difficulty = 6  # Adjust the difficulty level (number of leading zeros)
    nonce_limit = 10000  # Set the maximum nonce to test
    pow_string = generate_proof_of_work(difficulty, nonce_limit)
    print(pow_string)
