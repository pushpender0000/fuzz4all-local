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

template<typename T, std::size_t N>
class StaticVector : public std::vector<T> {
public:
    constexpr StaticVector() : std::vector<T>(N) {}
};

int main() {
    constexpr int a = 5;
    constexpr int b = 7;
    auto sum = add(a, b);

    StaticVector<double, 3> vec1;
    vec1.push_back(1.1);
    vec1.push_back(2.2);
    vec1.push_back(3.3);

    StaticVector<StaticVector<int, 4>, 2> nestedVecs;
    nestedVecs[0].push_back(1);
    nestedVecs[0].push_back(2);
    nestedVecs[0].push_back(3);
    nestedVecs[0].push_back(4);
    nestedVecs[1].push_back(5);
    nestedVecs[1].push_back(6);
    nestedVecs[1].push_back(7);
    nestedVecs[1].push_back(8);

    int result = 0;
    for (const auto& vec : nestedVecs) {
        for (int val : vec) {
            if constexpr(IsSame<int, decltype(val)>::value) {
                result += multiply(val, sum);
            } else {
                std::cout << "Error: Incorrect type used in calculation." << std::endl;
                return 1;
            }
        }
    }

    std::cout << result << std::endl;
}