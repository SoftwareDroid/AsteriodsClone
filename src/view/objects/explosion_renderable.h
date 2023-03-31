#pragma once
#include "view/geometry.h"
#include "share/timer/timer.h"

/**
 * An grafic reprensation of an explosion
 */
class ExplosionRenderable {
public:
    /**
     * The type of the explosion
     */
    enum class Type {Spaceship,Asteriod};
    /**
     * return if the explosion is alive 
     * @return the result
     */
    bool isAlive();
    /**
     * Return data for rending the explosions as a vector of lines
     * @return a list of lines
     */
    std::vector<Geometry::Line> getRenderData() const;
    /**
     * Constructs an explosion
     * @param startPosition the startPosition of the explosion
     * @param type spaceship or point cloud
     */
    ExplosionRenderable(const Vector2f& startPosition, Type type);
private:
    /**
     * A part of the explosion with heading and life time
     */
   struct Part 
    {
        Geometry::Line startLine;
        Vector2f heading;
        int liveTimeInMS;
    };
    /**
     * The type of the explosion
     */
    const Type type;
    /**
     * A timer for measuring the life of the explosion
     */
    Timer timer;
    /**
     * the position (center) of the explsoion
     */
    Vector2f pos;
    /**
     * the parts of the explsion
     */
    std::vector<ExplosionRenderable::Part> parts;
    /**
     * creates an asteriod explosion
     */
    void initAsteriodExplosion();
        /**
     * creates an spaceship explosion
     */
    void initSpaceshipExplosion();

};
