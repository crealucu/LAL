#ifndef __H__LINEAR_ALGEBRA_LIBRARY_DATA_CELL_H__
#define __H__LINEAR_ALGEBRA_LIBRARY_DATA_CELL_H__

#include <iostream>
#include <stdlib.h>
#include <string.h>

using namespace std;

#define DEBUG_PRINT_DATA_CELL 0

/// DATACELL class 
///
/// Topest class of the LINEAR ALGEBRA LIBRARY
/// Matrix type of data array for any data types 
template <class T> class DATACELL
{
public:
  
  /// number of row
  int m_row;
  /// number of col 
  int m_col;
  /// memory for data array
  T *m_pdata;

  // constructors
  DATACELL();                                
  DATACELL(const DATACELL<T> &A);
  DATACELL(const int m_size, const int n_size);
  DATACELL(const int m_size, const int n_size, const T &value);
  DATACELL(const int m_size, const int n_size, const T *value);
  void set_nulls(void);

  // destructor
  ~DATACELL();
  
  // initialize DATACELL
  void initialization(const int m_size, const int n_size, const T &value);       
  void initialization(const int m_size, const int n_size);                       
  void initialization(const DATACELL<T> &A);                           
  void initialization(const int m_size, const int n_size, const T *p);

  // deallocate memory of member array  
  void cleanup(void);
  
  // check data array size
  int check_size_and_null(const int m, const int n);             

  // set a value 
  void set_a_value(const int m, const int n, const T &value);      
  void set_values(const int m_size, const int n_size, const T *p);  
  void set_values(const T &p);

  // get a value
  constexpr T  get_a_value(const int m, const int n);
  T* get_a_value_pointer(const int m, const int n);
  
  // get data block
  void get_cell(const DATACELL<T> &B, const int a, const int b, const int c, const int d);
  void add2row(const DATACELL<T> &B);  // add DATACELL B to the row of this DATACELL 
  void add2col(const DATACELL<T> &B);  // add DATACELL B to the column of this DATACELL
  
  /// indexing data through bracket
  ///
  /// e.g. A(a, b) = c;
  ///
  /// \param[in] a row index
  /// \param[in] b column index
  /// \return data component at a, b
  constexpr T& operator () (const int a, const int b)
  {
    return *(m_pdata+(a-1)*m_col+(b-1));
  };
  
  /// operator overriding for datacell  
  ///
  /// \param[in] obj a data cell to be assigned
  /// \return this data cell
  DATACELL<T> & operator = (const DATACELL<T> &obj)
  {
    initialization(obj);
    return *this;
  };
};  

/// default constructor
template <class T> DATACELL<T>::DATACELL()
{
  set_nulls();  
};

/// constructor with a already exist object
///
/// \param[in] A a DATACELL
/// \return no return
template <class T> DATACELL<T>::DATACELL(const DATACELL<T> &A)
{
  set_nulls();
  this->initialization(A);
};

/// constructor with initialization of m by n data cell
///
/// \param[in] m_size row index
/// \param[in] n_size column index
/// \return no return
template <class T> DATACELL<T>::DATACELL(const int m_size, 
                                         const int n_size)
{
  set_nulls();
  this->initialization(m_size, n_size);
};

/// constructor with initialization of m by n DATACELL and fill data with a (type T) value
///
/// \param[in] m_size row index
/// \param[in] n_size column index
/// \param[in] value a data (type T) value
/// \return no return
template <class T> DATACELL<T>::DATACELL(const int m_size, 
                                         const int n_size, 
                                         const T &value)
{
  set_nulls();
  this->initialization(m_size, n_size, value);
};

/// constructor with initialization of m by n DATACELL and fill data with a (type T) data array
///
/// \param[in] m_size row index
/// \param[in] n_size column index
/// \param[in] value a data (type T) value
/// \return no return
template <class T> DATACELL<T>::DATACELL(const int m_size, 
                                         const int n_size, 
                                         const T *value)
{
  set_nulls();
  this->initialization(m_size, n_size, value);
};

/// default destructor
template <class T> DATACELL<T>::~DATACELL()
{
  cleanup();
};

/// set all members to NULL
///
/// \return void
template <class T> void DATACELL<T>::set_nulls(void)
{
  m_row=0;
  m_col=0;
  m_pdata=NULL;
  if(DEBUG_PRINT_DATA_CELL)
    cout << "Debug mode >> set NULL ...\n";
};

/// initialize DATACELL to have m by n data array and fill the data array with (type T) value
///
/// \param[in] m_size row index
/// \param[in] n_size column index
/// \param[in] value a data (type T) value
/// \return void
template <class T> void DATACELL<T>::initialization(const int m_size, 
                                                    const int n_size, 
                                                    const T &value)
{
  this->initialization(m_size, n_size);
  
  for(int i=1; i<=m_row; i++)
  {
    for(int j=1; j<=m_col; j++)
    {
      set_a_value(i, j, value);
    }
  }
};

