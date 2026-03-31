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
    constexpr int size = 10;
    std::vector<int> vec(size);
    std::iota(vec.begin(), vec.end(), 1);

    NestedTemplate<double> nestedVector;
    for (const auto& v : vec) {
        nestedVector.push_back({static_cast<double>(v), static_cast<double>(v * 2)});
    }

    double result = 0.0;
    for (const auto& outerVec : nestedVector) {
        if (!outerVec.empty()) {
            const auto& val = outerVec[0];
            result += multiply(val, add(vec[nestedVector.size() - 1], vec[nestedVector.size() / 2]));
        } else {
            std::cout << "Error: Empty vector in nested structure." << std::endl;
            return 1;
        }
    }

    if constexpr(IsSame<double, decltype(result)>::value) {
        std::cout << static_cast<int>(result) << std::endl;
    } else {
        std::cout << "Error: Incorrect type used in calculation." << std::endl;
        return 1;
    }
}