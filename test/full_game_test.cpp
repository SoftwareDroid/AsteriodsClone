#include "gtest/gtest.h"
#include "share/random.h"
#include "model/game_logic.h"
#include "dummy_view.h"

TEST(GameTest, Start) {
    
    Random::useFixedSeed();
    // create game logic
    GameLogic gameLogic;
    gameLogic.init(Vector2f(500,500));
    DummyView dummyView;
    gameLogic.setView(&dummyView);
    ASSERT_EQ(gameLogic.getPlayer(),nullptr); 
    // Start the game
    ASSERT_EQ(gameLogic.getState(),GameLogic::GameState::START_SCREEN_1);
    gameLogic.initGame();
    gameLogic.startGame();
    ASSERT_NE(gameLogic.getPlayer(),nullptr);
    auto playerPos = gameLogic.getPlayer()->getPosition();
    ASSERT_EQ(  playerPos.x,250); 
    ASSERT_EQ(  playerPos.y,250); 
    // Check Asteriod counts
    ASSERT_EQ(gameLogic.getAllAsteriods().size(),4);
    ASSERT_EQ(gameLogic.getAllUfos().size(),0);
    ASSERT_EQ(gameLogic.getAllMissles().size(),0);
    ASSERT_EQ(gameLogic.getState(),GameLogic::GameState::INGAME);
    ASSERT_EQ(gameLogic.getRemainigLifes(),3);
    ASSERT_EQ(gameLogic.getScore(),0);
}

TEST(GameTest,SimulateShipCollision)
{
    Random::useFixedSeed();
     // create game logic
    GameLogic gameLogic;
   gameLogic.init(Vector2f(500,500));
    DummyView dummyView;
    gameLogic.setView(&dummyView);
    gameLogic.initGame();
    gameLogic.startGame();
    gameLogic.pressFire();
    gameLogic.pressFire();

    ASSERT_EQ(gameLogic.getAllMissles().size(),2);
    // Simulate some time steps so that the collides with something
    for(int i = 0; i < 10;i++)
    {
      gameLogic.update(0.25);  
    }
    ASSERT_EQ(gameLogic.getRemainigLifes(),2);
    ASSERT_EQ(gameLogic.getAllAsteriods().size(),8);
    ASSERT_EQ(gameLogic.getScore(),140);

}

TEST(GameTest,ShipControl) {
    Random::useFixedSeed();
    // create game logic
    GameLogic gameLogic;
  gameLogic.init(Vector2f(5000,5000));
    DummyView dummyView;
    gameLogic.setView(&dummyView);
    gameLogic.initGame();
    gameLogic.startGame();
      // Test hyperspace to random postion
    gameLogic.pressHyperspace();
    Timer t;
    t.start();
    while(t.get_ticks() < Spaceship::TIME_IN_HYPERSPACE_IN_MS + 10){}
    gameLogic.update(0.25);
    ASSERT_NE(gameLogic.getPlayer()->getPosition().x,5000);
    ASSERT_NE(gameLogic.getPlayer()->getPosition().y,5000);
    // accelerate Ship
    ASSERT_EQ(gameLogic.getPlayer()->getLinearVelocity(),0);
    gameLogic.acceleratePlayer(1);
    ASSERT_GT(gameLogic.getPlayer()->getLinearVelocity(),0);
    // Rotate Spaceship
    auto ship = gameLogic.getPlayer();
    ASSERT_EQ(ship->getHeading().y,0);
    ASSERT_EQ(ship->getHeading().x,1);
    gameLogic.rotatePlayer(1);
    ASSERT_LT(ship->getHeading().y,0);
    ASSERT_LT(ship->getHeading().x,1);
}
