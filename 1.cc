#include <fstream>
#include <iostream>

int main() {
    std::ifstream f("1_input.txt");

// first part

/*
    int n1, n2, count = 0;
    f >> n1;
    while(f >> n2) {
        if(n1 < n2) ++count;
        n1 = n2;
    }
*/

// second part

    int n1, n2, n3, sum1, sum2, count = 0;
    f >> n1;
    f >> n2;
    f >> n3;
    sum1 = n1 + n2 + n3;
    do {
        int sum2 = n1 + n2 + n3;
        if(sum1 < sum2) ++count;
        sum1 = sum2;
        n1 = n2;
        n2 = n3;
    } while(f >> n3);

    std::cout << count << std::endl;
}
