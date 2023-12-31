// Qizhao Rong
// Due (09/26)
// p1.cc : Read a given pgm image, convert those different gray-levels into 0 or 255, and saved it to another pgm image  
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
  const string input_threshold(argv[2]);
  const string output_img(argv[3]);

  Image an_image;
  if (!ReadImage(input_gray_img, &an_image)) {
    cout <<"Can't open file " << input_gray_img << endl;
    return 0;
  }

  // convert the input_threshold into integer.
  int threshold = std::stoi(input_threshold);

  if (threshold > 255) return 0; 

  Image another_img(an_image);

  // scanning through the image
  // And convert any pixel that less than threshold into 0;
  // any pixel >= threshold then convert to 255.
  for (size_t i = 0; i < an_image.num_rows() ; ++i){
    for (size_t j = 0; j < an_image.num_columns();++j){
      if (an_image.GetPixel(i,j) < threshold)
        another_img.SetPixel(i,j,0);

      else{another_img.SetPixel(i,j,255);}
    }
  }
  
  // Save the binary-image to another pgm file.
  if (!WriteImage(output_img, another_img)){
    cout << "Can't write to file " << output_img << endl;
    return 0;
  }

  return 0;
}
