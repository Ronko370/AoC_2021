#include <fstream>
#include <iostream>
#include <queue>
#include <deque>
#include <set>
#include <typeinfo>

class Point {
public:
    Point(uint w) : weight(w){};

    void addNeighbour(Point* p) {
        nb_points.insert(p);
        p->nb_points.insert(this);
    }
    const auto& neighbours() const { return nb_points; }
    const auto& distance() const { return d; }
    const auto& getWeight() const { return weight; }
    void setDistance(uint dist) { d = dist; }

private:
    uint d = UINT32_MAX;
    uint weight;
    std::set<Point*> nb_points;
};

int main() {
    std::ifstream f("15_input.txt");
    //std::ifstream f("temp.txt");
    std::deque<std::string> lines;
    std::deque<std::deque<Point*>> points;

    for(std::string s; f >> s;) lines.push_back(std::move(s));
    const int n = lines.size();

    for(int i = n; i < n*5; ++i) {
        int index = i - i/n*n;
        int add = (i/n);
        std::string new_line;
        new_line.resize(n);
        std::transform(lines[index].begin(),
            lines[index].end(),
            new_line.begin(),
            [add](char c) {
                int val = c - '0' + add;
                return (val - val/10*9 + '0');
            });
        lines.push_back(std::move(new_line));
    }

    for(int i = 0; i < lines.size(); ++i) {
        std::string& s = lines[i];
        std::deque<Point*> points_line;
        for(int j = 0, n = s.length(); j < n*5; ++j) {
            int index = j - j/n*n;
            int add = (j/n);
            int val = s[index] - '0' + add;
            Point* p = new Point(val - val/10*9);
            if(i > 0) {
                p->addNeighbour(points[i - 1][j]);
            }
            if (j > 0) {
                p->addNeighbour(points_line[j - 1]);
            }
            points_line.push_back(std::move(p));
        }
        points.push_back(std::move(points_line));
    }

    auto comp = [](auto x, auto y) {
        return x->distance() > y->distance();};
    std::priority_queue<Point*,
        std::deque<Point*>,
        decltype(comp)> num_queue;

    points[0][0]->setDistance(0);
    num_queue.push(points[0][0]);
    while(!num_queue.empty()) {
        Point* p = num_queue.top();
        num_queue.pop();

        for(auto* n : p->neighbours()) {
            int d = p->distance() + n->getWeight();
            if(d < n->distance()) {
                n->setDistance(d);
                num_queue.push(n);
            }
        }
    }

    std::cout << points[5*n-1][5*n-1]->distance() << std::endl;
}