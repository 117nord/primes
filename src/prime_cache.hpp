#include <bitset>

constexpr std::size_t CACHE_SIZE {256};

class Prime_cache {
    std::bitset<CACHE_SIZE> multiples;

    public:
    Prime_cache();
    bool isprime(int n);
};