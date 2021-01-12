#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <pybind11/stl.h>
#include <map>
#include <vector>

namespace py = pybind11;

// naive
std::vector<std::map<int, std::vector<std::vector<int> > > > proc(py::array_t<float> input){
    auto data = input.unchecked<3>();
    std::vector<std::map<int, std::vector<std::vector<int> > > > results(3);
    for (py::ssize_t cat = 0; cat < 3; ++cat){
        for (py::ssize_t row = 0; row < data.shape(0); ++row){
            bool flag = false;
            int start = -1;
            for (py::ssize_t col = 0; col < data.shape(1); ++col){
                if (data(row, col, cat) >= 0.5){
                    if (!flag) {
                        flag = true;
                        start = (int)col;
                    }
                } else {
                    if (flag) {
                        flag = false;
                        results[cat][row].push_back(std::vector<int>{start, (int)(col) - 1});
                    }
                }
            }
            if (flag) {
                results[cat][row].push_back(std::vector<int>{start, (int)(data.shape(1)) - 1});
            }
        }
    }
    return results;
}

// x20
std::vector<std::map<int, std::vector<std::vector<int> > > > proc2(py::array_t<float> input){
    auto data = input.unchecked<3>();
    std::vector<std::map<int, std::vector<std::vector<int> > > > results(3);
    for (py::ssize_t cat = 0; cat < 3; ++cat){
        for (py::ssize_t row = 0; row < data.shape(0); ++row){
            bool flag = false;
            int start = -1;
            for (py::ssize_t col = 0; col < data.shape(1); ++col){
                if (data(row, col, cat) >= 0.5){
                    if (!flag) {
                        flag = true;
                        start = col;
                    }
                } else {
                    if (flag) {
                        flag = false;
                        for (int scale_f=0; scale_f<20; ++scale_f){
                            results[cat][20*row+scale_f].push_back(std::vector<int>{20*start, 20*(int)(col) - 1});
                        }
                    }
                }
            }
            if (flag) {
                for (int scale_f=0; scale_f<20; ++scale_f){
                    results[cat][20*row+scale_f].push_back(std::vector<int>{20*start, 20*(int)(data.shape(1)) - 1});
                }
            }
        }
    }
    return results;
}

// x20
std::vector<std::map<int, std::vector<std::vector<int> > > > proc_x20(py::array_t<float> input){
    auto data = input.unchecked<3>();
    std::vector<std::map<int, std::vector<std::vector<int> > > > results(3);
    for (py::ssize_t cat = 0; cat < 3; ++cat){
        for (py::ssize_t row = 0; row < data.shape(0); ++row){
            bool flag = false;
            int start = -1;
            for (py::ssize_t col = 0; col < data.shape(1); ++col){
                if (data(row, col, cat) >= 0.5){
                    if (!flag) {
                        flag = true;
                        start = col;
                    }
                } else {
                    if (flag) {
                        flag = false;
                        for (int scale_f=0; scale_f<20; ++scale_f){
                            results[cat][20*row+scale_f].push_back(std::vector<int>{20*start, 20*(int)(col) - 1});
                        }
                    }
                }
            }
            if (flag) {
                for (int scale_f=0; scale_f<20; ++scale_f){
                    results[cat][20*row+scale_f].push_back(std::vector<int>{20*start, 20*(int)(data.shape(1)) - 1});
                }
            }
        }
    }
    return results;
}

// x20bool
std::vector<std::map<int, std::vector<std::vector<int> > > > proc_x20bool(py::array_t<bool> input){
    auto data = input.unchecked<3>();
    std::vector<std::map<int, std::vector<std::vector<int> > > > results(3);
    for (py::ssize_t cat = 0; cat < 3; ++cat){
        for (py::ssize_t row = 0; row < data.shape(0); ++row){
            bool flag = false;
            int start = -1;
            for (py::ssize_t col = 0; col < data.shape(1); ++col){
                if (data(row, col, cat)){
                    if (!flag) {
                        flag = true;
                        start = col;
                    }
                } else {
                    if (flag) {
                        flag = false;
                        for (int scale_f=0; scale_f<20; ++scale_f){
                            results[cat][20*row+scale_f].push_back(std::vector<int>{20*start, 20*(int)(col) - 1});
                        }
                    }
                }
            }
            if (flag) {
                for (int scale_f=0; scale_f<20; ++scale_f){
                    results[cat][20*row+scale_f].push_back(std::vector<int>{20*start, 20*(int)(data.shape(1)) - 1});
                }
            }
        }
    }
    return results;
}

PYBIND11_MODULE(signate131, m){
    m.doc() = "signate131 postprocess implementations";
    m.def("proc", &proc, "naive");
    m.def("proc2", &proc2, "x20 (legacy)");
    m.def("proc_x20", &proc_x20, "x20 rename");
    m.def("proc_x20bool", &proc_x20bool, "x20 bool");
}
