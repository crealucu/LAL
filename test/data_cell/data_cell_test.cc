#include <iostream>
#include <cmath>
#include <data_cell.h>

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
  cout << "Test" <<  test_no << ": " << str;
  cout << "--------------------------------------------------\n";
  return err;
}

/// print data array
///
/// \param[in] A DATACELL<double> object
/// \return non-zero on internal error
int print_data(DATACELL<double> &A, const char *name)
{
  int err = 0;
  cout << name << " = [\n";
  for(int i=1; i<=A.m_row; i++)
	{
		for(int j=1; j<=A.m_col; j++)
		  cout << A.get_a_value(i, j) << " ";

		if(i==A.m_row)
		  cout << "];\n";
		else
		  cout << "\n";
	}
	return err;
}

/// determine whether test is good or failed
///
/// \param[in] A DATACELL<double> object
/// \param[in] data double array
/// \return non-zero on internal error
int judge_test(DATACELL<double> &A, const double *data)
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
  double data[9] = {0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9};
  double data_row[18] = {0.1,0.2,0.3,0.1,0.2,0.3,
                         0.4,0.5,0.6,0.4,0.5,0.6,
                         0.7,0.8,0.9,0.7,0.8,0.9};

  double data_col[18] = {0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,
                         0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9};
  double data_get_cell[4] = {0.8,0.9,0.2,0.3};                         
                         

  // test 0: Construct data cell with a data pointer
  err += print_test_header(test_no++, "Construct a data cell with a data array\n");
  DATACELL<double> A(3,3,data);
  err += print_data(A, "A");
  err += judge_test(A,data);
  
  // test 1: B = A
  err += print_test_header(test_no++, "Perform A = B\n");
  DATACELL<double> B;
  B = A;
  err += print_data(B, "B");
  err += judge_test(B,data);
  
  // test 2: C[4 by 4] = A[3 by 3]
  err += print_test_header(test_no++, "Perform C[4 by 4] = A[3 by 3], re-size matrix\n");
  DATACELL<double> C(4,4,1.0);
  
  err += print_data(C, "C");
  err += print_data(A, "A");
  C = A;
  err += print_data(C, "C");
  err += judge_test(C,data);

  // test 3: B = [B; A]
  err += print_test_header(test_no++, "Perform add to row B[3 by 3] => [3 by 6] \n \t by doning B = [B,A]\n");  
  err += print_data(B, "B");
  err += print_data(A, "A");
  B.add2row(A);
  err += print_data(B, "B");
  err += judge_test(B,data_row);
  
  // test 4: C = [C; A]
  err += print_test_header(test_no++, "Perform add to col C[3 by 3] => [6 by 3] \n \t by doning C = [C;A]\n");  
  err += print_data(C, "C");
  err += print_data(A, "A");
  C.add2col(A);
  err += print_data(C, "C");
  err += judge_test(C,data_col);

  // test 5: D = C(3:4, 2:3);
  err += print_test_header(test_no++, "Perform get a cell from C[6 by 3]\n \t D = C(3:4, 2:3)\n");    
  DATACELL<double> D;
  D.get_cell(C,3,4,2,3);
  err += print_data(D, "D");
  err += judge_test(D,data_get_cell);
    
  return err;
}
