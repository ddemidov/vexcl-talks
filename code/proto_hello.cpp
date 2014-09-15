#include <iostream>
#include <boost/proto/proto.hpp>
using namespace std;
using namespace boost;

int main() {
    auto expr = proto::as_expr(6) * 7 - 2;
    proto::display_expr(expr);

    proto::default_context ctx;
    cout << proto::eval(expr, ctx) << endl;
}
