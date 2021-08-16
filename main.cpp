#include <iostream>
#include <opencv2/opencv.hpp>

#include "f_load.h"
 

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
    if (argc < 4){
        std::cerr << "argc: " << argc << "should be 4" << std::endl;
        std::cout << argv[0] << " filename_pose filename_pcl filename_write" << std::endl;
        std::cout <<"\nexample1:\n./build/main SfM_quality_evaluation/p11_tf.txt bunny/data/bun000.xyz uv.txt" << std::endl;
        std::cout <<"example2:\n./build/main tum_rgbd/pose_rgb.txt bunny/data/bun000.xyz uv.txt" << std::endl;
        
        return 1;
    }
    const char *filename_pose =  argv[1];
    const char *filename_pcl = argv[2];//"bunny/data/bun000.xyz", "model_house_oxford/house.p3d";
    const char *filename_write = argv[3];//"uv.txt";
    // std::remove(filename_write);
    const std::string tum_rgbd = "tum_rgbd/pose_rgb.txt";
    const std::string fou_p11 = "SfM_quality_evaluation/p11_tf.txt";
    std::vector<cv::Mat> vec_R, vec_t;
    std::vector<std::vector<float>> vec_vec_pcl;
    float fx, fy, cx, cy;

    
    if (std::string(filename_pose) == tum_rgbd){
        fx = 525;
        fy = 525;
        cx = 319.5;
        cy = 239.5;
    }
    else if (std::string(filename_pose) == fou_p11){
        fx = 2759.48; 
        fy = 2764.16;
        cx = 1520.69;
        cy = 1006.81;
    }
    else{
        std::cerr << "file invalid tum_rgbd, fou_p11" << std::endl;
    }
    pcl_loader(filename_pcl, vec_vec_pcl);
    pose_loader(filename_pose, vec_R, vec_t, tum_rgbd, fou_p11);      
    
    cv::Mat K = (cv::Mat_<float>(3,3) <<  fx,  0.0,  cx,
                                        0.0,   fy,  cy,
                                        0.0,  0.0, 1.0);    
    std::cout << "K:\n" << K << std::endl;
    

    
    
    int i = 0;//10;//2;//1;
    // for (int i = 0; i < 9; i++){
    cv::Mat Rwc, twc, Rcw, tcw, P;
    if (std::string(filename_pose) == tum_rgbd){
        Rcw = vec_R[i];
        tcw = vec_t[i];
    }
    else if (std::string(filename_pose) == fou_p11){
        Rwc = vec_R[i];
        twc = vec_t[i];
        getRcw_fromRwc(Rwc, twc, Rcw, tcw);
    }
    getP_fromK_Rcw(K, Rcw, tcw, P);

    // std::cout << "Rcw:\n" << Rcw << "\ntcw:\n" << tcw << std::endl;
    std::cout << "P: \n" << P << std::endl;
    


    

    // cv::Mat vec01 = (cv::Mat_<float>(3,1) <<  0,
    //                                           0,
    //                                           1);
    // std::cout << "camera z axis: " << Rwc*vec01 << std::endl;
    
    // Rwc = cv::Mat::eye(3, 3, CV_32FC1);
    // twc = cv::Mat::zeros(3, 1, CV_32FC1);


    // int k = 0;
    for (int k = 0; k < vec_vec_pcl.size(); k++){
    // for (int k = 25; k < 28; k++){
        std::cout << "k: " << k << std::endl;
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
        // float depth_diff;
        // depth_diff = 1 - zw;
        // // float offset=9.6;
        // // xw = xw + offset;
        // // yw = yw + offset;
        // // zw = zw + offset;
        // camera_xyz = depth_diff + camera_xyz;
        std::cout << "camera_xyz: " << camera_xyz << std::endl;

        

        cv::Mat pcl = (cv::Mat_<float>(4,1) <<  xw,
                                                yw,
                                                zw,
                                                1);
        cv::Mat uv =  P * pcl;
        std::cout << "homogenous uv: " << uv << std::endl;
        float scale = 1/uv.at<float>(2,0);
        uv = scale * uv;// normalize, devide by scale
        
        std::cout << "pcl ==> uv\npcl: \n" << pcl << "\nuv: \n" << uv << std::endl;
        uv_writer(filename_write, uv);
    }
    return 0;
}

