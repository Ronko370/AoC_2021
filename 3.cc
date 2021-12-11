#include <fstream>
#include <iostream>
#include <bitset>
#include <list>
#include <algorithm>

int main() {
    std::ifstream f("3_input.txt");
    constexpr int NUM_OF_BITS = 12;

// first part
    std::string s;
    f >> s;
    uint n = s.length(), count = 0, gamma = 0b0, epsilon = 0b0;
    int num_of_zeros [n] = {0};
    std::list<std::string> o2_candidates;
    std::list<std::string> co2_candidates;

    do {
        for(int i = 0; i < n; ++i) num_of_zeros[i] += (s[i]=='0');
        o2_candidates.push_back(s);
        ++count;
    } while(f >> s);

    int avg = count/2;
    for(int i = 0; i < n; ++i) {
        gamma <<= 1;
        epsilon <<= 1;
        int zero = (num_of_zeros[i] > avg ? 0 : 1);
        gamma += zero;
        epsilon += 1 - zero;
    }

    std::cout << std::bitset<NUM_OF_BITS>(gamma) << " " << std::bitset<NUM_OF_BITS>(epsilon) << std::endl;
    std::cout << gamma << " " << epsilon << " " << gamma * epsilon << std::endl;

// second part

    co2_candidates = o2_candidates;

    for(int i = 0; i < n; ++i) {
        auto count_zeros = [i](auto s){ return s[i] == '0';};
        int num_zeros = std::count_if(o2_candidates.begin(), o2_candidates.end(), count_zeros);
        char c = (num_zeros > o2_candidates.size() / 2 ? '0' : '1');

        if (o2_candidates.size() > 1) {
            o2_candidates.remove_if([c, i](auto elem){
                return elem[i] != c;
            });
        }

        num_zeros = std::count_if(co2_candidates.begin(), co2_candidates.end(), count_zeros);
        c = (num_zeros > co2_candidates.size() / 2 ? '1' : '0');
        if (co2_candidates.size() > 1) {
            co2_candidates.remove_if([c, i](auto elem){
                return elem[i] != c;
            });
        }
    }

    int o2 = std::stoi(o2_candidates.front(), nullptr, 2);
    int co2 = std::stoi(co2_candidates.front(), nullptr, 2);
    std::cout << o2 << " " << co2 << " " << o2 * co2 << std::endl;
}
