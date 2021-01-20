#ifndef DALITZMODEL_COEFFICIENT_H
#define DALITZMODEL_COEFFICIENT_H

// STL.
#include <iostream>
#include <complex>

// DalitzModel.
#include "parameter.h"

namespace DalitzModel {

using complex_t = std::complex<double>;

class Parameter;

class Coefficient
{
friend class Parameter;
private:
  double    m_c1 = {0.};
  double    m_c2 = {0.}; 

public:
  complex_t m_state = {complex_t(0.,0.)};
  Coefficient() = default;
  Coefficient(const double& c1, const double& c2) :
    m_c1( c1 ),
    m_c2( c2 ),
    m_state( m_c1 , m_c2 )
  {}
  Coefficient(const Parameter& c1, const Parameter& c2) :
    m_c1( c1.m_state ),
    m_c2( c2.m_state ),
    m_state( m_c1 , m_c2 )
  {}
  virtual ~Coefficient() {}

  // Operators.
  friend std::ostream& operator<<(std::ostream& os, const Coefficient& coeff);
  friend std::istream& operator>>(std::istream& is, Coefficient& coeff);

  // Coefficient * Coefficient.
  friend const complex_t operator+(const Coefficient& left, const Coefficient& right);
  friend const complex_t operator-(const Coefficient& left, const Coefficient& right);
  friend const complex_t operator*(const Coefficient& left, const Coefficient& right);
  friend const complex_t operator/(const Coefficient& left, const Coefficient& right);

  // Coefficient ad left hand argument.
  friend const complex_t operator+(const Coefficient& left, const int&       right);
  friend const complex_t operator-(const Coefficient& left, const int&       right);
  friend const complex_t operator*(const Coefficient& left, const int&       right);
  friend const complex_t operator/(const Coefficient& left, const int&       right);
  friend const complex_t operator+(const Coefficient& left, const double&    right);
  friend const complex_t operator-(const Coefficient& left, const double&    right);
  friend const complex_t operator*(const Coefficient& left, const double&    right);
  friend const complex_t operator/(const Coefficient& left, const double&    right);
  friend const complex_t operator+(const Coefficient& left, const float&     right);
  friend const complex_t operator-(const Coefficient& left, const float&     right);
  friend const complex_t operator*(const Coefficient& left, const float&     right);
  friend const complex_t operator/(const Coefficient& left, const float&     right);
  friend const complex_t operator+(const Coefficient& left, const complex_t& right);
  friend const complex_t operator-(const Coefficient& left, const complex_t& right);
  friend const complex_t operator*(const Coefficient& left, const complex_t& right);
  friend const complex_t operator/(const Coefficient& left, const complex_t& right);
  friend const complex_t operator+(const Coefficient& left, const Parameter& right);
  friend const complex_t operator-(const Coefficient& left, const Parameter& right);
  friend const complex_t operator*(const Coefficient& left, const Parameter& right);
  friend const complex_t operator/(const Coefficient& left, const Parameter& right);

