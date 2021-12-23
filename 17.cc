#include <iostream>
#include <set>

/*
// Part 1:

static const int min_x = 20;
static const int max_x = 30;
static const int min_y = -10;
static const int max_y = -5;
*/

static const int min_x = 117;
static const int max_x = 164;
static const int min_y = -140;
static const int max_y = -89;

int main() {
    std::set<std::pair<int, int>> results;
    for(int i = 0; i <= max_x; i++) {
        for(int j = min_y; std::abs(j) <= (std::abs(min_y)*2 + 1); j++) {
            for(int pos_x = 0, pos_y = 0, x = i, y = j;
                pos_x <= max_x && pos_y >= min_y;) {
                if(min_x <= pos_x
                    && pos_x <= max_x
                    && min_y <= pos_y
                    && pos_y <= max_y) {
                        results.insert({i, j});
                }

                if(x != 0) {
                    pos_x += x;
                    x += x > 0 ? -1 : 1;
                }

                pos_y += y;
                y -= 1;
            }
        }
    }

    for(const auto& [k, v] : results) {
        std::cout << k << ", " << v << std::endl;
    }

    std::cout << "Size: " << results.size() << std::endl;
}