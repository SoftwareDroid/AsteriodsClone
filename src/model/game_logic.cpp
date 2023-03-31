#include "game_logic.h"
#include "../view/iview.h"
#include <assert.h>
#include <iostream>
#include "share/random.h"
#include "share/math/transformation2d.h"
#include "share/math/helper.h"
#include "model/asteriod/asteriod.h"
#include <algorithm>
#include "audio/asteriod_sounds.h"
#include "model/audio/soundmanager.h"
#include <memory>

void GameLogic::eventCollisionCallback(CollisionListener::CollisionInfo event)
{
    int objectType1 = (int)event.d1.objectType;
    int objectType2 = (int)event.d2.objectType;
    std::shared_ptr<PhysicComponent> c1 = event.d1.collisionObject;
   std::shared_ptr<PhysicComponent> c2 = event.d2.collisionObject;
   
   // We don't need to check collison between the same type
   if(objectType1 == objectType2)
   {
     return;  
   }
    // order the collsion events to reduce checks later
    if (objectType2 < objectType1)
    {
      std::swap(event.d1,event.d2);
    }
    
    if (event.d1.objectType == (int)CollisonType::Asteriod)
    {
        handleAsteriodCollisions(event);
    } else if (event.d1.objectType == (int)CollisonType::Missle)
    {
        handleMissleCollisions(event);
    } 
    else if(event.d1.objectType == (int)CollisonType::Ufo)
    {
        destroyUfo(true,event.d1.key);
        eventPlayerCollsion();
    }
    
}


void GameLogic::init(const Vector2f& windowSize)
{
    this->windowSize = windowSize;
    player->init(this->windowSize);
    AsteriodSounds::loadAllSounds();
    changeState(GameState::START_SCREEN_1);
}


GameLogic::GameLogic(): physicEngine(this)
{

}

void GameLogic::acceleratePlayer(float passedTimeinSeconds)
{
    if(player->isAlive())
    {
        this->player->accelerate(passedTimeinSeconds);
    }
}

void GameLogic::rotatePlayer(float passedTimeinSeconds)
{
    this->player->setRotationSpeed(passedTimeinSeconds);
}

void GameLogic::setView(IView* iview)
{
    assert(iview != nullptr);
    this->iview = iview;
}

const std::map<int,std::shared_ptr<Missle>>& GameLogic::getAllMissles() const {
  return this->misseles;  
}

const std::map<int, std::shared_ptr<Asteriod>> & GameLogic::getAllAsteriods() const
{
    return this->asteriods;
}

const std::map<int, std::shared_ptr<Ufo>> & GameLogic::getAllUfos() const
{
    return this->ufos;
}

void GameLogic::updateState()
{
    switch(this->state)
    {
        case(GameState::INGAME):
        {
            if(ufos.size() == 0 && asteriods.size() == 0)
            {
                changeState(GameState::WIN_LEVEL); 
            }
          break;  
        }
        case(GameState::SHOW_GAME_OVER_MESSAGE):
        {
          if(this->timerBetweenStates.get_ticks() > GameLogic:: TIME_SHOW_GAME_OVER_MESSAGE_IN_MS)
          {
            changeState(GameState::ASK_FOR_PLAYER_NAME);  
          }
          break;
        }
        case(GameState::ASK_FOR_PLAYER_NAME):
        {
          break;  
        }
        case(GameState::WAIT_FOR_DEATH_MESSAGE):
        {
          if(this->timerBetweenStates.get_ticks() > GameLogic::TIME_WAIT_FOR_DEATH_MESSAGE)
          {
            changeState(GameState::SHOW_GAME_OVER_MESSAGE);  
          }
          break;
        };
        case (GameState::START_SCREEN_1):
        {
           break;
        }
        case (GameState::START_SCREEN_PUSH_START):
        {
           
           break;
        }
        default:
        {
            std::cout<<"Wrong State"<<(int)state<<std::endl;
            assert(false);
        }
    };
}


