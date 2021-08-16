#include <iostream>
#include <unordered_map>
#include <opencv2/opencv.hpp>
#include "f_load.h"

 
int main (int argc, char* argv[])
{
    if (argc < 2){
        std::cerr << "argc: " << argc << "should be 2";
        return 1;
    }
    const char *filename = argv[1];// "rgb.txt"; // tf_stamp.txt
    
    std::vector<std::string> vec_stamp;
    std::unordered_map<std::string, cv::Mat> hash_Rwc, hash_twc;// cv::Mat R = hash_R["012345"(=vec_stamp[i])]
    std::string imgname;            
    

    file_loader(filename, vec_stamp, hash_Rwc, hash_twc, imgname);

    cv::Mat src_cpu, Rwc, twc;
    // for (int i = 0; i < vec_stamp.size(); i++){
    for (int i = 0; i < 2; i++){
        try {
            src_cpu = cv::imread(imgname);
            if (src_cpu.empty()) {
                std::cout << "failed to load image." << std::endl;
                return 1;
            }
            // cv::resize(src_cpu, src_cpu, cv::Size(width, height));//fixed_img.size());
            // cv::resize(src_cpu, src_cpu, cv::Size(), height/src_cpu.cols , width/src_cpu.rows);
            // std::cout << src_cpu.type();// element type 16 = CV_8UC3// https://koshinran.hateblo.jp/entry/2017/10/30/200250
            src_cpu.convertTo(src_cpu, CV_32F);// CV_8UC3 -> CV_32FC3
            // std::cout << src_cpu.isContinuous();
        }
        catch(const cv::Exception& ex)
        {
            std::cout << "Error: " << ex.what() << std::endl;
        }
        Rwc = hash_Rwc[vec_stamp[i]];
        twc = hash_twc[vec_stamp[i]];
    }
    std::cout << "Rwc: " << Rwc << std::endl;
    std::cout << "twc: " << twc << std::endl;

    
    return 0;
}

