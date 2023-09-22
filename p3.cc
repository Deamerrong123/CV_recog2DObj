// Qizhao Rong
// p1.cc
// 

#include "image.h"
#include <cstdio>
#include <iostream>
#include <string>

using namespace std;
using namespace ComputerVisionProjects;

int
main(int argc, char **argv){
  
  if (argc!=3) {
    printf("Usage: %s file1 file2\n", argv[0]);
    return 0;
  }
  const string input_bin_img(argv[1]);
  const string output_database(args[2]);
  const string output_img(argv[3]);

  Image an_image;
  if (!ReadImage(input_gray_img, &an_image)) {
    cout <<"Can't open file " << input_file << endl;
    return 0;
  }

  // Draw a line from (0, 0) to (100, 240) having gray-value
  // 200.
  // DrawLine(0, 0, 100, 240, 200,
	 //   &an_image); 
  // 
  // if (!WriteImage(output_img, an_image)){
  //   cout << "Can't write to file " << output_file << endl;
  //   return 0;
  // }
  return 0;
}
