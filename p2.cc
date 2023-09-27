// Qizhao Rong
// Due (09/26)
// p2.cc : Read a given binary pgm image, segment those into different gray-levels 
// with Sequential Labeling Algo, and saved it to another pgm image  
// 

#include "image.h"
#include "DisjSets.h"
#include <cstdio>
#include <iostream>
#include <string>

using namespace std;
using namespace ComputerVisionProjects;

/**
Update the Equivalence Table if label(B) != Label(C).

@C        : int denote as the label on labels[i][j-1]
@B        :  int denote as the label on labels[i-1][j]
@A        :  int denote as the label on labels[i][j]
@eq_Table : A Unioned set datastructure, i.e. Equivalance table
*/
void updatedEquTable( int& C, int& B,int& A,  DisjSets& eq_Table){
  if (C > 0 && B > 0 && C != B){
      eq_Table.unionSets(B,C);
    }
  }

/**
Labeling the pixel at location (@i , @j), 
and comparing it with its neighbors, 
updated and marked on the @labels 2D arrays.

@ i        : size_t , where rows locations of pixel
@ j        : size_t , wherea columns location of pixel
@ an_image : Reference to a image object.
@ labels   : A 2D int array, for clustering purpose.
@ levels   : reference to int, denotes # of cluster for gray-level.
@ eq_Table : A Unioned set datastructure, i.e. Equivalance table

*/
void Labeling(
  size_t i , size_t j, Image*& an_img, 
  int**& labels,int& levels , DisjSets& eq_Table){
  int current_level;
  int label1_ ,  label2_ ,  label3_ ;
  label1_ =  label2_ =  label3_ = 0;
  int pixel = an_img -> GetPixel(i,j) % 254;
  // current_level = pixel;
  current_level = 0;


  // Handel pixels on the margins.
  if (i + j == 0){
    current_level = pixel;
  }
  else if (i == 0 && j > 0)
    current_level = labels[i][j-1];
  else if (j == 0 && i > 0)
    current_level = labels[i-1][j];

  // Handel pixel that at not on top or on the leftest columns.
  else{
    label1_ = labels[i-1][j-1];
    label2_ = labels[i][j-1];
    label3_ = labels[i-1][j];

    if (label1_ > 0) // if the pixel D been labeled
      current_level = label1_;
    else {
      // elss, would copy label from C, if C labeled.
      if (label2_ > 0) {
              current_level = label2_;
            }
      else if (label2_ == 0 && label3_ > 0){
                current_level = label3_;
            }
    }
  }
  // if all 3 Neighbor of A is not labeled.
  if (current_level == 0) {
    // incr. if the A is region
    current_level = levels + pixel;
    levels = current_level; // update the counter of labels
  }
  
  labels[i][j] = pixel * current_level; // set the label if pixel present as 1 on A
  updatedEquTable( label2_ , label3_ , labels[i][j], eq_Table); // updated the equivalence table if need.

}

/**
Apply Sequencial Labeling Algorithm

@ an_image : A Pointer to an Image object.
@ labels_  : Reference to An 2D int arrays
*/
bool SeqLablingAlgo(Image* an_image , int**& labels_ ){
  const int n_cols = an_image->num_columns();
  const int n_rows = an_image->num_rows();
  int levels_ = 1;
  size_t i, j;
  // Define Equivalence table with #(n_rows * n_cols) of nodes.
  DisjSets EqTable_(n_rows * n_cols);

  // First phase of marking.
  for (i = 0; i < n_rows; ++i){
    for (j = 0 ; j < n_cols ; ++j)
      Labeling(i,j,an_image,labels_,levels_ , EqTable_);
  }

  // Second phase of re-marking with Equivalence table
  for (i = 0 ; i < n_rows ; ++i){
    for (j = 0; j < n_cols ; ++j){
      labels_[i][j] = EqTable_.find(labels_[i][j]);
    }
  }

  return false;
}

int
main(int argc, char **argv){

  int n_cols, n_rows;
  size_t i , j;
  int** labels_;
  
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

  // allocates 2-D array for labeling.
  // labels the 
  n_cols = an_image.num_columns();
  n_rows = an_image.num_rows();
  labels_ = new int*[n_rows];
  for(i = 0; i < n_rows ; ++i)
    labels_[i] = new int[n_cols];
  SeqLablingAlgo(&an_image , labels_);


  // Re-shaping the gray-level for labeled obj.
  for(i = 0 ; i < n_rows ; ++i){
    for (j = 0 ; j < n_cols; ++j){
      an_image.SetPixel(i,j, labels_[i][j] * 7);
    }
  }

  // Deallocated memory
  for (i = 0; i < n_rows ; i++)
    delete labels_[i];
    delete labels_;
  labels_ = nullptr;

  if (!WriteImage(output_img, an_image)){
    cout << "Can't write to file " << output_img<< endl;
    return 0;
  }

  return 0;
}
