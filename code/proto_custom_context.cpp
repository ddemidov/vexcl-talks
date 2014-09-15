#include <iostream>
#include <boost/proto/proto.hpp>

namespace proto = boost::proto;

template <class Term> struct terminal_expression {
    static void get(std::ostream &os, unsigned &pos) {
        os << "prm_" << ++pos;
    }
};

struct print_expression_context {
    template <typename Expr, typename Tag = typename Expr::proto_tag>
    struct eval {};

#define BINARY_OP(the_tag, op)                                                  \
    template <typename Expr>                                                    \
    struct eval<Expr, boost::proto::tag::the_tag> {                             \
        typedef void result_type;                                               \
        void operator()(const Expr &expr, print_expression_context &ctx) const {\
            std::cout << "( ";                                                  \
            proto::eval( proto::left (expr), ctx );                             \
            std::cout << " " #op " ";                                           \
            proto::eval( proto::right(expr), ctx );                             \
            std::cout << " )";                                                  \
        }                                                                       \
    }

    BINARY_OP(plus,         + );
    BINARY_OP(minus,        - );
    BINARY_OP(multiplies,   * );
    BINARY_OP(divides,      / );

    unsigned pos = 0;

    template <typename Expr>
    struct eval<Expr, boost::proto::tag::terminal> {
        typedef void result_type;
        void operator()(const Expr &expr, print_expression_context &ctx) const {
                terminal_expression<
                        typename proto::result_of::value<Expr>::type
                    >::get(std::cout, ctx.pos);
        }
    };
};

int main() {
    auto expr = proto::as_expr(6) * 7 + 5;
    print_expression_context ctx;
    proto::eval( expr, ctx );
    std::cout << std::endl;
}
