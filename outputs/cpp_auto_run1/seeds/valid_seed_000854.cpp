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
auto generateVector(U size) {
    std::vector<T> vec(size, T{0});
    for (int i = 0; i < size; ++i) {
        vec[i] = static_cast<T>(i + 1);
    }
    return vec;
}

template<typename T>
struct LambdaTemplate {
    std::vector<T> data;

    void initialize(size_t size) {
        auto lambdaInit = [](auto val, int index) -> T {
            if constexpr(std::is_arithmetic_v<decltype(val)>) {
                return static_cast<T>(index + 1) * val;
            } else {
                std::cout << "Error: Invalid type in lambda initialization." << std::endl;
                std::exit(1);
            }
        };

        data.resize(size, T{0});
        for (int i = 0; i < size; ++i) {
            data[i] = lambdaInit(static_cast<T>(i + 1), i);
        }
    }

    void printData() const {
        for (const auto& val : data) {
            std::cout << static_cast<int>(val) << " ";
        }
        std::cout << std::endl;
    }
};

int main() {
    NestedTemplate<double> nestedDouble;
    nestedDouble.addRow({1.1, 2.2, 3.3});
    nestedDouble.addRow({4.4, 5.5, 6.6});

    std::cout << nestedDouble.calculateResult() << std::endl;

    LambdaTemplate<double> lambdaVec;
    lambdaVec.initialize(5);
    lambdaVec.printData();
}