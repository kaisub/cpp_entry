#include "algorithms/printDir.h"

#include <iostream>
#include <filesystem>
#include <string>
#include <sstream>
#include <iomanip>
#include <vector>

namespace fs = std::filesystem;

std::wstring formatSize(std::uintmax_t bytes) {
    std::wstringstream wss;
    wss << std::fixed << std::setprecision(2);

    constexpr double size_kb = 1024.0;
    constexpr double size_mb = size_kb * 1024.0;
    constexpr double size_gb = size_mb * 1024.0;

    if (bytes >= static_cast<std::uintmax_t>(size_gb)) {
        wss << static_cast<double>(bytes) / size_gb << L" GB";
    } else if (bytes >= static_cast<std::uintmax_t>(size_mb)) {
        wss << static_cast<double>(bytes) / size_mb << L" MB";
    } else if (bytes >= static_cast<std::uintmax_t>(size_kb)) {
        wss << static_cast<double>(bytes) / size_kb << L" KB";
    } else {
        wss << std::setprecision(0) << bytes << L" B";
    }

    return wss.str();
}

void printDirAt(const std::wstring_view& pathStr = L".") {
    try {
        fs::path path = fs::absolute(pathStr).lexically_normal();
        std::wcout << L"Contents of directory: " << path.wstring() << L"\n";

        if (fs::is_empty(path)) {
            std::wcout << L" -> The directory is completely empty!\n";
            return;
        }

        // Single I/O pass to minimize disk reads
        std::vector<fs::directory_entry> directories;
        std::vector<fs::directory_entry> files;

        for (const auto& entry : fs::directory_iterator(path)) {
            if (entry.is_directory()) {
                directories.push_back(entry);
            } else {
                files.push_back(entry);
            }
        }

        // Output directories first
        for (const auto& dir : directories) {
            std::wcout << L">   " << dir.path().filename().wstring() << L"\n";
        }

        // Output files second
        for (const auto& file : files) {
            if (file.is_regular_file()) {
                std::wcout << L"    [" << formatSize(file.file_size()) << L"] ";
            } else {
                std::wcout << L"[?] ";
            }
            std::wcout << file.path().filename().wstring() << L"\n";
        }

    } catch (const fs::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << '\n';
    } catch (...) {
        std::cerr << "FATAL ERROR: unknown exception during directory traversal!\n";
    }
}

void demonstratePrintDir()
{
    std::cout << "*** printDir ***\n";
    printDirAt();
}
