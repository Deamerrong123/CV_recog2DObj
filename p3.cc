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


void calculations(const Image& an_image,  const int& label , const int& n_rows, const int& n_cols, std::vector<doubld> values){
  size_t i , j;
  int a_pr, b_pr, c_pr;
  double x_bar, y_bar , region_area , a, b ,c ;
  double theta_1, theta_2, e_min, e_max , roundedness, rho;
  a_pr = b_pr = c_pr = region_area;
  x_bar = y_bar = 0;
  values[0] = label;

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
  values[1] = x_bar;

  y_bar = y_bar / region_area;
  values[2] = y_bar;

  a = a_pr - x_bar * x_bar * region_area;
  b = b_pr - 2 * x_bar * y_bar * region_area;
  c = c_pr - y_bar * y_bar * regions_area;
  theta_1 = atan2( b , a - c) / 2.0; // theta1 in radians
  e_min = a * sin( theta_1 ) * sin( theta_1 ) - b * sin( theta_1 ) * cos( theta_1 ) + c* cos (theta_1) * cos(theta_1);
  values[3] = e_min;
  values[4] = region_area;
  theta_2 = theta_1 + M_PI / 2.0;
  e_max = a * sin( theta_2 ) * sin( theta_2 ) - b * sin( theta_2 ) * cos( theta_2 ) + c* cos (theta_2) * cos(theta_2);
  roundedness = e_min / e_max;
  values[5] = roundedness;
  rho = y_bar * cos(theta_1) - x_bar * sin( theta_1 );
  values[6] = theta_1;
  values[7] = rho;
}

bool writeDataBase ( const std::string& filename , const std::vector<double>& values){
  FILE *output = fopen(filenamea,"w");
  if (output == 0){
    cout << "Write Database: cannot open file." << endl;
    return false;
  }
  
  fprintf(ouput, "%d %d %d %d %d %d %d %d", values)
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
  std::vector<int> labels;
  std::vector<std::vector<double>> values_;
  
  

  Image an_image;
  if (!ReadImage(input_bin_img, &an_image)) {
    cout <<"Can't open file " << input_fiAkkle << endl;
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

  std::vector<std::vector<doubld>> values_ ( labels.size() ,
                                            std::vector<double>(0,8)); 

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
