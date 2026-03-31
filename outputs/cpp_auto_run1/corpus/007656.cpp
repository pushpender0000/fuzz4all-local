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
constexpr auto sumVector(const std::vector<T>& vec) -> T {
    T result = 0;
    for (const auto& val : vec) {
        if constexpr(IsSame<decltype(val), int>::value) {
            result += val;
        } else {
            result += static_cast<int>(multiply(val, add(1, -1)));
        }
    }
    return result;
}

template<typename T>
constexpr auto minMaxSum(const std::vector<T>& vec) -> std::pair<T, T> {
    if (vec.empty()) return {0, 0};
    T minVal = *vec.begin();
    T maxVal = *vec.begin();
    for (const auto& val : vec) {
        if (val < minVal) minVal = val;
        if (val > maxVal) maxVal = val;
    }
    return {minVal, maxVal};
}

int main() {
    constexpr int size = 5;
    std::vector<int> vec(size);
    for (int i = 0; i < size; ++i) {
        vec[i] = i + 1;
    }

    auto [minVal, maxVal] = minMaxSum(vec);
    int sumResult = sumVector(vec);

    std::cout << "Min: " << minVal << ", Max: " << maxVal << ", Sum: " << sumResult << std::endl;
}