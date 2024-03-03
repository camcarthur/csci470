#include <fstream>
#include <iostream>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/file.h>
#include <string>
#include <vector>
#include <cstdio>

std::string generateOutcomeString(int flips, int outcome) {
    std::string result;
    for (int i = 0; i < flips; i++) {
        if (outcome & (1 << i)) result = "H" + result;
        else result = "T" + result;
    }
    return result;
}

void log_to_csv(const char* filename, const char* outcome, double probability) {
    int fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0666);
    if (fd == -1) {
        perror("open failed");
        exit(EXIT_FAILURE);
    }

    if (flock(fd, LOCK_EX) == -1) { // Lock the file
        perror("flock failed");
        close(fd);
        exit(EXIT_FAILURE);
    }

    dprintf(fd, "%s,%f\n", outcome, probability);

    if (flock(fd, LOCK_UN) == -1) { // Unlock the file
        perror("flock unlock failed");
    }

    close(fd);
}

void simulateAndLog(int flips, int currentFlip = 0, int outcome = 0) {
    if (currentFlip == 0) {
        std::cout << "Grandparent PID: " << getppid() << ", Parent PID: " << getpid() << std::endl;
    }

    if (currentFlip == flips) {
        std::string outcomeStr = generateOutcomeString(flips, outcome);
        double probability = 1.0 / (1 << flips); // 2^flips outcomes
        log_to_csv("prob.csv", outcomeStr.c_str(), probability);
        std::cout << "Outcome: " << outcomeStr << ", Probability: " << probability << ", PID: " 
                  << getpid() << ", Parent PID: " << getppid() << std::endl;
        return;
    }

    if (fork() == 0) {
        std::cout << "Child PID: " << getpid() << ", Parent PID: " << getppid() << std::endl;
        simulateAndLog(flips, currentFlip + 1, outcome); // Continue with T outcome
        exit(0);
    } else {
        wait(NULL); // Wait for the child process
        simulateAndLog(flips, currentFlip + 1, outcome | (1 << currentFlip)); // Flip to H
    }
}

int main() {
    std::ofstream file("prob.csv");
    file << "Outcome,Probability\n";
    file.close();

    for (int flips = 1; flips <= 10; flips++) {
        if (fork() == 0) {
            simulateAndLog(flips);
            exit(0);
        } else {
            wait(NULL);
        }
    }

    return 0;
}
