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

    Number(const Number& n) {
        if(n.value) {
            value = new int(*n.value);
        } else if(n.left) {
            left = new Number(*n.left);
            right = new Number(*n.right);
        }
    }

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
    }

    Number(){}

    int magnitude() const {
        if(value) {
            return *value;
        }

        return 3*left->magnitude() + 2*right->magnitude();
    }

    friend std::ostream& operator<<(std::ostream& o, const Number& n) {
        if(n.value) {
            o << *n.value;
        } else {
            o << "[" << *n.left << "," << *n.right << "]";
        }

        return o;
    }

    Number& operator=(const Number& n) {
        if(n.value) {
            value = new int(*n.value);
        } else if(n.left) {
            left = new Number(*n.left);
            right = new Number(*n.right);
        }
        return *this;
    }

    Number operator+(const Number& n) {
        if(!left) {
            return n;
        } else {
            Number result (*this, n);
            for(bool updated = true; updated;) {
                updated = explode(&result) || split(&result);

            }
            return result;
        }
    }

    auto operator<=>(const Number& rhs) const = default;

    ~Number(){
        delete left, right, value;
    }

private:
    Number* getLeaf (Number* n, bool right = false) {
        Number* first = right ? n->right : n->left;
        Number* second = right ? n->left : n->right;
        Number* _n = nullptr;

        if(n->value) {
            return n;
        } else {
            return getLeaf(first, right);
        }
    }

    Number* explode (Number* n, int depth = 0) {
        Number* _n = nullptr;
        if (depth == 4 && n->left && n->right) {
            if(n->value) {
                delete n->value;
                n-> value = nullptr;
            }
            n->value = new int(0);
            return n;
        }

        depth++;
        if(!n->value) {
            _n = explode(n->left, depth);
            if(_n && _n->right) {
                *getLeaf(n->right)->value += *_n->right->value;
                delete _n->right;
                _n->right = nullptr;
            }

            if(!_n) {
                _n = explode(n->right, depth);
                if(_n && _n->left) {
                    *getLeaf(n->left, true)->value += *_n->left->value;
                    delete _n->left;
                    _n->left = nullptr;
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
    std::ifstream f("18_input.txt");
   // std::ifstream f("temp.txt");
    std::vector<Number> numbers;
    Number sum;
    for(std::string s; f >> s;) {
        Number n(s);
        sum = sum + n;
        numbers.push_back(n);
    }

    std::cout << sum << std::endl;
    std::cout << sum.magnitude() << std::endl;

    int max_magnitude = 0;
    for(const auto& n1 : numbers) {
        for(const auto& n2: numbers) {
            if(n1 != n2) {
                max_magnitude =
                    std::max((Number(n1) + n2).magnitude(), max_magnitude);
            }
        }
    }

    std::cout << "Maximum magnitude: " << max_magnitude << std::endl;
}