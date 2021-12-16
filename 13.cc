#include <fstream>
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <boost/algorithm/string.hpp>
#include <cstdio>
#include <chrono>
#include <thread>


using T_points = std::set<std::pair<int,int>>;

void print(const T_points& points){
    printf("\e[2J");
    for(const auto& p : points) {
        int x = p.first+1 < 55 ? p.first+1 : 54;
        int y = p.second+1 < 178 ? p.second+1 : 177;
        printf("\e[%u;%uH#", x, y);
    }
    std::cout << std::endl;
    std::cout.flush();
}

int main() {
    std::ifstream f("13_input.txt");
   // std::ifstream f("temp.txt");
    T_points points;
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
        std::map<std::pair<int, int>, std::pair<int, int>>
            changes,
            no_changes;

        for(auto it = points.begin(); it != points.end();) {
            const auto p = *it;
            auto new_point = p;
            if(d.first == 'y' && p.second > d.second) {
                new_point = {p.first, 2*d.second - p.second};
            }
            else if(d.first == 'x' && p.first > d.second) {
                new_point = {2*d.second - p.first, p.second};
            }

            if(p == new_point) {
                no_changes.insert({p, p});
            } else {
                changes.insert({new_point, p});
            }

            it = points.erase(it);
            points.insert(new_point);
        }

// Animation for 1 fold
        bool updated;
        do {
            updated = false;
            T_points changes_print;
            for(const auto& [k, v] : changes)
                changes_print.insert(v);
            for(const auto& [k, v] : no_changes)
                changes_print.insert(v);

            print(changes_print);
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            for(const auto& [k, v] : changes){
                if(d.first == 'y' && v.second > k.second) {
                    changes[k] = {v.first, v.second-1};
                    updated = true;
                }

                if(d.first == 'x' && v.first > k.first) {
                    changes[k] = {v.first-1, v.second};
                    updated = true;
                }
            }
        } while(updated);

// Part 1
      //  break;
    }

    std::cout << "Number of points: " << points.size() << std::endl;
}