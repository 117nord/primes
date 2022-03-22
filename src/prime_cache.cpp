#include <cmath>
#include "prime_cache.hpp"

Prime_cache::Prime_cache() {
    multiples[0] = multiples[1] = true; // not really multiples of primes but not primes anyway

    std::size_t candidate {2}; // first prime
    std::size_t max_candidate = static_cast<std::size_t>(std::floor(std::sqrt(CACHE_SIZE)));
    while(candidate <= max_candidate) {
        // mark multiples of our current prime
        for (std::size_t i = candidate * candidate; i < CACHE_SIZE; i += candidate) {
            multiples[i] = true;
        }

        // advance to next prime
        do {
            candidate++;
        } while(candidate < CACHE_SIZE && multiples[candidate]);
    }
}

bool Prime_cache::isprime(int n) {
    if (n <= 0) {
        return false;
    }
    if (n <= CACHE_SIZE) {
        return !multiples[n];
    }
    // TODO: write proper fallback
    return false;
}