/// initialize DATACELL to have m by n data array
///
/// \param[in] m_size row index
/// \param[in] n_size column index
/// \return void
template <class T> void DATACELL<T>::initialization(const int m_size, 
                                                    const int n_size)
{
  // if size of data array is same as inputs
  // no need to do memory allocation.

  if(DEBUG_PRINT_DATA_CELL)
    cout << "Debug mode >> construct [" << m_size << "x" << n_size << "] data cell...\n";

  if((m_row*m_col == m_size*n_size) && (m_pdata != NULL)) 
  {
    if(DEBUG_PRINT_DATA_CELL)
      cout << "Debug mode >> already constructed.done.\n";

    m_row = m_size; // just set the size     
    m_col = n_size;    
    return;
  }

  if(m_pdata != NULL)
  {
    if(DEBUG_PRINT_DATA_CELL)
    {  
      cout << "Debug mode >> already constructed but size is different: ";
      cout << "Debug mode >> this  = [" << m_row  << "x" << m_col  << "] vs "; 
      cout << "Debug mode >> input = [" << m_size << "x" << n_size << "], "; 
      cout << "cleanup...\n";
    }
    cleanup();
  }
    
  m_row = m_size;
  m_col = n_size;
  m_pdata = new T [m_size*n_size];
    
  if(m_pdata == NULL)
    cout << "Memory is not allocated. " << __func__ << ":" << __FILE__ << ":" << __LINE__ << "\n";
  else if(DEBUG_PRINT_DATA_CELL)
    cout << "Debug mode >> [" << m_row << "x" << m_col << "] data cell is constructed.done.\n";    
};

/// initialize DATACELL with a already exist object
///
/// If the size of this DATACELL is different from the input object,
/// this will be re-sized.
///
/// \param[in] A a DATACELL object
/// \return void
template <class T> void DATACELL<T>::initialization(const DATACELL<T> &A)
{
  this->initialization(A.m_row, A.m_col);
  for(int ia=0; ia<A.m_row*A.m_col; ia++)
    m_pdata[ia] = A.m_pdata[ia];     
};

/// initialize DATACELL with a data array
///
/// If the size of this DATACELL is different than inputs,
/// this will be re-sized.
///
/// \param[in] m_size number of row of input array
/// \param[in] n_size number of columns of input array
/// \param[in] p a data (type T) array to be set
/// \return void
template <class T> void DATACELL<T>::initialization(const int m_size, 
                                                    const int n_size, 
                                                    const T *p)
{ 
  this->initialization(m_size, n_size);

  for(int i=1; i<=m_row; i++)
  {
    for(int j=1; j<=m_col; j++)
      set_a_value(i, j, p[(i-1)*m_size + j-1]);
  }
};

/// deallocate memory and set size to zeros 
///
/// \return void
template <class T> void DATACELL<T>::cleanup(void)
{
  m_row = 0;
  m_col = 0;

  if(m_pdata!=NULL)
  {
    if(DEBUG_PRINT_DATA_CELL)
      cout << "Debug mode >> delete data and set NULL\n";      
    delete m_pdata;
    m_pdata = NULL;
  }

};

/// check input indices are bounded by the number of row and column
///
/// If indices are outbounded, return 0 otherwise return 1.
///
/// \param[in] m row index
/// \param[in] n column index
/// \return 0: m or n is out of range of the data array
///         1: within the range of the data array
template <class T> int DATACELL<T>::check_size_and_null(const int m, 
                                                        const int n)
{
  if((0<m && m<=m_row) && (0<n && n<=m_col) && (m_pdata != NULL)) 
    return 1;
  else
    return 0;
}

/// set a component(m, n) with a data (type T) value 
///
/// If the size of this DATACELL is different from inputs,
/// this will be re-sized.
///
/// \param[in] m row index
/// \param[in] n column index
/// \param[in] value a data (type T) value
/// \return void
template <class T> void DATACELL<T>::set_a_value(const int m, 
                                                 const int n, 
                                                 const T &value)
{
  *(m_pdata+(m-1)*m_col+(n-1)) = value;
};

/// set all components by a data array
///
/// If the size of this DATACELL is different than inputs,
/// this will be re-sized.
///
/// \param[in] m_size number of row of input array
/// \param[in] n_size number of columns of input array
/// \param[in] p a data (type T) array to be set
/// \return void
template <class T> void DATACELL<T>::set_values(const int m_size, 
                                                const int n_size, 
                                                const T *p)
{
  initialization(m_size, n_size, p);
};

/// set all components by a data
///
/// If the size of this DATACELL is different than inputs,
/// this will be re-sized.
///
/// \param[in] d a data (type T)
/// \return void
template <class T> void DATACELL<T>::set_values(const T &d)
{
  this->initialization(m_row, m_col, d);
};

