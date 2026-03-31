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
class NestedVector {
public:
    void push_back(const std::vector<U>& vec) {
        nested.push_back(vec);
    }

    auto sum() const -> T {
        T result = 0;
        for (const auto& vec : nested) {
            for (auto val : vec) {
                if constexpr(IsSame<decltype(val), U>::value) {
                    result += static_cast<T>(multiply(val, add(*vec.begin(), *vec.rbegin())));
                } else {
                    std::cout << "Error: Incorrect type used in calculation." << std::endl;
                    exit(1);
                }
            }
        }
        return result;
    }

private:
    std::vector<std::vector<U>> nested;
};

int main() {
    constexpr int a = 5;
    constexpr int b = 7;
    auto sum = add(a, b);

    NestedVector<int, double> nestedVec;
    nestedVec.push_back({1.1, 2.2, 3.3});
    nestedVec.push_back({4.4, 5.5, 6.6});

    std::cout << nestedVec.sum() << std::endl;
}