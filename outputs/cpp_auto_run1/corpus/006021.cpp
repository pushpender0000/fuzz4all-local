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
struct NestedTemplate {
    std::vector<std::vector<T>> data;

    void fillData() {
        for (int i = 0; i < 10; ++i) {
            std::vector<T> innerVec(5);
            for (auto& val : innerVec) {
                val = static_cast<T>(i * 2 + 3);
            }
            data.push_back(innerVec);
        }
    }

    void processData() const {
        int result = 0;
        for (const auto& vec : data) {
            if constexpr(IsSame<T, double>::value) {
                for (auto val : vec) {
                    result += static_cast<int>(multiply(val, add(vec[0], vec[1])));
                }
            } else if constexpr(IsSame<T, int>::value) {
                for (auto val : vec) {
                    result += multiply(val, add(vec[0], vec[1]));
                }
            } else {
                std::cout << "Unsupported type." << std::endl;
                return;
            }
        }
        std::cout << result << std::endl;
    }
};

int main() {
    NestedTemplate<double> doubleNested;
    doubleNested.fillData();
    doubleNested.processData();

    NestedTemplate<int> intNested;
    intNested.fillData();
    intNested.processData();
}