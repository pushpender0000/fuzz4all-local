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
auto generateVectorPair(T min, T max) {
    std::vector<T> vec1(max - min + 1);
    for (int i = 0; i <= max - min; ++i) {
        vec1[i] = static_cast<T>(min + i);
    }
    std::vector<U> vec2(vec1.size());
    for (size_t i = 0; i < vec1.size(); ++i) {
        vec2[i] = static_cast<U>(vec1[i]);
    }
    return std::make_pair(vec1, vec2);
}

int main() {
    auto [doubleVec, intVec] = generateVectorPair<double, int>(1.0, 6.0);
    NestedTemplate<double> nestedDouble;
    nestedDouble.addRow(doubleVec);
    nestedDouble.addRow(intVec);

    std::cout << nestedDouble.calculateResult() << std::endl;
}