#ifndef __H__LINEAR_ALGEBRA_LIBRARY_MATRIX_VECTOR_H__
#define __H__LINEAR_ALGEBRA_LIBRARY_MATRIX_VECTOR_H__

#include <iostream>
#include <data_cell.h>
#include <operators.h>
#include "mkl_cblas.h"

using namespace std;

#define DIM_3        3
#define DIM_3x3      9
#define DIM_3x3x3   29
#define DIM_3x3x3x3 81

#define CRM CblasRowMajor
#define CNT CblasNoTrans
#define CYT CblasTrans

/// C = aAxB + bC
/// C[m,n] = a*A[m,k] x B[k,n] + b*C[m,n]
// cblas_dgemm(CblasRowMajor,CblasNoTrans,CblasNoTrans,m,n,k,a,A,k,B,n,b,C,n);
template <class T>
int Matrix_AxB_large(const T &C, 
                     double a, 
                     double b, 
                     const T &A, 
                     const int AT, 
                     const T &B, 
                     const int BT)
{
  int err = 0;               
  if(AT==0 && BT==0)
    cblas_dgemm(CRM,CNT,CNT,A.m_row,B.m_col,A.m_col,a,A.m_pdata,A.m_col,B.m_pdata,B.m_col,b,C.m_pdata,C.m_col);
    
  if(AT==1 && BT==0)
    cblas_dgemm(CRM,CYT,CNT,C.m_row,C.m_col,B.m_row,a,A.m_pdata,A.m_col,B.m_pdata,B.m_col,b,C.m_pdata,C.m_col);

  if(AT==0 && BT==1)
    cblas_dgemm(CRM,CNT,CYT,C.m_row,C.m_col,A.m_col,a,A.m_pdata,A.m_col,B.m_pdata,B.m_col,b,C.m_pdata,C.m_col);

  if(AT==1 && BT==1)
    cblas_dgemm(CRM,CYT,CYT,C.m_row,C.m_col,A.m_row,a,A.m_pdata,A.m_col,B.m_pdata,B.m_col,b,C.m_pdata,C.m_col);

  return err;
}


/// check Matrix size A and B for operatations: multiplication
///
/// if not same, print function name and error massage.
///
/// \param[in] A 1st matrix to be compared
/// \param[in] B 2nd matrix to be compared
/// \param[in] func_name function name calling this function
/// \param[in] lineno line number
/// \return true or false
template <class T>
bool check_matrix_size_AxB(const T &A, const T &B, const char *func_name, const int lineno)
{
  bool is_it_same = true;
  if(A.m_col !=B.m_row)
  {  
    cout << "MATRIX<T>" << func_name << "(" << lineno <<"): Error MATRIX size does not match. ";
    cout << "[" << A.m_row << "x" << A.m_col <<"] * ";
    cout << "[" << B.m_row << "x" << B.m_col <<"] \n";    
    is_it_same = false;
  }
  return is_it_same;
};

/// check Matrix size A and B for operatations: =, +, -
///
/// if not same, print function name and error massage.
///
/// \param[in] A 1st matrix to be compared
/// \param[in] B 2nd matrix to be compared
/// \param[in] func_name function name calling this function
/// \param[in] lineno line number
/// \return true or false
template <class T>
bool check_matrix_size_A_B(const T &A, const T &B, const char *func_name, const int lineno)
{
  bool is_it_same = true;
  if((A.m_row !=B.m_row)||(A.m_col !=B.m_col))
  {  
    cout << "MATRIX<T>" << func_name << "(" << lineno <<"): Error MATRIX size does not match!\n";
    is_it_same = false;
  }
  return is_it_same;
}
                     
