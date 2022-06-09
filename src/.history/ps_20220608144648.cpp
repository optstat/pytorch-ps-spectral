#include <torch/extension.h>
#include <iostream>
#include "polylib.hpp"
/**
 * @brief Code follows the pattern defined here
 * https://github.com/pytorch/extension-cpp
 * 
 * @param np
 * @param alpha
 * @param beta
 * @return torch::Tensor 
 */
torch::Tensor zgj(int np, torch::Scalar alpha, torch::Scalar beta) {
    torch::Tensor zs = torch::zeros(np);
    torch::Tensor ws = torch::zeros(np);
    std::vector<double> vzs(np), vws(np);
    zwgj    (&vzs[0], &vws[0], np , alpha , beta);
    for ( int i=0; i < np; i++) {
        zs[i]=vzs[i];
        ws[i]=vws[i];
    }
}
torch::Tensor d_sigmoid(torch::Tensor z) {
  auto s = torch::sigmoid(z);
  return (1 - s) * s;
}

PYBIND11_MODULE(TORCH_EXTENSION_NAME, m) {
  m.def("zwgj", &zwgj, "zwgj");
}