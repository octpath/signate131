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

// proc2 with scale
std::vector<std::map<int, std::vector<std::vector<int> > > > proc2_with_scale(py::array_t<float> input, int scale){
    auto data = input.unchecked<3>();
    std::vector<std::map<int, std::vector<std::vector<int> > > > results(3);
    for (py::ssize_t cat = 0; cat < 3; ++cat){
        for (py::ssize_t row = 0; row < data.shape(0); ++row){
            bool flag = false;
            int start = -1;
            for (py::ssize_t col = 0; col < data.shape(1); ++col){
                auto ref_val = data(row, col, cat);
                if ((ref_val >= 0.5) && (!flag)) {
                    flag = true;
                    start = col;
                } 
                else if ((ref_val < 0.5) && (flag)) {
                    flag = false;
                    for (int scale_f = 0; scale_f < scale; ++scale_f){
                        results[cat][scale * row + scale_f].push_back(std::vector<int>{scale * start, scale * (int)(col) - 1});
                    }
                }
            }
            if (flag) {
                for (int scale_f = 0; scale_f < scale; ++scale_f){
                    results[cat][scale * row + scale_f].push_back(std::vector<int>{scale * start, scale * (int)(data.shape(1)) - 1});
                }
            }
        }
    }
    return results;
}

// proc3
std::vector<std::map<int, std::vector<std::vector<int> > > > proc3(py::array_t<float> input){
    auto data = input.unchecked<3>();
    std::vector<std::map<int, std::vector<std::vector<int> > > > results(3);
    for (py::ssize_t cat = 0; cat < 3; ++cat){
        for (py::ssize_t row = 0; row < data.shape(0); ++row){
            bool flag = false;
            int start = -1;
            for (py::ssize_t col = 0; col < data.shape(1); ++col){
                auto ref_val = data(row, col, cat);
                if ((ref_val >= 0.5) && (!flag)) {
                    flag = true;
                    start = col;
                } 
                else if ((ref_val < 0.5) && (flag)) {
                    flag = false;
                    for (int scale_f = 0; scale_f < 20; ++scale_f){
                        results[cat][20 * row + scale_f].push_back(std::vector<int>{20 * start, 20 * (int)(col) - 1});
                    }
                }
            }
            if (flag) {
                for (int scale_f = 0; scale_f < 20; ++scale_f){
                    results[cat][20 * row + scale_f].push_back(std::vector<int>{20 * start, 20 * (int)(data.shape(1)) - 1});
                }
            }
        }
    }
    return results;
}


PYBIND11_MODULE(signate131, m){
    m.doc() = "signate131 postprocess implementations";
    m.def("proc", &proc, "naive");
    m.def("proc2", &proc2, "x20");
    m.def("proc2_with_scale", &proc2_with_scale, "with scale");
    m.def("proc3", &proc3, "x20");
}
