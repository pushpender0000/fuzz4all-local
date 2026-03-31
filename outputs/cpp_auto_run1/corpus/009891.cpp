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
void nestedTemplateInstantiation() {
    std::vector<std::vector<double>> vecOfVecs = {{1.1, 2.2}, {3.3, 4.4}};
    int result = 0;

    auto sumLambda = [](const std::vector<T>& vec) -> T {
        T sum = T{};
        for (const auto& val : vec) {
            sum += val;
        }
        return sum;
    };

    constexpr U factor = 2.0;
    const auto totalSum = sumLambda(vecOfVecs[0]);

    if constexpr(IsSame<decltype(totalSum), double>::value) {
        result += static_cast<int>(multiply(factor, totalSum));
    } else {
        std::cout << "Error: Incorrect type used in calculation." << std::endl;
    }

    std::cout << result << std::endl;
}

int main() {
    nestedTemplateInstantiation<std::vector<double>, double>();
}