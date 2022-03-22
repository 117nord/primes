#include "primes.hpp"
#include "prime_cache.hpp"

Prime_cache cache;

bool is_prime(int n) {
    return cache.isprime(n);
}
