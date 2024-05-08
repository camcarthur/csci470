// Using threads to log my name to a file without overwriting or interference
// based on code in chat.md

#include <iostream>
#include <fstream>
#include <thread>
#include <mutex>
#include <vector>

using namespace std;
mutex mtx;
ofstream logFile("log.txt");

void writeLog(int threadId) {
    lock_guard<mutex> lock(mtx); //
    logFile << "Thread " << threadId << " grabs the mutex" << endl;
    logFile << "Thread " << threadId << ": Colin McArthur" << endl;
    logFile << "Mutex dropped" << endl;
}

int main() {
    vector<thread> threads;
    int numThreads = 5;

    for (int i = 0; i < numThreads; ++i) {
        threads.push_back(thread(writeLog, i + 1));
    }

    for (auto& thread : threads) {
        thread.join();
    }

    return 0;
}
