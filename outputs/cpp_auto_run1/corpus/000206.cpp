#include <iostream>
#include <vector>
#include <type_traits>

template<typename T, typename U>
struct IsSame {
    static const bool value = std::is_same_v<T, U>;
};

template<typename T, size_t N>
constexpr auto sumVector(const std::vector<T>& vec) -> T {
    T result = 0;
    for (const auto& val : vec) {
        if constexpr(IsSame<decltype(val), int>::value) {
            result += val;
        } else {
            throw std::runtime_error("Error: Incorrect type used in calculation.");
        }
    }
    return result;
}

int main() {
    constexpr size_t outerSize = 10, innerSize = 10;
    std::vector<std::vector<int>> nestedVector(outerSize, std::vector<int>(innerSize));

    for (auto& vec : nestedVector) {
        for (auto& val : vec) {
            val = rand() % 100; // Placeholder for deterministic value assignment
        }
    }

    int totalSum = 0;
    try {
        for (const auto& vec : nestedVector) {
            totalSum += sumVector(vec);
        }
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    std::cout << totalSum << std::endl;
}