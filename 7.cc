#include <fstream>
#include <iostream>
#include <map>

int main() {
    std::ifstream f("7_input.txt");
    //std::ifstream f("temp.txt");

    std::map<int, int> positions;
    int max_pos = 0;
    for (std::string n; std::getline(f, n, ',');) {
        int num = std::stoi(n, nullptr, 10);
        positions[num]++;
        if (num > max_pos) max_pos = num;
    }

    int min = INT32_MAX, lowest;
    for(int i = 0; i < max_pos; ++i) {
        int sum = 0, v_current = positions[i];
        for(const auto& [k_other, v_other] : positions) {
            int distance = std::abs(k_other - i);
            int n = distance % 2;
            sum += v_other * (distance * (distance / 2 + n) + (n ? 0 : distance / 2));
        }

        if(sum < min) {
            min = sum;
            lowest = i;
        }
    }

    std::cout << "Sum: " << min << " | Position: " << lowest <<  std::endl;
}
