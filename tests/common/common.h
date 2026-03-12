#pragma once

#include <string>
#include <functional>

// Helper function to capture both std::cout and std::puts (C-style stdout)
std::string captureCout(std::function<void()> func);