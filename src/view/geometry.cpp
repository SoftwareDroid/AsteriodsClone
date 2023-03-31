#include "geometry.h"
#include "share/math/transformation2d.h"
#include <vector>
#include <limits>
#include <tuple>
#include <iostream>
#include <assert.h>

std::vector<Geometry::Line> Geometry::getTransformedLines() const
{
    std::vector<Line> result;
    for(std::size_t n = 0; n < lines.size();++n) {
        // const Vector2f& input ,float translateX,float translateY, float rotateAngle, float scaleX, float scaleY
        Vector2f newStart = Transformation::applyTransformation2D(lines[n].start,this->position, this->angle,this->scale.x,this->scale.y);
        Vector2f newEnd = Transformation::applyTransformation2D(lines[n].end,this->position, this->angle,this->scale.x,this->scale.y);
        result.push_back( Line(newStart, newEnd));
    }   
    return result;
}

Geometry::Line Geometry::getTransformedLine(std::size_t index) const
{
    assert(index < this->lines.size());
    Vector2f newStart = Transformation::applyTransformation2D(lines[index].start,this->position, this->angle,this->scale.x,this->scale.y);
    Vector2f newEnd = Transformation::applyTransformation2D(lines[index].end,this->position, this->angle,this->scale.x,this->scale.y);
    return Line(newStart, newEnd);
}


void Geometry::centerObjectInOrigin()
{
    std::tuple<Vector2f, Vector2f> boundingBox = this->getBoundingBox2(lines);
    float sizeX = (std::get<1>(boundingBox).x - std::get<0>(boundingBox).x) / 2.0;
    float sizeY = (std::get<1>(boundingBox).y - std::get<0>(boundingBox).y) / 2.0;
    Vector2f centerOfBox(std::get<0>(boundingBox).x + sizeX,std::get<0>(boundingBox).y + sizeY);

    std::vector<Line> lines2;
     for(std::size_t n = 0; n < this->lines.size();++n) 
    {
        lines[n] = Line(lines[n].start  - centerOfBox,lines[n].end  - centerOfBox);
    }
    

}

void Geometry::setPosition(const Vector2f& pos)
{
    this->position = pos;
    this->worldBoundingBox =  getBoundingBox2(getTransformedLines());
}
void Geometry::setRotation(float angle)
{
    this->angle = angle;
    dir = Transformation::rotatePoint(Vector2f(1,0),angle);
    this->worldBoundingBox =  getBoundingBox2(getTransformedLines());
}

void Geometry::setScale(const Vector2f& scale)
{
    this->scale = scale;
    this->worldBoundingBox =  getBoundingBox2(getTransformedLines());
}
const Vector2f & Geometry::getPosistion() const
{
    return position;

}

const Vector2f & Geometry::getScale() const
{
    return scale;
}

Geometry::Geometry(const std::vector<Line>& lines) :lines(lines),angle(0),position(0,0),scale(1,1),dir(1,0), worldBoundingBox(std::make_tuple(Vector2f(0,0),Vector2f(0,0)))
{
    centerObjectInOrigin();
    // Recalc the bounding box here so that have a bounding box every time
    this->worldBoundingBox =  getBoundingBox2(getTransformedLines());
}

std::tuple<Vector2f,Vector2f> Geometry::getBoundingBox2(const std::vector<Geometry::Line>& lines)
{
    Vector2f::VecDataType minX = std::numeric_limits<Vector2f::VecDataType>::max();
    Vector2f::VecDataType maxX  = std::numeric_limits<Vector2f::VecDataType>::min();
    Vector2f::VecDataType minY  = std::numeric_limits<Vector2f::VecDataType>::max();
    Vector2f::VecDataType maxY = std::numeric_limits<Vector2f::VecDataType>::min();
    for(const Line& l : lines) {
        minX = std::min(l.start.x,minX);
        minX = std::min(l.end.x,minX);
        maxX = std::max(l.start.x,maxX);
        maxX = std::max(l.end.x,maxX);
        
        minY = std::min(l.start.y,minY);
        minY = std::min(l.end.y,minY);
        maxY = std::max(l.start.y,maxY);
        maxY = std::max(l.end.y,maxY);
    }
    return std::make_tuple(Vector2f(minX,minY),Vector2f(maxX,maxY)); 
}

std::tuple<Vector2f, Vector2f> Geometry::getBoundingBox() const
{
    return this->worldBoundingBox;
}





