#include "f_load.h"

void pose_loader (const char *filename,
	std::vector<cv::Mat> &vec_Rcw, 
	std::vector<cv::Mat> &vec_tcw)
{
	// https://qiita.com/Reed_X1319RAY/items/098596cda78e9c1a6bad
	std::ifstream ifs(filename, std::ios::in);
	if(!ifs.is_open()){
		std::cerr << "Error, cannot open file, check argv: " << filename << std::endl;
		std::exit(1); 
	}
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
		// vec_stamp.push_back(stamp);
		vec_Rcw.push_back(Rcw);
		vec_tcw.push_back(tcw);
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
   for(int i = 0; i < 24; i++){
   	std::getline(ifs, line);
   }
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

// int main(){
// 	const char *filename = "SfM_quality_evaluation/p11_tf.txt";
// 	std::vector<std::string> vec;
// 	pose_loader (filename, vec);
// 	std::cout << vec[0] << std::endl;
// 	std::cout << vec.size() << std::endl;
//    return 0;
// }