void GameLogic::update(float passedTimeInSeconds)
{
    updateState();  // Führe ggf ein State Transistion aus
    updatePlayer(passedTimeInSeconds);
    updateMissles(passedTimeInSeconds);
    updateAsteriods();
    updateUfos();
    this->physicEngine.tick(passedTimeInSeconds);
    if (state == GameState::INGAME)
    {
        ufoLogic();
    }
    if(state == GameState::START_SCREEN_1 || state == GameState::START_SCREEN_PUSH_START)
    {
        startScreenLogic();
        ufoLogic();
    }
    if(ufos.size() == 0)
    {
        SoundManager::getInstance()->stopSound(AsteriodSounds::asteriodSounds[AsteriodSounds::SoundName::LSAUCER]);
    }
    // Call update to render all objects
    this->iview->update();
    
}

void GameLogic::ufoLogic()
{
    constexpr int minSpawnTimeInS = 7;  // 7
    constexpr int maxSpawnTimeInS = 30;  // 30
    if(spawnNextUfo < 0)
    {
      spawnNextUfo = Random::getRandomInt(minSpawnTimeInS * 1000,maxSpawnTimeInS * 1000);
      ufoSpawnTimer.start();
    }
    else 
    {
      if(ufoSpawnTimer.get_ticks() > spawnNextUfo)
      {
        if(this->ufos.size() == 0)
        {
            float probalitySmallUfo = 0.33;
            auto type = Random::getRandomFloat(0,1) < probalitySmallUfo ? Ufo::Type::Small : Ufo::Type::Big;
            Ufo ufo = Ufo(this->windowSize,type);
            this->addUfo(ufo);
             SoundManager::getInstance()->playSound(AsteriodSounds::asteriodSounds[AsteriodSounds::SoundName::LSAUCER]);
        }
        //We don't want more that one ufo 
        ufoSpawnTimer.start();
        spawnNextUfo = Random::getRandomInt(minSpawnTimeInS * 1000,maxSpawnTimeInS * 1000);
      }
    }
}

void GameLogic::updateAsteriods()
{
    for (auto it = asteriods.begin(); it != asteriods.end();it++)
    {
        Asteriod& a = *it->second.get();
        applyScreenWrapping(&a);
    }
}
GameLogic::~GameLogic()
{
    SoundManager::getInstance()->shutdown();
}

void GameLogic::updateUfos()
{
    for (auto it = ufos.begin(); it != ufos.end();it++)
    {
        Ufo& a = *it->second.get();
        a.update();
        if (a.canFire())
        {            
            Missle missle = a.fire(*player.get());
            this->addMissle(missle);
        }
        applyScreenWrapping(&a);
    }
}


void GameLogic::applyScreenWrapping(PhysicComponent* comp)
{
    {
        Vector2f pos = comp->getPosition();
            if(pos.x > this->windowSize.x) {
        pos.x = 0;
    }
    if(pos.y > this->windowSize.y) {
        pos.y = 0;
    }
    if(pos.x < 0) {
        pos.x = this->windowSize.x;
    }
    if(pos.y < 0) {
        pos.y = this->windowSize.y;
    }    
    comp->setPosition(pos);
        
    }
}

void GameLogic::pressFire()
{
    if(player->isAlive())
    {
        if(this->misseles.size() < GameLogic::MAX_NUMBER_OF_MISSLES) {
            SoundManager::getInstance()->playSound(AsteriodSounds::asteriodSounds[AsteriodSounds::SoundName::FIRE]);
            Missle missle = this->player->fire();
            this->addMissle(missle);
        }
    }
}

void GameLogic::pressHyperspace()
{
    if(player->isAlive())
    {
        player->useHyperspace( );
    }
}

void GameLogic::startScreenLogic()
{
    if(this->asteriods.size() < 4)
    {
        bool xZero = Random::getRandomBool();
        Vector2f startPos(0,0);
        if (xZero) {
            startPos.y = Random::getRandomInt(0,windowSize.y);
        } else {
            startPos.x = Random::getRandomInt(0,windowSize.x);
        }
        //Create a random trajectory
        Vector2f trajectory = Transformation::rotatePoint(Vector2f(1,0), degToRad( Random::getRandomInt(0,360)));
        Asteriod a(startPos,trajectory,Asteriod::Type::BIG);
        addAsteriod(a);
    }
}


