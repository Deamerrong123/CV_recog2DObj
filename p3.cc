// Qizhao Rong
// Due (09/26)
// p3.cc : Read a given segemented binary pgm image, 
// and computes object attributes and generates the database
// of the objects.
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

/**
 * @brief convert the matched pixed to become 1, 0 otherwise
 * 
 * @param pixel  :  const reference to int, pixel value 
 * @param label  :  const reference to int, labeled value
 * @return int   :  return 1 if pixel match with label values
 *                  return 0 otherwise.
 */
int convert ( const int& pixel , const int& label){
  // Fermat's Little Theorem
  if (pixel == label) return 1;
  return 0;
}

/**
 * @brief  solving for value of y, given the values of x. equ: x* cos (@theta) - y * sin (@theta) + jlh
 * 
 * @param theta  :  const reference to double , orientation , in radian
 * @param rho    : const ref of double, distance between origion
 * @param x_val  : const ref of double, value for input
 * @return int
 */
int solveForY( const double &theta, const double &rho , const double &x_val){
  return (x_val * sin( theta ) + rho ) / cos( theta );
}
       

/**
 * @brief  calculating these attributes valuse by giving an image object
 * 
 * @param an_image  :   const ref of an image object
 * @param label     :   const ref. of int, an distinted label valu
 * @param n_rows    :   const ref. of int, number of rows of the image
 * @param n_cols    :   const ref. of int, number of columns of the image
 * @param values    :   ref. of a 2D arrays, which contains all the attributes of each labeled obj.
 */
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
  values[6] = theta_1;
  values[7] = rho;
}

/**
 * @brief write those attribute into a databse file.
 * 
 * @param filename   :   const ref. of string, name of the file
 * @param values     :   const ref. of 2D arrays, contains the attributes of each labeled obj.
 * @return true      if the file is opened
 * @return false     otherwise
 */
bool writeDataBase ( const std::string& filename , const std::vector<std::vector<double>>& values){
  FILE *output = fopen(filename.c_str(), "w");  
  if (output == 0){
    cout << "Write Database: cannot open file." << endl;
    return false;
  }
  
  for(auto row : values){
    for (auto val : row){
      fprintf(output, "%f \t",val);
    }
    fprintf(output , "\n");
  }
  fclose(output);
  return true;
}

/**
 * @brief  drawing a line along a giving orientation , with number of steps.
 * 
 * @param an_image   :   ref. of an image obj.
 * @param x_bar      :   const ref. of double, center of row of this obj
 * @param y_bar      :   const ref. of doubld, center of col of this obj.
 * @param theta      :   const ref. of double, the angle of orientation, in radian.
 * @param rho        :   const ref. of double, the rho
 * @param length     :   const ref. of int, the number of steps for the line.
 */
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

  for ( t = 0 ; t < length ; ++t){
       x_n = x_vals.at(t);
       y_n = y_vals.at(t);
       an_image.SetPixel(x_n , y_n, 255);
       }

  // DrawLine(x_bar , y_bar , x_vals.back() , y_vals.back() , 255 , an_image);

}


int
main(int argc, char **argv){
  
  if (argc!=4) {
    printf("Usage: %s file1 file2\n", argv[0]);
    return 0;
  }
  const string input_bin_img(argv[1]);
  const string output_database(argv[2]);
  const string output_img(argv[3]);
  size_t i , j;
  int pixel;
  std::vector<int> labels_;
  std::vector<std::vector<double>> values_;

  Image an_image;
  if (!ReadImage(input_bin_img, &an_image)) {
    cout <<"Can't open file " << input_bin_img << endl;
    return 0;
  }
  const int n_rows = an_image.num_rows();
  const int n_cols = an_image.num_columns();

  // Object label
  for (i = 0 ; i < n_rows ; ++i){
    for ( j = 0 ; j < n_cols ; ++j){
      pixel = an_image.GetPixel(i,j);
      if ( pixel > 0){
        auto it = std::find(labels_.begin() , labels_.end() , pixel);
        if (it == labels_.end()) labels_.push_back( pixel );
      }
    }
  }

  for( auto label : labels_ ){
    std::vector<double> temp_vals(8);
    calculations(an_image , label , n_rows, n_cols, temp_vals);
    values_.push_back(temp_vals);
  }
  

  // Display positions and orientations of objects
  for( auto label : values_ ) {
    Drawing(an_image , label[1] , label[2] , label[6] * M_PI /180 , label[7] , 20);
  }

  if (!WriteImage(output_img, an_image)){
    cout << "Can't write to file " << output_img << endl;
    return 0;
  }
  return 0;
}

