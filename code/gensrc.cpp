#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace dsl {

struct plus {
    static std::string string() {
        return "+";
    }
};

template <class LHS, class OP, class RHS>
struct binary_op {
    const LHS &lhs;
    const RHS &rhs;

    binary_op(const LHS &lhs, const RHS &rhs) : lhs(lhs), rhs(rhs) {}

    static void prm_decl(std::ostream &src, unsigned &pos) {
        LHS::prm_decl(src, pos);
        RHS::prm_decl(src, pos);
    }

    static void expr(std::ostream &src, unsigned &pos) {
        src << "( ";
        LHS::expr(src, pos);
        src << " " << OP::string() << " ";
        RHS::expr(src, pos);
        src << " )";
    }
};

template <class LHS, class RHS>
const binary_op<LHS, plus, RHS> operator+(const LHS &a, const RHS &b) {
    return binary_op<LHS, plus, RHS>(a, b);
}

template <typename T>
class vector {
    public:
        vector(size_t n) : data(n) {}

        T operator[](size_t i) const {
            return data[i];
        }

        static void prm_decl(std::ostream &src, unsigned &pos) {
            src << ",\n    global double * prm" << ++pos;
        }

        static void expr(std::ostream &src, unsigned &pos) {
            src << "prm" << ++pos << "[idx]";
        }

        template <class Expr>
        static std::string source() {
            std::ostringstream src; unsigned pos;

            src << "kernel void vexcl_vector_kernel(\n"
                    "    ulong n,\n    global double * res";

            pos = 0; Expr::prm_decl(src, pos);

            src << ")\n{\n"
                    "    for(size_t idx = get_global_id(0); idx < n; idx += get_global_size(0)) {\n"
                    "        res[idx] = ";

            pos = 0; Expr::expr(src, pos);

            src << ";\n    }\n}\n";

            return src.str();
        }
        template <class Expr>
        const vector& operator=(const Expr &expr) {
            std::cout << source<Expr>() << std::endl;
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

