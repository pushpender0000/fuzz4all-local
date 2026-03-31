```cpp
#include <iostream>
#include <vector>
#include <type_traits>
#include <algorithm>

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

template<typename T>
struct NestedTemplate : public std::vector<std::vector<T>> {};

int main() {
    constexpr int a = 5;
    constexpr int b = 7;
    auto sum = add(a, b);

    NestedTemplate<double> nestedVector;
    nestedVector.push_back({1.1, 2.2, 3.3});
    nestedVector.push_back({4.4, 5.5, 6.6});

    int result = 0;
    for (const auto& vec : nestedVector) {
        for (auto val : vec) {
            if constexpr(IsSame<decltype(val), double>::value) {
                result += static_cast<int>(multiply(val, sum));
            } else {
                std::cout << "Error: Incorrect type used in calculation." << std::endl;
                return 1;
            }
        }
    }

    std::vector<std::vector<double>> largeVector(100, std::vector<double>(100, 2.3));
    int largeResult = 0;
    for (const auto& vec : largeVector) {
        for (auto val : vec) {
            if constexpr(IsSame<decltype(val), double>::value) {
                largeResult += static_cast<int>(multiply(val, sum));
            } else {
                std::cout << "Error: Incorrect type used in calculation." << std::endl;
                return 1;
            }
        }
    }

    std::vector<std::vector<double>> hugeVector(500, std::vector<double>(500, 3.4));
    int hugeResult = 0;
    for (const auto& vec : hugeVector) {
        for (auto val : vec) {
            if constexpr(IsSame<decltype(val), double>::value) {
                hugeResult += static_cast<int>(multiply(val, sum));
            } else {
                std::cout << "Error: Incorrect type used in calculation." << std::endl;
                return 1;
            }
        }
    }

    std::vector<std::vector<double>> ginormousVector(1000, std::vector<double>(1000, 4.5));
    int ginormousResult = 0;
    for (const auto& vec : ginormousVector) {
        for (auto val : vec) {
            if constexpr(IsSame<decltype(val), double>::value) {
                ginormousResult += static_cast<int>(multiply(val, sum));
            } else {
                std::cout << "Error: Incorrect type used in calculation." << std::endl;
                return 1;
            }
        }
    }

    std::vector<std::vector<double>> colossalVector(2000, std::vector<double>(2000, 5.6));
    int colossalResult = 0;
    for (const auto& vec : colossalVector) {
        for (auto val : vec) {
            if constexpr(IsSame<decltype(val), double>::value) {
                colossalResult += static_cast<int>(multiply(val, sum));
            } else {
                std::cout << "Error: Incorrect type used in calculation." << std::endl;
                return 1;
            }
        }
    }

    std::vector<std::vector<double>> titanicVector(3000, std::vector<double>(3000, 6.7));
    int titanicResult = 0;
    for (const auto& vec : titanicVector) {
        for (auto val : vec) {
            if constexpr(IsSame<decltype(val), double>::value) {
                titanicResult += static_cast<int>(multiply(val, sum));
            } else {
                std::cout << "Error: Incorrect type used in calculation." << std::endl;
                return 1;
            }
        }
    }

    std::vector<std::vector<double>> enormousVector(4000, std::vector<double>(4000, 7.8));
    int enormousResult = 0;
    for (const auto& vec : enormousVector) {
        for (auto val : vec) {
            if constexpr(IsSame<decltype(val), double>::value) {
                enormousResult += static_cast<int>(multiply(val, sum));
            } else {
                std::cout << "Error: Incorrect type used in calculation." << std::endl;
                return 1;
            }
        }
    }

    std::vector<std::vector<double>> massiveVector(5000, std::vector<double>(5000, 8.9));
    int massiveResult = 0;
    for (const auto& vec : massiveVector) {
        for (auto val : vec) {
            if constexpr(IsSame<decltype(val), double>::value) {
                massiveResult += static_cast<int>(multiply(val, sum));
            } else {
                std::cout << "Error: Incorrect type used in calculation." << std::endl;
                return 1;
            }
        }
    }

    std::vector<std::vector<double>> whoppingVector(6000, std::vector<double>(6000, 9.0));
    int whoppingResult = 0;
    for (const auto& vec : whoppingVector) {
        for (auto val : vec) {
            if constexpr(IsSame<decltype(val), double>::value) {
                whoppingResult += static_cast<int>(multiply(val, sum));
            } else {
                std::cout << "Error: Incorrect type used in calculation." << std::endl;
                return 1;
            }
        }
    }

    std::vector<std::vector<double>> mammothVector(7000, std::vector<double>(7000, 9.1));
    int mammothResult = 0;
    for (const auto& vec : mammothVector) {
        for (auto val : vec) {
            if constexpr(IsSame<decltype(val),