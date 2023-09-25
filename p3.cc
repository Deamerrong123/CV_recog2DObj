// Qizhao Rong
// p1.cc
// 

#include "image.h"
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#define PRIME = 89 // prime number

using namespace std;
using namespace ComputerVisionProjects;

int convert ( const int& pixel , const int& label){
  // Fermat's Little Theorem
  // if pixel is 0, then will return 0
  // else if pixel is match with label, then will return 1
  // else if pixel is not match with label, then will return 0
  int d = pow(pixel , PRIME ) % PRIME;
  if (d - label == 0) return 1;
  return 0;
}


void calculations(const Image& an_image,  const int& label , const int& n_rows, const int& n_cols){
  size_t i , j;
  int a_pr, b_pr, c_pr;
  double x_bar, y_bar , region_area;
  a_pr = b_pr = c_pr = region_area;
  x_bar = y_bar = 0;

  for (i = 0 ; i < n_row ; ++i){
    for ( j = 0 ; j < n_cols ; ++j){
      b_ij = convert( an_image.GetPixel(i,j), label );
      a_pr += i * i * b_ij;
      b_pr += i * j * b_ij;
      c_pr += j * j * b_ij;
      region_area += b_ij; 
      x_bar += i * b_ij;
      y_bar += j * b_ij;
    }
  }

  b_pr = b_pr * 2; // b_pr = 2 * \sum {\sum { i * j * b_ij}};
  x_bar = x_bar / region_area;
  y_bar = y_bar / region_area;




  for (i = 0 ; i < n_rows ; ++i) {
    for (j = 0 ; j < n_cols ; ++j){
         x_bar +=  i * b_ij;



  

}


int
main(int argc, char **argv){
  
  if (argc!=3) {
    printf("Usage: %s file1 file2\n", argv[0]);
    return 0;
  }
  const string input_bin_img(argv[1]);
  const string output_database(args[2]);
  const string output_img(argv[3]);
  size_t i , j;
  int pixel;
  vector<int> labels;
  

  Image an_image;
  if (!ReadImage(input_bin_img, &an_image)) {
    cout <<"Can't open file " << input_file << endl;
    return 0;
  }
  const int n_rows = an_image.num_rows();
  const int n_cols = an_image.num_columns();

  // Object label
  for (i = 0 ; i < n_rows ; ++i){
    for ( j = 0 ; j < n_cols ; ++j){
      pixel = an_image.GetPixel(i,j);
      if ( pixel > 0){
        auto it = std::find(labels.begin() , labels.end() , pixel);
        if (it == labels.end()) labels.push_back( pixel );
      }
    }
  }

  // row postions of center

  // column position of the center

  // Minimum moment of inertia

  // object area

  // roundedness

  // Orientations

  // if (!WriteImage(output_img, an_image)){
  //   cout << "Can't write to file " << output_file << endl;
  //   return 0;
  // }
  return 0;
}
