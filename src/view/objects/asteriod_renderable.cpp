#include "asteriod_renderable.h"
#include "share/random.h"
#include <iostream>
#include <assert.h>

constexpr float AsteriodRenderable::SCALE_FACTORS[];

AsteriodRenderable::AsteriodRenderable(int type) :shape(static_cast<AsteriodRenderable::Shape>(Random::getRandomInt(0,2))), type(type),asteriodGeometry( createAsteriodGeometry())
{
}


Geometry AsteriodRenderable::createAsteriodGeometry()
{
//    assert(this->type == 0);

    std::vector<Geometry::Line> lines;    
    const float scale = SCALE_FACTORS[(int)this->type];

    switch(shape) {
        case AsteriodRenderable::Shape::FORM_1:
        {
            lines.push_back(Geometry::Line(1,65,24,87));
            lines.push_back(Geometry::Line(24,87,34,75));
            lines.push_back(Geometry::Line(34,75,66,87));
            lines.push_back(Geometry::Line(66,87,88,55));
            lines.push_back(Geometry::Line(88,55,68,34));
            lines.push_back(Geometry::Line(68,34,88,23));
            lines.push_back(Geometry::Line(88,23,66,1));
            lines.push_back(Geometry::Line(66,1,45,13));
            lines.push_back(Geometry::Line(45,13,24,1));
            lines.push_back(Geometry::Line(24,1,1,23));
            lines.push_back(Geometry::Line(1,23,13,44));
            lines.push_back(Geometry::Line(13,44,1,65));
            break;
        }
        case AsteriodRenderable::Shape::FORM_2:
        {
            lines.push_back(Geometry::Line(2,59,25,91));
            lines.push_back(Geometry::Line(25,91,45,58));
            lines.push_back(Geometry::Line(45,58,45,91));
            lines.push_back(Geometry::Line(45,91,68,91));
            lines.push_back(Geometry::Line(68,91,89,59));
            lines.push_back(Geometry::Line(89,59,89,37));
            lines.push_back(Geometry::Line(89,37,67,6));
            lines.push_back(Geometry::Line(67,6,35,6));
            lines.push_back(Geometry::Line(35,6,2,37));
            lines.push_back(Geometry::Line(2,37,25,48));
            lines.push_back(Geometry::Line(25,48,2,59));
            break;;
        }
        case AsteriodRenderable::Shape::FORM_3:
        {
          lines.push_back(Geometry::Line(5,66,26,88));
          lines.push_back(Geometry::Line(26,88,60,88));
          lines.push_back(Geometry::Line(60,88,92,66));
          lines.push_back(Geometry::Line(92,66,80,45));
          lines.push_back(Geometry::Line(80,45,92,24));
          lines.push_back(Geometry::Line(92,24,70,2));
          lines.push_back(Geometry::Line(70,2,49,24));
          lines.push_back(Geometry::Line(49,24,26,2));
          lines.push_back(Geometry::Line(26,2,5,23));
          lines.push_back(Geometry::Line(5,23,5,66));
         break;
        }
    };

     auto g = Geometry(lines);
     g.setScale(Vector2f(scale,scale));

    return g;
}
