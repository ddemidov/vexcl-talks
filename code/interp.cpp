#include <iostream>
#include <fstream>

#include <mba.hpp>

int main() {
    std::vector< std::array<double,2> > p;
    std::vector<double> v;

    std::ifstream f("peaks.dat");

    while(f) {
        double x, y, z;

        if (f >> x >> y >> z) {
            p.push_back(mba::make_array<double>(x, y));
            v.push_back(z);
        }
    }

    std::array<double, 2> xmin = {-0.01, -0.01};
    std::array<double, 2> xmax = { 1.01,  1.01};

    mba::cloud<2> c(
            xmin, xmax, p, v, mba::default_grid(xmin, xmax)
            );

    std::ofstream dat("c.dat");
    dat << std::scientific;
    for(double y = 0; y <= 1; y += 0.05) {
        for(double x = 0; x <= 1; x += 0.05)
            dat << c(x, y) << " ";
        dat << std::endl;
    }
}

