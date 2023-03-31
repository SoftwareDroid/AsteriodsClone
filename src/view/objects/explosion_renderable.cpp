#include "explosion_renderable.h"
#include <cmath>

ExplosionRenderable::ExplosionRenderable(const Vector2f& startPosition, ExplosionRenderable::Type type): 
type(type),
pos(startPosition)
{
    timer.start();
    if(type == Type::Spaceship)
    {
      initSpaceshipExplosion();  
    }
    else 
    {
        initAsteriodExplosion();
    }
}

bool ExplosionRenderable::isAlive()
 {
    return timer.get_ticks() <= (500.0f * 6);
}

std::vector<Geometry::Line> ExplosionRenderable::getRenderData() const
{
    int passedTicks = timer.get_ticks();

    float velocity = 39.0f / 3000.0f; //Pixel per ms
    float movedWay = velocity * passedTicks;
    std::vector<Geometry::Line> ret;
    for(int i = 0; i < parts.size();i++)
    {
        const Part& p = parts[i];
        if(passedTicks <= p.liveTimeInMS)
        {
            Vector2f newStart = p.startLine.start + p.heading * movedWay;
            Vector2f newEnd = p.startLine.end + p.heading * movedWay;
            ret.push_back(Geometry::Line(newStart,newEnd));
        }
    }
    return ret;
}

void ExplosionRenderable::initSpaceshipExplosion()
{
   Part partF{Geometry::Line(-11,12,-1,-2),Vector2f(5.1,3),3000};
   Part partA{Geometry::Line(0,3,4,8),Vector2f(5,-3),500};
   Part partC{Geometry::Line(7,2,11,11),Vector2f(-13,-6),2500};
   Part partB{Geometry::Line(2,5,10,1),Vector2f(-2,-3.9),2000};
   Part partD{Geometry::Line(-3,-12,7,-2),Vector2f(-5.2,2.9),1500};
   Part partE{Geometry::Line(-4,-8,2,-8),Vector2f(1,7.9),1000};
   parts.push_back(partA);
   parts.push_back(partB);
   parts.push_back(partC);
   parts.push_back(partD);
   parts.push_back(partE);
   parts.push_back(partF);
   for(Part& p : parts)
   {
       // Normalize all headings
       p.heading /= -std::sqrt(p.heading.getSquaredLen());
       // Move to the start
       p.startLine.start += pos;
       p.startLine.end += pos;
   }
}

void ExplosionRenderable::initAsteriodExplosion()
{
    std::vector<Geometry::Line> lines;    
    lines.push_back(Geometry::Line(9,7,10,8));
    lines.push_back(Geometry::Line(33,13,34,14));
    lines.push_back(Geometry::Line(64,7,65,8));
    lines.push_back(Geometry::Line(72,24,73,25));
    lines.push_back(Geometry::Line(26,31,27,32));
    lines.push_back(Geometry::Line(10,42,11,43));
    lines.push_back(Geometry::Line(48,47,49,48));
    lines.push_back(Geometry::Line(65,43,66,44));
    lines.push_back(Geometry::Line(64,53,65,54));
    lines.push_back(Geometry::Line(21,77,22,78));
    Vector2f min(9,7);
    Vector2f max(73,78);
    Vector2f center = min + ((max - min) * 0.5f);
    for(auto& l : lines)
    {
        Part part{l,l.start - center,2000};
        part.heading /= std::sqrt(part.heading.getSquaredLen());
        part.startLine.start += pos;
        part.startLine.end += pos;
        parts.push_back(part);
    }
}

