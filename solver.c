#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <regex.h>
#include <time.h>
#include <math.h>

int check_command(const char *command) {
    return system(command) == 0;
}

void generate_random_string(char *output, int length) {
    const char charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    for (int n = 0; n < length; n++) {
        output[n] = charset[rand() % (sizeof(charset) - 1)];
    }
    output[length] = '\0';
}

long calculate_difficulty(const char *difficulty) {
    return (long) pow(256, (4 - log(atof(difficulty)) / log(256)));
}

char* argon2_hash(const char *password, const char *salt, const char *time_cost, const char *memory_cost) {
    // Placeholder for actual argon2 hashing
    // Use an external library or a system call to perform the hashing
    char *hash = malloc(9); // Simulated output (8 bytes + null terminator)
    strcpy(hash, "00000000"); // Simulated output
    return hash;
}

int main(int argc, char *argv[]) {
    const char *utils[] = {"argon2", "xxd", "bc"};
    for (int i = 0; i < 3; i++) {
        if (!check_command(utils[i])) {
            printf("%s is not installed. Please install it and try again.\n", utils[i]);
            return 1;
        }
    }

    char challenge[256];
    if (argc < 2) {
        printf("Enter Challenge Code: ");
        fgets(challenge, sizeof(challenge), stdin);
    } else {
        strncpy(challenge, argv[1], sizeof(challenge));
    }
    challenge[strcspn(challenge, "\n")] = 0; // Trim newline

    regex_t regex;
    regcomp(&regex, "^([0-9]+):([0-9]+):([A-Za-z0-9]+):([0-9]+)$", REG_EXTENDED);
    if (regexec(&regex, challenge, 0, NULL, 0)) {
        printf("Invalid challenge format. Expected format: memory_cost:time_cost:salt:difficulty\n");
        return 2;
    }
    regfree(&regex);

    char *memory_cost = strtok(challenge, ":");
    char *time_cost = strtok(NULL, ":");
    char *salt = strtok(NULL, ":");
    char *difficulty = strtok(NULL, ":");

    // Debugging output
    printf("Memory Cost: %s\n", memory_cost);
    printf("Time Cost: %s\n", time_cost);
    printf("Salt: %s\n", salt);
    printf("Difficulty: %s\n", difficulty);

    char pw_prefix[256];
    generate_random_string(pw_prefix, 8);
    sprintf(pw_prefix, "UNBLOCK-%s-", pw_prefix);

    long difficulty_raw = calculate_difficulty(difficulty);

    printf("Estimated iterations: %s\n", difficulty);
    printf("Time Cost: %s\n\n", time_cost);

    int n = 1;
    time_t start_time = time(NULL);

    // Function to display elapsed time
    while (1) {
        char pw[256];
        sprintf(pw, "%s%d", pw_prefix, n);
        char *hash = argon2_hash(pw, salt, time_cost, memory_cost);
        char hash_bytes[9] = {0}; // 8 bytes + null terminator
        strncpy(hash_bytes, hash, 8);

        if (strtol(hash_bytes, NULL, 16) < difficulty_raw) {
            printf("\nSOLUTION FOUND\n");
            printf("Your unblock code is: %s\n", pw);
            printf("This is the code you enter into the site to pass the challenge.\n\n");
            free(hash);
            return 0;
        } else {
            time_t current_time = time(NULL);
            printf("\rElapsed Time: %ld seconds.", current_time - start_time);
            fflush(stdout);
            n++;
        }
        free(hash);
    }

    return 0;
}
