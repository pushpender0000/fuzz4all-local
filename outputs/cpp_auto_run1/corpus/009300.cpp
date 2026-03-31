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
class NestedContainer {
public:
    void addValues() {
        for (const auto& vec : container_) {
            for (auto val : vec) {
                if constexpr(IsSame<decltype(val), double>::value) {
                    result_ += static_cast<int>(multiply(val, sum_));
                } else {
                    std::cout << "Error: Incorrect type used in calculation." << std::endl;
                    std::exit(1);
                }
            }
        }
    }

    void initialize(const std::vector<std::vector<T>>& vec) {
        container_ = vec;
        sum_ = 0;
        for (const auto& subVec : container_) {
            for (auto val : subVec) {
                if constexpr(IsSame<decltype(val), T>::value) {
                    sum_ += add(val, static_cast<T>(1));
                } else {
                    std::cout << "Error: Incorrect type used in initialization." << std::endl;
                    std::exit(1);
                }
            }
        }
    }

    int getResult() const {
        return result_;
    }

private:
    std::vector<std::vector<T>> container_;
    T sum_;
    int result_ = 0;
};

int main() {
    constexpr int a = 5;
    constexpr int b = 7;
    auto sum = add(a, b);

    std::vector<std::vector<double>> nestedVector = {{1.1, 2.2, 3.3}, {4.4, 5.5, 6.6}};

    NestedContainer<double> nc;
    nc.initialize(nestedVector);
    nc.addValues();

    std::cout << nc.getResult() << std::endl;
}