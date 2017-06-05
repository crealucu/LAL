#ifndef __H__LINEAR_ALGEBRA_LIBRARY_OPERATORS_H__
#define __H__LINEAR_ALGEBRA_LIBRARY_OPERATORS_H__

/// operator + overriding : do result = A + B
///
/// param[in] A 1st input object
/// param[in] B 2nd input object
/// return T instant
template <class T>
constexpr T operator + (const T &A, const T &B)
{ 
  T temp;
  temp.add(A,B);
  return temp;
};

/// operator + overriding : do result = A + b, b = scalar
///
/// param[in] A input object
/// param[in] b a scalar
/// return T instant
template <class T>
constexpr T operator + (const T &A, const double b)
{ 
  T temp;
  temp.add(A,b);
  return temp;
};

/// operator + overriding : do result = a + B
///
/// param[in] a a scalar
/// param[in] B input object
/// return T instant
template <class T>
constexpr T operator + (const double a, const T &B)
{ 
  T temp;
  temp.add(B,a);
  return temp;
};

/// operator - overriding : do result = A - B
///
/// param[in] A 1st input object
/// param[in] B 2nd input object
/// return T instant
template <class T>
constexpr T operator - (const T &A, const T &B)
{ 
  T temp;
  temp.sub(A,B);
  return temp;
};

/// operator - overriding : do result = A - b
///
/// param[in] A 1st input object
/// param[in] B 2nd input object
/// return T instant
template <class T>
constexpr T operator - (const T &A, const double b)
{ 
  T temp;
  temp.add(A,-b);
  return temp;
};

/// operator - overriding : do result = A - b
///
/// param[in] A 1st input object
/// param[in] B 2nd input object
/// return T instant
template <class T>
constexpr T operator - (const double b, const T &A)
{ 
  T temp;
  temp.sub(b,A);
  return temp;
};

/// operator * overriding : do result = A * B
///
/// param[in] A 1st input object
/// param[in] B 2nd input object
/// return T instant
template <class T>
constexpr T operator * (const T &A, const T &B)
{ 
  T temp;
  temp.prod(A,B);
  return temp;
};

/// operator * overriding : do result = a * B
///
/// param[in] a a scalar
/// param[in] B input object
/// return T instant
template <class T>
constexpr T operator * (const double a, const T &B)
{ 
  T temp;
  temp.prod(B,a);
  return temp;
};

/// operator * overriding : do result = A * b
///
/// param[in] A input object to be multiplied
/// param[in] b a scalar to be multiplied
/// return T instant
template <class T>
constexpr T operator * (const T &A, const double b)
{ 
  T temp;
  temp.prod(A,b);
  return temp;
};

#endif