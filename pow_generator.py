import random
import string

def generate_salt(length=16):
    # Generate a salt with alphanumeric characters (A-Z, a-z, 0-9)
    return 'SALT' + ''.join(random.choices(string.ascii_letters + string.digits, k=length))

def generate_proof_of_work():
    # Randomize memory cost, time cost, and difficulty
    memory_cost = random.randint(1, 262144)  # Up to 262144
    time_cost = 1  # Always set to 1
    salt = generate_salt()
    difficulty = random.randint(1000, 1500)  # Between 1000 and 1500

    # Format the challenge code
    proof_of_work_code = f"{memory_cost}:{time_cost}:{salt}:{difficulty}"
    print(f"Generated Proof of Work Code: {proof_of_work_code}")

if __name__ == "__main__":
    generate_proof_of_work()
