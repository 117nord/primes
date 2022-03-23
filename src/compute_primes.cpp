#include <iostream>
#include <bitset>
#include <limits>
#include <cmath>
#include <ctime>

// Take first prime 2, and mark all multiples of it through successive additions.
// Next unmarked number in set is also prime; it has no factors smaller than itself. If it had one, it would be marked as a multiple. 
// So mark all multiples of it through additions.
// Repeat...
// Invert bits to end up with primes being marked.
//
// A few optimisations...
// When you start to mark multiples of a new prime p, adding it to itself you end up with 2*p. That number is a multiple of 2. If you already marked the multiples
// of 2, then 2*p is already marked. Same for 3*p and so on for all n*p where n < p. So you can start by marking p*p as the first unmarked multiple of p and 
// continuing from there by successive additions of p. For p >= 3, p*p + kp where k is odd is an even number. 
// For p >= 3, we can start marking at p*p then adding 2p per iteration.
//
// It also means that once you reach the square root of the range of numbers you are interested in, its smallest unmarked multiple is sqrt(size)^2 == size and any
// further multiple is out of bounds. At that point, all the non-primes left in the range have already been marked because they must be multiple of some number 
// smaller than the square root of the size of the number range. 
//
// To advance to the next unmarked prime, since primes > 2 can't be even, we can search for it by adding 2 so that we only look at odd numbers. No sense looking
// up an even one to see if it is marked.

static std::clock_t steptime = std::clock();
constexpr size_t size = 1L + std::numeric_limits<unsigned int>::max();
static std::bitset<size> candidates;

int main() {
    std::cout << "initialization time:    " << std::clock() - steptime << " ticks" << std::endl ;
    steptime = std::clock();

    // We are initially marking non-primes
    candidates[0] = true;
    candidates[1] = true; 

    std::size_t candidate {2}; // first prime
    std::size_t max_candidate = static_cast<std::size_t>(std::floor(std::sqrt(size)));

    std::cout << (std::clock() - steptime) / CLOCKS_PER_SEC << ": " << candidate << std::endl;
    for (std::size_t i = candidate * candidate; i < size; i += candidate) {
        candidates[i] = true;
    }

    candidate = 3;

    while(candidate <= max_candidate) {
        std::cout << (std::clock() - steptime) / CLOCKS_PER_SEC << ": " << candidate << std::endl;

        // mark multiples of our current prime
        for (std::size_t i = candidate * candidate; i < size; i += 2 * candidate) {
            candidates[i] = true;
        }

        // advance to next prime
        do {
            candidate += 2;
        } while(candidate < size && candidates[candidate]);
    }

    std::cout << (std::clock() - steptime) / CLOCKS_PER_SEC << ": done finding all primes smaller or equal to " << size - 1 << std::endl;
    steptime = std::clock();

    // all the primes are now false since non-primes have all been set to true so we flip all the bits to get primes.
    candidates.flip();
    std::cout << "flip() took " << std::clock() - steptime << " ticks" << std::endl;
    size_t count = candidates.count();
    double density = static_cast<double>(count) / size * 100;
    std::cout << "found " << count << " primes, density is " << density << "%" << std::endl;

    //std::cout << candidates;
}