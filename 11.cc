#include <fstream>
#include <iostream>
#include <vector>

int main() {
 //   std::ifstream f("11_input.txt");
    std::ifstream f("temp.txt");
    std::vector<std::vector<std::pair<int, bool>>> octopuses;
    int steps = 1;

    for (std::string line; std::getline(f, line, '\n');) {
        std::vector<std::pair<int, bool>> numbers_line;
        for(const auto& n : line) {
            numbers_line.push_back({n - '0', false});
        }
        octopuses.push_back(std::move(numbers_line));
    }
}
