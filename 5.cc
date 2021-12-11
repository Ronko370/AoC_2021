#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <array>
#include <unordered_map>
#include <boost/algorithm/string.hpp>
#include <boost/functional/hash.hpp>

class Point {
public:
    Point() : x(0), y(0) {}
    Point(int x, int y) : x(x), y(y){};
    Point(const Point& p) : x(p.x), y(p.y){};

    std::tuple<int, int> getPoints() const {
        return {x, y};
    }

    bool operator== (const Point& p) const {
        return x == p.x && y == p.y;
    }
    friend std::istream& operator>> (std::istream& o, Point& p) {
        std::vector<std::string> numbers;
        std::string s;
        o >> s;

        boost::split(numbers, s, [](char c){return c == ',';});
        p.x = std::stoi(numbers[0], nullptr, 10);
        p.y = std::stoi(numbers[1], nullptr, 10);
        return o;
    }

private:
    int x, y;
};

struct PointHash {
    std::size_t operator() (const Point& p) const {
        auto [x ,y] = p.getPoints();
        std::size_t seed = 0;
        boost::hash_combine(seed, x);
        boost::hash_combine(seed, y);

        return seed;
    }
};

int main() {
    std::ifstream f("5_input.txt");
   // std::ifstream f("temp.txt");

    std::unordered_map<Point, int, PointHash> points;
    for (std::string line; std::getline(f, line); ) {
        Point p1, p2;
        std::stringstream ss(line);
        std::string s;
        ss >> p1;
        ss >> s; // ->
        ss >> p2;

        auto [x1, y1] = p1.getPoints();
        auto [x2, y2] = p2.getPoints();

        int op_x = x1 < x2 ? 1 : -1;
        int op_y = y1 < y2 ? 1 : -1;
        if (x1 == x2) op_x = 0;
        if (y1 == y2) op_y = 0;

        for(int i = 0, x = x1, y = y1; i <= std::max(std::abs(x2 - x1), std::abs(y2 - y1)); ++i) {
            Point p((x + i * op_x), (y + i * op_y));
            ++points[p];
        }
    }

    int count = 0;
    for(const auto& [k, v] : points) {
         if(v > 1) {
            count++;
         }
    }

    std::cout << count << " | " << points.size() << std::endl;
}