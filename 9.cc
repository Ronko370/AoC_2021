#include <fstream>
#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <map>

auto find_tag(auto& basins, int basin_tag) {
    return std::find_if(basins.begin(), basins.end(),
        [basin_tag](const auto& s){return s.first.contains(basin_tag);});
}

int main() {
    std::ifstream f("9_input.txt");
   // std::ifstream f("temp.txt");
    std::vector<std::vector<std::pair<int, int>>> numbers;
    std::map<std::set<int>, int> basins;
    int max_tag = -1, sum = 0, prod = 1, i = 0;

    for (std::string line; std::getline(f, line, '\n');) {
        int j = 0;
        std::vector<std::pair<int, int>> numbers_line;

// Second part
        for(const auto& n : line) {
            int basin_tag = -1;

            if(n != '9') {
                if(j > 0 && numbers_line[j-1].first != 9) {
                    basin_tag = numbers_line[j-1].second;
                    auto it = find_tag(basins, basin_tag);
                }

                if(i > 0 && numbers[i-1][j].first != 9) {
                    int other_tag = numbers[i-1][j].second;

                    if(basin_tag == -1) {
                        basin_tag = other_tag;
                    } else if (basin_tag != other_tag) {
                        auto it = find_tag(basins, other_tag);
                        auto it2 = find_tag(basins, basin_tag);

                        if(it != it2) {
                            std::set<int> orig_key{it->first};
                            orig_key.insert(it2->first.begin(), it2->first.end());
                            int sum = it->second + it2->second;

                            std::erase_if(basins, [basin_tag, other_tag]
                                (const auto& item) {
                                        auto const& [k, v] = item;
                                        return (k.contains(basin_tag)
                                            || k.contains(other_tag));
                                });

                            basins.insert({orig_key, sum});
                        }
                    }
                }

                if(basin_tag == -1) basin_tag = ++max_tag;
                auto it = find_tag(basins, basin_tag);
                if(it == basins.end()) {
                    basins.insert({{basin_tag}, 1});
                } else {
                    it->second++;
                }
            }

            numbers_line.push_back({n - '0', basin_tag});
            j++;
        }

        numbers.push_back(std::move(numbers_line));
        i++;
    }

// First part
    for(int i = 0, column_length = numbers.size(); i < column_length; i++) {
        for(int j = 0, row_length = numbers[i].size(); j < row_length; j++) {
            int n = numbers[i][j].first;
            if((j > 0 && n < numbers[i][j-1].first || j == 0)
                && (j < row_length-1 && n < numbers[i][j+1].first || j == row_length - 1)
                && (i > 0 && n < numbers[i-1][j].first || i == 0)
                && (i < column_length-1 && n < numbers[i+1][j].first || i == column_length - 1)) {
                    sum += 1 + n;
                }
        }
    }

    std::vector<int> prod_result;
    for(const auto& [k, v] : basins) {
        prod_result.push_back(v);
    }
    std::sort(prod_result.begin(), prod_result.end());
    for(int i = 1; i <= 3; ++i) prod *= prod_result[prod_result.size() - i];

    std::cout << "Sum of risk levels: " << sum << " | Product of basins: " << prod << std::endl;
}
