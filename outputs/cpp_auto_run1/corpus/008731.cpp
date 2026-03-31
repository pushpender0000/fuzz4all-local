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
void nestedVectorsMultiply(const std::vector<std::vector<T>>& outerVec, const std::vector<U>& innerVec) {
    if (outerVec.size() != innerVec.size()) {
        std::cout << "Error: Vector sizes do not match." << std::endl;
        return;
    }

    T result = 0;
    for (size_t i = 0; i < outerVec.size(); ++i) {
        if constexpr(IsSame<decltype(outerVec[i][0]), decltype(innerVec[i])>::value) {
            result += multiply(outerVec[i][0], innerVec[i]);
        } else {
            std::cout << "Error: Type mismatch in nested vectors." << std::endl;
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
    std::vector<int> innerVec = {7, 8, 9};

    nestedVectorsMultiply(nestedVector, innerVec);
}