#include <iostream>
#include <unistd.h> // for getpid()

int main() {
    // Get the process ID
    pid_t pid = getpid();

    // Print the process ID
    std::cout << "The process ID is: " << pid << std::endl;

    return 0; // Exit the program
}
