#include <opencv2/opencv.hpp>
#include <opencv4/opencv2/core.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include "config.h"
#include "data_loader.h"

using namespace std;

template <class Type>
Type stringToNum(const string str) {
    istringstream iss(str);
    Type num;
    iss >> num;
    return num;
}

Data::Data() {
    imgL = new cv::Mat(), imgR = new cv::Mat();
    insL = new cv::Mat(), insR = new cv::Mat();
    depth = new cv::Mat();
    doffs = 0;
    baseline = 0;
    width = 0;
    height = 0;
    ndisp = 0;
    isint = 0;
    vmin = 0;
    vmax = 0;
    dyavg = 0;
    dymax = 0;
}

Data::~Data(){
    delete imgL;
    delete imgR;
    delete insL;
    delete insR;
}

DataLoader::DataLoader(string path, Data& args) {
    this->load_img(path, args);
    this->load_para(path, args);
    this->load_gt(path, args);
}

void DataLoader::load_img(string path, Data& args) {
    *(args.imgL) = cv::imread(path + "im0.png").clone();
    *(args.imgR) = cv::imread(path + "im1.png").clone();
    
}

void DataLoader::load_para(string path, Data& args) {
    ifstream f;
    f.open(path + "calib.txt");
    if (!f.is_open()) {
        cout << "[ERROR]: Open param file failed!" << endl;
    }
    double ins[3][3] = {0};
    string buf;
    vector<string> vStr;
    getline(f, buf);

    // cam0 instinct
    boost::split(vStr, buf, boost::is_any_of("=[] ;"),
                 boost::token_compress_on);
    for (vector<string>::iterator it = vStr.begin() + 1; it != vStr.end();
         ++it) {
        ins[(it - vStr.begin() - 1) / 3][(it - vStr.begin() - 1) % 3] =
            stringToNum<double>(*it);
    }
    *(args.insL) = cv::Mat(3, 3, CV_64F, ins).clone();

    // cam1 instinct
    getline(f, buf);
    boost::split(vStr, buf, boost::is_any_of("=[] ;"),
                 boost::token_compress_on);
    for (vector<string>::iterator it = vStr.begin() + 1; it != vStr.end(); ++it)
        ins[(it - vStr.begin() - 1) / 3][(it - vStr.begin() - 1) % 3] =
            stringToNum<double>(*it);
    *(args.insR) = cv::Mat(3, 3, CV_64F, ins).clone();

    // doffs
    getline(f, buf);
    boost::split(vStr, buf, boost::is_any_of("=[] ;"),
                 boost::token_compress_on);
    args.doffs = stringToNum<double>(vStr[1]);

    // baseline
    getline(f, buf);
    boost::split(vStr, buf, boost::is_any_of("=[] ;"),
                 boost::token_compress_on);
    args.baseline = stringToNum<double>(vStr[1]);

    // height
    getline(f, buf);
    boost::split(vStr, buf, boost::is_any_of("=[] ;"),
                 boost::token_compress_on);
    args.height = stringToNum<int>(vStr[1]);

    // width
    getline(f, buf);
    boost::split(vStr, buf, boost::is_any_of("=[] ;"),
                 boost::token_compress_on);
    args.width = stringToNum<int>(vStr[1]);

    // ndisp
    getline(f, buf);
    boost::split(vStr, buf, boost::is_any_of("=[] ;"),
                 boost::token_compress_on);
    args.ndisp = stringToNum<int>(vStr[1]);

    // isint
    getline(f, buf);
    boost::split(vStr, buf, boost::is_any_of("=[] ;"),
                 boost::token_compress_on);
    args.isint = stringToNum<bool>(vStr[1]);

    // vmin
    getline(f, buf);
    boost::split(vStr, buf, boost::is_any_of("=[] ;"),
                 boost::token_compress_on);
    args.vmin = stringToNum<double>(vStr[1]);

    // vmax
    getline(f, buf);
    boost::split(vStr, buf, boost::is_any_of("=[] ;"),
                 boost::token_compress_on);
    args.vmax = stringToNum<double>(vStr[1]);

    // dyavg
    getline(f, buf);
    boost::split(vStr, buf, boost::is_any_of("=[] ;"),
                 boost::token_compress_on);
    args.dyavg = stringToNum<double>(vStr[1]);

    // dyavg
    getline(f, buf);
    boost::split(vStr, buf, boost::is_any_of("=[] ;"),
                 boost::token_compress_on);
    args.dymax = stringToNum<double>(vStr[1]);
}

void DataLoader::load_gt(string path, Data &args){
    cv::Mat gt =
        cv::imread(path+"disp0.pfm", cv::IMREAD_UNCHANGED);
    cv::Size shape = gt.size();
    cv::Mat depth = cv::Mat::zeros(shape, CV_64F);
    
    depth = args.baseline * args.insL->at<double>(0, 0) / (gt + args.doffs);
    cv::patchNaNs(depth, 0);
    *(args.depth) = depth.clone();
}