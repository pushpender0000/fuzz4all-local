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

int main() {
    constexpr int size = 10;
    std::vector<std::vector<int>> nestedVector(size, std::vector<int>(size));

    for (auto& vec : nestedVector) {
        for (int& val : vec) {
            val = rand() % 100;
        }
    }

    int result = 0;
    auto multiplyAndSum = [&](const std::vector<int>& vec) {
        for (int val : vec) {
            if constexpr(IsSame<decltype(val), int>::value) {
                result += val * add(rand() % 10, rand() % 10);
            } else {
                std::cout << "Error: Incorrect type used in calculation." << std::endl;
                return;
            }
        }
    };

    for (const auto& vec : nestedVector) {
        multiplyAndSum(vec);
    }

    std::cout << result << std::endl;
}