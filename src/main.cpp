#include <iostream>
#include "primes.hpp"

int main() {
    init();
    for(int i = 0; i < 64; i++) {
        if(is_prime(i)) {
            std::cout << i << std::endl;
        }
    }
}