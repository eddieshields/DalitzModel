#ifndef DALITZMODEL_PARAMETER_H
#define DALITZMODEL_PARAMETER_H

// STL.
#include <iostream>
#include <complex>

// DalitzModel.
#include "random.h"

namespace DalitzModel {

using complex_t = std::complex<double>;

class Parameter
{
private:
  double m_value = {0.};
  double m_error = {0.};

public:
  double m_state = {0.};
  Parameter() = default;
  Parameter(const double& val, const double& err = 0) :
    m_value( val ),
    m_error( Random::normal( 0 , err ) )
  {
    m_state = m_value + m_error;
  }
  virtual ~Parameter() {}

  double value() const { return m_value; }
  double error() const { return m_error; }

  void SetValue(const double& value) { m_value = value; }
  void SetError(const double& error) { m_error = error; }

  // Operators.
  friend std::ostream& operator<<(std::ostream& os, const Parameter& param);
  friend std::istream& operator>>(std::istream& is, Parameter& param);


  // Parameter * Parameter.
  friend const double    operator+(const Parameter& left, const Parameter&   right);
  friend const double    operator-(const Parameter& left, const Parameter&   right);
  friend const double    operator*(const Parameter& left, const Parameter&   right);
  friend const double    operator/(const Parameter& left, const Parameter&   right);

  // Parameter as left hand argument.
  friend const double    operator+(const Parameter& left, const int&         right);
  friend const double    operator-(const Parameter& left, const int&         right);
  friend const double    operator*(const Parameter& left, const int&         right);
  friend const double    operator/(const Parameter& left, const int&         right);
  friend const double    operator+(const Parameter& left, const double&      right);
  friend const double    operator-(const Parameter& left, const double&      right);
  friend const double    operator*(const Parameter& left, const double&      right);
  friend const double    operator/(const Parameter& left, const double&      right);
  friend const double    operator+(const Parameter& left, const float&       right);
  friend const double    operator-(const Parameter& left, const float&       right);
  friend const double    operator*(const Parameter& left, const float&       right);
  friend const double    operator/(const Parameter& left, const float&       right);
  friend const complex_t operator+(const Parameter& left, const complex_t&   right);
  friend const complex_t operator-(const Parameter& left, const complex_t&   right);
  friend const complex_t operator*(const Parameter& left, const complex_t&   right);
  friend const complex_t operator/(const Parameter& left, const complex_t&   right);

  // Parameter as right hand argument.
  friend const double    operator+(const int&         left, const Parameter& right);
  friend const double    operator-(const int&         left, const Parameter& right);
  friend const double    operator*(const int&         left, const Parameter& right);
  friend const double    operator/(const int&         left, const Parameter& right);
  friend const double    operator+(const double&      left, const Parameter& right);
  friend const double    operator-(const double&      left, const Parameter& right);
  friend const double    operator*(const double&      left, const Parameter& right);
  friend const double    operator/(const double&      left, const Parameter& right);
  friend const double    operator+(const float&       left, const Parameter& right);
  friend const double    operator-(const float&       left, const Parameter& right);
  friend const double    operator*(const float&       left, const Parameter& right);
  friend const double    operator/(const float&       left, const Parameter& right);
  friend const complex_t operator+(const complex_t&   left, const Parameter& right);
  friend const complex_t operator-(const complex_t&   left, const Parameter& right);
  friend const complex_t operator*(const complex_t&   left, const Parameter& right);
  friend const complex_t operator/(const complex_t&   left, const Parameter& right);
};


// I/O operators.
std::ostream& operator<<(std::ostream& os, const Parameter& param)
{
  os << param.m_value << " +- " << param.m_error;
  return os;
}

std::istream& operator>>(std::istream& is, Parameter& param)
{
  // Input of the form " value +- error".
  std::string pm;
  double err_val;
  is >> param.m_value >> pm >> err_val;
  param.m_error = Random::normal( 0 , err_val );
  return is;
}

// Operators.
inline const double operator+(const Parameter& left, const Parameter& right)
{
  return left.m_state + right.m_state;
}

inline const double operator-(const Parameter& left, const Parameter& right)
{
  return left.m_state - right.m_state;
}

inline const double operator*(const Parameter& left, const Parameter& right)
{
  return left.m_state * right.m_state;
}

inline const double operator/(const Parameter& left, const Parameter& right)
{
  return left.m_state / right.m_state;
}

inline const double operator+(const Parameter& left, const int& right)
{
  return left.m_state + (double)right;
}

inline const double operator-(const Parameter& left, const int& right)
{
  return left.m_state - (double)right;
}

inline const double operator*(const Parameter& left, const int& right)
{
  return left.m_state * (double)right;
}

inline const double operator/(const Parameter& left, const int& right)
{
  return left.m_state / (double)right;
}

inline const double operator+(const Parameter& left, const double& right)
{
  return left.m_state + right;
}

inline const double operator-(const Parameter& left, const double& right)
{
  return left.m_state - right;
}

inline const double operator*(const Parameter& left, const double& right)
{
  return left.m_state * right;
}

inline const double operator/(const Parameter& left, const double& right)
{
  return left.m_state / right;
}

inline const double operator+(const Parameter& left, const float& right)
{
  return left.m_state + (double)right;
}

inline const double operator-(const Parameter& left, const float& right)
{
  return left.m_state - (double)right;
}

inline const double operator*(const Parameter& left, const float& right)
{
  return left.m_state * (double)right;
}

inline const double operator/(const Parameter& left, const float& right)
{
  return left.m_state / (double)right;
}

inline const complex_t operator+(const Parameter& left, const complex_t& right)
{
  return left.m_state + right;
}

inline const complex_t operator-(const Parameter& left, const complex_t& right)
{
  return left.m_state - right;
}

inline const complex_t operator*(const Parameter& left, const complex_t& right)
{
  return left.m_state * right;
}

inline const complex_t operator/(const Parameter& left, const complex_t& right)
{
  return left.m_state / right;
}

inline const double operator+(const int& left, const Parameter& right)
{
  return (double)left + right.m_state;
}

inline const double operator-(const int& left, const Parameter& right)
{
  return (double)left - right.m_state;
}

inline const double operator*(const int& left, const Parameter& right)
{
  return (double)left * right.m_state;
}

inline const double operator/(const int& left, const Parameter& right)
{
  return (double)left / right.m_state;
}

inline const double operator+(const double& left, const Parameter& right)
{
  return left + right.m_state;
}

inline const double operator-(const double& left, const Parameter& right)
{
  return left - right.m_state;
}

inline const double operator*(const double& left, const Parameter& right)
{
  return left * right.m_state;
}

inline const double operator/(const double& left, const Parameter& right)
{
  return left / right.m_state;
}

inline const double operator+(const float& left, const Parameter& right)
{
  return (double)left + right.m_state;
}

inline const double operator-(const float& left, const Parameter& right)
{
  return (double)left - right.m_state;
}

inline const double operator*(const float& left, const Parameter& right)
{
  return (double)left * right.m_state;
}

inline const double operator/(const float& left, const Parameter& right)
{
  return (double)left / right.m_state;
}

inline const complex_t operator+(const complex_t& left, const Parameter& right)
{
  return left + right.m_state;
}
inline const complex_t operator-(const complex_t& left, const Parameter& right)
{
  return left - right.m_state;
}
inline const complex_t operator*(const complex_t& left, const Parameter& right)
{
  return left * right.m_state;
}
inline const complex_t operator/(const complex_t& left, const Parameter& right)
{
  return left / right.m_state;
}

} // namespace DalitzModel

#endif