template <class T> class MATRIX: public DATACELL<T>
{
public:
  MATRIX(): DATACELL<T>(){};
  ~MATRIX(){};

  // add  
  void add(const MATRIX<T> &B);						          // this += B
  void add(const MATRIX<T> &A, const MATRIX<T> &B); // this = A + B
  void add(const double b);                         // this += b  
  void add(const MATRIX<T> &A, const double b);     // this = A + b
  
  // subtract
  void sub(const MATRIX<T> &B);	                    // this -= B
  void sub(const MATRIX<T> &A, const MATRIX<T> &B);	// this = A - B
  void sub(const double b);	                        // this = b - this 
  void sub(const double a, const MATRIX<T> &B);	    // this = a - B

  // product
  void prod(const MATRIX<T> &B);                     // this *= B
  void prod(const MATRIX<T> &A, const MATRIX<T> &B); // this = A*B
  void prod(const MATRIX<T> &A, const double b);     // this = A*b
  void prod(const double b);                         // this *= b (scalar)
  
  void trans(void);                      // transpose
  double norm(void);                     // sqrt(this:this)
  double ddot(MATRIX<T> &B);             // this:B
  double ox(MATRIX<T> &A, MATRIX<T> &B); // this = A /otimes B 
  void input_from_str(char *str);
  void print(void);
  void print(const char *name);  
};

/// matrix addition to self
///
/// data calling this function will be updated as a result of
/// operation : this += B
///
/// \param[in] B input matrix to be added
template <class T> void MATRIX<T>::add(const MATRIX<T> &B)
{
  if((this->m_row==0)||(this->m_col==0))
  {
    this->set_values(B.m_row, B.m_col, B.m_pdata);
    return;
  }
  if((B.m_row==0)||(B.m_col==0))
    return;
    
  if(check_matrix_size_A_B(*this, B, __func__, __LINE__))
  {
    for(int i=0; i<(this->m_row)*(this->m_col); i++)
      this->m_pdata[i] += B.m_pdata[i];

  }
};

/// matrix addition
///
/// data calling this function will be updated as a result of
/// operation : this = A + B
///
/// \param[in] A 1st input matrix to be added
/// \param[in] B 2nd input matrix to be added
template <class T> void MATRIX<T>::add(const MATRIX<T> &A, const MATRIX<T> &B)
{
  if((A.m_row==0)||(A.m_col==0))
    return;
    
  if(check_matrix_size_A_B(A, B, __func__, __LINE__))
  {
    this->initialization(B.m_row, B.m_col);
    for(int i=0; i<(this->m_row)*(this->m_col); i++)
      this->m_pdata[i] = A.m_pdata[i] + B.m_pdata[i];
  }
};

/// matrix addition
///
/// data calling this function will be updated as a result of
/// operation : this += b, b = scalar
///
/// \param[in] b a scalar to be added
template <class T> void MATRIX<T>::add(const double b)
{
  for(int i=0; i<(this->m_row)*(this->m_col); i++)
      this->m_pdata[i] += b;
};

/// matrix addition
///
/// data calling this function will be updated as a result of
/// operation : this = A + b, b = scalar
///
/// \param[in] A input matrix to be added
/// \param[in] b a scalar to be added
template <class T> void MATRIX<T>::add(const MATRIX<T> &A, const double b)
{
  if((A.m_row==0)||(A.m_col==0))
    return;
  
  this->initialization(A.m_row, A.m_col);  
  for(int i=0; i<(this->m_row)*(this->m_col); i++)
      this->m_pdata[i] = A.m_pdata[i] + b;
};

/// matrix subtract to self
///
/// data calling this function will be updated as a result of
/// operation : this -= B
///
/// \param[in] B input matrix to be subtracted
template <class T> void MATRIX<T>::sub(const MATRIX<T> &B)
{
  if((this->m_row==0)||(this->m_col==0))
  {
    this->set_values(B.m_row, B.m_col, B.m_pdata);
    return;
  }
  if((B.m_row==0)||(B.m_col==0))
    return;
  if(check_matrix_size_A_B(*this, B, __func__, __LINE__))
  {
    for(int i=0; i<(this->m_row)*(this->m_col); i++)
      this->m_pdata[i] -= B.m_pdata[i];

  }
};

