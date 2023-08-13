#include <iostream>
#include <thread>
#include <mutex>
#include <experimental/filesystem>
#include <bits/stdc++.h>

using namespace std;

mutex mtx;

struct d_stats {
    int numFile;
    int numDir;
};

void processDirectory(const string& path, d_stats& stats) {
    int localNumFiles = 0;
    int localNumDirs = 0;

    for (const auto& entry : experimental::filesystem::directory_iterator(path)) {
        if (entry.is_regular_file()) {
            localNumFiles++;
        } else if (entry.is_directory()) {
            localNumDirs++;
        }
    }

    lock_guard<mutex> lock(mtx);
    stats.numFile += localNumFiles;
    stats.numDir += localNumDirs;
}

void processDirectoriesInParallel(const vector<string>& paths, d_stats& stats) {
    vector<thread> threads;
    for (const auto& path : paths) {
        threads.emplace_back(processDirectory, path, ref(stats));
    }

    for (auto& thread : threads) {
        thread.join();
    }
}

int main() {
    vector<string> directoriesToScan = {"/path/to/dir1", "/path/to/dir2", /* ... */};
    d_stats totalStats;

    processDirectoriesInParallel(directoriesToScan, totalStats);

    cout << "Total Files: " << totalStats.numFile << endl;
    cout << "Total Directories: " << totalStats.numDir << endl;

    return 0;
}