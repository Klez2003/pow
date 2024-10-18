import random
import string

def generate_salt():
    # Generate the salt in the specified format
    first_letter = random.choice(string.ascii_lowercase)
    first_number = random.choice(string.digits)
    second_letter = random.choice(string.ascii_lowercase)
    three_numbers1 = ''.join(random.choices(string.digits, k=3))
    third_letter = random.choice(string.ascii_lowercase)
    second_number = random.choice(string.digits)
    fourth_letter = random.choice(string.ascii_lowercase)
    three_numbers2 = ''.join(random.choices(string.digits, k=3))

    # Combine to form the salt
    salt = f"SALT{first_letter}{first_number}{second_letter}{three_numbers1}{third_letter}{second_number}{fourth_letter}{three_numbers2}"
    return salt

def generate_proof_of_work():
    # Set fixed memory cost and difficulty
    memory_cost = 262144
    time_cost = 1  # Always set to 1
    salt = generate_salt()
    difficulty = 1500

    # Format the challenge code
    proof_of_work_code = f"{memory_cost}:{time_cost}:{salt}:{difficulty}"
    return proof_of_work_code

if __name__ == "__main__":
    result = generate_proof_of_work()
    print(f"Generated Proof of Work Code: {result}")
