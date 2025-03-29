#include <iostream>
#include <filesystem>
#include <string>

int main()
{
        std::string tes = "name.dat";
        std::filesystem::path curr_dir = std::filesystem::current_path().parent_path();
        std::filesystem::path test_dir = curr_dir;
        test_dir /= "data/" + tes; 

        std::cout << test_dir << std::endl;
}