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
struct SumArithmeticSequence {
    static constexpr unsigned long value = (start + end) * (end - start + 1) / 2;
};

// Helper function to check if two types are the same
template<typename T, typename U>
constexpr bool is_same_v = std::is_same_v<T, U>;

// Template for a compile-time minimum function
template<typename T>
constexpr T min(T a, T b) {
    return (a < b) ? a : b;
}

// Nested template instantiation example
template<auto value>
struct StaticValue {};

template<typename T, typename U>
void nested_template_example() {
    if constexpr (is_same_v<T, int>) {
        std::cout << "Nested template: int\n";
    } else if constexpr (is_same_v<T, double>) {
        std::cout << "Nested template: double\n";
    } else {
        std::cout << "Nested template: unknown type\n";
    }
}

// Main function to demonstrate the usage of templates and lambdas
int main() {
    // Test factorial at compile-time
    std::cout << Factorial<5>::value << "\n";

    // Test Fibonacci sequence at compile-time
    std::cout << Fibonacci<10>::value << "\n";

    // Test sum of an arithmetic sequence at compile-time
    std::cout << SumArithmeticSequence<1, 10>::value << "\n";

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

    // Lambda to demonstrate nested template instantiation and constexpr usage
    auto test_nested_template = [](auto x) {
        if constexpr (is_same_v<decltype(x), int>) {
            std::cout << "Nested template: int\n";
        } else if constexpr (is_same_v<decltype(x), double>) {
            std::cout << "Nested template: double\n";
        } else {
            std::cout << "Nested template: unknown type\n";
        }
    };

    // Test with different types
    test_nested_template(42);
    test_nested_template(3.14);

    return 0;
}