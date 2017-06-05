#include <iostream>
#include <cmath>
#include <matrix_vector.h>

using namespace std;

#define TOL 1.0e-15

/// print test statement
///
/// \param[in] test_no test number
/// \param[in] str printing statement
/// \return non-zero on internal error
int print_test_header(const int test_no, const char *str)
{
  int err = 0;
  cout << "==================================================\n";
  cout << "Test " <<  test_no << ": " << str;
  cout << "--------------------------------------------------\n";
  return err;
}

/// determine whether test is good or failed
///
/// \param[in] A DATACELL<double> object
/// \param[in] data double array
/// \return non-zero on internal error
int judge_test(MATRIX<double> &A, const double *data)
{
  int err = 0;
  double diff = 0.0;
  if((A.m_row*A.m_col == 0) || (A.m_pdata == NULL))
  {  
    cout << "WARNING!, Test failed\n\n";
    err++;    
    return err;
  }
    
  for(int ia = 0; ia<A.m_row*A.m_col; ia++)
    diff = (A.m_pdata[ia]-data[ia])*(A.m_pdata[ia]-data[ia]);
  
  double norm = sqrt(diff);
  if(norm<TOL)
    cout << ">> Test passed\n\n";
  else
    cout << ">> WARNING!, Test faild\n\n";

  return err;  
}

int main(int argc,char *argv[])
{
  int err = 0;
  int test_no = 0;
  double data[9] = {0.3,0.3,0.3,0.3,0.3,0.3,0.3,0.3,0.3};
  
  // test 0: test for A = B + C
  err += print_test_header(test_no++, "A = B + C\n");
  MATRIX<double> A, B, C;
  
  B.initialization(3,3, 0.1);
  C.initialization(3,3, 0.2);
  
  A = B + C;
  A.print("A");
  B.print("B");
  C.print("C");
  err += judge_test(A,data);
  
  // test 1: test for A = B - C
  B.initialization(3,3, 0.5);
  err += print_test_header(test_no++, "A = B - C\n");
    
  A = B - C;
  A.print("A");
  B.print("B");
  C.print("C");
  err += judge_test(A,data);
  
  // test 2: test for A = B*C
  B.initialization(3,2, 0.5);
  C.initialization(2,3, 0.3);  
  err += print_test_header(test_no++, "A = B * C\n");
    
  A = B*C;
  A.print("A");
  B.print("B");
  C.print("C");
  err += judge_test(A,data);
  
  // test 3: test for B *= C
  err += print_test_header(test_no++, "B *= C\n");

  B.print("B");
  C.print("C");  
  B.prod(C);
  B.print("B");

  err += judge_test(B,data);
  
  // test 4: test for A = a*B + C;
  err += print_test_header(test_no++, "A = a*B + C\n");
  
  double a = 0.2;
  B.initialization(3,3,1.0);
  C.initialization(3,3,0.1);
 
  A = a*B + C;

  printf("a = %f\n", a);
  B.print("B");
  C.print("C");

  A.print("A");

  err += judge_test(A,data);   
  
  return err;
}
