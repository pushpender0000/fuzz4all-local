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
void nestedLoop(const std::vector<std::vector<T>>& outerVec, const std::vector<U>& innerVec) {
    for (const auto& vec : outerVec) {
        if constexpr(IsSame<decltype(vec[0]), double>::value) {
            T sum = 0;
            for (auto val : vec) {
                sum += static_cast<T>(multiply(val, val));
            }
            std::cout << add(sum, innerVec.size()) << std::endl;
        } else {
            std::cout << "Error: Incorrect type used in calculation." << std::endl;
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

    std::vector<int> innerVec = {1, 2, 3};

    nestedLoop(nestedVector, innerVec);
}