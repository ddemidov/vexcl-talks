#include <iostream>
#include <vector>
#include <boost/compute.hpp>

namespace compute = boost::compute;

int main() {
    compute::command_queue q = compute::system::default_queue();
    std::cout << q.get_device().name() << std::endl;

    size_t n = 1024 * 1024;
    std::vector<float> a(n, 1), b(n, 2);

    compute::vector<float> A(a, q);
    compute::vector<float> B(b, q);

    compute::transform(A.begin(), A.end(), B.begin(), B.begin(), compute::plus<float>(), q);

    compute::copy(B.begin(), B.end(), b.begin(), q);
    std::cout << b[42] << std::endl;
}
