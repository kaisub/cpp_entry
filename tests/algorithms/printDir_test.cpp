#include "stdafx.h"

#include <chrono>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <string_view>

namespace fs = std::filesystem;

// printDir.cpp defines these symbols, but they are not currently exposed in a header.
std::wstring formatSize(std::uintmax_t bytes);
void printDirAt(const std::wstring_view& pathStr);

namespace {

std::wstring captureWcout(const std::function<void()>& fn) {
    std::wstringstream buffer;
    auto* original = std::wcout.rdbuf(buffer.rdbuf());
    fn();
    std::wcout.rdbuf(original);
    return buffer.str();
}

fs::path makeUniqueTempDir() {
    const auto unique_id = std::chrono::steady_clock::now().time_since_epoch().count();
    fs::path dir = fs::temp_directory_path() / ("cpp_entry_printdir_test_" + std::to_string(unique_id));
    fs::create_directories(dir);
    return dir;
}

class PrintDirTest : public ::testing::Test {
protected:
    fs::path temp_dir;

    void SetUp() override {
        temp_dir = makeUniqueTempDir();
    }

    void TearDown() override {
        std::error_code ec;
        fs::remove_all(temp_dir, ec);
    }
};

} // namespace

TEST(PrintDirFormatSizeTest, FormatsBytesKilobytesMegabytesAndGigabytes) {
    EXPECT_EQ(formatSize(0), L"0 B");
    EXPECT_EQ(formatSize(1023), L"1023 B");
    EXPECT_EQ(formatSize(1024), L"1.00 KB");
    EXPECT_EQ(formatSize(1024 * 1024), L"1.00 MB");
    EXPECT_EQ(formatSize(1024ULL * 1024ULL * 1024ULL), L"1.00 GB");
}

TEST_F(PrintDirTest, PrintsEmptyDirectoryMessage) {
    const std::wstring output = captureWcout([&]() {
        printDirAt(temp_dir.wstring());
    });

    EXPECT_NE(output.find(L"Contents of directory:"), std::wstring::npos);
    EXPECT_NE(output.find(L" -> The directory is completely empty!"), std::wstring::npos);
}

TEST_F(PrintDirTest, PrintsDirectoriesBeforeFilesWithFileSize) {
    const fs::path subdir = temp_dir / "alpha_dir";
    const fs::path file = temp_dir / "zeta.txt";

    fs::create_directory(subdir);
    {
        std::ofstream out(file, std::ios::binary);
        out << "hello";
    }

    const std::wstring output = captureWcout([&]() {
        printDirAt(temp_dir.wstring());
    });

    const auto dir_pos = output.find(L">   alpha_dir");
    const auto file_pos = output.find(L"[5 B] zeta.txt");

    ASSERT_NE(dir_pos, std::wstring::npos);
    ASSERT_NE(file_pos, std::wstring::npos);
    EXPECT_LT(dir_pos, file_pos);
}

TEST(PrintDirErrorHandlingTest, PrintsFilesystemErrorForMissingPath) {
    const std::wstring missing =
        (fs::temp_directory_path() / "cpp_entry_missing_dir_does_not_exist").wstring();

    testing::internal::CaptureStderr();
    printDirAt(missing);
    const std::string stderr_output = testing::internal::GetCapturedStderr();

    EXPECT_THAT(stderr_output, ::testing::HasSubstr("Filesystem error:"));
}
