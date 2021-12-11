#include <fstream>
#include <sstream>
#include <iostream>
#include <deque>
#include <map>
#include <array>

int main() {
    std::ifstream f("6_input.txt");
   // std::ifstream f("temp.txt");
    int days = 256;

    std::array <unsigned long long, 9> occurrences = {0};
    for (std::string n; std::getline(f, n, ',');) {
        occurrences[std::stoi(n, nullptr, 10)]++;
    }

    for(int i = 0; i++ < days;) {
        std::rotate(occurrences.begin(), occurrences.begin()+1, occurrences.begin()+7);
        unsigned long long old_init = occurrences[8];
        occurrences[8] = occurrences[6];
        occurrences[6] += occurrences[7];
        occurrences[7] = old_init;
    }

    unsigned long long sum = 0;
    for(const auto& e : occurrences) {
        sum += e;
        std::cout << e << " | ";
    }
    std::cout << std::endl;
    std::cout << sum << std::endl;
}
