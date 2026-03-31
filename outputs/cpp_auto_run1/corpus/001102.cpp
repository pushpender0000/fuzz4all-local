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
class NestedVector {
public:
    void push_back(const std::vector<T>& vec) {
        nested.push_back(vec);
    }

    void calculate() const {
        int result = 0;
        for (const auto& vec : nested) {
            for (auto val : vec) {
                if constexpr(IsSame<decltype(val), double>::value) {
                    result += static_cast<int>(multiply(val, add(1.1, 2.2)));
                } else {
                    std::cout << "Error: Incorrect type used in calculation." << std::endl;
                    std::exit(1);
                }
            }
        }
        std::cout << result << std::endl;
    }

private:
    std::vector<std::vector<T>> nested;
};

int main() {
    NestedVector<double> nv;
    nv.push_back({1.1, 2.2, 3.3});
    nv.push_back({4.4, 5.5, 6.6});
    nv.calculate();
}