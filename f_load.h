#ifndef FILELOADER_H
#define FILELOADER_H
#include <iostream>
#include <string>    // string
#include <fstream>   // ifstream, ofstream
#include <sstream>   // stringstream
#include <vector>
#include <unordered_map>

// opencv
#include <opencv2/opencv.hpp>
// #include <opencv2/core/version.hpp>


void pose_loader (const char*,
	std::vector<cv::Mat>&, 
	std::vector<cv::Mat>&);

void pcl_loader (const char*,
	std::vector<std::vector<float>>&);

void uv_writer (const char *,
	cv::Mat&);

#endif