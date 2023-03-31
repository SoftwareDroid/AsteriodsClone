#include "spaceship_renderable.h"

SpaceshipRenderable::SpaceshipRenderable()
{
    thrustAnimationTimer.start();
}

void SpaceshipRenderable::update(const Vector2f& pos, float angle, bool lastFrameAccelerating)
{
    this->playerGeometry.setPosition(pos);
    this->playerGeometry.setRotation(angle);
    this->lastFrameAccelerating = lastFrameAccelerating;
    updateThrust();
}


std::vector<Geometry::Line> SpaceshipRenderable::getTransformedLines() const
{
    std::vector<Geometry::Line> ret = this->playerGeometry.getTransformedLines();
    // Remove ANimation if we don't accelelarte or toggling (phaseA)
    if(thrushAnimationPhaseA || !lastFrameAccelerating)
    {
        //Remove Thrusht Animation in PhaseA
        ret.pop_back();
        ret.pop_back();
    }
    return ret;
}

Geometry& SpaceshipRenderable::getGeometry()
{
    return playerGeometry;
}

void SpaceshipRenderable::updateThrust()
{
        // Toggle ANimation TImer
    if(thrushAnimationPhaseA)
    {
      if(thrustAnimationTimer.get_ticks() > THRUST_ANINIMATION_PHASE_A_IN_MS)
      {
          thrustAnimationTimer.start();
          thrushAnimationPhaseA = !thrushAnimationPhaseA;
      }
    }
    else 
    {
       if(thrustAnimationTimer.get_ticks() > THRUST_ANINIMATION_PHASE_B_IN_MS)
      {
          thrustAnimationTimer.start();
          thrushAnimationPhaseA = !thrushAnimationPhaseA;
      }
    }
}
