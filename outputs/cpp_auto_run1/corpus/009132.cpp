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
void fuzzTemplate() {
    NestedTemplate<T> nestedFuzz;
    nestedFuzz.addRow({static_cast<T>(1e6), static_cast<T>(2e6), static_cast<T>(3e6)});
    std::cout << nestedFuzz.calculateResult() << std::endl;
}

int main() {
    fuzzTemplate<double>();
    return 0;
}