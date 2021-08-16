#include "f_load.h"

void pose_loader (const char *filename_pose,
	std::vector<cv::Mat> &vec_R, 
	std::vector<cv::Mat> &vec_t,
	const std::string &tum_rgbd,
	const std::string &fou_p11)
{
	std::ifstream ifs(filename_pose, std::ios::in);
	if(!ifs.is_open()){
			std::cerr << "Error, cannot open file, check argv: " << filename_pose << std::endl;
			std::exit(1); 
	}

	if (std::string(filename_pose) == tum_rgbd){
	   std::string line;
	   while (std::getline(ifs, line)){
	   	// https://github.com/Scoobadood/TSDF/blob/master/src/DataLoader/TUMDataLoader.cpp
	   	std::stringstream ss(line);// ss << line;
	   	std::string stamp, img_stamp, imgname;
		   float R00, R01, R02, R10, R11, R12, R20, R21, R22;//, tx, ty, tz;
		   float x,y,z,w, tx, ty, tz;
		   ss >> stamp >> tx >> ty >> tz >> x >> y >> z >> w >> img_stamp >> imgname ;
		   
	      R00 = 1 - 2 * ( y*y + z*z );
	      R01 = 2 * ( x*y - w*z);
	      R02 = 2 * ( x*z + w*y);

	      R10 = 2 * ( x*y + w*z );
	      R11 = 1 - 2 * ( x*x + z*z );
	      R12 = 2 * ( y*z - w*x );

	      R20 = 2 * ( x*z - w*y );
	      R21 = 2 * ( y*z + w*x );
	      R22 = 1 - 2 * ( x*x + y*y );


	      cv::Mat Rcw = (cv::Mat_<float>(3,3) <<
					   R00, R01, R02,
					   R10, R11, R12,
					   R20, R21, R22);
			cv::Mat tcw = (cv::Mat_<float>(3,1) <<
					   tx, ty, tz);
			vec_R.push_back(Rcw);
			vec_t.push_back(tcw);
			}
		
   }
   else if (std::string(filename_pose) == fou_p11){
	   // https://qiita.com/Reed_X1319RAY/items/098596cda78e9c1a6bad
		 std::string line;
	   // skip 2 line
	   for(int i = 0; i < 2; i++){
	   	std::getline(ifs, line);
	   }
	   while (std::getline(ifs, line)){
	   	std::stringstream ss(line);// ss << line;
	   	std::string tmp;
		   float R00, R01, R02, R10, R11, R12, R20, R21, R22, tx, ty, tz;
		   ss >> tmp >> R00 >> R01 >> R02 >> R10 >> R11 >> R12 >> R20 >> R21 >> R22 >> tx >> ty >> tz;
	      cv::Mat Rcw = (cv::Mat_<float>(3,3) <<
					   R00, R01, R02,
					   R10, R11, R12,
					   R20, R21, R22);
			cv::Mat tcw = (cv::Mat_<float>(3,1) <<
					   tx, ty, tz);
			vec_R.push_back(Rcw);
			vec_t.push_back(tcw);
		}
	}
	ifs.close();

}


void pcl_loader (const char *filename,
	std::vector<std::vector<float>> &vec_vec_pcl)
{
	// https://qiita.com/Reed_X1319RAY/items/098596cda78e9c1a6bad
	std::ifstream ifs(filename, std::ios::in);
	if(!ifs.is_open()){
		std::cerr << "Error, cannot open file, check argv: " << filename << std::endl;
		std::exit(1); 
	}
   std::string line;
   // skip 24 line
   // for(int i = 0; i < 24; i++){
   // 	std::getline(ifs, line);
   // }
   while (std::getline(ifs, line)){
   	std::stringstream ss(line);// ss << line;
   	std::vector<float> vec_pcl;
   	float xw, yw, zw;
	   ss >> xw >> yw >> zw;
      vec_pcl.push_back(xw);
      vec_pcl.push_back(yw);
      vec_pcl.push_back(zw);
      vec_vec_pcl.push_back(vec_pcl);
   }
	ifs.close();
}

void uv_writer (const char *filename,
	cv::Mat &uv)
{
	std::ofstream file;
	file.open(filename, std::ios::app);
   std::string line;
   file << uv.at<float>(0,0) << " " << uv.at<float>(1,0) << std::endl;   
	file.close();
}
