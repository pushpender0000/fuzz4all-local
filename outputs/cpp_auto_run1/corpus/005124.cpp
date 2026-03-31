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
void nestedTemplateFunction(const std::vector<std::vector<T>>& outerVec, const std::vector<U>& innerVec) {
    int result = 0;
    for (const auto& vec : outerVec) {
        if constexpr(IsSame<decltype(vec[0]), T>::value) {
            for (auto val : innerVec) {
                if constexpr(IsSame<decltype(val), U>::value) {
                    result += static_cast<int>(multiply(add(val, vec[0]), add(T(2), T(3))));
                } else {
                    std::cout << "Error: Incorrect type used in innerVec." << std::endl;
                    return;
                }
            }
        } else {
            std::cout << "Error: Incorrect type used in outerVec." << std::endl;
            return;
        }
    }
    std::cout << result << std::endl;
}

int main() {
    constexpr int a = 5;
    constexpr int b = 7;
    auto sum = add(a, b);

    std::vector<std::vector<double>> nestedVector;
    nestedVector.push_back({1.1, 2.2, 3.3});
    nestedVector.push_back({4.4, 5.5, 6.6});

    std::vector<int> innerVec = {7, 8, 9};

    nestedTemplateFunction(nestedVector, innerVec);
}