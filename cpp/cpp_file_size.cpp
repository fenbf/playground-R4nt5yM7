#include <chrono>
#include <filesystem>  
#include <iostream>

namespace fs = std::filesystem;

int main(int argc, char* argv[])
{
    try
    {
        const auto fsize = fs::file_size("a.out");
        std::cout << fsize << '\n';
    }
    catch (const fs::filesystem_error& err)
    {
        std::cerr << "filesystem error! " << err.what() << '\n';
        if (!err.path1().empty())
            std::cerr << "path1: " << err.path1().string() << '\n';
        if (!err.path2().empty())
            std::cerr << "path2: " << err.path2().string() << '\n';
    }
    catch (const std::exception& ex)
    {
        std::cerr << "general exception: " << ex.what() << '\n';
    }
    
    // using error_code
    std::error_code ec{};
    auto size = std::filesystem::file_size("a.out", ec);
    if (ec == std::error_code{})
        std::cout << "size: " << size << '\n';
    else
        std::cout << "error when accessing test file, size is: " 
              << size << " message: " << ec.message() << '\n';
}