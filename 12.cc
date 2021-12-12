#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <boost/algorithm/string.hpp>

std::vector<std::string> paths;
std::map<std::string, std::set<std::string>> neighbours;

void find_path(const std::string node, std::string path, bool small_visited) {
    if(node == "start") return;

    if(node == "end") {
        path += "end";
        paths.push_back(path);
        return;
    }

    if (std::find_if(node.begin(), node.end(), [](const char& c) {
        return std::isupper(c);
    }) == node.end()) {
        if(path.find("," + node + ",") != std::string::npos) {
            if(small_visited) return;
            small_visited = true;
        }
    }

    path += node + ",";
    //std::cout << "current path: " << path << std::endl;

    for(const auto& v : neighbours[node]) {
        find_path(v, path, small_visited);
    }
}

int main() {
    std::ifstream f("12_input.txt");
   // std::ifstream f("temp.txt");

    for (std::string line; std::getline(f, line, '\n');) {
        std::vector<std::string> line_elements;
        boost::split(line_elements, line, [](char c){return c == '-';});

        neighbours[line_elements[0]].insert(line_elements[1]);
        neighbours[line_elements[1]].insert(line_elements[0]);
    }

    for(const auto& s : neighbours["start"]) {
        find_path(s, "start,", false);
    }

    std::cout << paths.size() << " paths found: " << std::endl;
   // for(const auto& p : paths) std::cout << p << std::endl;

}