#include <gtest/gtest.h>

#include "common/common.h"

// Helper function to capture both std::cout and std::puts (C-style stdout)
std::string captureCout(std::function<void()> func) {
    // Start capturing standard output at the OS level
    testing::internal::CaptureStdout();

    // Execute the user's function
    func();

    // Force flush both C++ and C streams to ensure all output is captured
    std::cout.flush();
    std::fflush(stdout);

    // Stop capturing and return the accumulated string
    return testing::internal::GetCapturedStdout();
}
