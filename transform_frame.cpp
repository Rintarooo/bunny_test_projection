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

void getTcw(const cv::Mat &Rcw, const cv::Mat &tcw, cv::Mat &Tcw){
        Tcw = (cv::Mat_<float>(4,4) <<
           Rcw.at<float>(0,0), Rcw.at<float>(0,1), Rcw.at<float>(0,2), tcw.at<float>(0),
           Rcw.at<float>(1,0), Rcw.at<float>(1,1), Rcw.at<float>(1,2), tcw.at<float>(1),
           Rcw.at<float>(2,0), Rcw.at<float>(2,1), Rcw.at<float>(2,2), tcw.at<float>(2),
           0,0,0,1);
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
    const char *filename_pcl = "bunny/data/bun000.xyz";
    // const char *filename_pcl = "bunny/reconstruction/bun_zipper.ply";
    
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
        
    // float* Kptr = (float*)K.data;// Mat.data returns uchar*, so cast into float*
    // for (int i = 0; i < K.total(); i++){
    //     std::cout << Kptr[i] << std::endl;
    // }
    std::cout << "K:\n" << K << std::endl;
    
    int i = 0;//10;//2;//1;
    // for (int i = 0; i < 9; i++){
    cv::Mat Rwr, twr, Rrw, trw, P, Trw;
    Rwr = vec_Rwc[i];
    twr = vec_twc[i];


    i++;
    cv::Mat Rwm, twm, Rmw, tmw, P_m, Tmw;
    Rwm = vec_Rwc[i];
    twm = vec_twc[i];
    
    

    // cv::Mat vec01 = (cv::Mat_<float>(3,1) <<  0,
    //                                           0,
    //                                           1);
    // std::cout << "camera z axis: " << Rwc*vec01 << std::endl;
    
    // Rwc = cv::Mat::eye(3, 3, CV_32FC1);
    // twc = cv::Mat::zeros(3, 1, CV_32FC1);


    // ref frame
    getRcw_fromRwc(Rwr, twr, Rrw, trw);
    getP_fromK_Rcw(K, Rrw, trw, P);
    getTcw(Rrw, trw, Trw);

    // m frame
    getRcw_fromRwc(Rwm, twm, Rmw, tmw);
    getP_fromK_Rcw(K, Rmw, tmw, P_m);
    getTcw(Rmw, tmw, Tmw);
    
    // Tmr: ref frame --> m frame
    cv::Mat Tmr = Tmw * Trw.inv();


    // std::cout << "Rcw:\n" << Rcw << "\ntcw:\n" << tcw << std::endl;
    std::cout << "P: \n" << P << std::endl;
    std::cout << "P_m: \n" << P_m << std::endl;
     
   

    // int k = 0;
    for (int k = 0; k < vec_vec_pcl.size(); k++){
    // for (int k = 25; k < 28; k++){
    // for (int k = 0; k < 20; k++){
        std::cout << "k: " << k << std::endl;
        std::vector<float> vec_pcl = vec_vec_pcl[k];
        float xw, yw, zw;
        xw = vec_pcl[0];
        yw = vec_pcl[1];
        zw = vec_pcl[2];
        std::cout << "xw: " << xw << ", yw: " << yw << ", zw" << zw << std::endl;
        
        cv::Mat pcl = (cv::Mat_<float>(4,1) <<  xw,
                                                yw,
                                                zw,
                                                1);
        cv::Mat uv =  P * pcl;
        std::cout << "homogenous uv: " << uv << std::endl;
        float scale = 1/uv.at<float>(2,0);
        uv = scale * uv;// normalize, devide by scale
        

        std::cout << "pcl ==> uv\npcl: \n" << pcl << "\nuv: \n" << uv << std::endl;
        // uv_writer(filename_write, uv);


        cv::Mat camera_xyz_ref = 1/scale * K.inv() * uv;// 2D->3D(camera frame. not world frame)
        std::cout << "camera_xyz: " << camera_xyz_ref << std::endl;
        float xr,yr,zr;
        xr = camera_xyz_ref.at<float>(0,0);
        yr = camera_xyz_ref.at<float>(1,0);
        zr = camera_xyz_ref.at<float>(2,0);
        cv::Mat camera_xyz_hom = (cv::Mat_<float>(4,1) <<  xr,
                                                yr,
                                                zr,
                                                1);
        cv::Mat camera_xyz_m_hom = Tmr*camera_xyz_hom;
        
        std::cout << "camera_xyz_m_hom: " << camera_xyz_m_hom << std::endl;
        // cv::Mat world_xyz = (cv::Mat_<float>(3,1) <<  xw,
        //                                         yw,
        //                                         zw);
        // std::cout << "camera_xyz_m_debug: " << Rmw * world_xyz + tmw << std::endl;
        // std::cout << "camera_xyz ref debug: " << Rrw * world_xyz + trw<< std::endl;
        
        
        float xm,ym,zm;
        xm = camera_xyz_m_hom.at<float>(0,0);
        ym = camera_xyz_m_hom.at<float>(1,0);
        zm = camera_xyz_m_hom.at<float>(2,0);
        cv::Mat camera_xyz_m = (cv::Mat_<float>(3,1) <<  xm,
                                                ym,
                                                zm);

        cv::Mat uv_m = 1/zm * K * camera_xyz_m;// 1/zm is normalize

        std::cout << "uv_m: " << uv_m << std::endl;
        uv_writer(filename_write, uv_m);
        
    }
    return 0;
}

