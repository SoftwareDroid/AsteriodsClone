#pragma once
#include "view/geometry.h"
#include "spaceship_geometry.h"
#include "share/timer/timer.h"

 /**
  * A grafic animation of the spaceship
  */
class SpaceshipRenderable {
public:
    constexpr static int THRUST_ANINIMATION_PHASE_A_IN_MS = 300; //Time betweeen hit han spawning a new ship
    constexpr static int THRUST_ANINIMATION_PHASE_B_IN_MS = 300; //Time betweeen hit han spawning a new ship
     /**
      * Constructs the spaceship animation
      */
    SpaceshipRenderable();
    /**
     * Return the data relevant for rendering
     *  @return the geometry of the spaceship
     */
    Geometry& getGeometry();
    //const Geometry& getRenderData() const {return playerGeometry;}
     /**
      * returns the transformed geometry of the spaceship including a thrush aninmation
      * @return the spaceship with animation depending of the time
      */
    std::vector<Geometry::Line> getTransformedLines() const;
     /**
      * Updates the spaceship and the thrust anination
      */
    void update(const Vector2f& pos,float angle,bool lastFrameAccelerating);
private:
    /**
     * The geometry of the spaceship
     */
    Geometry playerGeometry = SpaceShipGeometry::create(true);
    /*
     * The current animation phase of the thrust
     */
    bool thrushAnimationPhaseA = true;
    /**
     * Was the spaceship accelrating in the last time frame
     * Is need to correctly show a thrust animation
     */
    bool lastFrameAccelerating; 
    /**
     * A Timer for measuring the thrust anination phases
     */
    Timer thrustAnimationTimer;
    /**
     * Updates the thrust animation
     */
    void updateThrust();
};
