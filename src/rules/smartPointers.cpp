#include <cstdio> // Required for std::puts
#include <format>
#include <iostream>
#include <memory>

#include "rules/smartPointers.h"

using std::cout;

Simple::Simple(const char *name) : name(name) {
  cout << std::format("Simple {} def construct {}\n", name, id);
}

Simple::~Simple() { std::printf("Simple %s dest %d\n", name.c_str(), id); }

void pointersCreation()
{
  int val = 55;

  auto const *pi1 = &val;
  const auto *pi2 = &val;

  cout << "wpi1: " << *pi1 << " pi2: " << *pi2 << '\n';

  std::unique_ptr<Simple> uptr1(new Simple("unique")); // NOLINT(modernize-make-unique)
  auto uptr2 = std::unique_ptr<Simple>(new Simple()); // NOLINT(modernize-make-unique)
  auto uptr3 = std::make_unique<Simple>();

  std::unique_ptr<Simple[]> uptr_tab1(new Simple[2]{Simple("tab"), Simple("tab")}); // NOLINT(modernize-avoid-c-arrays)
  auto uptr_tab2 = std::unique_ptr<Simple[]>(new Simple[2]); // NOLINT(modernize-avoid-c-arrays)
  auto uptr_tab3 = std::make_unique<Simple[]>(2); // NOLINT(modernize-avoid-c-arrays)

  std::shared_ptr<Simple> sptr1(new Simple("shared")); // NOLINT(modernize-make-shared)
  auto sptr2 = std::shared_ptr<Simple>(new Simple("shared")); // NOLINT(modernize-make-shared)
  auto sptr3 = std::make_shared<Simple>("shared");
}

void demonstrateSmartPointers()
{
  cout << "*** printPointers ***\n";

  pointersCreation();
}