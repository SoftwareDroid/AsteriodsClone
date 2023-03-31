#include "sdl_view.h"
#include "controller/icontroller.h"
#include "SDL.h"
#include "share/timer/timer.h"
#include <iostream>
#include "SDL.h"
#include <array>
#include <assert.h>

SDLView::SDLView(GameLogic* logic,IController*  controller) : controller(controller), game_logic(logic)
{
    controller->view = this;
    controller->logic = logic;
}

void SDLView::run()
{
        
        Timer delta;
        delta.start();
        this->isRunning = true;
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO) == 0) {
        SDL_Window* window = NULL;

        if (SDL_CreateWindowAndRenderer(WIN_SIZE_X, WIN_SIZE_Y, 0, &window, &this->renderer) == 0) {
            this->game_logic->init(Vector2f(WIN_SIZE_X,WIN_SIZE_Y));
            //initialise GUI
            this->gui.init(Vector2f(WIN_SIZE_X,WIN_SIZE_Y));    
            gui.setPoints(this->game_logic->getScore());
            gui.setBestHighScore(this->game_logic->getBestHighScore());
            gui.setInsertOneCoinMessage();
            
            while (this->isRunning) {
                unsigned int passedTicks = delta.get_ticks();
                if(passedTicks < 10) {
                     SDL_Delay(1);
                     continue;
                }

                // Verarbeite alle Tasten eingaben
                controller->update(delta.get_ticks() / 1000.0f);
                
                SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
                SDL_RenderClear(this->renderer);
                SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

                renderAll();
                delta.start();
                // Lasse Zeit vergehen
               // game_logic->update();
                //render alles
                //renderAll(this->renderer);
                SDL_RenderPresent(this->renderer);
            }
        }
        if (this->renderer) {
            SDL_DestroyRenderer(this->renderer);
        }
        if (window) {
            SDL_DestroyWindow(window);
        }
    }
    SDL_Quit();

}

void SDLView::renderMissles()
{
    const auto&  misseles = game_logic->getAllMissles();
    int counter = 0;
    for(const auto& pair : misseles) {
       const  Missle& m = *pair.second.get();
         SDL_RenderDrawPointF(renderer,       m.getPosition().x,       m.getPosition().y);
        counter++;
    }

    //SDL_RenderDrawPoints(renderer,points,misseles.size());
}

void SDLView::renderAsteriods()
{
    const auto& asteriodsModel = game_logic->getAllAsteriods();
     for(const auto& pair : asteriodsModel) {
         auto it = this->asteriods.find(pair.first);
         assert(it != this->asteriods.end());
         // Set the postion of the grafic as the same as in the model
         it->second.asteriodGeometry.setPosition(pair.second->getPosition());
         this->renderGeometry(it->second.asteriodGeometry);
         
     }
}
void SDLView::renderExplosions()
{
    for (auto it = explosions.begin(); it != explosions.end(); )
    {
        ExplosionRenderable& explosion = it->second;
        if (!explosion.isAlive())
        {
            explosions.erase(it++);
        }
        else
        {
            const auto& data  = explosion.getRenderData();
            for(std::size_t n = 0; n < data.size();n++)
            {
                const Geometry::Line& line = data[n];
                SDL_RenderDrawLineF(renderer, line.start.x,line.start.y, line.end.x, line.end.y);
            }
            ++it;
        }
    }
}

void SDLView::renderUfos()
{
    const auto&  ufos = game_logic->getAllUfos();
    for(const auto& pair : ufos) {
        auto it = this->ufos.find(pair.first);
        assert(it !=  this->ufos.end());
        // Set the position of grafic the same as in the model
        it->second.setPosition(pair.second->getPosition());
        this->renderGeometry(it->second.getRenderData());
    }
}



void SDLView::renderAll()
{
    renderMissles();
    renderAsteriods();
    renderUfos();
    // if player exists
    if(auto spaceshipModel = game_logic->getPlayer())
    {
        this->spaceship.update(spaceshipModel->getPosition(),spaceshipModel->getRotation(),spaceshipModel->getLastFrameAccelrating());
        
        auto lines = this->spaceship.getTransformedLines();
        for(const Geometry::Line& line : lines) 
        {
            int len = (line.start.x - line.end.x) * (line.start.x - line.end.x) +  (line.start.y - line.end.y) * (line.start.y - line.end.y);
            int ret = SDL_RenderDrawLineF(renderer, line.start.x,line.start.y, line.end.x, line.end.y);

        }
    }

    renderExplosions();
    renderText();
     //SDL_RenderDrawPointF(renderer,0,0);
}

