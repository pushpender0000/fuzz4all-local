#include <iostream>
#include <vector>
#include <type_traits>

template<typename T, typename U>
struct IsSame {
    static const bool value = std::is_same_v<T, U>;
};

template<typename T, typename... Args>
constexpr auto sum(Args... args) -> T {
    return (args + ...);
}

template<typename T, typename U>
auto multiply(T a, U b) -> decltype(a * b) {
    return a * b;
}

template<typename T, typename U>
class NestedTemplate {
public:
    std::vector<std::vector<T>> data;

    NestedTemplate() : data(2, std::vector<T>(3)) {}

    auto calculateResult() const -> int {
        int result = 0;
        for (const auto& vec : data) {
            for (const auto& val : vec) {
                if constexpr(IsSame<decltype(val), T>::value) {
                    result += multiply(val, sum<int>(1, 2));
                } else {
                    std::cout << "Error: Incorrect type used in calculation." << std::endl;
                    return 1;
                }
            }
        }
        return result;
    }
};

int main() {
    NestedTemplate<int> nt;
    nt.data[0] = {1, 2, 3};
    nt.data[1] = {4, 5, 6};

    auto result = nt.calculateResult();
    std::cout << result << std::endl;
}