#pragma once
#include <vector>
#include "share/math/vector2f.h"
#include <tuple>

/**
 * A representation of an transformed set of simple line segements
 */
class Geometry {
/**
 * the rotation angle of all line segments
 */
    float angle;
    /**
     * the transformation origin of the ufo
     */
    Vector2f position;
    /**
     * The scaling of the ufo in x and y direction
     */
    Vector2f scale;
    /**
     * a vector which describes the alignment in the world
     */
    Vector2f dir;

public:
    /**
     * A line segemnt of an start and end point
     */
    class Line{
    public:
        Vector2f start;
        Vector2f end;
        /**
         * constructs an new line of foor scalars
         * @param a x of first point 
         * @param b y of first point
         * @param c x of second point
         * @param d y of second point
         */
        Line(const Vector2f::VecDataType& a,const Vector2f::VecDataType& b,const Vector2f::VecDataType& c,const Vector2f::VecDataType& d) : start(a,b), end(c,d) {}
        /**
         * costructs a line of two 
         */
        Line(const Vector2f& start,const Vector2f& end) : start(start), end(end) {}
    };
    /**
     * constructs a geometry of an vector of lines
     * @param lines an vector of lines
     */
    Geometry(const std::vector< Geometry::Line >& lines); 
    /**
     * returns the bounding box of the geometry in world corrdinates 
     * @return an tuple which consits of min and max
     */
    std::tuple<Vector2f,Vector2f> getBoundingBox() const;   
    /**
     * returns the rotation in radian
     * @return the rotation angle
     */
    float getRotation() const {return angle;} 
    /**
     * return the position of the geomery
     * @return an vector
     */
    const Vector2f& getPosistion() const;
    /**
     * returns the scaling of the geometry
     * @return an vector describes the scaling with the x and y axis
     */
    const Vector2f& getScale() const;
    /**
     * Sets the rotation of geometry 
     * @param angle in radina
     */
    void setRotation(float angle); 
    /**
     * returns the forward direction of the geomtry 
     * @return an vector describes the forward direction
     */
    const Vector2f& getForwardDirection() const {return dir;}
    /**
     * sets the position of the geometry
     * @param pos the new position
     */
    void setPosition(const Vector2f& pos);
     /**
      * sets the new scale of geomery
      * @param scale the new scale of the x and y axis
      */
    void setScale(const Vector2f& scale);
    /**
     * return an all lines segemnts with the applied transformation
     * @return an vector of transformed lines
     */
    std::vector<Geometry::Line> getTransformedLines() const;
        /**
     * return an all lines segemnts without the applied transformation
     * @return an vector of not transformed lines
     */
    const std::vector<Geometry::Line>& getObjectWithoutTransformation() const {return lines;}
    /**
     * return a transformed lines of an index
     * @param index the index of the line
     * @return the transformed line
     */
    Geometry::Line getTransformedLine(std::size_t index) const;
    /**
     * return the number of line segments 
     * @return the number of line segemetns
     */
    inline int size() const {return lines.size();}
private:
    /**
     * returns the bounding box of lines
     * @param lines the lines for calculting the bounding box 
     * @return the bounding box of the lines
     */
    std::tuple<Vector2f,Vector2f> getBoundingBox2(const std::vector<Geometry::Line>& lines);
    /**
     * the cached bounding box
     */
    std::tuple<Vector2f,Vector2f> worldBoundingBox;
    /**
     * the line segements
     */
    std::vector<Line> lines;
    /**
     * centers all line segments at the origin
     */
    void centerObjectInOrigin();
};
