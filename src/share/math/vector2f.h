#pragma once
#include <algorithm>

/**
 * A 2d vector math class 
 */
class Vector2f {
public:
    using VecDataType = float;
    VecDataType x;
    VecDataType y;
   /**
   * Constructs a new vector
   * @param x1 the first component
   * @param x2 the second component
   */
    Vector2f(VecDataType x1, VecDataType y1) : x(x1),y(y1) 
    {
        
    }
  /**
   * Returns the squared length of the vector
   * @return the squared length
   */
    inline float getSquaredLen() const {
        return x*x + y*y;
    }
    

    
    
   /**
   * A vector assignment by another vector
   * @param other a other vector
   * @return the result of the assignment
   */
    Vector2f& operator=(Vector2f other)
    {
        std::swap(x, other.x);
        std::swap(y, other.y);
        return *this;
    }
   /**
   * Substracts two vectors
   * @param v another vector
    * @return the result
   */
    inline const Vector2f operator - (const Vector2f&  v) const { return Vector2f(x - v.x, y - v.y); }
       /**
   * Adds two vectors
   * @param v another vector
  * @return the result
   */
    inline const Vector2f operator + (const Vector2f&  v) const { return Vector2f(x + v.x, y + v.y); }
       /**
   * multiplies a vector with a number
   * @param v a scalar
   * @return the result
   */
    inline const Vector2f operator * (VecDataType v) const { return Vector2f(x * v, y * v); }
    /**
   * divides a vector with a number
   * @param v a scalar
   * @return the result
   */
    inline const Vector2f operator / (VecDataType v) const { return Vector2f(x / v, y / v); }
    /**
   * muliply this vector with a scalars
   * @param v a scalar
   * @return the result
   */
    inline Vector2f & operator *= (VecDataType v) { x *= v; y *= v; return *this; }
    /**
   * divide this vector with a scalars
   * @param v a scalar
   * @return the result
   */
    inline Vector2f & operator /= (VecDataType v) { x /= v; y /= v; return *this; }
   /**
   * Add a vector to this vector
   * @param v a vector
   * @return the result
   */
    inline Vector2f & operator += (const Vector2f & v) { x += v.x; y += v.y; return *this; }
    /**
   * Substracs a vector from this vector
   * @param v a vector
   * @return the result
   */
    inline Vector2f & operator -= (const Vector2f & v) { x -= v.x; y -= v.y; return *this; }
        /**
   * Multiplies a vector with vector
   * @param v a vector
   * @return the result
   */
    inline Vector2f & operator *= (const Vector2f & v) { x *= v.x; y *= v.y; return *this; }
    /**
   * Divides a vector with vector
   * @param v a vector
   * @return the result
   */
    inline Vector2f & operator /= (const Vector2f & v) { x /= v.x; y /= v.y; return *this; }
};
