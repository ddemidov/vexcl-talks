#include <iostream>
#include <vector>

class vector;

struct vsum {
    const vector &a;
    const vector &b;
    vsum(const vector &a, const vector &b) : a(a), b(b) {}
};

vsum operator+(const vector &a, const vector &b) {
    return vsum(a, b);
}

class vector {
    public:
        vector(size_t n) : data(n) {}

        double operator[](size_t i) const {
            return data[i];
        }

        const vector& operator=(const vsum &s) {
            for(size_t i = 0; i < data.size(); ++i)
                data[i] = s.a[i] + s.b[i];
            return *this;
        }
    private:
        std::vector<double> data;
};

int main() {
    const size_t n = 1024;

    vector a(n), x(n), y(n), z(n);

    a = x + y + z;
}
