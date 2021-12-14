#include <fstream>
#include <iostream>
#include <map>

using T_polymer = std::map<std::string, unsigned long long>;

int main() {
    std::ifstream f("14_input.txt");
   // std::ifstream f("temp.txt");
    std::map<std::string, char> rules;
    T_polymer polymer;
    std::map<char, unsigned long long> occurrences;
    const int steps = 40;
    std::string pol_templ;
    f >> pol_templ;

    for(int i = 0; i + 1 < pol_templ.length(); ++i) {
        occurrences[pol_templ[i]]++;
        polymer[{pol_templ[i], pol_templ[i+1]}]++;
    }
    // Consider last element:
    occurrences[pol_templ[pol_templ.length()-1]]++;

    for(std::string s; f >> s;) {
        std::string key = s;
        f >> s; // ->
        f >> s;
        rules[key] = s[0];
    }

    for(int i = 0; i < steps; ++i) {
        T_polymer _polymer;
        for(auto& [k, v] : polymer) {
            if(v > 0) {
                char c = rules[k];
                _polymer[{k[0], c}] += v;
                _polymer[{c, k[1]}] += v;
                occurrences[c] += v;
                v = 0;
            }
        }

        for(const auto& [k, v] : _polymer) {
            polymer[k] += v;
        }
    }

    unsigned long long min = UINT64_MAX, max = 0;
    for(const auto& [k, v]: occurrences) {
        if(v < min) min = v;
        if(v > max) max = v;
    }

    for(const auto& o : occurrences)
        std::cout << o.first << ": " << o.second << std::endl;
    std::cout << std::endl;

    for(const auto& p : polymer)
        std::cout << p.first << ": " << p.second << std::endl;

    std::cout << "max: " << max
        << ", min: "<< min
        << ", max-min = " << max - min
        << std::endl;
}