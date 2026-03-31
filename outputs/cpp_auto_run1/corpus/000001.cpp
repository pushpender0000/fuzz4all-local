#include <iostream>
#include <vector>
#include <type_traits>

template<typename T>
class Container {
public:
    Container(const std::vector<T>& values) : data_(values) {}

    template<typename U, typename = std::enable_if_t<!std::is_same_v<U, void>>>
    void printSum() const {
        T sum = 0;
        for (const auto& item : data_) {
            if constexpr (std::is_arithmetic_v<T>) {
                sum += item;
            }
        }
        std::cout << static_cast<int>(sum) << "\n";
    }

private:
    std::vector<T> data_;
};

template<typename T, typename U>
constexpr auto add(T a, U b) {
    return a + b;
}

int main() {
    constexpr int a = 5;
    volatile double b = 3.14;

    auto lambda = [](auto x) {
        return x * x;
    };

    std::vector<int> vec = {1, 2, 3, 4, 5};
    Container<int> container(vec);
    container.printSum();

    auto result = add(a, static_cast<int>(b));
    std::cout << "Result of addition: " << result << "\n";

    return static_cast<int>(lambda(result));
}