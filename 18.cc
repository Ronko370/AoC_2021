#include <iostream>
#include <vector>
#include <stack>
#include <fstream>
#include <numeric>
//#include <execution>

class Number {
public:
    Number(const int& n) : value(new int(n)){}

    Number(Number* const _left, Number* const _right) : left(_left), right(_right){}
    Number(const Number& _left, const Number& _right) :
        left(new Number(_left)), right(new Number(_right)){}

    Number(const std::string& s) {
        std::stack<Number*> numbers;
        for(const auto& c : s) { {}
            if (c == ']') {
                Number* right = numbers.top();
                numbers.pop();
                Number* left = numbers.top();
                numbers.pop();
                numbers.push(new Number(left, right));
            } else if(c != ',' and c != '[') {
                numbers.push(new Number(c - '0'));
            }
        }

        left = numbers.top()->left;
        right = numbers.top()->right;
        value = numbers.top()->value;
        delete numbers.top();
    }

    Number(){}

    friend std::ostream& operator<<(std::ostream& o, const Number& n) {
        if(n.value) {
            o << *n.value;
        } else {
            o << "[" << *n.left << "," << *n.right << "]";
        }

        return o;
    }

    Number operator+(const Number& n) {
        if(!left) {
            return n;
        } else {
            Number result (*this, n);
            for(bool updated = true; updated;) {
                std::cout << result << std::endl;;
                updated = explode(&result) || split(&result);
                std::cout << "end of round" << std::endl;
            }
            return result;
        }
    }

//private:
    Number* getLeaf (Number* n, bool right = false) {
        Number* first = right ? n->right : n->left;
        Number* second = right ? n->left : n->right;
        Number* _n = nullptr;

        if(n->value) {
            return n;
        }
        if(first) {
            _n = getLeaf(first);
        }

        if(!_n && second) {
            _n = getLeaf(second);
        }

        return _n;
    }

    Number* explode (Number* n, int depth = 0) {
      //  std::cout << "a" << std::endl;
        Number* _n = nullptr;
        if (depth == 4 && n->left && n->right) {
            if(n->value) {
                delete n->value;
            }
            n->value = new int(0);
            return n;
        }

        depth++;
        if(!n->value) {
         //   std::cout << "b" << std::endl;
            _n = explode(n->left, depth);
            if(_n && _n->right) {
            //    std::cout << "c" << std::endl;
                *getLeaf(n->right)->value += *_n->right->value;
                delete _n->right;
                _n->right = nullptr;
            //    std::cout << "cc" << std::endl;
            }

            if(!_n) {
             //   std::cout << "d" << std::endl;
                _n = explode(n->right, depth);
                if(_n && _n->left) {
                 //   std::cout << "e" << std::endl;
                    *getLeaf(n->left, true)->value += *_n->left->value;
                 //   std::cout << "e_e" << std::endl;
                    delete _n->left;
                    _n->left = nullptr;
             //       std::cout << "ee" << std::endl;
                }
            }
        }

        return _n;
    }

    bool split(Number* n) {
        if(n->value && *n->value >= 10) {
            Number* _left = new Number(*n->value / 2);
            Number* _right = new Number(*n->value / 2 + *n->value % 2);
            n->left = _left;
            n->right = _right;
            delete n->value;
            n->value = nullptr;
            return true;
        } else if (n->value) {
            return false;
        }

        return split(n->left) || split(n->right);
    }

    Number* left = nullptr, *right = nullptr;
    int* value = nullptr;
};

int main() {
    //std::ifstream f("18_input.txt");
    std::ifstream f("temp.txt");
    Number sum;
    for(std::string s; f >> s;) {
        sum = sum + Number(s);
    }

    std::cout << sum << std::endl;

/*
    std::vector<Number> numbers;
    for(std::string s; f >> s;) {
        numbers.push_back(Number(s));
    }


    Number sum = std::accumulate(
        numbers.begin(), numbers.end(), Number());
    std::cout << sum << std::endl;
    std::cout << "------------------" << std::endl;
    for(auto& n : numbers) {
        std::cout << n << std::endl;
        std::cout << "--------" << std::endl;
    }
*/
}