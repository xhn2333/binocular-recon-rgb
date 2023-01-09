#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include <opencv4/opencv2/core.hpp>
#include "config.h"
#include "data_loader.h"
using namespace std;

int main(int argc, char* argv[]) {
    string path = "../config/test.json";
    Config config(path);
    config.show_config();
    Data* data = new Data();
    DataLoader dataloader("../data/Pipes-perfect/", *data);
    cv::Mat gt =
        cv::imread("../data/Pipes-perfect/disp0.pfm", cv::IMREAD_UNCHANGED);

    cv::imwrite("./depth.png", *(data->depth));
    return 0;
}