/// matrix subtraction
///
/// data calling this function will be updated as a result of
/// operation : this = A - B
///
/// \param[in] A 1st input matrix
/// \param[in] B 2nd input matrix to be subtracted
template <class T> void MATRIX<T>::sub(const MATRIX<T> &A, const MATRIX<T> &B)
{
  if((A.m_row==0)||(A.m_col==0))
    return;
    
  if(check_matrix_size_A_B(A, B, __func__, __LINE__))
  {
    this->initialization(B.m_row, B.m_col);
    for(int i=0; i<(this->m_row)*(this->m_col); i++)
      this->m_pdata[i] = A.m_pdata[i] - B.m_pdata[i];
  }
};

/// matrix subtraction
///
/// data calling this function will be updated as a result of
/// operation : this = b - this
///
/// \param[in] b a scalar
template <class T> void MATRIX<T>::sub(const double b)
{
  for(int i=0; i<(this->m_row)*(this->m_col); i++)
    this->m_pdata[i] = b - this->m_pdata[i];
};

/// matrix subtraction
///
/// data calling this function will be updated as a result of
/// operation : this = a - B
///
/// \param[in] a a scalar
/// \param[in] B input matrix to be subtracted
template <class T> void MATRIX<T>::sub(const double a, const MATRIX<T> &B)
{
  if((B.m_row==0)||(B.m_col==0))
    return;

  this->initialization(B.m_row, B.m_col);
  for(int i=0; i<(this->m_row)*(this->m_col); i++)
    this->m_pdata[i] = a - B.m_pdata[i];
};

/// perform matrix product to itself
///
/// data calling this function will be updated as a result of
/// this *= B
///
/// \param[in] B input matrix to be multiplied
template <class T> void MATRIX<T>::prod(const MATRIX<T> &B)
{
  if(check_matrix_size_AxB(*this, B, __func__, __LINE__))
  {
    MATRIX<T> A(*this);
    this->initialization(A.m_row, B.m_col);
    Matrix_AxB_large(*this,1.0,0.0,A,0,B,0);    
  }  
};               

/// perform two matrices product to itself 
///
/// data calling this function will be updated as a result of
/// this = A*B
/// \param[in] A 1st input matrix to be multiplied
/// \param[in] B 2nd input matrix to be multiplied
template <class T> void MATRIX<T>::prod(const MATRIX<T> &A, const MATRIX<T> &B)
{
  if(check_matrix_size_AxB(A, B, __func__, __LINE__))
  {
    this->initialization(A.m_row, B.m_col);
    Matrix_AxB_large(*this,1.0,0.0,A,0,B,0);
  }  
};

/// perform matrices product with a scalar and aply to this 
///
/// data calling this function will be updated as a result of
/// this = A*b
/// \param[in] A input matrix to be multiplied
/// \param[in] b a scalar to be multiplied
template <class T> void MATRIX<T>::prod(const MATRIX<T> &A, const double b)
{
  this->initialization(A.m_row, A.m_col);
  for(int ia=0; ia<(this->m_row)*(this->m_col); ia++)
    this->m_pdata[ia] = A.m_pdata[ia]*b;
};

/// perform multiply a scalar to itself 
///
/// data calling this function will be updated as a result of
/// this = a*B, a is scalar
/// \param[in] a a scalar value to be multiplied
template <class T> void MATRIX<T>::prod(const double value)
{
  for(int ia=0; ia<(this->m_row*this->m_col); ia++)
    this->m_pdata[ia] *= value;    
};
void prod(double value);               // this *= value (scalar)*/

/// print MATRIX components with input name
///
/// \param[in] name name of matrix
template <class T> void MATRIX<T>::print(const char *name)
{
  cout << name << " = [\n";

  for(int i=0; i<this->m_row; i++)
  {
    for(int j=0; j<this->m_col; j++)
      cout << this->get_a_value(i+1, j+1) << " ";

    cout << "\n";
  }
  cout << "];\n";
};

/// print MATRIX components without name input
///
/// default name A will be used
template <class T> void MATRIX<T>::print(void)
{
  char A[2] = "A";
  this->print(A);
};

#endif