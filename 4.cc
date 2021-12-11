#include <fstream>
#include <iostream>
#include <vector>
#include <boost/algorithm/string.hpp>

struct Board {
    std::pair<std::string, bool> numbers[5][5];

    bool find_and_mark (std::string n) {
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 5; ++j) {
                if(numbers[i][j].first == n) {
                    numbers[i][j].second = true;
                    if (check_row_column(i, j)) {
                        bingo = true;
                        return bingo;
                    }
                }
            }
        }
        return false;
    }

    bool check_row_column(int i, int j) {
        bool row_completed = true;
        for (int j = 0; j < 5; ++j) {
            if(numbers[i][j].second == false) {
                row_completed = false;
            }
        }

        bool column_completed = true;
        for (int i = 0; i < 5; ++i) {
            if(numbers[i][j].second == false) {
                column_completed = false;
            }
        }
        return (row_completed || column_completed);
    }

    int sum_unmarked() {
        int sum = 0;
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 5; ++j) {
                if(numbers[i][j].second == false) {
                    sum += std::stoi(numbers[i][j].first, nullptr, 10);
                }
            }
        }
        return sum;
    }

    friend std::ostream& operator<<(std::ostream& o, const Board& b) {
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 5; ++j) {
                o << "(" << b.numbers[i][j].first
                    << ", " << b.numbers[i][j].second << ") ";
            }
            o << std::endl;
        }
        return o;
    }

    friend std::istream& operator>>(std::istream& o, Board& b) {
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 5; ++j) {
                std::string s;
                o >> s;
                b.numbers[i][j] = std::pair(s, false);
            }
        }
        return o;
    }

    bool isBingo() {
        return bingo;
    }

private:
    bool bingo = false;
};

int f1(const std::vector<std::string>& numbers,
       std::vector<Board>& boards) {
    for(const auto& n : numbers) {
        for(auto& b : boards) {
            if (b.find_and_mark(n)) {
                std::cout << "Winner: " << n << std::endl;
                return (b.sum_unmarked() *
                    std::stoi(n, nullptr, 10));
            }
        }
    }
    return 0;
}

int f2(const std::vector<std::string>& numbers,
       std::vector<Board>& boards) {
    Board* last_winner;
    std::string last_number;
    for(const auto& n : numbers) {
        for(auto& b : boards) {
            if (!b.isBingo() && b.find_and_mark(n)) {
                std::cout << "Winner: " << n << std::endl;
                last_winner = &b;
                last_number = n;
            }
        }
    }
    if(last_winner) {
        return (last_winner->sum_unmarked() *
        std::stoi(last_number, nullptr, 10));
    }
    return 0;
}


int main() {
    std::ifstream f("4_input.txt");
   // std::ifstream f("temp.txt");

// first part

    std::string s;
    f >> s;

    std::vector<std::string> numbers;
    boost::split(numbers, s, [](char c){return c == ',';});
    std::vector<Board> boards;

    int i = 0, j = 0, count = -1;
    do {
        if(i == 0 && j == 0){
            ++count;
            boards.push_back({});
        }
    } while (f >> boards[count]);

    std::cout << f1(numbers, boards) << std::endl;
    std::cout << f2(numbers, boards) << std::endl;
    // for (const auto& b : boards) std::cout << b << "\n";

// second part
}
