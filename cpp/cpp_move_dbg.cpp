#include <iostream>
#include <string>
#include <vector>
#include <optional>

std::vector<int> CreateVec() {
    std::vector<int> v { 0, 1, 2, 3, 4 };
    std::cout << std::hex << v.data() << '\n';
    //return {std::move(v)}; // this one will cause a copy
    return (v); // this one moves
    //return v; // this one moves as well
}

std::optional<std::vector<int>> CreateOptVec() {
    std::vector<int> v { 0, 1, 2, 3, 4 };
    std::cout << static_cast<void *>(v.data()) << '\n';
    return {v}; // this one will cause a copy
    //return v; // this one moves
}

int main() {
    std::cout << "CreateVec:\n";
    auto vec = CreateVec();
    std::cout << static_cast<void *>(vec.data()) << '\n';
    
    std::cout << "CreateOptVec:\n";
    auto optVec = CreateOptVec();
    std::cout << static_cast<void *>(optVec->data()) << '\n';
}