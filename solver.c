#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <time.h>

int check_utility(const char *utility) {
    return (system(utility) == 0);
    }

    unsigned long hex_to_int(const char *hex) {
        return strtoul(hex, NULL, 16);
        }

        void elapsed_time(time_t start_time) {
            time_t current_time = time(NULL);
                printf("\rElapsed Time: %ld seconds.", current_time - start_time);
                    fflush(stdout);
                    }

                    int main(int argc, char *argv[]) {
                        const char *required_utils[] = {"argon2", "xxd", "bc"};
                            for (int i = 0; i < 3; i++) {
                                    if (!check_utility(required_utils[i])) {
                                                printf("%s is not installed. Please install it and try again.\n", required_utils[i]);
                                                            return 1;
                                                                    }
                                                                        }

                                                                            char challenge[100];
                                                                                if (argc < 2) {
                                                                                        printf("Enter Challenge Code: ");
                                                                                                fgets(challenge, sizeof(challenge), stdin);
                                                                                                    } else {
                                                                                                            strcpy(challenge, argv[1]);
                                                                                                                }

                                                                                                                    // Trim newline character
                                                                                                                        challenge[strcspn(challenge, "\n")] = 0;

                                                                                                                            // Validate the challenge format
                                                                                                                                if (sscanf(challenge, "%*[^:]:%*[^:]:%*[^:]:%*[^:]") != 4) {
                                                                                                                                        printf("Invalid challenge format. Expected format: memory_cost:time_cost:salt:difficulty\n");
                                                                                                                                                return 2;
                                                                                                                                                    }

                                                                                                                                                        // Parse challenge code
                                                                                                                                                            int memory_cost, time_cost, difficulty;
                                                                                                                                                                char salt[100];
                                                                                                                                                                    sscanf(challenge, "%d:%d:%[^:]:%d", &memory_cost, &time_cost, salt, &difficulty);

                                                                                                                                                                        // Debugging output
                                                                                                                                                                            printf("Memory Cost: %d\n", memory_cost);
                                                                                                                                                                                printf("Time Cost: %d\n", time_cost);
                                                                                                                                                                                    printf("Salt: %s\n", salt);
                                                                                                                                                                                        printf("Difficulty: %d\n", difficulty);

                                                                                                                                                                                            // Generate prefix for the password
                                                                                                                                                                                                char pw_prefix[100];
                                                                                                                                                                                                    snprintf(pw_prefix, sizeof(pw_prefix), "UNBLOCK-%08x-", rand() % 0xFFFFFFFF);
                                                                                                                                                                                                        unsigned long difficulty_raw = (unsigned long)exp(log(256) * (4 - log(difficulty) / log(256)));

                                                                                                                                                                                                            printf("Estimated iterations: %d\n", difficulty);
                                                                                                                                                                                                                printf("Time Cost: %d\n\n", time_cost);

                                                                                                                                                                                                                    int n = 1;
                                                                                                                                                                                                                        time_t start_time = time(NULL);

                                                                                                                                                                                                                            // Main loop to find the solution
                                                                                                                                                                                                                                while (1) {
                                                                                                                                                                                                                                        char pw[100];
                                                                                                                                                                                                                                                snprintf(pw, sizeof(pw), "%s%d", pw_prefix, n);
                                                                                                                                                                                                                                                        char command[256];
                                                                                                                                                                                                                                                                snprintf(command, sizeof(command), "echo -n '%s' | argon2 %s -t %d -k %d -p 1 -id -v 13 -r", pw, salt, time_cost, memory_cost);
                                                                                                                                                                                                                                                                        
                                                                                                                                                                                                                                                                                // Execute command and get hash result
                                                                                                                                                                                                                                                                                        FILE *fp = popen(command, "r");
                                                                                                                                                                                                                                                                                                if (!fp) {
                                                                                                                                                                                                                                                                                                            printf("Failed to run command\n");
                                                                                                                                                                                                                                                                                                                        exit(1);
                                                                                                                                                                                                                                                                                                                                }

                                                                                                                                                                                                                                                                                                                                        char hash_result[256];
                                                                                                                                                                                                                                                                                                                                                fgets(hash_result, sizeof(hash_result), fp);
                                                                                                                                                                                                                                                                                                                                                        pclose(fp);

                                                                                                                                                                                                                                                                                                                                                                char hash_bytes[9];
                                                                                                                                                                                                                                                                                                                                                                        strncpy(hash_bytes, hash_result + 3, 8); // Extract the first 8 bytes from the hash result
                                                                                                                                                                                                                                                                                                                                                                                hash_bytes[8] = '\0'; // Null-terminate

                                                                                                                                                                                                                                                                                                                                                                                        if (hex_to_int(hash_bytes) < difficulty_raw) {
                                                                                                                                                                                                                                                                                                                                                                                                    printf("\nSOLUTION FOUND\n");
                                                                                                                                                                                                                                                                                                                                                                                                                printf("Your unblock code is: %s\n", pw);
                                                                                                                                                                                                                                                                                                                                                                                                                            printf("This is the code you enter into the site to pass the challenge.\n\n");
                                                                                                                                                                                                                                                                                                                                                                                                                                        break;
                                                                                                                                                                                                                                                                                                                                                                                                                                                } else {
                                                                                                                                                                                                                                                                                                                                                                                                                                                            elapsed_time(start_time);
                                                                                                                                                                                                                                                                                                                                                                                                                                                                        n++;
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                }
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    }

                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        return 0;
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        }