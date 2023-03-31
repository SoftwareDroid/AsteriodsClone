#pragma once
#include "view/geometry.h"
#include <iostream>

/**
 * The grafic representation of the spaceship
 */
class SpaceShipGeometry {
public:
     /**
      * The scale factor to get the real dimensions
      */
    constexpr static float SCALE = 0.1842105;// 0.1842105;
    /**
     * Creates a spaceship geomerty
     * @param withThrust Should be geometry contain the thrust animation
     * @return the geometry of a spaceshi
     */
    static Geometry create(bool withThrust)  {
        std::vector<Geometry::Line> lines;
        //NOW nearly overlapping with Asteriodsv4 
        // NOTE Used Gimp to extract the pixel postions of the orginal space spaceship
        lines.push_back(Geometry::Line(0,128,192,64));
        lines.push_back(Geometry::Line(192,64,0,0));
        lines.push_back(Geometry::Line(0,0,40,30));
        lines.push_back(Geometry::Line(40,30,40,98));
        lines.push_back(Geometry::Line(40,98,0,128));
        // Antribs animation
        if(withThrust)
        {
            lines.push_back(Geometry::Line(40,30,6,64));
            lines.push_back(Geometry::Line(40,98,6,64));
        }
        
        // The origin is set automaticcly to center of the bounding box
        auto g = Geometry(lines);
        g.setScale(Vector2f(SCALE,SCALE));
        return g;
    }
};
