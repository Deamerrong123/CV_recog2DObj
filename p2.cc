// Qizhao Rong
// p1.cc
// 

#include "image.h"
#include <cstdio>
#include <iostream>
#include <string>

using namespace std;
using namespace ComputerVisionProjects;

void print2DArr(int** arr){
  for (size_t i = 0 ; i < sizeof(arr); ++i){
    for (size_t j = 0; j < sizeof(arr[i]); ++j)
      printf("arr[%ld][%ld] = %d",i,j,arr[i][j]);
  }
}

bool SeqLablingAlgo(Image* an_image){
  const int n_rows = an_image->num_rows();
  const int n_cols = an_image->num_columns();

  // allocates 2-D array for labeling.
  // labels the 
  int** labels;
  labels = new int*[n_rows];
  for(size_t i = 0; i < n_rows ; ++i)
    labels[i] = new int[n_cols];

  return false;
}

int
main(int argc, char **argv){
  
  if (argc!=3) {
    printf("Usage: %s file1 file2\n", argv[0]);
    return 0;
  }
  const string input_bin_img(argv[1]);
  const string output_img(argv[2]);

  Image an_image;
  if (!ReadImage(input_bin_img, &an_image)) {
    cout <<"Can't open file " << input_bin_img << endl;
    return 0;
  }

  SeqLablingAlgo(&an_image);



  // if (!WriteImage(output_img, an_image)){
  //   cout << "Can't write to file " << output_file << endl;
  //   return 0;
  // }
  return 0;
}
