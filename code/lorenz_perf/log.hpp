#ifndef LOG_HPP
#define LOG_HPP

#include <string>
#include <fstream>
#include <boost/timer/timer.hpp>
#include <boost/filesystem.hpp>

void log_perf(const std::string &cmd, size_t size, size_t iter, boost::timer::cpu_times time) {
    std::string version = boost::filesystem::path(cmd).filename().string() + ".dat";
    std::ofstream f(version, std::ios::app);
    f << size << "\t" << iter << "\t" << boost::timer::format(time, 8, "%w") << "\n";
}

#endif
