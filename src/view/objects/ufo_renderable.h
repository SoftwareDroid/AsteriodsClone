#pragma once
#include "view/geometry.h"

/**
 * The grafic represation of an ufo
 * 
 */
class UfoRenderable {
public:
    /**
     * different scale factors of the ufos
     */
    constexpr static float SCALE_FACTORS[] = {1.0,0.512f}; 
    /**
     * A ufo can be small or big
     */
    enum class Type {Big = 0,Small = 1};
    /**
     * constructs an ufo of a certain type
     * @param type the type of the ufo
     */
    UfoRenderable(Type t);
    /**
     * Returns the data for rendering the ufo 
     * @return the geometry of the ufo
     */
    const Geometry& getRenderData() const {return ufoGeometry;}
    /**
     * sets the position of the ufo 
     * @param pos the new position
     */
    void setPosition(const Vector2f& pos) {this->ufoGeometry.setPosition(pos);}
private:
    /**
     * The type of the ufo
     */
    Type t;
    /**
     * Creates the ufo geometry 
     * @return a geometry of a ufo
     */
    Geometry createUfoGeometry( );
    /**
     * the geometry of the ufo
     */
    Geometry ufoGeometry;
};
