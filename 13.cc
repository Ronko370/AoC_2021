#include <fstream>
#include <iostream>
#include <vector>
#include <set>
#include <boost/algorithm/string.hpp>

int main() {
    std::ifstream f("13_input.txt");
   // std::ifstream f("temp.txt");
    std::set<std::pair<int,int>> points;
    std::vector<std::pair<char,int>> directions;

    for (std::string line; std::getline(f, line, '\n') && line != "";) {
        std::vector<std::string> coordinates;
        boost::split(coordinates, line, [](char c){return c == ',';});
        points.insert({
            std::stoi(coordinates[0], nullptr, 10),
            std::stoi(coordinates[1], nullptr, 10)});
    }

    for (std::string line; std::getline(f, line, '\n');) {
        std::vector<std::string> direction;
        boost::split(direction, line, [](char c){return c == '=';});
        directions.push_back({
            direction[0][direction[0].length()-1],
            std::stoi(direction[1], nullptr, 10)});
    }

// Fold
    for(const auto& d : directions) {
        for(auto it = points.begin(); it != points.end();) {
            const auto& p = *it;
            if(d.first == 'y' && p.second > d.second) {
                it = points.erase(it);
                points.insert({p.first, 2*d.second - p.second});
            }
            else if(d.first == 'x' && p.first > d.second) {
                it = points.erase(it);
                points.insert({2*d.second - p.first, p.second});
            } else {
                it++;
            }
        }

// Part 1
      //  break;
    }

// Print
    std::cout << "Points:" << std::endl;
    int i = 0, j = 0;
    for(const auto& p : points) {
        while(i < p.first) {
            std::cout << std::endl;
            i++;
            j = 0;
        }

        while(j < p.second) {
            std::cout << " ";
            j++;
        }
        std::cout << "#";
        j++;
    }
    std::cout << std::endl;

    std::cout << "Number of points: " << points.size() << std::endl;
}