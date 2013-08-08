#include <iostream>
#include <vector>

namespace dsl {

template <class LHS, class RHS>
struct vsum {
    const LHS &a;
    const RHS &b;
    vsum(const LHS &a, const RHS &b) : a(a), b(b) {}
    auto operator[](size_t i) const -> decltype(a[i] + b[i]) {
        return a[i] + b[i];
    }
};

template <class LHS, class RHS>
const vsum<LHS, RHS> operator+(const LHS &a, const RHS &b) {
    return vsum<LHS, RHS>(a, b);
}

template <typename T>
class vector {
    public:
        vector(size_t n) : data(n) {}

        T operator[](size_t i) const {
            return data[i];
        }

        template <class LHS, class RHS>
        const vector& operator=(const vsum<LHS, RHS> &s) {
            for(int i = 0; i < data.size(); ++i)
                data[i] = s[i];
            return *this;
        }
    private:
        std::vector<T> data;
};

}

int main() {
    const size_t n = 1024;

    dsl::vector<double> a(n), x(n), y(n), z(n);

    a = x + y + z;
}
