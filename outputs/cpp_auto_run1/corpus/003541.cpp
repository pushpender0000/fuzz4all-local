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
    NestedTemplate(const std::vector<T>& vec1, const std::vector<U>& vec2) : vec1_(vec1), vec2_(vec2) {}

    auto calculate() -> int {
        static_assert(IsSame<T, double>::value && IsSame<U, double>::value, "Incorrect types used in calculation");
        T sum = 0;
        for (const auto& val : vec1_) {
            sum += val;
        }
        int result = 0;
        for (auto val : vec2_) {
            if constexpr(IsSame<decltype(val), double>::value) {
                result += static_cast<int>(multiply(val, sum));
            } else {
                std::cout << "Error: Incorrect type used in calculation." << std::endl;
                return 1;
            }
        }
        return result;
    }

private:
    const std::vector<T>& vec1_;
    const std::vector<U>& vec2_;
};

int main() {
    constexpr int a = 5;
    constexpr int b = 7;
    auto sum = add(a, b);

    std::vector<std::vector<double>> nestedVector;
    nestedVector.push_back({1.1, 2.2, 3.3});
    nestedVector.push_back({4.4, 5.5, 6.6});

    NestedTemplate nt(nestedVector[0], nestedVector[1]);
    std::cout << nt.calculate() << std::endl;
}