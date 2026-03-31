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
    std::vector<std::vector<T>> data;

    void push_back(const std::vector<U>& vec) {
        std::vector<U> tempVec(vec.size());
        for (size_t i = 0; i < vec.size(); ++i) {
            if constexpr(IsSame<T, double>::value && IsSame<U, int>::value) {
                tempVec[i] = static_cast<int>(multiply(vec[i], add(static_cast<double>(add(1, 2)), static_cast<double>(3))));
            } else if constexpr(IsSame<T, int>::value && IsSame<U, double>::value) {
                tempVec[i] = static_cast<int>(multiply(vec[i], add(static_cast<double>(add(4, 5)), static_cast<double>(6))));
            } else {
                throw std::runtime_error("Incorrect type combination");
            }
        }
        data.push_back(tempVec);
    }
};

int main() {
    NestedTemplate<double, int> nt;
    std::vector<int> input = {1, 2, 3};
    for (auto& val : input) {
        nt.push_back({static_cast<double>(val)});
    }

    int result = 0;
    for (const auto& vec : nt.data) {
        for (auto val : vec) {
            if constexpr(IsSame<decltype(val), double>::value) {
                result += static_cast<int>(multiply(val, add(static_cast<double>(add(7, 8)), static_cast<double>(9))));
            } else {
                std::cout << "Error: Incorrect type used in calculation." << std::endl;
                return 1;
            }
        }
    }

    std::cout << result << std::endl;
}