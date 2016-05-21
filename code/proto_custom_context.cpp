#include <iostream>
#include <boost/proto/proto.hpp>

namespace proto = boost::proto;

template <class Term> struct partial_vector_expr {
    static void get(std::ostream &os, unsigned &pos) {
        os << "prm_" << ++pos;
    }
};

struct vector_expr_context {
    template <typename Expr, typename Tag = typename Expr::proto_tag>
    struct eval {};

    unsigned pos = 0;

    template <typename Expr>
    struct eval<Expr, boost::proto::tag::plus> {
        typedef void result_type;
        void operator()(const Expr &expr, vector_expr_context &ctx) const {
            std::cout << "( ";
            proto::eval(proto::left(expr), ctx);
            std::cout << " + ";
            proto::eval(proto::right(expr), ctx);
            std::cout << " )";
        }
    };

    template <typename Expr>
    struct eval<Expr, boost::proto::tag::terminal> {
        typedef void result_type;
        void operator()(const Expr &expr, vector_expr_context &ctx) const {
            partial_vector_expr<typename proto::result_of::value<Expr>::type>::get(std::cout, ctx.pos);
        }
    };
};

int main() {
    auto expr = proto::as_expr(2) + "hi";
    vector_expr_context ctx;
    proto::eval( expr, ctx );
    std::cout << std::endl;
}
