#include <cstddef>
#include <vector>

class Primes {
    public:
    // Constructors
    Primes();
    Primes(std::size_t capacity);
    Primes(std::size_t capacity, std::size_t size);


    // Primes

    // Returns true if n is prime. Will grow the set of Primes if n > size().
    bool is_prime(std::size_t n);

    // Returns the first prime number.
    std::size_t first() const { return 2; };

    // Returns the smallest prime greater than n.
    std::size_t next(std::size_t n);

    // Returns the largest prime less than n.
    std::size_t prev(std::size_t n);

    // Capacity

    // Returns the current count of pre-computed integers.
    std::size_t size() const;

    // Returns the number of integer we can pre-compute if we use all currently allocated storage
    std::size_t capacity() const;

    // Increases the capacity of the set of primes. Doesn't change size().
    void reserve(std::size_t new_capacity);

    // Requests the removal of unused capacity.
    void shrink_to_fit();

    private:
    using Storage = std::vector<unsigned int>;

    Storage m_mem;
    std::size_t m_size;
    std::size_t m_capacity;

    void set(std::size_t n);
    void unset(std::size_t n);
    void init(std::size_t size);
    bool lookup(std::size_t n) const;
    bool test(std::size_t n) const;

    static std::size_t word_count(std::size_t capacity);
    static std::size_t capacity(std::size_t word_count);

};
