#include "gtest/gtest.h"
#include "share/math/transformation2d.h"
#include "share/math/helper.h"

TEST(Math, transformation) {
    //Vector2f origin(0,0);
    Vector2f point1(1,0);
    // (const Vector2f& origin,const Vector2f& input ,const Vector2f& translate, float rotateAngle, float scaleX, float scaleY) {
    Vector2f result = Transformation::applyTransformation2D(point1,Vector2f(0,0),degToRad(0),1,1);
    // 0 Grad
    EXPECT_NEAR(result.x,1,0.1);
    EXPECT_NEAR(result.y,0,0.1);
    // 190 Grad
    result = Transformation::applyTransformation2D(point1,Vector2f(0,0),degToRad(180),1,1);
    EXPECT_NEAR(result.x,-1,0.1);
    EXPECT_NEAR(result.y,0,0.1);
    // 90 Grad
    result = Transformation::applyTransformation2D(point1,Vector2f(0,0),degToRad(90),1,1);
    EXPECT_NEAR(result.x,0,0.1);
    EXPECT_NEAR(result.y,1,0.1);
    
    // Test with scale factor
    float scaleFactor = 1.25;
    result = Transformation::applyTransformation2D(point1,Vector2f(0,0),degToRad(90),scaleFactor,scaleFactor);
    EXPECT_NEAR(result.x,0 * scaleFactor,0.1);
    EXPECT_NEAR(result.y,1 * scaleFactor,0.1);
    scaleFactor = 0.2;
    result = Transformation::applyTransformation2D(point1,Vector2f(0,0),degToRad(0),scaleFactor,scaleFactor);
    EXPECT_NEAR(result.x,1 * scaleFactor,0.1);
    EXPECT_NEAR(result.y,0 * scaleFactor,0.1);
    
    // Test with translate, scale and Rotation
    Vector2f t1(0.4,0.6);
    scaleFactor = 1.4;
    result = Transformation::applyTransformation2D(point1,t1,degToRad(90),scaleFactor,scaleFactor);
    EXPECT_NEAR(result.x,(0 * scaleFactor) + t1.x,0.1);
    EXPECT_NEAR(result.y,(1 * scaleFactor) + t1.y,0.1);

}
