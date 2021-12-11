#include <fstream>
#include <iostream>
#include <vector>

using T_octopuses = std::vector<std::vector<std::pair<int, bool>>>;
int flashes = 0;

void flash (T_octopuses& octopuses, int i, int j) {
    if(i < 0 || i >= octopuses.size()
    || j < 0 || j >= octopuses[0].size()) return;

    auto& octopus = octopuses[i][j];
    if(!octopus.second && octopus.first > 8) {
        octopus.first = 0;
        octopus.second = true;
        flashes++;

        for(int _i = i-1; _i <= i+1; ++_i) {
            for(int _j = j-1; _j <= j+1; ++_j) {
                flash(octopuses, _i, _j);
            }
        }
    } else if(!octopus.second){
        octopus.first++;
    }
}

void reset_flash (T_octopuses& octopuses) {
    for(auto& i : octopuses) {
        for(auto& j : i) {
            j.second = false;
        }
    }
}

int main() {
    std::ifstream f("11_input.txt");
  //  std::ifstream f("temp.txt");
    T_octopuses octopuses;
    int steps = 100;
    int all_flash_step = 0;

    for (std::string line; std::getline(f, line, '\n');) {
        std::vector<std::pair<int, bool>> numbers_line;
        for(const auto& n : line) {
            numbers_line.push_back({n - '0', false});
        }
        octopuses.push_back(std::move(numbers_line));
    }

// Part 1
/*
    for(int s = 0; s < steps; ++s) {
        int prev_count = flashes
        for(int i = 0; i < octopuses.size(); ++i) {
            for(int j = 0; j < octopuses[i].size(); ++j) {
                flash(octopuses, i, j);
            }
        }
        reset_flash(octopuses);
    }
*/

// Part 2

    int prev_count = flashes;
    do {
        prev_count = flashes;
        for(int i = 0; i < octopuses.size(); ++i) {
            for(int j = 0; j < octopuses[i].size(); ++j) {
                flash(octopuses, i, j);
            }
        }
        reset_flash(octopuses);
        all_flash_step++;
    } while (flashes - prev_count !=
        octopuses.size()*octopuses[0].size());

// Part 1
 //   std::cout << "Number of total flashes: " << flashes << std::endl;

 // Part 2
    std::cout << "Step when all flashed: " << all_flash_step << std::endl;
}
