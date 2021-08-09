#include <iostream>
#include <string> //std::cinを使用
#include <cstdio>
#include <vector>
#include <fstream>

int main(int argc, char* argv[]) {
	if (argc < 2){
       std::cerr << "argc: " << argc << "should be 2";
       return 1;
	}

	FILE *gid;
	gid = popen("/usr/bin/gnuplot", "w");
	if (gid == NULL) {
		std::cerr << "check gnuplot path";
		return -1;
	}


	fprintf(gid, "set terminal png\n");//gnuplotのグラフを保存する際の拡張子の指定
	fprintf(gid, "set output 'graph.png'\n");
	fprintf(gid, "plot './uv.txt' with dots");
	pclose(gid);
	return 0;
}


/*
// #include <iostream>
// #include <cstdio> 
// using namespace std; 

// int main(int argc, char* argv[]) {
// 	if (argc < 2){
//        std::cerr << "argc: " << argc << "should be 2";
//        return 1;
//    FILE *fp;

// 	fp = _popen("/usr/bin/gnuplot", "w");
// 	if (fp == NULL) return -1; 


// 	fprintf(gid, "set xlabel \"x\n");
// 	fprintf(gid, "set ylabel \"sin\n");

// 	// fprintf(gid, "set xrange [-10:10]\n"); 
// 	// fprintf(gid, "set yrange [-1:1]\n");

//    fprintf(gid, "plot sin(x);\n");

// 	//guplotの後処理
// 	fprintf(gid, "e\n");
// 	fflush(gid);
// 	fprintf(gid, "pause mouse\n");
// 	fflush(gid);
// 	_pclose(gid);
// 	return 0;
// }
*/

/*
// https://baseball-y-programming.com/c-plus-plus-gnuplot-graph/
#include <iostream>
#include <string> //std::cinを使用
#include <cstdio>
#include <vector>
#include <fstream>

struct Function
{
	// int x;
	// int y;
	float x;
	float y;
};



int main(int argc, char* argv[]) {
	if (argc < 2){
       std::cerr << "argc: " << argc << "should be 2";
       return 1;
	}
	std::vector<struct Function>all_function;
	
	std::string TextFileName = argv[1];
	// std::cin >> TextFileName;
	

	std::ifstream input_file;
	input_file.open(TextFileName);

	int i = 0;
	while (1)
	{
		if (!input_file.eof())
		{
			std::cout << i << std::endl;
			i++;
			struct Function function;
			input_file >> function.x;
			input_file >> function.y;

			all_function.push_back(function);
		}
		else
		{
			input_file.close();

			break;
		}
	}

	// input_file.close();

	
	



	FILE *gid;
	gid = popen("/usr/bin/gnuplot", "w");
	if (gid == NULL) {
		std::cerr << "gnuplot path";
		return -1;
	}


	fprintf(gid, "set terminal png\n");//gnuplotのグラフを保存する際の拡張子の指定
	fprintf(gid, "set output 'graph_.png'\n");
	
	// fprintf(gid, "plot y=x with dots");
	// for (int i = 0; i < (int)all_function.size(); i++)
	// {
	// 	// fprintf(gid, "%d\t%d\n", all_function[i].x, all_function[i].y);
	// 	fprintf(gid, "%f\t%f\n", all_function[i].x, all_function[i].y);
	// }

	fprintf(gid, "plot './uv.txt' with dots");




	// fprintf(gid, "e\n");
	// fflush(gid);
	// fprintf(gid, "pause mouse\n");
	// fflush(gid);
	pclose(gid);


	// 今回は必要ない
	// all_function.clear();     all_function.shrink_to_fit();



	return 0;
}*/