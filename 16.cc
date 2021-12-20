#include <fstream>
#include <iostream>
#include <vector>
#include <bitset>
#include <numeric>

enum class Type {sum, prod, min, max, literal, gt, lt, eq};

class Packet {

public:
    int length() const { return bin_length; }
    int sum() const { return version_sum; }
    long value() const { return val; }

protected:
    Packet(const std::string& s) {
        version = std::stoi(s.substr(0,3), nullptr, 2);
        t = static_cast<Type>(std::stoi(s.substr(3,3), nullptr, 2));
        version_sum = version;
    }

    uint version, version_sum;
    long val;
    Type t;
    int bin_length = 6;
};

Packet* createPacket(const std::string&);

class Literal : public Packet {
public:
    Literal(const std::string& s) : Packet(s) {
        std::string value;
        do {
            value += s.substr(bin_length + 1, 4);
            bin_length += 5;
        } while(s[bin_length - 5] != '0');

        val = std::stol(value, nullptr, 2);
    }
};

class Operation : public Packet {
public:
    Operation(const std::string& s) : Packet(s) {
        lt_id = std::stoi(s.substr(6,1), nullptr, 2);
        bin_length += 1;

        if(lt_id == 0) {
            bin_length += 15;
            count = std::stoi(s.substr(7,15), nullptr, 2);
            for(int i = 0; i < count;) {
                Packet *p =
                    createPacket({s.begin() + 22 + i, s.end()});
                subpackets.push_back(p);
                version_sum += p->sum();
                i += p->length();
            }

            bin_length += count;
        } else {
            bin_length += 11;
            count = std::stoi(s.substr(7,11), nullptr, 2);
            int n = 0;
            for(int i = 0; i < count; ++i) {
                Packet *p =
                    createPacket({s.begin() + 18 + n, s.end()});
                subpackets.push_back(p);
                version_sum += p->sum();
                n += p->length();
            }

            bin_length += n;
        }

        //std::transform_reduce: a bit uglier
        std::vector<long> values;
        std::transform(subpackets.cbegin(), subpackets.cend(),
            std::back_inserter(values), [](auto* p)
                {return p->value();});

        switch(t) {
            case Type::sum:
                val = std::reduce(values.cbegin(), values.cend(),
                    (long)0, std::plus());
                break;
            case Type::prod:
                val = std::reduce(values.cbegin(), values.cend(),
                    (long)1, std::multiplies());
                break;
            case Type::min:
                val =
                    *std::min_element(values.cbegin(), values.cend());
                break;
            case Type::max:
                val =
                    *std::max_element(values.cbegin(), values.cend());
                break;
            case Type::gt:
                val = (values[0] > values[1]);
                break;
            case Type::lt:
                val = (values[0] < values[1]);
                break;
            case Type::eq:
                val = (values[0] == values[1]);
                break;
        }

        std::cout << "Operation: " << (int)t << std::endl;
        for(const auto& v : values) std::cout << v << " ";
        std::cout << "result: " << val << std::endl;
        std::cout << "-------------" << std::endl;
    }
private:
    int lt_id, count;
    std::vector<Packet*> subpackets;
};

Packet* createPacket(const std::string& s) {
    Packet *p;
    if(4 == std::stoi(s.substr(3,3), nullptr, 2)) {
        p = new Literal(s);
    } else {
        p = new Operation(s);
    }
    return p;
}

int main() {
    std::ifstream f("16_input.txt");
   // std::ifstream f("temp.txt");
    std::string s;
    f >> s;
    std::string binary;
    for(const auto& c : s) {
        binary +=
            std::bitset<4>(std::stoi(std::string{c}, nullptr, 16))
                .to_string();
    }

    Packet* p = createPacket(binary);
    std::cout << "Version sum: " << p->sum()
        << " | result: " << p->value() << std::endl;
}