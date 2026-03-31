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
class FixedVector {
public:
    constexpr FixedVector() : data_{} {}
    constexpr void push_back(const T& value) {
        if (size_ >= N) throw std::out_of_range("FixedVector is full");
        data_[size_] = value;
        ++size_;
    }
    constexpr T operator[](size_t index) const {
        if (index >= size_) throw std::out_of_range("Index out of range");
        return data_[index];
    }
private:
    T data_[N];
    size_t size_;
};

int main() {
    constexpr int a = 5;
    constexpr int b = 7;
    auto sum = add(a, b);

    FixedVector<double, 3> fixedVec;
    fixedVec.push_back(1.1);
    fixedVec.push_back(2.2);
    fixedVec.push_back(3.3);

    int result = 0;
    for (const auto& val : fixedVec) {
        if constexpr(IsSame<decltype(val), double>::value) {
            result += static_cast<int>(multiply(val, sum));
        } else {
            std::cout << "Error: Incorrect type used in calculation." << std::endl;
            return 1;
        }
    }

    std::cout << result << std::endl;
}