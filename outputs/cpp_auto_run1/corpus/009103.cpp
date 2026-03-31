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

    void addRow(const std::vector<T>& row) {
        nestedVector.push_back(row);
    }

    auto calculateResult() const {
        int result = 0;
        for (const auto& vec : nestedVector) {
            for (auto val : vec) {
                if constexpr(IsSame<decltype(val), T>::value) {
                    result += static_cast<int>(multiply(val, add(T{1}, T{2})));
                } else {
                    std::cout << "Error: Incorrect type used in calculation." << std::endl;
                    std::exit(1);
                }
            }
        }
        return result;
    }
};

template<typename T>
constexpr auto sumVector(const std::vector<T>& vec) -> T {
    T sum = 0;
    for (auto val : vec) {
        if constexpr(!std::is_same_v<decltype(val), int>) {
            sum += static_cast<int>(multiply(val, add(T{1}, T{2})));
        } else {
            std::cout << "Error: Incorrect type used in calculation." << std::endl;
            std::exit(1);
        }
    }
    return sum;
}

int main() {
    NestedTemplate<double> nestedDouble;
    nestedDouble.addRow({1.1, 2.2, 3.3});
    nestedDouble.addRow({4.4, 5.5, 6.6});

    std::cout << nestedDouble.calculateResult() << std::endl;

    std::vector<double> testVec = {1.1, 2.2, 3.3};
    std::cout << sumVector(testVec) << std::endl;
}