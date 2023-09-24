// Qizhao Rong
// p1.cc
// 

#include "image.h"
#include "DisjSets.h"
#include <cstdio>
#include <iostream>
#include <string>

using namespace std;
using namespace ComputerVisionProjects;

int max_3(const int& first, const int& second, const int& third){
  return (max(first,max(second,third)));
}

void print2DArr(int**& arr,const int& n_rows,const int& n_cols){
  for (size_t i = 0 ; i < n_rows; ++i){
    for (size_t j = 0; j < n_cols; ++j){
      if (arr[i][j] > 0)
        printf("arr[%ld][%ld] = %d \t",i,j,arr[i][j]);
      }
    cout << endl;
  }
}

void Labeling(size_t i , size_t j, Image*& an_img, int**& labels,int& levels){
  int current_level;
  int pixel = an_img -> GetPixel(i,j) % 254;

  if (i + j == 0){
    current_level = levels;
  }
  else if (i == 0 && j > 0)
    current_level = labels[i][j-1];
  else if (j == 0 && i > 0)
    current_level = labels[i-1][j];


  else{
    int label1_ = labels[i-1][j-1];
    int label2_ = labels[i][j-1];
    int label3_ = labels[i-1][j];

    current_level = max_3(label1_,label2_,label3_);
    }

  if (current_level == 0) {
    current_level = levels + pixel;
    levels = current_level;
  }


  labels[i][j] = pixel * current_level;


}

bool SeqLablingAlgo(Image* an_image){
  const int n_rows = an_image->num_rows();
  const int n_cols = an_image->num_columns();
  int levels_ = 1;
  size_t i, j;

  cout << "num_rows = " << n_rows << endl;
  cout << "num_columns = " << n_cols << endl;


  // allocates 2-D array for labeling.
  // labels the 
  int** labels_ = new int*[n_rows];
  for(i = 0; i < n_rows ; ++i)
    labels_[i] = new int[n_cols];

  // print2DArr(labels_);
  cout << "\n" << endl;

  for (i = 0; i < n_rows; ++i){
    for (j = 0 ; j < n_cols ; ++j)
      Labeling(i,j,an_image,labels_,levels_);
  }

  print2DArr(labels_,n_rows,n_cols);


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
