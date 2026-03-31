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

template<typename T>
auto multiplyAndAdd(const std::vector<std::vector<T>>& vec, int multiplier) {
    int total = 0;
    for (const auto& subVec : vec) {
        for (const auto& val : subVec) {
            if constexpr(IsSame<decltype(val), T>::value) {
                total += static_cast<int>(val * multiplier);
            } else {
                std::cout << "Error: Incorrect type used in calculation." << std::endl;
                return -1; // Indicate error with a negative result
            }
        }
    }
    return total;
}

template<typename T, typename U>
auto multiplyAndAddMixed(const std::vector<std::vector<T>>& vecInts, const std::vector<std::vector<U>>& vecFloats) {
    int intTotal = 0;
    double floatTotal = 0.0;
    for (const auto& subVecInt : vecInts) {
        for (const auto& valInt : subVecInt) {
            if constexpr(IsSame<decltype(valInt), T>::value) {
                intTotal += static_cast<int>(valInt * 2);
            } else {
                std::cout << "Error: Incorrect type used in calculation." << std::endl;
                return -1; // Indicate error with a negative result
            }
        }
    }
    for (const auto& subVecFloat : vecFloats) {
        for (const auto& valFloat : subVecFloat) {
            if constexpr(IsSame<decltype(valFloat), U>::value) {
                floatTotal += static_cast<double>(valFloat * 3.0);
            } else {
                std::cout << "Error: Incorrect type used in calculation." << std::endl;
                return -1; // Indicate error with a negative result
            }
        }
    }
    return intTotal + static_cast<int>(floatTotal);
}

template<typename T>
auto generateVector(size_t size, const T& val) {
    std::vector<T> vec(size, val);
    return vec;
}

int main() {
    constexpr int multiplier = 3;
    std::vector<std::vector<double>> nestedVector = {{1.1, 2.2, 3.3}, {4.4, 5.5, 6.6}};
    
    auto resultDouble = multiplyAndAdd(nestedVector, multiplier);
    if (resultDouble >= 0) {
        std::cout << "Total from doubles: " << resultDouble << std::endl;
    } else {
        std::cout << "Error: Calculation failed." << std::endl;
    }

    std::vector<std::vector<int>> nestedVectorInt = {{1, 2, 3}, {4, 5, 6}};
    auto resultMixed = multiplyAndAddMixed(nestedVectorInt, nestedVector);
    if (resultMixed >= 0) {
        std::cout << "Total from mixed types: " << resultMixed << std::endl;
    } else {
        std::cout << "Error: Calculation failed." << std::endl;
    }
}