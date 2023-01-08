#include <opencv2/opencv.hpp>
#include <string>

using namespace std;

class DataLoader {
   public:
    DataLoader(std::string path);

    cv::Mat imgL, imgR;
    cv::Mat insL, insR;
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

   private:
    void load_para(string path);

};