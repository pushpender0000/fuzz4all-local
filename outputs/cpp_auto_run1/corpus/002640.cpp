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
void nestedVectorsMultiplyAdd(const std::vector<std::vector<T>>& outerVec, const std::vector<U>& innerVec) {
    if (outerVec.size() != innerVec.size()) {
        std::cout << "Error: Vector sizes do not match." << std::endl;
        return;
    }

    T result = 0;
    for (const auto& vec : outerVec) {
        if constexpr(IsSame<decltype((vec)[0]), U>::value) {
            for (auto val : vec) {
                result += static_cast<T>(multiply(val, innerVec[&val - &vec[0]]));
            }
        } else {
            std::cout << "Error: Incorrect type used in calculation." << std::endl;
            return;
        }
    }

    std::cout << result << std::endl;
}

int main() {
    constexpr int a = 5;
    constexpr int b = 7;
    auto sum = add(a, b);

    std::vector<std::vector<double>> nestedVector = {{1.1, 2.2, 3.3}, {4.4, 5.5, 6.6}};
    std::vector<int> innerVec = {1, 2, 3};

    nestedVectorsMultiplyAdd(nestedVector, innerVec);
}