void GameLogic::updatePlayer(float passedTimeInSeconds)
{
    this->player->update(passedTimeInSeconds);
    applyScreenWrapping(player.get());
}

void GameLogic::updateMissles(float passedTimeInSeconds)
{
    for (auto it = misseles.begin(); it != misseles.end() /* not hoisted */; /* no increment */)
    {
        Missle& m = *it->second.get();
        //m.update(passedTimeInSeconds);
        applyScreenWrapping(&m);
        bool remove = m.travelLimitReached();
        if (remove)
        {
            this->iview->eventDestroyMissle(it->first);
            misseles.erase(it++);    // or "it = m.erase(it)" since C++11
        }
        else
        {
            ++it;
        }
    }
}


void GameLogic::handleAsteriodCollisions(const CollisionListener::CollisionInfo& event)
{
        switch(static_cast<CollisonType>(event.d2.objectType))
        {
            case(CollisonType::Missle):
            {
                this->destroyMissle(event.d2.key);
            }
            break;
            case(CollisonType::Ufo):
            {
                 destroyUfo(true,event.d2.key);
            }
            break;
            case(CollisonType::Ship):
            {
                if(player->isAlive())
                {
                    eventPlayerCollsion();
                }
            }
            break;
            default:
                assert(false);
        };
        
        SoundManager::getInstance()->playSound(AsteriodSounds::asteriodSounds[AsteriodSounds::SoundName::EXPLODE]);
       auto a = dynamic_cast<Asteriod*>( event.d1.collisionObject.get());
        std::vector<Asteriod> newAsteriods = a->split();
        if(this->state  == GameState::INGAME)
          {
          score += a->getPoints();
          this->iview->setPoints(score);
          }
          this->iview->eventDestroyAsteriod(event.d1.key,true);
          this->physicEngine.removeObject(event.d1.key);
          asteriods.erase(event.d1.key);
         for (Asteriod& a: newAsteriods) {
            this->addAsteriod(a);
        }
}


void GameLogic::eventGameOver()
{
    bestHighScore = score;
    this->iview->setBestHighScore(bestHighScore);
    changeState(GameState::WAIT_FOR_DEATH_MESSAGE);
}


void GameLogic::eventPlayerCollsion()
{
    if(player->isAlive())
    {
        this->iview->eventDestroySpaceship();
        this->remainingLives--;
        this->iview->setRemainingLifes(remainingLives);
        bool respawn = this->remainingLives > 0;
        this->player->destroyShip(respawn);
        if(remainingLives == 0)
        {
            eventGameOver();
        }
    }
}

void GameLogic::handleMissleCollisions(const CollisionListener::CollisionInfo& event)
{
    switch(static_cast<CollisonType>( event.d2.objectType))
    {
        case(CollisonType::Ufo):
        {
            destroyUfo(true,event.d2.key);
            break;

        };
        case(CollisonType::Ship):
        {
            eventPlayerCollsion();
            break;
        };
        default:
        {
        assert(false); 
        }
    };
    this->destroyMissle(event.d1.key);
}


void GameLogic::changeState(GameLogic::GameState s)
{
    switch(s)
    {
        case(GameState::INGAME):
        {
            startLevel1();
            break;
        }
        case (GameState::SHOW_GAME_OVER_MESSAGE):
        {
          timerBetweenStates.start();  
          this->iview->showGameOverMessage();
          break;  
        }
        case(GameState::ASK_FOR_PLAYER_NAME):
        {
            // Remove all remainig ufos and Asteriods
            SoundManager::getInstance()->stopSound(AsteriodSounds::asteriodSounds[AsteriodSounds::SoundName::LSAUCER]);
            // Callback to view
            this->clearAsteriods(false);
            this->clearUfos(false);
            this->iview->askForPlayerName();
            break;
        }
        case(GameState::WAIT_FOR_DEATH_MESSAGE):
        {
          this->timerBetweenStates.start();  
          break;  
        }
        case(GameState::START_SCREEN_1):
        {
            break;
        }
            
    };
    state = s;
}

