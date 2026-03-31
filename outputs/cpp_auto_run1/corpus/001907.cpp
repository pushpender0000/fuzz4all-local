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

template<typename T, size_t N>
consteval auto sumVector(const std::vector<T>& vec) -> T {
    T result = 0;
    for (const auto& val : vec) {
        if constexpr(IsSame<decltype(val), double>::value) {
            result += static_cast<int>(multiply(val, add(static_cast<T>(1.1), static_cast<T>(2.2))));
        } else {
            std::cout << "Error: Incorrect type used in calculation." << std::endl;
            return 0; // Assuming error handling returns a default value or exits gracefully
        }
    }
    return result;
}

int main() {
    constexpr int size = 3;
    std::vector<double> vec(size, 4.4);
    
    auto result = sumVector<double, size>(vec);
    std::cout << result << std::endl;
}