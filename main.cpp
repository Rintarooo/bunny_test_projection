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
    // tcw = cv::Mat::zeros(3, 1, CV_32FC1);// camera origin is fixed to (0,0,0) in world frame
}

void getP_fromK_Rcw(const cv::Mat &K, const cv::Mat &Rcw, const cv::Mat &tcw, 
    cv::Mat &P)
{
    cv::Mat Rtcw = (cv::Mat_<float>(3,4) <<
           Rcw.at<float>(0,0), Rcw.at<float>(0,1), Rcw.at<float>(0,2), tcw.at<float>(0),
           Rcw.at<float>(1,0), Rcw.at<float>(1,1), Rcw.at<float>(1,2), tcw.at<float>(1),
           Rcw.at<float>(2,0), Rcw.at<float>(2,1), Rcw.at<float>(2,2), tcw.at<float>(2));
    // cv::Mat Rtcw = (cv::Mat_<float>(3,4) <<
    //        1,0,0,0,
    //        0,1,0,0,
    //        0,0,1,0);
    P = K * Rtcw;
    // P = K.inv() * Rtcw;    
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
    const char *filename_pose = "SfM_quality_evaluation/p11_tf.txt";// argv[1];
    // const char *filename_pcl = "model_house_oxford/house.p3d";
    // const char *filename_pcl = "bunny/data/bun000.ply";
    const char *filename_pcl = "bunny/reconstruction/bun_zipper.ply";
    
    // const char *filename_pcl = "fou.ply";
    const char *filename_write = "uv.txt";
    // std::remove(filename_write);
    std::vector<cv::Mat> vec_Rwc, vec_twc;
    std::vector<std::vector<float>> vec_vec_pcl;
    int width, height;
    float fx, fy, cx, cy;
    
    if (std::string(filename_pose) == "tf_stamp.txt"){
        width = 640;
        height = 480;
        fx = 525;
        fy = 525;
        cx = 319.5;
        cy = 239.5;    
    }
       else if (std::string(filename_pose) == "SfM_quality_evaluation/p11_tf.txt"){
        width = 3072;// 480;// 640;// 480;// 3072
        height = 2048;//320;// 480;// 320;// 2048
        fx = 2759.48*width/3072.;// 2759.48;// 
        fy = 2764.16*height/2048.;// 2764.16;// 2764.16*height/2048.;
        cx = 1520.69*width/3072.;// 1520.69;// 1520.69*width/3072.;
        cy = 1006.81*height/2048.;// 1006.81;// 1006.81*height/2048.;
    
    }

    pose_loader(filename_pose, vec_Rwc, vec_twc);
    pcl_loader(filename_pcl, vec_vec_pcl);

    cv::Mat K = (cv::Mat_<float>(3,3) <<  fx,  0.0,  cx,
                                        0.0,   fy,  cy,
                                        0.0,  0.0, 1.0);
    // cv::Mat K = (cv::Mat_<float>(3,4) <<  fx,  0.0,  cx, 0.0,
    //                                     0.0,   fy,  cy, 0.0,
    //                                     0.0,  0.0, 0.0, 1.0);
        
    // float* Kptr = (float*)K.data;// Mat.data returns uchar*, so cast into float*
    // for (int i = 0; i < K.total(); i++){
    //     std::cout << Kptr[i] << std::endl;
    // }
    std::cout << "K:\n" << K << std::endl;
    
    int i = 0;
    // for (int i = 0; i < 9; i++){
    cv::Mat Rwc, twc, Rcw, tcw, P;
    // Rwc = vec_Rwc[i];
    // twc = vec_twc[i];

    // cv::Mat vec01 = (cv::Mat_<float>(3,1) <<  0,
    //                                           0,
    //                                           1);
    // std::cout << "camera z axis: " << Rwc*vec01 << std::endl;
    Rwc = cv::Mat::eye(3, 3, CV_32FC1);
    twc = cv::Mat::zeros(3, 1, CV_32FC1);




    getRcw_fromRwc(Rwc, twc, Rcw, tcw);
    // Rcw = vec_Rwc[i];
    // tcw = vec_twc[i];
    getP_fromK_Rcw(K, Rcw, tcw, P);

    std::cout << "Rcw:\n" << Rcw << "\ntcw:\n" << tcw << std::endl;
    std::cout << "P: \n" << P << std::endl;
    
   

    // int k = 0;
    for (int k = 0; k < vec_vec_pcl.size(); k++){
    // for (int k = 25; k < 28; k++){
    // for (int k = 0; k < 10; k++){
        std::vector<float> vec_pcl = vec_vec_pcl[k];
        float xw, yw, zw;
        // std::cout << vec_pcl.size();
        xw = vec_pcl[0];
        yw = vec_pcl[1];
        zw = vec_pcl[2];
        // xw = -0.001;//0.0002;
        // yw = 1;//0.0002;
        // zw = 10;
        
        // xw = xw/zw;
        // yw = yw/zw;
        // zw = zw/zw;
        std::cout << "xw: " << xw << ", yw: " << yw << ", zw" << zw << std::endl;
        

        cv::Mat world_xyz = (cv::Mat_<float>(3,1) <<  xw,
                                                yw,
                                                zw);
        cv::Mat camera_xyz =  Rcw * world_xyz;
        float depth_diff;
        depth_diff = 1 - zw;
        // float offset=9.6;
        // xw = xw + offset;
        // yw = yw + offset;
        // zw = zw + offset;
        camera_xyz = depth_diff + camera_xyz;
        std::cout << "camera_xyz: " << camera_xyz << std::endl;

        

        cv::Mat pcl = (cv::Mat_<float>(4,1) <<  xw,
                                                yw,
                                                zw,
                                                1);
        cv::Mat uv =  P * pcl;
        std::cout << "homogenous uv: " << uv << std::endl;
        float scale = 1/uv.at<float>(2,0);
        uv = scale * uv;// normalize, devide by scale
        
        // cv::Mat pcl = (cv::Mat_<float>(3,1) <<  xw,
        //                                         yw,
        //                                         zw);
        // cv::Mat uv;
        // cv::projectPoints(pcl, Rcw, tcw, K, 0, uv);

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

