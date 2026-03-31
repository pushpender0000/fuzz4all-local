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
class NestedTemplate {
public:
    std::vector<std::vector<T>> nestedVector;

    void push_back(const std::initializer_list<U>& values) {
        for (auto val : values) {
            if constexpr(IsSame<decltype(val), U>::value && IsSame<T, double>::value) {
                nestedVector.push_back({static_cast<T>(val * 2)});
            } else {
                std::cout << "Error: Incorrect type used in calculation." << std::endl;
                throw std::invalid_argument("Incorrect types");
            }
        }
    }

    void printSum() const {
        int result = 0;
        for (const auto& vec : nestedVector) {
            for (auto val : vec) {
                if constexpr(IsSame<decltype(val), double>::value) {
                    result += static_cast<int>(multiply(val, add(T{1}, T{2})));
                } else {
                    std::cout << "Error: Incorrect type used in calculation." << std::endl;
                    throw std::invalid_argument("Incorrect types");
                }
            }
        }
        std::cout << result << std::endl;
    }
};

int main() {
    NestedTemplate<double, int> nested;
    try {
        nested.push_back({1, 2, 3});
        nested.printSum();
    } catch (const std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
}