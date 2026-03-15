#include "stdafx.h"
#include "rules/classArrays.h"

TEST(MyContainerTest, ConstructorWithInitializerList) {
    std::string output = captureCout([&]() {
        MyContainer<int> container({1, 2, 3, 4, 5});
        container.print();
    });
    EXPECT_THAT(output, testing::HasSubstr("MyContainer id:"));
    EXPECT_THAT(output, testing::HasSubstr("has: 1 2 3 4 5"));
}

TEST(MyContainerTest, CopyConstructor) {
    MyContainer<std::string> original({"Hello", "World"});
    std::string output = captureCout([&]() {
        MyContainer<std::string> copy = original;
        copy.print();
    });
    EXPECT_THAT(output, testing::HasSubstr("MyContainer id:"));
    EXPECT_THAT(output, testing::HasSubstr("has: Hello World"));
}

TEST(MyContainerTest, CopyAssignment) {
    MyContainer<int> source({10, 20, 30});
    MyContainer<int> target({1, 2});
    std::string output = captureCout([&]() {
        target = source;
        target.print();
    });
    EXPECT_THAT(output, testing::HasSubstr("MyContainer id:"));
    EXPECT_THAT(output, testing::HasSubstr("has: 10 20 30"));
}

TEST(MyContainerTest, MoveConstructor) {
    MyContainer<std::string> original({"Move", "Test"});
    std::string output = captureCout([&]() {
        MyContainer<std::string> moved = std::move(original);
        moved.print();
    });
    EXPECT_THAT(output, testing::HasSubstr("MyContainer id:"));
    EXPECT_THAT(output, testing::HasSubstr("has: Move Test"));
}

TEST(MyContainerTest, MoveAssignment) {
    MyContainer<int> source({100, 200});
    MyContainer<int> target({1});
    std::string output = captureCout([&]() {
        target = std::move(source);
        target.print();
    });
    EXPECT_THAT(output, testing::HasSubstr("MyContainer id:"));
    EXPECT_THAT(output, testing::HasSubstr("has: 100 200"));
}

TEST(MyContainerTest, PrintMethod) {
    std::string output = captureCout([&]() {
        MyContainer<int> container({1, 2, 3});
        container.print();
    });
    EXPECT_THAT(output, testing::HasSubstr("MyContainer id:"));
    EXPECT_THAT(output, testing::HasSubstr("has: 1 2 3"));
}

TEST(MyContainerTest, EmptyContainer) {
    std::string output = captureCout([&]() {
        MyContainer<int> container({});
        container.print();
    });
    EXPECT_THAT(output, testing::HasSubstr("MyContainer id:"));
    EXPECT_THAT(output, testing::HasSubstr("has:"));
}

// --- Missing Template Instantiations (Int Constructors) ---

TEST(MyContainerTest, CopyConstructorInt) {
    MyContainer<int> original({10, 20});
    std::string output = captureCout([&]() {
        MyContainer<int> copy(original);
        copy.print();
    });
    EXPECT_THAT(output, testing::HasSubstr("Copy for id:"));
    EXPECT_THAT(output, testing::HasSubstr("has: 10 20"));
}

TEST(MyContainerTest, MoveConstructorInt) {
    MyContainer<int> original({30, 40});
    std::string output = captureCout([&]() {
        MyContainer<int> moved(std::move(original));
        moved.print();
    });
    EXPECT_THAT(output, testing::HasSubstr("Move for id:"));
    EXPECT_THAT(output, testing::HasSubstr("has: 30 40"));
}

// --- Self-Assignment Branch Coverage (False Path) ---

TEST(MyContainerTest, SelfCopyAssignmentInt) {
    MyContainer<int> container({1, 2, 3});
    MyContainer<int>* ptr = &container;
    
    // Trigger self-assignment branch cleanly
    container = *ptr; 

    std::string output = captureCout([&]() {
        container.print();
    });
    EXPECT_THAT(output, testing::HasSubstr("has: 1 2 3"));
}

TEST(MyContainerTest, SelfMoveAssignmentInt) {
    MyContainer<int> container({4, 5, 6});
    MyContainer<int>* ptr = &container;
    
    // Trigger self-move branch cleanly
    container = std::move(*ptr);

    std::string output = captureCout([&]() {
        container.print();
    });
    EXPECT_THAT(output, testing::HasSubstr("has: 4 5 6"));
}

TEST(MyContainerTest, SelfCopyAssignmentString) {
    MyContainer<std::string> container({"Self", "Copy"});
    MyContainer<std::string>* ptr = &container;
    
    container = *ptr; 

    std::string output = captureCout([&]() {
        container.print();
    });
    EXPECT_THAT(output, testing::HasSubstr("has: Self Copy"));
}

TEST(MyContainerTest, SelfMoveAssignmentString) {
    MyContainer<std::string> container({"Self", "Move"});
    MyContainer<std::string>* ptr = &container;
    
    container = std::move(*ptr);

    std::string output = captureCout([&]() {
        container.print();
    });
    EXPECT_THAT(output, testing::HasSubstr("has: Self Move"));
}

// --- D0 (Deleting Destructor) Coverage ---

TEST(MyContainerTest, HeapAllocationInt) {
    auto* ptr = new MyContainer<int>({99, 88});
    
    std::string output = captureCout([&]() {
        ptr->print();
    });
    
    EXPECT_THAT(output, testing::HasSubstr("has: 99 88"));
    
    // Triggers the D0 deleting destructor variant
    delete ptr; 
}

TEST(MyContainerTest, HeapAllocationString) {
    auto* ptr = new MyContainer<std::string>({"Heap", "Alloc"});
    
    std::string output = captureCout([&]() {
        ptr->print();
    });
    
    EXPECT_THAT(output, testing::HasSubstr("has: Heap Alloc"));
    
    // Triggers the D0 deleting destructor variant
    delete ptr; 
}
