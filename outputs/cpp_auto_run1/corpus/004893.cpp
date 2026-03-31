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

template<typename T, typename U>
void nestedMultiplyAdd(const std::vector<std::vector<T>>& vecVec, const std::vector<U>& vecU, int& result) {
    for (const auto& vec : vecVec) {
        if (!vec.empty()) {
            auto val = vec[0];
            if constexpr(IsSame<decltype(val), T>::value && IsSame<decltype(val), U>::value) {
                result += static_cast<int>(multiply(val, add(val, 1)));
            } else {
                std::cout << "Error: Incorrect type used in calculation." << std::endl;
                return;
            }
        }
    }
}

int main() {
    constexpr int a = 5;
    constexpr int b = 7;
    auto sum = add(a, b);

    std::vector<std::vector<double>> nestedVector;
    nestedVector.push_back({1.1, 2.2, 3.3});
    nestedVector.push_back({4.4, 5.5, 6.6});

    std::vector<int> vecU = {1, 2, 3};

    int result = 0;
    nestedMultiplyAdd(nestedVector, vecU, result);

    std::cout << result << std::endl;
}