void GameLogic::initGame()
{
    if(this->state == GameState::START_SCREEN_1)
    {
        changeState(GameState::START_SCREEN_PUSH_START);
    }
}

void GameLogic::startGame()
{
    if(this->state == GameState::START_SCREEN_PUSH_START)
    {
        changeState(GameState::INGAME);
    }
}


void GameLogic::startLevel1()
{
    this->clearUfos(false);
    this->clearAsteriods(false);
   int NUMBER_OF_ASTERIODS = 4;
   remainingLives = 3;   // Set lives of Player
    player->spawn();
    this->physicEngine.addObject(player,static_cast<int>(CollisonType::Ship),++uidCounter);
    this->iview->setRemainingLifes(remainingLives);
    for(int n = 0; n < NUMBER_OF_ASTERIODS;n++) {
        // Create a Random Start Pos
        bool xZero = Random::getRandomBool();
        Vector2f startPos(0,0);
        if (xZero) {
            startPos.y = Random::getRandomInt(0,windowSize.y);
        } else {
            startPos.x = Random::getRandomInt(0,windowSize.x);
        }
        //Create a random trajectory
        Vector2f trajectory = Transformation::rotatePoint(Vector2f(1,0), degToRad( Random::getRandomInt(0,360)));
        Asteriod a(startPos,trajectory,Asteriod::Type::BIG);
        this->addAsteriod(a);
    }
}

void GameLogic::addMissle(Missle& m)
{
    int uid = ++uidCounter;
    auto ptr = std::make_shared<Missle>(m);
    misseles.insert(std::make_pair(uid,ptr));
    this->physicEngine.addObject(ptr,static_cast<int>(CollisonType::Missle),uid);
    this->iview->eventCreateMissle(uid);
}


void GameLogic::addUfo(Ufo& u)
{
    int uid = ++uidCounter;
    auto ptr = std::make_shared<Ufo>(u);
    ufos.insert(std::make_pair(uid,ptr));
    this->physicEngine.addObject(ptr,static_cast<int>(CollisonType::Ufo),uid);
    this->iview->eventCreateUfo(uid);

}


void GameLogic::addAsteriod(Asteriod& a)
{
    int uid = ++uidCounter;
   auto ptr = std::make_shared<Asteriod>(a);
    asteriods.insert(std::make_pair(uid,ptr));
    this->physicEngine.addObject(ptr,static_cast<int>(CollisonType::Asteriod),uid);
    this->iview->eventCreateAsteriod(uid);
}


void GameLogic::clearAsteriods(bool animation)
{
    for (auto it = asteriods.begin(); it != asteriods.end() ; )
    {
        this->iview->eventDestroyAsteriod(it->first,animation);
        this->physicEngine.removeObject(it->first);
        asteriods.erase(it++);
    }
}

void GameLogic::destroyUfo(bool ingame,int key)
{
        auto it = ufos.find(key);
        if(ingame && this->state  == GameState::INGAME)
        {
                score += it->second->getPoints();
                this->iview->setPoints(score);
                SoundManager::getInstance()->playSound(AsteriodSounds::asteriodSounds[AsteriodSounds::SoundName::EXPLODE]);
        }
        this->physicEngine.removeObject(key);
        this->iview->eventDestroyUfo(key,true);
        ufos.erase(key);
}

void GameLogic::destroyMissle(int key)
{
        this->physicEngine.removeObject(key);
        this->iview->eventDestroyMissle(key);
        misseles.erase(key);
}


void GameLogic::clearUfos(bool animation)
{
    for (auto it = ufos.begin(); it != ufos.end() ; )
    {
        this->iview->eventDestroyUfo(it->first,animation);
        this->physicEngine.removeObject(it->first);
        ufos.erase(it++);
    }
}
