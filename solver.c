#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include <regex.h>
#include <stdint.h>

#define BUFFER_SIZE 1024

int check_command(const char *command) {
    char buffer[BUFFER_SIZE];
    snprintf(buffer, sizeof(buffer), "command -v %s > /dev/null 2>&1", command);
    return system(buffer) == 0;
}

void generate_random_string(char *str, size_t length) {
    const char charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    for (size_t i = 0; i < length; i++) {
        str[i] = charset[rand() % (sizeof(charset) - 1)];
    }
    str[length] = '\0';
}

double calculate_difficulty_raw(double difficulty) {
    return round(exp(log(256) * (4 - log(difficulty) / log(256))));
}

int main(int argc, char *argv[]) {
    if (!check_command("argon2") || !check_command("xxd") || !check_command("bc")) {
        printf("Required utilities are not installed. Please install them and try again.\n");
        return 1;
    }

    char challenge[BUFFER_SIZE];
    if (argc < 2) {
        printf("Enter Challenge Code: ");
        fgets(challenge, sizeof(challenge), stdin);
    } else {
        strncpy(challenge, argv[1], sizeof(challenge) - 1);
    }
    challenge[strcspn(challenge, "\n")] = 0;

    regex_t regex;
    regcomp(&regex, "^([0-9]+):([0-9]+):([A-Za-z0-9]+):([0-9]+)$", REG_EXTENDED);
    regmatch_t matches[5];
    if (regexec(&regex, challenge, 5, matches, 0) != 0) {
        printf("Invalid challenge format. Expected format: memory_cost:time_cost:salt:difficulty\n");
        return 2;
    }

    char *memory_cost = strtok(challenge, ":");
    char *time_cost = strtok(NULL, ":");
    char *salt = strtok(NULL, ":");
    char *difficulty = strtok(NULL, ":");

    printf("Memory Cost: %s\n", memory_cost);
    printf("Time Cost: %s\n", time_cost);
    printf("Salt: %s\n", salt);
    printf("Difficulty: %s\n", difficulty);

    char pw_prefix[BUFFER_SIZE];
    snprintf(pw_prefix, sizeof(pw_prefix), "UNBLOCK-");
    generate_random_string(pw_prefix + strlen(pw_prefix), 8);
    strcat(pw_prefix, "-");

    double difficulty_raw = calculate_difficulty_raw(atof(difficulty));
    printf("Estimated iterations: %s\n", difficulty);
    printf("Time Cost: %s\n\n", time_cost);

    int n = 1;
    time_t start_time = time(NULL);

    while (1) {
        char pw[BUFFER_SIZE];
        snprintf(pw, sizeof(pw), "%s%d", pw_prefix, n);
        
        char command[BUFFER_SIZE];
        snprintf(command, sizeof(command), "echo -n \"%s\" | argon2 %s -t %s -k %s -p 1 -id -v 13 -r", pw, salt, time_cost, memory_cost);
        
        FILE *fp = popen(command, "r");
        if (fp == NULL) {
            printf("Failed to run command\n");
            exit(1);
        }
        
        char hash_bytes[9] = {0};
        fread(hash_bytes, 1, 8, fp);
        pclose(fp);

        uint32_t hash_value = (uint32_t)strtoul(hash_bytes, NULL, 16);
        if (hash_value < (uint32_t)difficulty_raw) {
            printf("\nSOLUTION FOUND\n");
            printf("Your unblock code is: %s\n", pw);
            printf("This is the code you enter into the site to pass the challenge.\n\n");
            return 0;
        }

        n++;
        printf("\rElapsed Time: %ld seconds.", (time(NULL) - start_time));
        fflush(stdout);
    }

    regfree(&regex);
    return 0;
}
