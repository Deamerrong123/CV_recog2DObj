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
  
  if (argc!=4) {
    printf("Usage: %s file1 input_threshold file2\n", argv[0]);
    return 0;
  }
  const string input_gray_img(argv[1]);
  string input_threshold(argv[2]);
  const string output_img(argv[3]);

  Image an_image;
  if (!ReadImage(input_gray_img, &an_image)) {
    cout <<"Can't open file " << input_gray_img << endl;
    return 0;
  }

  int threshold = std::stoi(input_threshold);

  if (threshold > 255) return 0;

  Image another_img(an_image);

  for (size_t i = 0; i < an_image.num_rows() ; ++i){
    for (size_t j = 0; j < an_image.num_columns();++j){
      if (an_image.GetPixel(i,j) < threshold)
        another_img.SetPixel(i,j,0);

      else{another_img.SetPixel(i,j,255);}
    }
  }
  

  // Draw a line from (0, 0) to (100, 240) having gray-value
  // 200.
  // DrawLine(0, 0, 100, 240, 200,
	 //   &an_image); 
  // 
  if (!WriteImage(output_img, another_img)){
    cout << "Can't write to file " << output_img << endl;
    return 0;
  }
  return 0;
}
