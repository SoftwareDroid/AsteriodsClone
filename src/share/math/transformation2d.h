#pragma once
#include <cmath>
#include "vector2f.h"

/**
 * A class for applying 2d Transformations (Scale,Rotate,Transalte) to vectors
 */
class Transformation {
public:
      /**
   * Applies a 2d Transomfario to a point
   * @param input the vector which should be transformed
   * @param translate the translation
   * @param angle the rotation around the z-axis
   * @param scaleX the scaling in X direction
   * @param scaleY the scaling in Y direction 
   * @return the transformed vector
   */
    static Vector2f applyTransformation2D(const Vector2f& input ,const Vector2f& translate, float rotateAngle, float scaleX, float scaleY) {
    Vector2f result(input);
    float s = std::sin(rotateAngle);
    float c = std::cos(rotateAngle);
    result *= Vector2f(scaleX,scaleY);
    float xnew = result.x * c - result.y * s;
    float ynew = result.x * s + result.y * c;
    result.x = xnew ;
    result.y = ynew ;
    result += translate;
    return result;
    }

    /**
   * rotate a vector around the z axis in the origin
   * @param input the vector which should be transformed
   * @param rotateAnlge the rotation angle in radian
   */
    static Vector2f rotatePoint(const Vector2f& input,float rotateAngle) {
        Vector2f result(input);
        const float s = std::sin(rotateAngle);
        const float c = std::cos(rotateAngle);
        const float xnew = result.x * c - result.y * s;
        const float ynew = result.x * s + result.y * c;
        return Vector2f(xnew,ynew);
    }
    
};
