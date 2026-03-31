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

template<typename T, typename U>
auto sumVector(const std::vector<T>& vec) -> decltype(std::declval<U>().operator+()) {
    U result = U{};
    for (const auto& val : vec) {
        if constexpr(IsSame<decltype(val), T>::value) {
            result += static_cast<decltype(result)>(multiply(val, add(T{1}, T{2})));
        } else {
            std::cout << "Error: Incorrect type used in calculation." << std::endl;
            std::exit(1);
        }
    }
    return result;
}

template<typename T>
struct NestedTemplateLambda {
    std::vector<std::vector<T>> nestedVector;

    void addRow(const std::vector<T>& row) {
        nestedVector.push_back(row);
    }

    auto calculateResult() const {
        int result = 0;
        for (const auto& vec : nestedVector) {
            result += sumVector<T, int>(vec);
        }
        return result;
    }
};

int main() {
    NestedTemplateLambda<double> nestedDouble;
    nestedDouble.addRow({1.1, 2.2, 3.3});
    nestedDouble.addRow({4.4, 5.5, 6.6});

    std::cout << nestedDouble.calculateResult() << std::endl;
}