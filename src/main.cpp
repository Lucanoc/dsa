#include "search/binarySearchTree.hpp"
#include <iostream>
#include <stdexcept>
int main()
{
    dsa::bst<int, double> b;

    b.insert(1, 100.04);
    b.insert(2, 30.22);
    b.insert(3, 40.44);
    b.insert(4, 98.33);

    std::cout << b.contain(1) << '\n';
    std::cout << b.contain(2) << '\n';
    std::cout << b.contain(3) << '\n';
    std::cout << b.contain(4) << '\n';

    std::cout << b[1] << '\n';
    std::cout << b[2] << '\n';
    std::cout << b[3] << '\n';
    std::cout << b[4] << '\n';

    b.remove(3);

    std::cout << b.contain(1) << '\n';
    std::cout << b.contain(2) << '\n';
    std::cout << b.contain(3) << '\n';
    std::cout << b.contain(4) << '\n';

    std::cout << b[1] << '\n';
    std::cout << b[2] << '\n';
    
    try {
        std::cout << b[3] << '\n';
    } catch (const std::logic_error & le) {
        std::cout << le.what() << '\n';
    }

    std::cout << b[4] << '\n';

    return 0;
}