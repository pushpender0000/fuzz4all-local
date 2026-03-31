#include <iostream>
#include <vector>
#include <type_traits>

template<typename T, typename U>
constexpr auto add(T a, U b) {
    return a + b;
}

template<typename T, template<typename> class ContainerType>
class NestedContainer {
public:
    NestedContainer(const std::vector<T>& values) : data_(values) {}

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
    ContainerType<T> data_;
};

template<typename T, template<typename> class ContainerType = std::vector>
class CustomContainer {
public:
    CustomContainer(const std::vector<T>& values) : data_(values) {}

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
    ContainerType<T> data_;
};

template<typename T, template<typename> class ContainerType = std::vector>
class ConstexprContainer {
public:
    constexpr ConstexprContainer(const std::vector<T>& values) : data_(values) {}

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
    ContainerType<T> data_;
};

template<typename T, template<typename> class ContainerType = std::vector>
class LambdasContainer {
public:
    LambdasContainer(const std::vector<T>& values) : data_(values) {}

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
    ContainerType<T> data_;
};

int main() {
    constexpr int a = 5;
    volatile double b = 3.14;

    auto lambda = [](auto x) {
        return x * x;
    };

    std::vector<int> vec = {1, 2, 3, 4, 5};

    NestedContainer<int, std::vector> nested_container(vec);
    nested_container.printSum();

    CustomContainer<int> custom_container(vec);
    custom_container.printSum();

    ConstexprContainer<int> constexpr_container(vec);
    constexpr_container.printSum();

    LambdasContainer<int> lambdas_container(vec);
    lambdas_container.printSum();

    auto result = add(a, static_cast<int>(b));
    std::cout << "Result of addition: " << result << "\n";

    return static_cast<int>(lambda(result));
}