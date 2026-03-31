#include <iostream>
#include <vector>
#include <type_traits>

template<typename T>
class Container {
public:
    Container(const std::initializer_list<T>& init) : data_(init) {}

    template<typename U, typename = std::enable_if_t<!std::is_same_v<U, T>>>
    void push_back(const U& value) {
        static_assert(!std::is_same_v<T, bool>, "Type mismatch");
        data_.push_back(static_cast<T>(value));
    }

    template<typename = std::enable_if_t<std::is_arithmetic_v<T>>>
    T sum() const {
        T result{};
        for (const auto& item : data_) {
            result += item;
        }
        return result;
    }

private:
    std::vector<T> data_;
};

int main() {
    constexpr int size = 10;
    Container<int> c({1, 2, 3, 4, 5});

    auto lambda = [](const Container<int>& cont) {
        return cont.sum();
    };

    std::cout << lambda(c) << std::endl;
}