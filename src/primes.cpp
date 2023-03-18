#include <stdexcept>
#include <limits>
#include <cmath>
#include <array>
#include "primes.hpp"

#include <iostream>
#include <ctime>

/**
 * Storage: It is trivial to check if even integers prime or not. To save space, we only store bits for odd integers to represent if they are prime or not.
 *          
 * */

static const int bits_per_word = std::numeric_limits<unsigned>::digits;
static const std::array<unsigned int, 15> composite_pattern {
    1706347369,
    2574070490,
    2791001270,
    1771492141,
    3664098507,
    3063508274,
    765877068,
    3412694739,
    853173684,
    1287035245,
    3542984283,
    3033229718,
    1832049253,
    1531754137,
    2530422182
};

Primes::Primes() : Primes(1024) {
}

Primes::Primes(std::size_t capacity) : Primes(capacity, capacity) {
}

Primes::Primes(std::size_t capacity, std::size_t size) : m_mem(word_count(capacity)), m_capacity(Primes::capacity(m_mem.capacity())) {
    std::cout << "constructor: capacity = " << capacity << " size = " << size << std::endl;
    init(size);
}


// Returns true if n is prime. Will grow the set of Primes if n > size().
bool Primes::is_prime(std::size_t n) {
    if (n == 2) {
        return true;
    }

    if ((n & 1) == 0) {
        return false;
    }

    if (n >= size()) {
        init(n + 1);
    }

    if (n < size()) {
        return lookup(n);
    }

    return test(n);
}

// Returns the smallest prime greater than n.
std::size_t Primes::next(std::size_t n) {

}

// Returns the largest prime less than n.
std::size_t Primes::prev(std::size_t n) {

}

// Capacity

// Returns the current count of pre-computed integers.
std::size_t Primes::size() const {
    return m_size;
}

// Returns the number of integer we can pre-compute if we use all currently allocated storage
std::size_t Primes::capacity() const {
    return m_capacity;
}

// Increases the capacity of the set of primes. Doesn't change size().
void Primes::reserve(std::size_t new_capacity) {

}

// Requests the removal of unused capacity
void Primes::shrink_to_fit() {

}

// private

std::size_t Primes::word_count(std::size_t capacity) {
    // ensure a reasonable minimum capacity
    capacity = std::max(capacity, std::size_t{1});

    const std::size_t nb_bits = capacity / 2;
    return (nb_bits + bits_per_word - 1) / bits_per_word;
}

// Bits are multiplied by 2 because we do not represent even numbers. We also add 3 because 0, 1 and 2 are also not 
std::size_t Primes::capacity(std::size_t word_count) {
    return word_count * bits_per_word * 2;
}

void Primes::init(std::size_t size) {
    std::clock_t steptime = std::clock();

    m_size = size;

    // the pattern marks all multiples of 3 and 5 as composites and all other numbers as prime.
    std::size_t i {0};
    for (auto& n : m_mem) {
        n = composite_pattern[i % composite_pattern.size()];
        i++;
    }
    std::cout << (std::clock() - steptime) / CLOCKS_PER_SEC << ": " << "pattern init done" << std::endl;

    // adjust the first few numbers
    unset(1);
    set(3);
    set(5);

    std::size_t max = static_cast<std::size_t>(std::floor(std::sqrt(size)));
    std::size_t prime {7};

    do {
        // remove multiples of our current prime
        for (std::size_t i = prime * prime; i < size; i += 2 * prime) {
            unset(i);
        }

        std::cout << (std::clock() - steptime) / CLOCKS_PER_SEC << ": " << prime << std::endl;

        // advance to next prime
        do {
            prime += 2;
        } while(prime < size && !is_prime(prime));
    } while (prime <= max);

    std::cout << (std::clock() - steptime) / CLOCKS_PER_SEC << ": done finding all primes smaller or equal to " << size - 1 << std::endl;
}

bool Primes::lookup(std::size_t n) const {
    // storage only stores odd numbers so we first divide by 2 to convert to storage space
    std::size_t pos {n >> 1};
    std::size_t wpos {pos / bits_per_word};
    unsigned int mask {1u << (pos % bits_per_word)};

    return m_mem[wpos] & mask;
};

bool Primes::test(std::size_t n) const {

};


void Primes::set(std::size_t n) {
    // storage only stores odd numbers so we first divide by 2 to convert to storage space
    std::size_t pos {n >> 1};
    std::size_t wpos {pos / bits_per_word};
    unsigned int mask {1u << (pos % bits_per_word)};

    m_mem[wpos] |= mask;
}

void Primes::unset(std::size_t n) {
    // storage only stores odd numbers so we first divide by 2 to convert to storage space
    std::size_t pos {n >> 1};
    std::size_t wpos {pos / bits_per_word};
    unsigned int mask {~(1u << (pos % bits_per_word))};

    m_mem[wpos] &= mask;
}