/// get a component(m, n) value
///
/// \param[in] m row index
/// \param[in] n column index
/// \return a data (type T) value
template <class T> constexpr T DATACELL<T>::get_a_value(const int m, 
                                              const int n)
{
  return *(m_pdata+(m-1)*m_col+(n-1));
};

/// get pointer of a component(m, n)
///
/// If the pointer is used after, this object is destructed,
/// memory assess error could occor.
///
/// \param[in] m row index
/// \param[in] n column index
/// \return a pointer of a data (type T) at m, n
template <class T> T* DATACELL<T>::get_a_value_pointer(const int m, 
                                                       const int n)
{
  return m_pdata+((m-1)*m_col+(n-1));
};

/// get a data block from a existing data cell
///
/// perform A(a:b, c:d)
///
/// \param[in] A a data cell to be extracted
/// \param[in] a lower row index
/// \param[in] b upper row index
/// \param[in] c lower column index
/// \param[in] d upper column index
template <class T> void DATACELL<T>::get_cell(const DATACELL<T> &A, 
                                              const int a, 
                                              const int b, 
                                              const int c, 
                                              const int d)
{
  if((b==0)||(d==0))
    return;
  if((a>A.m_row)||(c>A.m_col))
    return;
  
  if((a>A.m_row)||(b>A.m_row)||(a>b)||(c>A.m_col)||(d>A.m_col)||(c>d))
  {
    cout << "DATACELL::get_cell Error: Matrix index does not match!\n";
    return;
  }
  else
  {

    DATACELL<T> temp;
    temp.m_pdata = A.m_pdata; // no memory is created
    temp.m_row   = A.m_row;
    temp.m_col   = A.m_col;
        
    initialization(b-a+1, d-c+1);
    for(int i=1; i<=b-a+1; i++)
    {
      for(int j=1; j<=d-c+1; j++)
        set_a_value(i, j, temp(a+i-1, c+j-1));
    }

    temp.m_pdata = NULL;
    temp.m_row   = 0;
    temp.m_col   = 0;    
  }
};

/// add source data cell to the target data cell in row direction
///
/// perfom A = [A, B]; A = target, B = source
///
/// \param[in] B a data cell to be added to this object
template <class T> void DATACELL<T>::add2row(const DATACELL<T> &B)
{
  if((m_row==0)||(m_col==0))
  {
    this->initialization(B);
    return;
  };
  
  if((B.m_row==0)||(B.m_col==0))
    return;
  
  if(B.m_row!=m_row)
  {
    cout << "DATACELL::add2row Error: Matrix size does not match!\n";
  }
  else
  {
    DATACELL<T> A;
    A.initialization(m_row,m_col,m_pdata);

    DATACELL<T> temp;
    temp.m_pdata = B.m_pdata; // no memory is created
    temp.m_row   = B.m_row;
    temp.m_col   = B.m_col;
    
    initialization(A.m_row, A.m_col + B.m_col);
    for(int i=1; i<=A.m_row; i++)
    {
      for(int j=1; j<=A.m_col + B.m_col; j++)
      {
        double value = 0.0;
        if(j<=A.m_col)
          value = A.get_a_value(i,j);
        else
          value = temp.get_a_value(i,j-A.m_col);
          
        set_a_value(i,j, value);
      }
    }
    
    temp.m_pdata = NULL;
    temp.m_row   = 0;
    temp.m_col   = 0;
  }
};


/// add source data cell to the target data cell in column direction
///
/// perfom A = [A; B]; A = target, B = source
///
/// \param[in] B a data cell to be added to this object
template <class T> void DATACELL<T>::add2col(const DATACELL<T> &B)
{
  if((m_row==0)||(m_col==0))
  {
    this->initialization(B);
    return;
  };
  
  if((B.m_row==0)||(B.m_col==0))
    return;
    
  if(B.m_col!=m_col)
  {
    cout << "DATACELL::add2row Error: Matrix size does not match!\n";
  }
  else
  {
    DATACELL<T> A;
    A.initialization(m_row,m_col,m_pdata);

    DATACELL<T> temp;
    temp.m_pdata = B.m_pdata; // no memory is created
    temp.m_row   = B.m_row;
    temp.m_col   = B.m_col;

    initialization(A.m_row + B.m_row, A.m_col);
    for(int i=1; i<=A.m_row + B.m_row; i++)
    {
      for(int j=1; j<=A.m_col; j++)
      {
        double value = 0.0;
        if(i<=A.m_row)
          value = A.get_a_value(i,j);
        else
          value = temp.get_a_value((i-A.m_row), j);
          
        set_a_value(i,j, value);          
      }
    }
    
    temp.m_pdata = NULL;
    temp.m_row   = 0;
    temp.m_col   = 0;    
  }
};

#endif
