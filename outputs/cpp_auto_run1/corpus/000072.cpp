#include <iostream>
#include <vector>
#include <type_traits>

template<typename T, typename U>
struct IsSame {
    static const bool value = std::is_same_v<T, U>;
};

template<typename T>
constexpr auto add(T a, T b) -> T {
    return a + b;
}

int main() {
    constexpr int size = 3;
    std::vector<std::vector<int>> nestedVector(size, std::vector<int>(size));
    
    for (auto& row : nestedVector) {
        for (int& val : row) {
            val = rand() % 100; // Placeholder for fuzzing input
        }
    }

    auto sumRow = [](const std::vector<int>& row) -> int {
        int s = 0;
        for (int val : row) {
            s += val;
        }
        return s;
    };

    int totalSum = 0;
    for (const auto& row : nestedVector) {
        if constexpr(IsSame<decltype(row[0]), int>::value) {
            totalSum += sumRow(row);
        } else {
            std::cout << "Error: Incorrect type used in calculation." << std::endl;
            return 1;
        }
    }

    auto multiplyAndAdd = [](const std::vector<std::vector<int>>& vec, int multiplier) -> int {
        int total = 0;
        for (const auto& subVec : vec) {
            if constexpr(IsSame<decltype(subVec[0]), int>::value) {
                int rowSum = 0;
                for (int val : subVec) {
                    rowSum += val * multiplier;
                }
                total += rowSum;
            } else {
                std::cout << "Error: Incorrect type used in calculation." << std::endl;
                return -1; // Indicate error with a negative result
            }
        }
        return total;
    };

    constexpr int multiplier = 2;
    auto finalResult = multiplyAndAdd(nestedVector, multiplier);
    if (finalResult >= 0) {
        std::cout << static_cast<int>(finalResult) << std::endl; // Ensure output is an integer for deterministic result
    } else {
        std::cout << "Error: Calculation failed." << std::endl;
    }
}