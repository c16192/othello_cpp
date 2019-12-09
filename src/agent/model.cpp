#include "model.h"

torch::nn::Sequential Net() {
    torch::nn::Sequential model(
            // Layer 1
            torch::nn::Conv2d(torch::nn::Conv2dOptions(1, 8, /*kernel_size=*/5).padding(2).with_bias(false)),
            torch::nn::Functional(torch::leaky_relu, 0.2),
            // Layer 2
            torch::nn::Conv2d(torch::nn::Conv2dOptions(8, 8, /*kernel_size=*/5).padding(2).with_bias(false)),
            torch::nn::Functional(torch::leaky_relu, 0.2),
            // Layer 3
            torch::nn::Conv2d(torch::nn::Conv2dOptions(8, 8, /*kernel_size=*/5).padding(2).with_bias(false)),
            torch::nn::Functional(torch::leaky_relu, 0.2),
            // Layer 4
            torch::nn::Conv2d(torch::nn::Conv2dOptions(8, 1, /*kernel_size=*/5).padding(2).with_bias(false)),
            torch::nn::Functional(torch::tanh)
    );
    return model;
}
