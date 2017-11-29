#include "vector.h"

Vector::Vector(){
  dimension = 0;
  vector = nullptr;
}

Vector::Vector(int dimension){
  this->dimension = dimension;
  initialize_vector();
}

Vector::~Vector(){
  delete[] vector;
  vector = nullptr;
}

int Vector::get_dimension(){
  return dimension;
}

double Vector::get_element(int num_row){
  return vector[num_row];
}

// Vector* get_vector(){
//   return vector;
// }

void Vector::set_dimension(int dimension){
  this->dimension = dimension;
}

void Vector::set_element(int num_row, double value){
  vector[num_row] = value;
}

void Vector::print(){
  cout<<endl;
  for(int i = 0; i < dimension; i++){
    cout<<vector[i]<<endl;
  }
  cout<<endl;
}

void Vector::initialize_vector(){
  vector = new double [dimension];
  scaling(0);
}

void Vector::scaling(double scaler){
  if(dimension == 0){
    cout<<"vector dimension not initialized properly"<<endl;
    return;
  }
  for(int i = 0; i < dimension; i++){
    vector[i] = scaler;
  }
}

void Vector::dot(Vector* vector){
  if(this->dimension != vector->dimension){
    cout<<"mismatch of dimension"<<endl;
    return;
  }
  for(int i = 0; i < this->dimension; i++){
    this->vector[i] *= vector[i];
  }
}

void Vector::copy(Vector* vector){
  if(dimension == vector->dimension){
    cout<<"mismatch dimension"<<endl;
    return;
  }
  for(int i = 0; i < dimension; i++){
    this->vector[i] = vector[i];
  }
}




Vector* dot(Vector* vector_a, Vector* vector_b){
  if(vector_a->get_dimension() != vector_b->get_dimension()){
    cout<<"mismatch of dimension"<<endl;
    return nullptr;
  }
  Vector* result = new Vector();
  result->
}

Vector* copy(Vector* vector){
  Vector* result = new Vector(vector->get_dimension());
  result->copy_vector(vector);
  return result;
}

Vector* multiply_matrix_v(Matrix* matrix, Vector* vector){
  if(matrix->get_num_col() != vector->get_dimension()){
    cout<<"mismatch of dimension"<<endl;
    return nullptr;
  }
  Vector* result = new Vector(matrix->get_num_row());
  for(int i = 0; i < result->get_dimension(); i++){
    double product = 0;
    for(int j = 0; j < matrix->get_num_col()){
      product += matrix->get_element(i, j)*vector->get_element(j);
    }
    result->set_element(i, product);
  }
  return result;
}