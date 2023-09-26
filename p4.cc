// Qizhao Rong
// p4.cc
// 

#include "image.h"
#include <cstdio>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <fstream>

using namespace std;
using namespace ComputerVisionProjects;


bool isEqual(double& val1 , double &val2 , double criteria){
  if (
    sqrt((val1 - val2) * (val1 - val2)) > criteria) return false;
  return true;
}
int convert ( const int& pixel , const int& label){
  // Fermat's Little Theorem
  // if pixel is 0, then will return 0
  // else if pixel is match with label, then will return 1
  // else if pixel is not match with label, then will return 0
  // int d = pow(pixel , PRIME ) % PRIME;
  // if (d - label == 0) return 1;
  if (pixel == label) return 1;
  return 0;
}

int solveForY( const double &theta, const double &rho , const double &x_val){
  return (x_val * sin( theta ) + rho ) / cos( theta );
}
       
void calculations(const Image& an_image,  const int& label , const int& n_rows, const int& n_cols, std::vector<double>& values){
  size_t i , j;
  int a_pr, b_pr, c_pr , b_ij;
  double x_bar, y_bar , region_area , a, b ,c ;
  double theta_1, theta_2, e_min, e_max , roundedness, rho;
  a_pr = b_pr = c_pr = region_area;
  x_bar = y_bar = 0;
  values[0] = label;

  for (i = 0 ; i < n_rows ; ++i){
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
  c = c_pr - y_bar * y_bar * region_area;
  theta_1 = atan2( b , a - c) / 2.0; // theta1 in radians
  e_min = a * sin( theta_1 ) * sin( theta_1 ) - b * sin( theta_1 ) * cos( theta_1 ) + c* cos (theta_1) * cos(theta_1);
  values[3] = e_min;
  values[4] = region_area;
  theta_2 = theta_1 + M_PI / 2.0;
  e_max = a * sin( theta_2 ) * sin( theta_2 ) - b * sin( theta_2 ) * cos( theta_2 ) + c* cos (theta_2) * cos(theta_2);
  roundedness = e_min / e_max;
  values[5] = roundedness;
  rho = y_bar * cos(theta_1) - x_bar * sin( theta_1 );
  values[6] = theta_1 * 180 / M_PI;
  values[7] = rho;
}

bool ReadDatabase( const std::string& filename , std::vector<std::vector<double>>& values){

  ifstream input_f;
  string readline;
  double value;
  input_f.open( filename );

  if (!input_f.is_open()){
    cout << "Write Database: cannot open file." << endl;
    return false;
  }
  while( getline(input_f, readline) ){
    std::stringstream line (readline);
    std::vector<double> row_values;
    
    while( line >> value){
      row_values.push_back(value);
    }
    values.push_back( row_values );
  }
  
  input_f.close();
  return true;
}

void scanning ( 
               std::vector<std::vector<double>> & comparison , const  std::vector<std::vector<double>> &standard ,
               const double& epsilon , std::vector<std::vector<double>>& recognized ){
  size_t i , j;
  int score;

  for (auto row_standard : standard){
    for (auto row_testing : comparison ){
      score = 0;
      for (i = 3 ; i < 6 ; ++i){
        if (isEqual( row_testing[i] , row_standard[i] , epsilon ))
          score++;
      }
      if (score >= 2){
        recognized.push_back(row_testing);
        }
      }
    }
  cout << "sizeof recognized() --> " << recognized.size() << endl;
  }

void Drawing( Image &an_image ,const double& x_bar, const double &y_bar , const double &theta , const double &rho, const int &length){

  if (length <= 0) 
    abort();
  std::vector<int> x_vals; 
  std::vector<int> y_vals;
  int x_n , y_n;
  size_t t;
  
  x_vals.push_back( (int) x_bar);
  y_vals.push_back( (int) y_bar);

  for (t = 0 ; t < length ; ++t){
        x_n = x_vals.back() + 1; 
         x_vals.push_back(x_n);
         y_vals.push_back( solveForY( theta , rho , x_n));
       }
  //
  for ( t = 0 ; t < length ; ++t){
       x_n = x_vals.at(t);
       y_n = y_vals.at(t);
       an_image.SetPixel(x_n , y_n, 255);
       }

  // DrawLine(x_bar , y_bar , x_vals.back() , y_vals.back() , 255 , &an_image);

}


int
main(int argc, char **argv){
  
  if (argc!=4) {
    printf("Usage: %s file1 file2\n", argv[0]);
    return 0;
  }
  const string input_bin_img(argv[1]);
  const string input_database(argv[2]);
  const string output_img(argv[3]);
  std::vector<std::vector<double>> D_database;
  std::vector<std::vector<double>> D_values;
  std::vector<std::vector<double>> D_recognized;
  std::vector<int> v_labels;
  int pixel;
  size_t i , j;

  Image an_image;
  if (!ReadImage(input_bin_img , &an_image)) {
    cout <<"Can't open file " << input_bin_img << endl;
    return 0;
  }

  ReadDatabase( input_database , D_database);

  const int n_rows = an_image.num_rows();
  const int n_cols = an_image.num_columns();

  // Object label
  for (i = 0 ; i < n_rows ; ++i){
    for ( j = 0 ; j < n_cols ; ++j){
      pixel = an_image.GetPixel(i,j);
      if ( pixel > 0){
        auto it = std::find(v_labels.begin() , v_labels.end() , pixel);
        if (it == v_labels.end()) v_labels.push_back( pixel );
      }
    }
  }

  for( auto label : v_labels){
    std::vector<double> temp_vals(8);
    calculations(an_image , label , n_rows, n_cols, temp_vals);
    D_values.push_back(temp_vals);
  }

  scanning( D_values, D_database , 105 , D_recognized);

  for ( auto label : D_recognized){
    Drawing(an_image , label[1] , label[2] , label[6] * M_PI /180 , label[7] , 20);
  }
  


  if (!WriteImage(output_img, an_image)){
    cout << "Can't write to file " << output_img << endl;
    return 0;
  }
  return 0;
}
