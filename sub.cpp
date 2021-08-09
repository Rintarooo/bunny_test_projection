#include <iostream>
// opencv
#include <opencv2/opencv.hpp>

#include "f_load.h"
// #include "CostVolume.h"
#include <unordered_map>
 

void getRcw_fromRwc(const cv::Mat &Rwc, const cv::Mat &twc,
    cv::Mat &Rcw, cv::Mat &tcw)
{
    Rcw =  Rwc.t();// Rcw = Rwc^-1, Rwc is rotation matrix from camera frame to world frame.
    tcw = -Rwc.t()*twc;// slide 28/80. https://www.slideshare.net/SSII_Slides/ssii2019ts3-149136612/28
    // tcw = -Rcw*twc;
}

void getP_fromK_Rcw(const cv::Mat &K, const cv::Mat &Rcw, const cv::Mat &tcw, 
    cv::Mat &P)
{
    cv::Mat Rtcw = (cv::Mat_<float>(3,4) <<
           Rcw.at<float>(0,0), Rcw.at<float>(0,1), Rcw.at<float>(0,2), tcw.at<float>(0),
           Rcw.at<float>(1,0), Rcw.at<float>(1,1), Rcw.at<float>(1,2), tcw.at<float>(1),
           Rcw.at<float>(2,0), Rcw.at<float>(2,1), Rcw.at<float>(2,2), tcw.at<float>(2));
    P = K * Rtcw;    
}

// void getP_fromRwc(const cv::Mat &K, const cv::Mat &Rwc, const cv::Mat &twc, 
//     cv::Mat &P)
// {
//     cv::Mat Rtcw = (cv::Mat_<float>(3,4) <<
//            Rcw.at<float>(0,0), Rcw.at<float>(0,1), Rcw.at<float>(0,2), tcw.at<float>(0),
//            Rcw.at<float>(1,0), Rcw.at<float>(1,1), Rcw.at<float>(1,2), tcw.at<float>(1),
//            Rcw.at<float>(2,0), Rcw.at<float>(2,1), Rcw.at<float>(2,2), tcw.at<float>(2));
//     P = K * Rtwc.inv();    
// }

int main (int argc, char* argv[])
{
    // if (argc < 3){
    //     std::cerr << "argc: " << argc << "should be 3";
    //     return 1;
    // }
    // const char *filename_pose = "tf_stamp.txt";
    // const char *filename_pose = "SfM_quality_evaluation/p11_tf.txt";// argv[1];
    const char *filename_pcl = "model_house_oxford/house.p3d";// argv[2]
    // const char *filename_pcl = "bunny/data/bun090.ply";
    const char *filename_write = "uv.txt";
    std::vector<cv::Mat> vec_Rwc, vec_twc;
    std::vector<std::vector<float>> vec_vec_pcl;
    // int width, height;
    // float fx, fy, cx, cy;
    
    // if (std::string(filename_pose) == "tf_stamp.txt"){
    //     width = 640;
    //     height = 480;
    //     fx = 525;
    //     fy = 525;
    //     cx = 319.5;
    //     cy = 239.5;    
    // }
    // else if (std::string(filename_pose) == "SfM_quality_evaluation/p11_tf.txt"){
    //     width = 3072;// 480;// 640;// 480;// 3072
    //     height = 2048;//320;// 480;// 320;// 2048
    //     fx = 2759.48*width/3072.;// 2759.48;// 
    //     fy = 2764.16*height/2048.;// 2764.16;// 2764.16*height/2048.;
    //     cx = 1520.69*width/3072.;// 1520.69;// 1520.69*width/3072.;
    //     cy = 1006.81*height/2048.;// 1006.81;// 1006.81*height/2048.;
    
    // }

    // pose_loader(filename_pose, vec_Rwc, vec_twc);
    pcl_loader(filename_pcl, vec_vec_pcl);

    // cv::Mat K = (cv::Mat_<float>(3,3) <<  fx,  0.0,  cx,
    //                                     0.0,   fy,  cy,
    //                                     0.0,  0.0, 1.0);
    // std::cout << "K:\n" << K << std::endl;
    
//     cv::Mat P = (cv::Mat_<float>(3,4) <<
//         -667.1324398703851557, 15.186601706999681483, -399.12216996267011382, -64.171047371437467177, 
// 0.26127780106302650465, -664.13069781367391897, -289.01467806003762462, -0.76296166656404640349, 
// -0.00013667887261007119113, 0.034010281383445604975, -1.0006416157197026706, 0.016977709775627819466);
    // cv::Mat P = (cv::Mat_<float>(3,4) <<
    //     1,0,0,0,
    //     0,1,0,0,
    //     0,0,1,-10);
    cv::Mat P = (cv::Mat_<float>(3,4) <<
 -45.052833811570238254, 37.811995428208618364, -187.34443805154967322, -525.78509187114605083, 
2.4743472067794698432, -168.20074865914810403, -77.438692252834272267 -24.77656437148394275,
0.17808589029664004255, -0.029790410686014245217, -0.19498212301599307517, 0.32216224820120575867); 

    std::cout << "P: \n" << P << std::endl;
 
    // int k = 0;
    for (int k = 0; k < vec_vec_pcl.size(); k++){
        std::vector<float> vec_pcl = vec_vec_pcl[k];
        float xw, yw, zw;
        // std::cout << vec_pcl.size();
        xw = vec_pcl[0];
        yw = vec_pcl[1];
        zw = vec_pcl[2];
        // std::cout << "xw: " << xw << ", yw: " << yw << ", zw" << zw << std::endl;
        cv::Mat pcl = (cv::Mat_<float>(4,1) <<  xw,
                                                yw,
                                                zw,
                                                1);
        cv::Mat uv = P * pcl;
        // cv::Mat uv = P * pcl;
        std::cout << "homo uv: \n" << uv << std::endl;
        float scale = 1/uv.at<float>(2,0);
        // uv = scale * uv;// normalize, devide by scale
        std::cout << "pcl ==> uv\npcl: \n" << pcl << "\nuv: \n" << uv << std::endl;
        uv_writer(filename_write, uv);
    }
    // float u, v;
    // u = uv.at<float>(0,0);
    // v = uv.at<float>(1,0);
    // std::cout << "u: " << u << ", v: " << v << std::endl;
    // std::cout << "u: " << u/uv.at<float>(2,0) << ", v: " << v/uv.at<float>(2,0) << std::endl;
    // }

    // std::cout << "1/zw * P * pcl: " << 1/zw * P * pcl << std::endl;
    return 0;
}

