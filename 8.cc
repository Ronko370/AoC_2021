#include <fstream>
#include <iostream>
#include <vector>
#include <array>
#include <boost/algorithm/string.hpp>

bool subset(const std::string& s1, const std::string& s2) {
    for(const auto& c : s1) {
        if(s2.find(c) == std::string::npos) return false;
    }

    return true;
}

int main() {
    std::ifstream f("8_input.txt");
   // std::ifstream f("temp.txt");

    int sum = 0;
    for (std::string s; std::getline(f, s, '\n');) {
        std::vector<std::string> line, digits, output;
        std::array<std::string, 10> result;

        boost::split(line, s, [](char c){return c == '|';});
        boost::split(digits, line[0], [](char c){return c == ' ';});
        digits.pop_back();

        s = line[1].substr(1, line[1].length() - 1);
        boost::split(output, s, [](char c){return c == ' ';});

        std::sort(digits.begin(), digits.end(),
            [](const std::string& s1, const std::string &s2) {
                return s1.size() > s2.size(); });

        for(auto& d : digits) {
            switch(d.length()) {
                case 2:
                    result[1] = d;
                    break;
                case 3:
                    result[7] = d;
                    break;
                case 4:
                    result[4] = d;
                    break;
                case 7:
                    result[8] = d;
                    break;
            }
        }

        for(auto& d : digits) {
            switch(d.length()) {
                case 6:
                    if(subset(result[4], d)) {
                        result[9] = d;
                    } else if(subset(result[1], d)) {
                        result[0] = d;
                    } else {
                        result[6] = d;
                    }
                    break;
                case 5: {
                    if(subset(result[1], d)) {
                            result[3] = d;
                    } else if(subset(d, result[9])){ // strings are in descending order
                        result[5] = d;
                    } else {
                        result[2] = d;
                    }

                }
            }
        }

        std::string numbers;
        for(auto& d : output) {
            std::sort(d.begin(), d.end());
            for(int i = 0; i < 10 /*&& result[i] != d*/; ++i) {
                std::sort(result[i].begin(), result[i].end());
                if(result[i] == d) numbers += std::to_string(i);
            }
        }
        sum += std::stoi(numbers, nullptr, 10);
    }

    std::cout << "Result: " << sum << std::endl;
}