void SDLView::renderText()
{
    for(const auto& pair :this->gui.getAllLines())
    {
        const LetterLine& line = pair.second;
        const std::vector<Geometry>& letters = line.getGeometry();
        for(const Geometry& g : letters)
        {
            renderGeometry(g);
        }
    }
}



void SDLView::renderGeometry(const Geometry& g)
{
    std::vector<Geometry::Line> lines = g.getTransformedLines();
    for(const Geometry::Line& line : lines) 
    {
        //int len = (line.start.x - line.end.x) * (line.start.x - line.end.x) +  (line.start.y - line.end.y) * (line.start.y - line.end.y);
        SDL_RenderDrawLineF(renderer, line.start.x,line.start.y, line.end.x, line.end.y);

    }
}


void SDLView::update()
{
    renderAll();

}

void SDLView::shutdown()
{
   this->isRunning  = false;
}

void SDLView::eventCreateAsteriod(int uid)
{
    const auto& asteriods = game_logic->getAllAsteriods();
    auto it = asteriods.find(uid);
    assert(it != asteriods.end());  //Asteriod doesn't exist
    const Asteriod& asteriodModel = *it->second.get();
    AsteriodRenderable renderableAsteriod((int)asteriodModel.type);
    renderableAsteriod.asteriodGeometry.setPosition(asteriodModel.getPosition());
    this->asteriods.insert(std::make_pair(uid,renderableAsteriod));

}

void SDLView::eventCreateMissle(int uid)
{
    const auto& misseles = game_logic->getAllMissles();
    auto it = misseles.find(uid);
    assert(it != misseles.end());  //Asteriod doesn't exist

}

void SDLView::eventDestroyMissle(int uid)
{
}

void SDLView::eventCreateUfo(int uid)
{
     const auto& ufos = game_logic->getAllUfos();
    auto it = ufos.find(uid);
    assert(it != ufos.end());  //Ufo doesn't exist
    UfoRenderable u(static_cast<UfoRenderable::Type>(it->second->type));
    this->ufos.insert(std::make_pair(uid,u));
}

void SDLView::eventDestroyUfo(int uid,bool destroyAnimation)
{
    auto it = ufos.find(uid);
    assert(it != ufos.end());
    if(destroyAnimation)
    {
        auto pos = it->second.getRenderData().getPosistion();
        explosions.insert(std::make_pair(++uidCounter,ExplosionRenderable(pos,ExplosionRenderable::Type::Asteriod)));
    }
    this->ufos.erase(uid);
}

void SDLView::eventDestroySpaceship()
{
    auto spaceship = this->game_logic->getPlayer();
    assert(spaceship != nullptr);
    auto pos = spaceship->getPosition();
    explosions.insert(std::make_pair(++uidCounter,ExplosionRenderable(pos,ExplosionRenderable::Type::Spaceship)));
}


void SDLView::eventDestroyAsteriod(int uid,bool destroyAnimation)
{
    auto it = asteriods.find(uid);
    assert(it != asteriods.end());
    if(destroyAnimation)
    {
        auto pos = it->second.asteriodGeometry.getPosistion();
        explosions.insert(std::make_pair(++uidCounter,ExplosionRenderable(pos,ExplosionRenderable::Type::Asteriod)));
    }
    this->asteriods.erase(uid);
}

void SDLView::setPushStartMessage()
{
    std::cout<<"Set push start message"<<std::endl;
    this->gui.setPushStartMessage();
}

void SDLView::setPoints(int points)
{
    this->gui.setPoints(points);
}

void SDLView::setRemainingLifes(int lifes)
{
    this->gui.setRemainingLifes(lifes);
}

void SDLView::setBestHighScore(int score)
{
    this->gui.setBestHighScore(score);
}

void SDLView::destroyStartscreenGUI()
{
    this->gui.destroyStartscreenGUI();
}

void SDLView::askForPlayerName()
{
    this->gui.askForPlayerNameMessage();
}

void SDLView::showGameOverMessage()
{
    this->gui.showGameOverMessage();
}

