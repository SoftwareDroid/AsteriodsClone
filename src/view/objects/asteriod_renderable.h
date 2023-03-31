#pragma once
#include "view/geometry.h"

/**
 *  Contains all things which are relevant for rendering a asteriod.
 */
class AsteriodRenderable {
public:
    /**
     * constructs a asteriod
     * @param type the type of asteriod
     */
    AsteriodRenderable(int type);
    /**
     * The scale factors of the different astiod sizes
     */
    constexpr static float SCALE_FACTORS[] = {1.0,0.5,0.25};    //NOTE correctly measured
    /**
     * Different shapes the asteriod
     */
    enum class Shape {FORM_1 = 0, FORM_2 = 1, FORM_3 = 2};
    /**
     * The shape of the asteriod
     */
    const Shape shape = Shape::FORM_1;
    /**
     * The type (size) of the asteriod
     */
    const int type;
    /**
     * The geometry of the asteriod
     */
    Geometry asteriodGeometry;
    private:
        /**
         * Creates a asteriod geometry 
         * @return the created asteriod geometr
         */
    Geometry createAsteriodGeometry();

    
};
