#include <fstream>
#include <iostream>

int main() {
    std::ifstream f("2_input.txt");

// first part
/*
    int depth = 0, horizon = 0;
    std::string s;
    while(f >> s) {
        int n;
        f >> n;
        if (s == "forward") {
            horizon += n;
        } else if (s == "down") {
            depth += n;
        } else {
            depth -= n;
        }
    }
*/

    int depth = 0, horizon = 0, aim = 0;
    std::string s;
    while(f >> s) {
        int n;
        f >> n;
        if (s == "forward") {
            horizon += n;
            depth += aim*n;
        } else if (s == "down") {
            aim += n;
        } else {
            aim -= n;
        }
    }

// second part

    std::cout << depth*horizon << std::endl;
}
