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

template<typename T>
struct NestedTemplate {
    std::vector<std::vector<T>> nestedVector;

    auto pushBackVec(const std::vector<T>& vec) {
        nestedVector.push_back(vec);
    }

    auto calculateResult() const {
        T result = 0;
        for (const auto& vec : nestedVector) {
            for (auto val : vec) {
                if constexpr(IsSame<decltype(val), T>::value) {
                    result += static_cast<T>(multiply(val, add(val, val)));
                } else {
                    std::cout << "Error: Incorrect type used in calculation." << std::endl;
                    return 1;
                }
            }
        }
        return result;
    }
};

int main() {
    constexpr int a = 5;
    constexpr int b = 7;
    auto sum = add(a, b);

    NestedTemplate<double> nestedVec;
    nestedVec.pushBackVec({1.1, 2.2, 3.3});
    nestedVec.pushBackVec({4.4, 5.5, 6.6});

    auto result = nestedVec.calculateResult();
    std::cout << result << std::endl;
}