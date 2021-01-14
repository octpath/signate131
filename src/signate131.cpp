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

// legacy
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

// x30
std::vector<std::map<int, std::vector<std::vector<int> > > > proc_x30(py::array_t<float> input){
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
                        for (int scale_f=0; scale_f<30; ++scale_f){
                            results[cat][30*row+scale_f].push_back(std::vector<int>{30*start, 30*(int)(col) - 1});
                        }
                    }
                }
            }
            if (flag) {
                for (int scale_f=0; scale_f<30; ++scale_f){
                    results[cat][30*row+scale_f].push_back(std::vector<int>{30*start, 30*(int)(data.shape(1)) - 1});
                }
            }
        }
    }
    return results;
}

// x20 each
std::map<int, std::vector<std::vector<int> > > proc_x20each(py::array_t<float> input){
    auto data = input.unchecked<2>();
    std::map<int, std::vector<std::vector<int> > > results;
    for (py::ssize_t row = 0; row < data.shape(0); ++row){
        bool flag = false;
        int start = -1;
        for (py::ssize_t col = 0; col < data.shape(1); ++col){
            if (data(row, col) >= 0.5){
                if (!flag) {
                    flag = true;
                    start = col;
                }
            } else {
                if (flag) {
                    flag = false;
                    for (int scale_f=0; scale_f<20; ++scale_f){
                        results[20*row+scale_f].push_back(std::vector<int>{20*start, 20*(int)(col) - 1});
                    }
                }
            }
        }
        if (flag) {
            for (int scale_f=0; scale_f<20; ++scale_f){
                results[20*row+scale_f].push_back(std::vector<int>{20*start, 20*(int)(data.shape(1)) - 1});
            }
        }
    }
    return results;
}

// x30 each
std::map<int, std::vector<std::vector<int> > > proc_x30each(py::array_t<float> input){
    auto data = input.unchecked<2>();
    std::map<int, std::vector<std::vector<int> > > results;
    for (py::ssize_t row = 0; row < data.shape(0); ++row){
        bool flag = false;
        int start = -1;
        for (py::ssize_t col = 0; col < data.shape(1); ++col){
            if (data(row, col) >= 0.5){
                if (!flag) {
                    flag = true;
                    start = col;
                }
            } else {
                if (flag) {
                    flag = false;
                    for (int scale_f=0; scale_f<30; ++scale_f){
                        results[30*row+scale_f].push_back(std::vector<int>{30*start, 30*(int)(col) - 1});
                    }
                }
            }
        }
        if (flag) {
            for (int scale_f=0; scale_f<30; ++scale_f){
                results[30*row+scale_f].push_back(std::vector<int>{30*start, 30*(int)(data.shape(1)) - 1});
            }
        }
    }
    return results;
}

// x20 non_negative
std::vector<std::map<int, std::vector<std::vector<int> > > > proc_x20_non_negative(py::array_t<float> input){
    auto data = input.unchecked<3>();
    std::vector<std::map<int, std::vector<std::vector<int> > > > results(3);
    for (py::ssize_t cat = 0; cat < 3; ++cat){
        for (py::ssize_t row = 0; row < data.shape(0); ++row){
            bool flag = false;
            int start = -1;
            for (py::ssize_t col = 0; col < data.shape(1); ++col){
                if (data(row, col, cat) >= 0.){
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

// x30 non_negative
std::vector<std::map<int, std::vector<std::vector<int> > > > proc_x30_non_negative(py::array_t<float> input){
    auto data = input.unchecked<3>();
    std::vector<std::map<int, std::vector<std::vector<int> > > > results(3);
    for (py::ssize_t cat = 0; cat < 3; ++cat){
        for (py::ssize_t row = 0; row < data.shape(0); ++row){
            bool flag = false;
            int start = -1;
            for (py::ssize_t col = 0; col < data.shape(1); ++col){
                if (data(row, col, cat) >= 0.){
                    if (!flag) {
                        flag = true;
                        start = col;
                    }
                } else {
                    if (flag) {
                        flag = false;
                        for (int scale_f=0; scale_f<30; ++scale_f){
                            results[cat][30*row+scale_f].push_back(std::vector<int>{30*start, 30*(int)(col) - 1});
                        }
                    }
                }
            }
            if (flag) {
                for (int scale_f=0; scale_f<30; ++scale_f){
                    results[cat][30*row+scale_f].push_back(std::vector<int>{30*start, 30*(int)(data.shape(1)) - 1});
                }
            }
        }
    }
    return results;
}

// x15 non_negative
std::vector<std::map<int, std::vector<std::vector<int> > > > proc_x15_non_negative(py::array_t<float> input){
    auto data = input.unchecked<3>();
    std::vector<std::map<int, std::vector<std::vector<int> > > > results(3);
    for (py::ssize_t cat = 0; cat < 3; ++cat){
        for (py::ssize_t row = 0; row < data.shape(0); ++row){
            bool flag = false;
            int start = -1;
            for (py::ssize_t col = 0; col < data.shape(1); ++col){
                if (data(row, col, cat) >= 0.){
                    if (!flag) {
                        flag = true;
                        start = col;
                    }
                } else {
                    if (flag) {
                        flag = false;
                        for (int scale_f=0; scale_f<15; ++scale_f){
                            results[cat][15*row+scale_f].push_back(std::vector<int>{15*start, 15*(int)(col) - 1});
                        }
                    }
                }
            }
            if (flag) {
                for (int scale_f=0; scale_f<15; ++scale_f){
                    results[cat][15*row+scale_f].push_back(std::vector<int>{15*start, 15*(int)(data.shape(1)) - 1});
                }
            }
        }
    }
    return results;
}

PYBIND11_MODULE(signate131, m){
    m.doc() = "signate131 postprocess implementations";
    m.def("proc", &proc, "naive");
    m.def("proc2", &proc2, "(legacy)");
    m.def("proc_x20", &proc_x20, "x20");
    m.def("proc_x20each", &proc_x20each, "x20 each");
    m.def("proc_x20_non_negative", &proc_x20_non_negative, "x20 non negative (for sigmoid logits)");
    m.def("proc_x30", &proc_x30, "x30");
    m.def("proc_x30each", &proc_x30each, "x30 each");
    m.def("proc_x30_non_negative", &proc_x30_non_negative, "x30 non negative (for sigmoid logits)");
    m.def("proc_x15_non_negative", &proc_x15_non_negative, "x15 non negative (for sigmoid logits)");
}
