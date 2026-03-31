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

template<typename T, size_t N>
class FixedVector : public std::vector<T> {
public:
    constexpr FixedVector() : std::vector<T>(N) {}
};

int main() {
    constexpr int a = 5;
    constexpr int b = 7;
    auto sum = add(a, b);

    using IntVec = FixedVector<int, 3>;
    IntVec vec1, vec2;
    vec1.push_back(1); vec1.push_back(2); vec1.push_back(3);
    vec2.push_back(4); vec2.push_back(5); vec2.push_back(6);

    int result = 0;
    for (const auto& vec : {vec1, vec2}) {
        for (int val : vec) {
            if constexpr(IsSame<decltype(val), int>::value) {
                result += multiply(val, sum);
            } else {
                std::cout << "Error: Incorrect type used in calculation." << std::endl;
                return 1;
            }
        }
    }

    std::cout << result << std::endl;
}