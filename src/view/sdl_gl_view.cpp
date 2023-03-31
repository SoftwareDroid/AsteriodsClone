#include "sdl_gl_view.h"
#include "controller/icontroller.h"
#include "SDL.h"
#include "share/timer/timer.h"
#include <iostream>
#include "SDL.h"
#include <GL/gl.h>
#include <array>
#include <assert.h>
#include <view/objects/asteriod_renderable.h>

 ViewWithOpenGlRendering::ViewWithOpenGlRendering(GameLogic* logic, IController* controller) : controller(controller), game_logic(logic)
{
    controller->view = this;
    controller->logic = logic;
}

bool ViewWithOpenGlRendering::init()
{
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO) < 0 )
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        //Use OpenGL 2.1
        SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 2 );
        SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 1 );

        //Create window
        gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIN_SIZE_X, WIN_SIZE_Y, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );
        if( gWindow == NULL )
        {
            printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            //Create context
            gContext = SDL_GL_CreateContext( gWindow );
            if( gContext == NULL )
            {
                printf( "OpenGL context could not be created! SDL Error: %s\n", SDL_GetError() );
                success = false;
            }
            else
            {
                //Use Vsync
                if( SDL_GL_SetSwapInterval( 1 ) < 0 )
                {
                    printf( "Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError() );
                }

                //Initialize OpenGL
                if( !initGL() )
                {
                    printf( "Unable to initialize OpenGL!\n" );
                    success = false;
                }
            }
        }
    }
    return success;
}

bool ViewWithOpenGlRendering::initGL()
{
    this->game_logic->init(Vector2f(WIN_SIZE_X,WIN_SIZE_Y));
    
    
    

     bool success = true;
    GLenum error = GL_NO_ERROR;

    //Initialize Projection Matrix
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glScaled(1.0f,-1.0f,-1.0f); //Invert Axis
    glOrtho(0,WIN_SIZE_X,0,WIN_SIZE_Y,-1,1);
    //glLoadIdentity();
    
    //Check for error
    error = glGetError();
    if( error != GL_NO_ERROR )
    {
        std::cout<<error<<std::endl;
        success = false;
    }

    //Initialize Modelview Matrix
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
   
    //glLoadIdentity();

    //Check for error
    error = glGetError();
    if( error != GL_NO_ERROR )
    {
        std::cout<<error<<std::endl;
        success = false;
    }
    //Initialize clear color
    glClearColor( 0.f, 0.f, 0.f, 1.f );
    
    //Check for error
    error = glGetError();
    if( error != GL_NO_ERROR )
    {
        std::cout<<error<<std::endl;

        success = false;
    }
    
    return success;
}

void ViewWithOpenGlRendering::update()
{
    renderAll();
}

void ViewWithOpenGlRendering::shutdown()
{
    this->isRunning  = false;

}

void ViewWithOpenGlRendering::renderGeometry(const Geometry& g)
{
    std::vector<Geometry::Line> lines = g.getTransformedLines();
    for(const Geometry::Line& line : lines) 
    {
        //int len = (line.start.x - line.end.x) * (line.start.x - line.end.x) +  (line.start.y - line.end.y) * (line.start.y - line.end.y);
        
        glBegin(GL_LINES);
            glVertex2f(line.start.x,line.start.y);
            glVertex2f(line.end.x, line.end.y);
        glEnd();
    }
}


void ViewWithOpenGlRendering::renderMissles()
{
    const auto&  misseles = game_logic->getAllMissles();
    int counter = 0;
    for(const auto& pair : misseles) {
       const  Missle& m = *pair.second.get();
        glBegin(GL_POINTS);
            glVertex2f(m.getPosition().x,m.getPosition().y);
        glEnd();
        counter++;
    }

    //SDL_RenderDrawPoints(renderer,points,misseles.size());
}

void ViewWithOpenGlRendering::renderAsteriods()
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
void ViewWithOpenGlRendering::renderExplosions()
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
                        glBegin(GL_LINES);
            glVertex2f(line.start.x,line.start.y);
            glVertex2f(line.end.x, line.end.y);
        glEnd();
                //SDL_RenderDrawLineF(renderer, line.start.x,line.start.y, line.end.x, line.end.y);
            }
            ++it;
        }
    }
}

void ViewWithOpenGlRendering::renderUfos()
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


void ViewWithOpenGlRendering::renderText()
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



