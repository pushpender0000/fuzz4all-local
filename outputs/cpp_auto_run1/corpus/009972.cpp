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
    NestedTemplate(const std::vector<std::vector<U>>& data) : data_(data) {}

    auto calculate() const -> int {
        int result = 0;
        for (const auto& vec : data_) {
            if constexpr(IsSame<typename decltype(vec)::value_type, U>::value) {
                for (auto val : vec) {
                    result += static_cast<int>(multiply(val, add(*vec.begin(), *vec.end())));
                }
            } else {
                std::cout << "Error: Incorrect type used in calculation." << std::endl;
                return 1;
            }
        }
        return result;
    }

private:
    const std::vector<std::vector<U>>& data_;
};

int main() {
    constexpr int a = 5;
    constexpr int b = 7;
    auto sum = add(a, b);

    std::vector<std::vector<double>> nestedVector;
    nestedVector.push_back({1.1, 2.2, 3.3});
    nestedVector.push_back({4.4, 5.5, 6.6});

    NestedTemplate nt(nestedVector);
    std::cout << nt.calculate() << std::endl;
}