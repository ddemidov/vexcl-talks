#include <iostream>
#include <boost/proto/proto.hpp>

namespace proto = boost::proto;

template <class Term> struct to_string {
    static void get(std::ostream &os, unsigned &pos) {
        os << "prm_" << ++pos;
    }
};

struct to_string_context {
    template <typename Expr, typename Tag = typename Expr::proto_tag>
    struct eval {};

    unsigned pos = 0;

    template <typename Expr>
    struct eval<Expr, boost::proto::tag::plus> {
        typedef void result_type;
        void operator()(const Expr &expr, to_string_context &ctx) const {
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
        void operator()(const Expr &expr, to_string_context &ctx) const {
            to_string<typename proto::result_of::value<Expr>::type>::get(std::cout, ctx.pos);
        }
    };
};

int main() {
    auto expr = proto::as_expr(2) + "hi";
    to_string_context ctx;
    proto::eval( expr, ctx );
    std::cout << std::endl;
}
