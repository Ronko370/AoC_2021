#include <fstream>
#include <iostream>
#include <stack>
#include <map>
#include <set>

int main() {
    std::ifstream f("10_input.txt");
 //   std::ifstream f("temp.txt");
    std::stack<char> symbols;
    std::map<char, int> points_corrupted = {{')', 3}, {']', 57}, {'}', 1197}, {'>', 25137}};
    std::map<char, int> points_completion = {{')', 1}, {']', 2}, {'}', 3}, {'>', 4}};
    std::map<char, char> chunks = {{'(', ')'}, {'[', ']'}, {'{', '}'}, {'<', '>'}};
    std::set<unsigned long long> scores;
    int sum = 0;

    for (std::string line; std::getline(f, line, '\n');) {
        symbols = std::stack<char>();
        bool not_corrupted = true;
        unsigned long long score = 0;
        for(int i = 0; not_corrupted && i < line.length(); ++i) {
            char c = line[i];
            switch(c) {
                case '(':
                case '[':
                case '{':
                case '<':
                    symbols.push(c);
                    break;
                default:
                    char opening_tag = symbols.top();
                    symbols.pop();
                    if(chunks[opening_tag] != c) {
                        not_corrupted = false;
                        sum += points_corrupted[c];
                    }
            }
        }

        if(not_corrupted) {
            while(!symbols.empty()) {
                char opening_tag = symbols.top();
                symbols.pop();
                (score *= 5) += points_completion[chunks[opening_tag]];
            }

            scores.insert(score);
        }
    }

    std::cout << "Sum: " << sum << " | middle score: "
        << *([&scores](){
            auto it = scores.begin();
            for(int i = 0; i < scores.size()/2; ++i) ++it;
            return it;
        })()
        << std::endl;
}
