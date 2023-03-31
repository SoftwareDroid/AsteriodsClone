#include "ufo_renderable.h"
#include <iostream>

UfoRenderable::UfoRenderable(UfoRenderable::Type t) : t(t),ufoGeometry(createUfoGeometry())
{
}


constexpr float UfoRenderable::SCALE_FACTORS[];

Geometry UfoRenderable::createUfoGeometry()
{
    std::vector<Geometry::Line> lines;    
    lines.push_back(Geometry::Line(0,22,17,33));
    lines.push_back(Geometry::Line(17,33,39,33));
    lines.push_back(Geometry::Line(39,33,56,22));
    lines.push_back(Geometry::Line(0,22,56,22));    
    lines.push_back(Geometry::Line(56,22,39,11)); 
    lines.push_back(Geometry::Line(39,11,34,0));    
    lines.push_back(Geometry::Line(34,0,23,0));    
    lines.push_back(Geometry::Line(23,0,17,11));    
    lines.push_back(Geometry::Line(17,11,0,22));
    lines.push_back(Geometry::Line(17,11,39,11));  
    auto g = Geometry(lines);
    const float scale = SCALE_FACTORS[static_cast<int>(t)];
     g.setScale(Vector2f(scale,scale));
    std::cout<<std::get<0>(g.getBoundingBox()).x<<std::endl;

    return g;
}
