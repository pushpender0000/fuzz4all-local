#include <iostream>
#include <vector>
#include <type_traits>

// Helper function to check if a type is a container
template<typename T>
struct is_container : std::false_type {};

template<typename T, typename Alloc>
struct is_container<std::vector<T, Alloc>> : std::true_type {};

template<typename T>
constexpr bool is_container_v = is_container<T>::value;

// Template for a compile-time factorial function
template<unsigned int n>
struct Factorial {
    static constexpr unsigned long value = n * Factorial<n - 1>::value;
};

template<>
struct Factorial<0> {
    static constexpr unsigned long value = 1;
};

// Template for a compile-time Fibonacci sequence generator
template<unsigned int n>
struct Fibonacci {
    static constexpr unsigned long value = Fibonacci<n - 1>::value + Fibonacci<n - 2>::value;
};

template<>
struct Fibonacci<0> {
    static constexpr unsigned long value = 0;
};

template<>
struct Fibonacci<1> {
    static constexpr unsigned long value = 1;
};

// Template for a compile-time sum of an arithmetic sequence
template<unsigned int start, unsigned int end>
constexpr unsigned long sum_arithmetic_sequence() {
    return (start + end) * (end - start + 1) / 2;
}

// Main function to demonstrate the usage of templates and lambdas
int main() {
    // Test factorial at compile-time
    std::cout << Factorial<5>::value << "\n";

    // Test Fibonacci sequence at compile-time
    std::cout << Fibonacci<10>::value << "\n";

    // Test sum of an arithmetic sequence at compile-time
    std::cout << sum_arithmetic_sequence<1, 10>() << "\n";

    // Lambda to check if a type is a container and demonstrate SFINAE
    auto check_container = [](auto x) {
        if constexpr (is_container_v<decltype(x)>) {
            std::cout << "Type is a container.\n";
        } else {
            std::cout << "Type is not a container.\n";
        }
    };

    // Test with an integer (not a container)
    check_container(42);

    // Test with a vector (a container)
    std::vector<int> vec = {1, 2, 3};
    check_container(vec);

    return 0;
}