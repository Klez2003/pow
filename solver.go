package main

import (
    "bufio"
    "fmt"
    "os"
    "os/exec"
    "regexp"
    "strconv"
    "strings"
    "time"
)

func checkCommand(cmd string) bool {
    _, err := exec.LookPath(cmd)
    return err == nil
}

func main() {
    utils := []string{"argon2", "xxd", "bc"}
    for _, util := range utils {
        if !checkCommand(util) {
            fmt.Printf("%s is not installed. Please install it and try again.\n", util)
            return
        }
    }

    var challenge string
    if len(os.Args) < 2 {
        reader := bufio.NewReader(os.Stdin)
        fmt.Print("Enter Challenge Code: ")
        challenge, _ = reader.ReadString('\n')
    } else {
        challenge = os.Args[1]
    }

    challenge = strings.TrimSpace(challenge)

    // Validate the challenge format
    re := regexp.MustCompile(`^([0-9]+):([0-9]+):([A-Za-z0-9]+):([0-9]+)$`)
    if !re.MatchString(challenge) {
        fmt.Println("Invalid challenge format. Expected format: memory_cost:time_cost:salt:difficulty")
        return
    }

    parts := strings.Split(challenge, ":")
    memoryCost := strings.TrimSpace(parts[0])
    timeCost := strings.TrimSpace(parts[1])
    salt := strings.TrimSpace(parts[2])
    difficulty := strings.TrimSpace(parts[3])

    // Debugging output
    fmt.Printf("Memory Cost: %s\n", memoryCost)
    fmt.Printf("Time Cost: %s\n", timeCost)
    fmt.Printf("Salt: %s\n", salt)
    fmt.Printf("Difficulty: %s\n", difficulty)

    pwPrefix := fmt.Sprintf("UNBLOCK-%s-", generateRandomString(8))
    difficultyRaw := int64(estimateIterations(difficulty))

    fmt.Printf("Estimated iterations: %s\n", difficulty)
    fmt.Printf("Time Cost: %s\n\n", timeCost)

    n := 1
    startTime := time.Now()

    for {
        pw := fmt.Sprintf("%s%d", pwPrefix, n)
        hash := argon2Hash(pw, salt, timeCost, memoryCost)
        hashBytes := hash[:8]

        hashValue, _ := strconv.ParseInt(hashBytes, 16, 64)
        if hashValue < difficultyRaw {
            fmt.Println("\nSOLUTION FOUND")
            fmt.Printf("Your unblock code is: %s\n", pw)
            fmt.Println("This is the code you enter into the site to pass the challenge.\n")
            return
        }

        elapsedTime := time.Since(startTime).Seconds()
        fmt.Printf("\rElapsed Time: %.0f seconds.", elapsedTime)
        n++
    }
}

// Placeholder functions for randomness and hashing
func generateRandomString(length int) string {
    // Implementation to generate a random string
    return "RANDOM" // Replace with actual implementation
}

func argon2Hash(password, salt, timeCost, memoryCost string) string {
    // Replace this with the actual command to generate the hash
    return "00000000" // Placeholder for the hash output
}

func estimateIterations(difficulty string) float64 {
    d, _ := strconv.ParseFloat(difficulty, 64)
    return 4 - (d / 256)
}
