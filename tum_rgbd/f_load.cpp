#include "f_load.h"

void file_loader (const char *filename, std::vector<std::string> &vec_stamp,
	std::unordered_map<std::string, cv::Mat> &hash_Rcw, 
	std::unordered_map<std::string, cv::Mat> &hash_tcw,
	std::string &imgname)
{
	// https://qiita.com/Reed_X1319RAY/items/098596cda78e9c1a6bad
	std::ifstream ifs(filename, std::ios::in);
	if(!ifs.is_open()){
		std::cerr << "Error, cannot open file, check argv: " << filename << std::endl;
		std::exit(1); 
	}
   std::string line;
   while (std::getline(ifs, line)){
   	// https://github.com/Scoobadood/TSDF/blob/master/src/DataLoader/TUMDataLoader.cpp
   	std::stringstream ss(line);// ss << line;
   	std::string stamp, img_stamp;
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
		vec_stamp.push_back(stamp);
		hash_Rcw[stamp] = Rcw;
		hash_tcw[stamp] = tcw;
	}
	ifs.close();
}

// int main(){
// 	const char *filename = "rgb.txt";
// 	std::vector<std::string> vec;
// 	file_loader (filename, vec);
// 	std::cout << vec[0] << std::endl;
// 	std::cout << vec.size() << std::endl;
//    return 0;
// }