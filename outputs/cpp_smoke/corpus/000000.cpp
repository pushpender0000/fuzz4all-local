#include <iostream>
#include <vector>
#include <algorithm>
#include <type_traits>

// Template for calculating factorial at compile time
template<unsigned n>
struct factorial {
    static constexpr unsigned value = n * factorial<n - 1>::value;
};

template<>
struct factorial<0> {
    static constexpr unsigned value = 1;
};

// Template for generating a sequence of Fibonacci numbers at compile time
template<unsigned N>
constexpr std::array<unsigned, N> generate_fibonacci() {
    std::array<unsigned, N> fibs{};
    fibs[0] = 0;
    if (N > 1) fibs[1] = 1;
    for (size_t i = 2; i < N; ++i) {
        fibs[i] = fibs[i - 1] + fibs[i - 2];
    }
    return fibs;
}

// Template for checking if a number is prime at compile time
template<unsigned n>
constexpr bool is_prime() {
    if (n <= 1) return false;
    for (unsigned i = 2; i * i <= n; ++i) {
        if (n % i == 0) return false;
    }
    return true;
}

// Template for printing a sequence of numbers
template<typename T, size_t N>
void print_sequence(const std::array<T, N>& seq) {
    for (const auto& item : seq) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
}

int main() {
    // Generate Fibonacci sequence at compile time and print it
    constexpr size_t fib_count = 10;
    auto fibs = generate_fibonacci<fib_count>();
    print_sequence(fibs);

    // Check if some numbers are prime at compile time and print the results
    std::array<unsigned, 5> primes = {2, 3, 4, 5, 7};
    for (const auto& p : primes) {
        constexpr bool is_prime = ::is_prime<p>();
        std::cout << "Is " << p << " prime? " << (is_prime ? "Yes" : "No") << std::endl;
    }

    // Calculate factorial at compile time and print it
    constexpr unsigned fact_value = factorial<5>::value;
    std::cout << "Factorial of 5: " << fact_value << std::endl;

    return 0;
}