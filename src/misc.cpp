#include <cstdint>
#include <iostream>

int main(int argc, char *argv[]) {
    uint64_t a[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    auto b = a[1];
    std::cout << sizeof(b) << "  " << *b << "\n";
    return EXIT_SUCCESS;
}