void ViewWithOpenGlRendering::renderAll()
{
    //Clear color buffer
    glClear( GL_COLOR_BUFFER_BIT );
    
    
    /*float q = 80;
    //Render quad
    {
        glBegin( GL_QUADS );
            glVertex2f( q, q );
            glVertex2f( 2* q, q);
            glVertex2f( 2* q,2* q );
            glVertex2f( q, 2*q );
        glEnd();
    }*/

    
   
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
                                    glBegin(GL_LINES);
            glVertex2f(line.start.x,line.start.y);
            glVertex2f(line.end.x, line.end.y);
        glEnd();
        

        }
    }

    renderExplosions();
    renderText();
     //SDL_RenderDrawPointF(renderer,0,0);
}


void ViewWithOpenGlRendering::run()
{
    init();
    initGL();

    Timer delta;
     delta.start();
     this->isRunning = true;
        SDL_StartTextInput();
        this->game_logic->init(Vector2f(WIN_SIZE_X,WIN_SIZE_Y));
        //initialise GUI
        this->gui.init(Vector2f(WIN_SIZE_X,WIN_SIZE_Y));    
        gui.setPoints(this->game_logic->getScore());
        gui.setBestHighScore(this->game_logic->getBestHighScore());
        gui.setInsertOneCoinMessage();
     while(this->isRunning)
     {
                unsigned int passedTicks = delta.get_ticks();
                if(passedTicks < 10) {
                     SDL_Delay(1);
                     continue;
                }

                // Verarbeite alle Tasten eingaben
                controller->update(delta.get_ticks() / 1000.0f);
                
   

                renderAll();
                delta.start();
                // Lasse Zeit vergehen
               // game_logic->update();
                //render alles
                //renderAll(this->renderer);
            SDL_GL_SwapWindow( gWindow );
     }
    SDL_StopTextInput();
      SDL_Quit();
}



void ViewWithOpenGlRendering::eventCreateAsteriod(int uid)
{
    const auto& asteriods = game_logic->getAllAsteriods();
    auto it = asteriods.find(uid);
    assert(it != asteriods.end());  //Asteriod doesn't exist
    const Asteriod& asteriodModel = *it->second.get();
    AsteriodRenderable renderableAsteriod((int)asteriodModel.type);
    renderableAsteriod.asteriodGeometry.setPosition(asteriodModel.getPosition());
    this->asteriods.insert(std::make_pair(uid,renderableAsteriod));

}

void ViewWithOpenGlRendering::eventCreateMissle(int uid)
{
    const auto& misseles = game_logic->getAllMissles();
    auto it = misseles.find(uid);
    assert(it != misseles.end());  //Asteriod doesn't exist
}

void ViewWithOpenGlRendering::eventDestroyMissle(int uid)
{
}

void ViewWithOpenGlRendering::eventCreateUfo(int uid)
{
     const auto& ufos = game_logic->getAllUfos();
    auto it = ufos.find(uid);
    assert(it != ufos.end());  //Ufo doesn't exist
    UfoRenderable u(static_cast<UfoRenderable::Type>(it->second->type));
    this->ufos.insert(std::make_pair(uid,u));
}

void ViewWithOpenGlRendering::eventDestroyUfo(int uid,bool destroyAnimation)
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

void ViewWithOpenGlRendering::eventDestroySpaceship()
{
    auto spaceship = this->game_logic->getPlayer();
    assert(spaceship != nullptr);
    auto pos = spaceship->getPosition();
    explosions.insert(std::make_pair(++uidCounter,ExplosionRenderable(pos,ExplosionRenderable::Type::Spaceship)));
}


void ViewWithOpenGlRendering::eventDestroyAsteriod(int uid,bool destroyAnimation)
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

void ViewWithOpenGlRendering::setPushStartMessage()
{
    this->gui.setPushStartMessage();
}

void ViewWithOpenGlRendering::setPoints(int points)
{
    this->gui.setPoints(points);
}

void ViewWithOpenGlRendering::setRemainingLifes(int lifes)
{
    this->gui.setRemainingLifes(lifes);
}

void ViewWithOpenGlRendering::setBestHighScore(int score)
{
    this->gui.setBestHighScore(score);
}

void ViewWithOpenGlRendering::destroyStartscreenGUI()
{
    this->gui.destroyStartscreenGUI();
}

void ViewWithOpenGlRendering::askForPlayerName()
{
    this->gui.askForPlayerNameMessage();
}

void ViewWithOpenGlRendering::showGameOverMessage()
{
    this->gui.showGameOverMessage();
}

