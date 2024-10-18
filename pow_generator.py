import random
import string

def generate_salt():
    # Ensure the first character after "SALT" is a lowercase letter
    first_char = random.choice(string.ascii_lowercase)
    # Generate the remaining characters (11 more to make a total of 16)
    remaining_chars = ''.join(random.choices(string.ascii_letters + string.digits, k=11))
    return 'SALT' + first_char + remaining_chars

def generate_proof_of_work():
    # Set fixed memory cost and difficulty
    memory_cost = 262144
    time_cost = 1  # Always set to 1
    salt = generate_salt()
    difficulty = 1500

    # Format the challenge code
    proof_of_work_code = f"{memory_cost}:{time_cost}:{salt}:{difficulty}"
    print(f"Generated Proof of Work Code: {proof_of_work_code}")

if __name__ == "__main__":
    generate_proof_of_work()