  // Coefficient as right hand argument.
  friend const complex_t operator+(const int&       left, const Coefficient& right);
  friend const complex_t operator-(const int&       left, const Coefficient& right);
  friend const complex_t operator*(const int&       left, const Coefficient& right);
  friend const complex_t operator/(const int&       left, const Coefficient& right);
  friend const complex_t operator+(const double&    left, const Coefficient& right);
  friend const complex_t operator-(const double&    left, const Coefficient& right);
  friend const complex_t operator*(const double&    left, const Coefficient& right);
  friend const complex_t operator/(const double&    left, const Coefficient& right);
  friend const complex_t operator+(const float&     left, const Coefficient& right);
  friend const complex_t operator-(const float&     left, const Coefficient& right);
  friend const complex_t operator*(const float&     left, const Coefficient& right);
  friend const complex_t operator/(const float&     left, const Coefficient& right);
  friend const complex_t operator+(const complex_t& left, const Coefficient& right);
  friend const complex_t operator-(const complex_t& left, const Coefficient& right);
  friend const complex_t operator*(const complex_t& left, const Coefficient& right);
  friend const complex_t operator/(const complex_t& left, const Coefficient& right);
  friend const complex_t operator+(const Parameter& left, const Coefficient& right);
  friend const complex_t operator-(const Parameter& left, const Coefficient& right);
  friend const complex_t operator*(const Parameter& left, const Coefficient& right);
  friend const complex_t operator/(const Parameter& left, const Coefficient& right);
};

// I/O operators.
std::ostream& operator<<(std::ostream& os, const Coefficient& coeff)
{
  os << "(" << coeff.m_c1 << "," << coeff.m_c2 << ")";
  return os;
}

std::istream& operator>>(std::istream& is, Coefficient& coeff)
{
  // Input of the form " c1 , c2".
  std::string comma;
  is >> coeff.m_c1 >> comma >> coeff.m_c2;
  coeff.m_state = complex_t(coeff.m_c1,coeff.m_c2);
  return is;
}

// Operators.
inline const complex_t operator+(const Coefficient& left, const Coefficient& right)
{
  return left.m_state + right.m_state;
}

inline const complex_t operator-(const Coefficient& left, const Coefficient& right)
{
  return left.m_state - right.m_state;
}

inline const complex_t operator*(const Coefficient& left, const Coefficient& right)
{
  return left.m_state * right.m_state;
}

inline const complex_t operator/(const Coefficient& left, const Coefficient& right)
{
  return left.m_state / right.m_state;
}

inline const complex_t operator+(const Coefficient& left, const int& right)
{
  return left.m_state + (double)right;
}

inline const complex_t operator-(const Coefficient& left, const int& right)
{
  return left.m_state - (double)right;
}

inline const complex_t operator*(const Coefficient& left, const int& right)
{
  return left.m_state * (double)right;
}

inline const complex_t operator/(const Coefficient& left, const int& right)
{
  return left.m_state / (double)right;
}

inline const complex_t operator+(const Coefficient& left, const double& right)
{
  return left.m_state + right;
}

inline const complex_t operator-(const Coefficient& left, const double& right)
{
  return left.m_state - right;
}

inline const complex_t operator*(const Coefficient& left, const double& right)
{
  return left.m_state * right;
}

inline const complex_t operator/(const Coefficient& left, const double& right)
{
  return left.m_state / right;
}

inline const complex_t operator+(const Coefficient& left, const float& right)
{
  return left.m_state + (double)right;
}

inline const complex_t operator-(const Coefficient& left, const float& right)
{
  return left.m_state - (double)right;
}

inline const complex_t operator*(const Coefficient& left, const float& right)
{
  return left.m_state * (double)right;
}

inline const complex_t operator/(const Coefficient& left, const float& right)
{
  return left.m_state / (double)right;
}

inline const complex_t operator+(const Coefficient& left, const complex_t& right)
{
  return left.m_state + right;
}

inline const complex_t operator-(const Coefficient& left, const complex_t& right)
{
  return left.m_state - right;
}

inline const complex_t operator*(const Coefficient& left, const complex_t& right)
{
  return left.m_state * right;
}

inline const complex_t operator/(const Coefficient& left, const complex_t& right)
{
  return left.m_state / right;
}

inline const complex_t operator+(const Coefficient& left, const Parameter& right)
{
  return left.m_state + right.m_state;
}

inline const complex_t operator-(const Coefficient& left, const Parameter& right)
{
  return left.m_state - right.m_state;
}

inline const complex_t operator*(const Coefficient& left, const Parameter& right)
{
  return left.m_state * right.m_state;
}

inline const complex_t operator/(const Coefficient& left, const Parameter& right)
{
  return left.m_state / right.m_state;
}

inline const complex_t operator+(const int& left, const Coefficient& right)
{
  return (double)left + right.m_state;
}

inline const complex_t operator-(const int& left, const Coefficient& right)
{
  return (double)left - right.m_state;
}

inline const complex_t operator*(const int& left, const Coefficient& right)
{
  return (double)left * right.m_state;
}

inline const complex_t operator/(const int& left, const Coefficient& right)
{
  return (double)left / right.m_state;
}

inline const complex_t operator+(const double& left, const Coefficient& right)
{
  return left + right.m_state;
}

inline const complex_t operator-(const double& left, const Coefficient& right)
{
  return left - right.m_state;
}

inline const complex_t operator*(const double& left, const Coefficient& right)
{
  return left * right.m_state;
}

inline const complex_t operator/(const double& left, const Coefficient& right)
{
  return left / right.m_state;
}

inline const complex_t operator+(const float& left, const Coefficient& right)
{
  return (double)left + right.m_state;
}

inline const complex_t operator-(const float& left, const Coefficient& right)
{
  return (double)left - right.m_state;
}

inline const complex_t operator*(const float& left, const Coefficient& right)
{
  return (double)left * right.m_state;
}

inline const complex_t operator/(const float& left, const Coefficient& right)
{
  return (double)left / right.m_state;
}

inline const complex_t operator+(const complex_t& left, const Coefficient& right)
{
  return left + right.m_state;
}
inline const complex_t operator-(const complex_t& left, const Coefficient& right)
{
  return left - right.m_state;
}
inline const complex_t operator*(const complex_t& left, const Coefficient& right)
{
  return left * right.m_state;
}
inline const complex_t operator/(const complex_t& left, const Coefficient& right)
{
  return left / right.m_state;
}

inline const complex_t operator+(const Parameter& left, const Coefficient& right)
{
  return left.m_state + right.m_state;
}

inline const complex_t operator-(const Parameter& left, const Coefficient& right)
{
  return left.m_state - right.m_state;
}

inline const complex_t operator*(const Parameter& left, const Coefficient& right)
{
  return left.m_state * right.m_state;
}

inline const complex_t operator/(const Parameter& left, const Coefficient& right)
{
  return left.m_state / right.m_state;
}

} // namespace DalitzModel

#endif