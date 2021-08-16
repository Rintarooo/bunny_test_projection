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


void file_loader (const char*,
	std::vector<std::string>&, 
	std::unordered_map<std::string, cv::Mat>&, 
	std::unordered_map<std::string, cv::Mat>&,
	std::string&);

#endif