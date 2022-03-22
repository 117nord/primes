#include <bitset>
#include <cmath>
#include <limits>
#include "primes.hpp"


constexpr std::size_t SIZE {static_cast<std::size_t>(std::numeric_limits<int>::max()) + 1};
std::bitset<SIZE> multiples;

bool is_prime(int n) {
    return !multiples[n];
}

template<std::size_t N> 
void compute_primes(std::bitset<N>& multiples) {
    multiples[0] = multiples[1] = true; // not really multiples of primes but not primes anyway
    std::size_t candidate {2}; // first prime
    std::size_t max_candidate = static_cast<std::size_t>(std::floor(std::sqrt(N)));
    while(candidate <= max_candidate) {
        // mark multiples of our current prime
        for (std::size_t i = candidate * candidate; i < N; i += candidate) {
            multiples[i] = true;
        }

        // advance to next prime
        do {
            candidate++;
        } while(candidate < N && multiples[candidate]);
    }
}

void init() {
    compute_primes<SIZE>(multiples);
}
