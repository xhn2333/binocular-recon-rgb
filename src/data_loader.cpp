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

DataLoader::DataLoader(string path) {
    this->imgL = cv::imread(path + "im0.png");
    this->imgR = cv::imread(path + "im1.png");
    this->load_para(path);
}

void DataLoader::load_para(string path){
    ifstream f;
    f.open(path + "calib.txt");
    if (!f.is_open()){
        cout << "[ERROR]: Open param file failed!" << endl;
    }
    double ins[3][3];
    string buf;
    vector<string> vStr;
    getline(f, buf);

    // cam0 instinct
    boost::split(vStr, buf, boost::is_any_of("=[] ;"), boost::token_compress_on);
    for( vector<string>::iterator it = vStr.begin() + 1; it != vStr.end(); ++ it ){
        ins[(it - vStr.begin() - 1) / 3][(it - vStr.begin() - 1) % 3] = stringToNum<double>(*it);
    }
    this->insL = cv::Mat(3, 3, CV_64F, ins);

    // cam1 instinct
    getline(f, buf);
    boost::split(vStr, buf, boost::is_any_of("=[] ;"), boost::token_compress_on);
    for( vector<string>::iterator it = vStr.begin() + 1; it != vStr.end(); ++ it )
        ins[(it - vStr.begin() - 1) / 3][(it - vStr.begin() - 1) % 3] = stringToNum<double>(*it);
    this->insR = cv::Mat(3, 3, CV_64F, ins);

    // doffs
    getline(f, buf);
    boost::split(vStr, buf, boost::is_any_of("=[] ;"), boost::token_compress_on);
    this->doffs = stringToNum<double>(vStr[1]);

    // baseline
    getline(f, buf);
    boost::split(vStr, buf, boost::is_any_of("=[] ;"), boost::token_compress_on);
    this->baseline = stringToNum<double>(vStr[1]);

    // height
    getline(f, buf);
    boost::split(vStr, buf, boost::is_any_of("=[] ;"), boost::token_compress_on);
    this->height = stringToNum<int>(vStr[1]);

    // width
    getline(f, buf);
    boost::split(vStr, buf, boost::is_any_of("=[] ;"), boost::token_compress_on);
    this->width = stringToNum<int>(vStr[1]);

    // ndisp
    getline(f, buf);
    boost::split(vStr, buf, boost::is_any_of("=[] ;"), boost::token_compress_on);
    this->ndisp = stringToNum<int>(vStr[1]);

    // isint
    getline(f, buf);
    boost::split(vStr, buf, boost::is_any_of("=[] ;"), boost::token_compress_on);
    this->isint = stringToNum<bool>(vStr[1]);

    // vmin
    getline(f, buf);
    boost::split(vStr, buf, boost::is_any_of("=[] ;"), boost::token_compress_on);
    this->vmin = stringToNum<double>(vStr[1]);

    // vmax
    getline(f, buf);
    boost::split(vStr, buf, boost::is_any_of("=[] ;"), boost::token_compress_on);
    this->vmax = stringToNum<double>(vStr[1]);

    // dyavg
    getline(f, buf);
    boost::split(vStr, buf, boost::is_any_of("=[] ;"), boost::token_compress_on);
    this->dyavg = stringToNum<double>(vStr[1]);

    // dyavg
    getline(f, buf);
    boost::split(vStr, buf, boost::is_any_of("=[] ;"), boost::token_compress_on);
    this->dymax = stringToNum<double>(vStr[1]);
}