```cpp
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

template<typename T, typename U>
auto multiplyAndAddMixedOptimized(const std::vector<std::vector<T>>& vecInts, const std::vector<std::vector<U>>& vecFloats) {
    int intTotal = 0;
    double floatTotal = 0.0;
    auto addInt = [](int a, T b) -> int { return static_cast<int>(a * 2); };
    auto addFloat = [](double a, U b) -> double { return a + b * 3.0; };

    for (const auto& subVecInt : vecInts) {
        for (const auto& valInt : subVecInt) {
            if constexpr(IsSame<decltype(valInt), T>::value) {
                intTotal = addInt(intTotal, valInt);
            } else {
                std::cout << "Error: Incorrect type used in calculation." << std::endl;
                return -1; // Indicate error with a negative result
            }
        }
    }
    for (const auto& subVecFloat : vecFloats) {
        for (const auto& valFloat : subVecFloat) {
            if constexpr(IsSame<decltype(valFloat), U>::value) {
                floatTotal = addFloat(floatTotal, valFloat);
            } else {
                std::cout << "Error: Incorrect type used in calculation." << std::endl;
                return -1; // Indicate error with a negative result
            }
        }
    }
    return intTotal + static_cast<int>(floatTotal);
}

template<typename T, typename U>
auto multiplyAndAddMixedComplex(const std::vector<std::vector<T>>& vecInts, const std::vector<std::vector<U>>& vecFloats) {
    int intTotal = 0;
    double floatTotal = 0.0;
    auto addInt = [](int a, T b) -> int { return static_cast<int>(a * 2); };
    auto addFloat = [](double a, U b) -> double { return a + b * 3.0; };

    for (const auto& subVecInt : vecInts) {
        for (const auto& valInt : subVecInt) {
            if constexpr(IsSame<decltype(valInt), T>::value) {
                intTotal = addInt(intTotal, valInt);
            } else {
                std::cout << "Error: Incorrect type used in calculation." << std::endl;
                return -1; // Indicate error with a negative result
            }
        }
    }
    for (const auto& subVecFloat : vecFloats) {
        for (const auto& valFloat : subVecFloat) {
            if constexpr(IsSame<decltype(valFloat), U>::value) {
                floatTotal = addFloat(floatTotal, valFloat);
            } else {
                std::cout << "Error: Incorrect type used in calculation." << std::endl;
                return -1; // Indicate error with a negative result
            }
        }
    }
    return intTotal + static_cast<int>(floatTotal);
}

template<typename T, typename U>
auto multiplyAndAddMixedComplexOptimized(const std::vector<std::vector<T>>& vecInts, const std::vector<std::vector<U>>& vecFloats) {
    int intTotal = 0;
    double floatTotal = 0.0;
    auto addInt = [](int a, T b) -> int { return static_cast<int>(a * 2); };
    auto addFloat = [](double a, U b) -> double { return a + b * 3.0; };

    for (const auto& subVecInt : vecInts) {
        for (const auto& valInt : subVecInt) {
            if constexpr(IsSame<decltype(valInt), T>::value) {
                intTotal = addInt(intTotal, valInt);
            } else {
                std::cout << "Error: Incorrect type used in calculation." << std::endl;
                return -1; // Indicate error with a negative result
            }
        }
    }
    for (const auto& subVecFloat : vecFloats) {
        for (const auto& valFloat : subVecFloat) {
            if constexpr(IsSame<decltype(valFloat), U>::value) {
                float