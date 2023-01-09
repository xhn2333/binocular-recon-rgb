#include <opencv2/opencv.hpp>
#include <string>

using namespace std;

class Data {
   public:
    cv::Mat *imgL, *imgR;
    cv::Mat *insL, *insR;
    cv::Mat *depth;
    double doffs;
    double baseline;
    int width;
    int height;
    int ndisp;
    bool isint;
    double vmin;
    double vmax;
    double dyavg;
    double dymax;
    

    Data();
    ~Data();

   private:
};

class DataLoader {
   public:
    DataLoader(std::string path, Data& args);

   private:
    void load_img(string path, Data& args);
    void load_para(string path, Data& args);
    void load_gt(string path, Data& args);
};
