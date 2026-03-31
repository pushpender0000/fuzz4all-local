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

template<typename T, typename U>
auto multiply(T a, U b) -> decltype(a * b) {
    return a * b;
}

int main() {
    constexpr int a = 5;
    constexpr int b = 7;
    auto sum = add(a, b);

    std::vector<std::vector<double>> nestedVector;
    nestedVector.push_back({1.1, 2.2, 3.3});
    nestedVector.push_back({4.4, 5.5, 6.6});

    int result = 0;
    for (const auto& vec : nestedVector) {
        if constexpr(IsSame<decltype(vec[0]), double>::value) {
            for (auto val : vec) {
                result += static_cast<int>(multiply(val, sum));
            }
        } else {
            std::cout << "Error: Incorrect type used in calculation." << std::endl;
            return 1;
        }
    }

    std::vector<std::vector<float>> nestedVectorFloat;
    nestedVectorFloat.push_back({1.1f, 2.2f, 3.3f});
    nestedVectorFloat.push_back({4.4f, 5.5f, 6.6f});

    int resultFloat = 0;
    for (const auto& vec : nestedVectorFloat) {
        if constexpr(IsSame<decltype(vec[0]), float>::value) {
            for (auto val : vec) {
                resultFloat += static_cast<int>(multiply(val, sum));
            }
        } else {
            std::cout << "Error: Incorrect type used in calculation." << std::endl;
            return 1;
        }
    }

    std::vector<std::vector<int>> nestedVectorInt;
    nestedVectorInt.push_back({1, 2, 3});
    nestedVectorInt.push_back({4, 5, 6});

    int resultInt = 0;
    for (const auto& vec : nestedVectorInt) {
        if constexpr(IsSame<decltype(vec[0]), int>::value) {
            for (auto val : vec) {
                resultInt += static_cast<int>(multiply(val, sum));
            }
        } else {
            std::cout << "Error: Incorrect type used in calculation." << std::endl;
            return 1;
        }
    }

    std::vector<std::vector<long>> nestedVectorLong;
    nestedVectorLong.push_back({1L, 2L, 3L});
    nestedVectorLong.push_back({4L, 5L, 6L});

    int resultLong = 0;
    for (const auto& vec : nestedVectorLong) {
        if constexpr(IsSame<decltype(vec[0]), long>::value) {
            for (auto val : vec) {
                resultLong += static_cast<int>(multiply(val, sum));
            }
        } else {
            std::cout << "Error: Incorrect type used in calculation." << std::endl;
            return 1;
        }
    }

    std::vector<std::vector<unsigned long>> nestedVectorULong;
    nestedVectorULong.push_back({1UL, 2UL, 3UL});
    nestedVectorULong.push_back({4UL, 5UL, 6UL});

    int resultULong = 0;
    for (const auto& vec : nestedVectorULong) {
        if constexpr(IsSame<decltype(vec[0]), unsigned long>::value) {
            for (auto val : vec) {
                resultULong += static_cast<int>(multiply(val, sum));
            }
        } else {
            std::cout << "Error: Incorrect type used in calculation." << std::endl;
            return 1;
        }
    }

    std::vector<std::vector<short>> nestedVectorShort;
    nestedVectorShort.push_back({1, 2, 3});
    nestedVectorShort.push_back({4, 5, 6});

    int resultShort = 0;
    for (const auto& vec : nestedVectorShort) {
        if constexpr(IsSame<decltype(vec[0]), short>::value) {
            for (auto val : vec) {
                resultShort += static_cast<int>(multiply(val, sum));
            }
        } else {
            std::cout << "Error: Incorrect type used in calculation." << std::endl;
            return 1;
        }
    }

    std::vector<std::vector<char>> nestedVectorChar;
    nestedVectorChar.push_back({'a', 'b', 'c'});
    nestedVectorChar.push_back({'d', 'e', 'f'});

    int resultChar = 0;
    for (const auto& vec : nestedVectorChar) {
        if constexpr(IsSame<decltype(vec[0]), char>::value) {
            for (auto val : vec) {
                resultChar += static_cast<int>(multiply(val, sum));
            }
        } else {
            std::cout << "Error: Incorrect type used in calculation." << std::endl;
            return 1;
        }
    }

    std::vector<std::vector<unsigned char>> nestedVectorUChar;
    nestedVectorUChar.push_back({'a', 'b', 'c'});
    nestedVectorUChar.push_back({'d', 'e', 'f'});

    int resultUChar = 0;
    for (const auto& vec : nestedVectorUChar) {
        if constexpr(IsSame<decltype(vec[0]), unsigned char>::value) {
            for (auto val : vec) {
                resultUChar += static_cast<int>(multiply(val, sum));
            }
        } else {
            std::cout << "Error: Incorrect type used in calculation." << std::endl;
            return 1;
        }
    }

    std::cout << result + resultFloat + resultInt + resultLong + resultULong + resultShort + resultChar + resultUChar << std::endl;
}