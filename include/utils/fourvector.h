#ifndef DALITZMODEL_FOURVECTOR_H
#define DALITZMODEL_FOURVECTOR_H

// STL.
#include <array>
#include <xmmintrin.h>
#include <smmintrin.h>

// DalitzModel.
#include "../colours.h"


/** \Class Vec4
 * 
 * A Four Vector class that is optimized using SIMD intrinsics.
 * Four vectors should be the ideal example for using SIMD intrinsics
 * as the entire vector can fit inside a register.
 * 
 * @author Edward Shields
 * @date 29/01/2021
 */
class Vec4
{
private:
  union {
    std::array<float,4> v;    ///< array that stores values.
    __m128              v4;   ///< intrinsic vector that is 128bits wide so can hold the full vector.
  };
public:
  Vec4() {}
  Vec4(const float& v1, const float& v2, const float& v3, const float& v4) :
    v( { v1 , v2 , v3 , v4 } )
  {}
  Vec4(const std::array<float,4>& vec) :
    v( vec )
  {}
  Vec4(const __m128& vec) :
    v4( vec )
  {}
  virtual ~Vec4() {};

  float& operator[](unsigned int& index) { return v[index]; }
  float& operator()(unsigned int& index) { return v[index]; }

  // I/O Operators.
  friend std::ostream& operator<<(std::ostream& os, const Vec4& vec);
  //friend std::istream& operator>>(std::istream& is, Vec4& vec);

  // Operators.
  Vec4  operator+(const Vec4& other);
  Vec4  operator-(const Vec4& other);
  float operator*(const Vec4& other);

  void operator+=(const Vec4& other);
  void operator-=(const Vec4& other);
};

// I/O operators.
std::ostream& operator<<(std::ostream& os, const Vec4& vec)
{
  os << MAGENTA << "(" << std::fixed << std::setprecision(5) << vec.v4[0]
                << "," << std::fixed << std::setprecision(5) << vec.v4[1]
                << "," << std::fixed << std::setprecision(5) << vec.v4[2]
                << "," << std::fixed << std::setprecision(5) << vec.v4[3]
                << ")" << RESET;
  return os;
}

Vec4 Vec4::operator+(const Vec4& other)
{
  return Vec4( _mm_add_ps( this->v4 , other.v4 ) );
}

Vec4 Vec4::operator-(const Vec4& other)
{
  return Vec4( _mm_sub_ps( this->v4 , other.v4 ) );
}

float Vec4::operator*(const Vec4& other)
{
  __m128 t4;
  // Multiply the two vectors together v1 = {v11,v12,v13,v14}, v2 = {v21,v22,v23,v24}.
  //  t = {v11*v21,v12*v22,v13*v23,v14*v24}.
  t4 = _mm_mul_ps( this->v4 , other.v4 );
  // Hadd the two vectors, now t becomes.
  // t = {v11*v21 + v12*v22, v13*v23 + v14*v24, v11*v21 + v12*v22, v13*v23 + v14*v24}.
  t4 = _mm_hadd_ps( t4 , t4 );
  // Hadd again so all elements become
  // ti = v11*v21 + v12*v22 + v13*v23 + v14*v24.
  t4 = _mm_hadd_ps( t4 , t4 );
  // Return first element of t1.
  // All elements are the same, the dot product of v1 and v2.
  return _mm_cvtss_f32(t4);
}

void Vec4::operator+=(const Vec4& other)
{
  this->v4 = _mm_add_ps( this->v4 , other.v4 );
}

void Vec4::operator-=(const Vec4& other)
{
  this->v4 = _mm_sub_ps( this->v4 , other.v4 );
}



#endif