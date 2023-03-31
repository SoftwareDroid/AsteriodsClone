#include "SDL.h"
#include "model/game_logic.h"
#include "view/sdl_view.h"
#include "view/sdl_gl_view.h"
#include "controller/sdlcontroller.h"

int main(int argc, char* argv[])
{
    GameLogic model;
    SDLController controller;
    /**
     * use a opengl renderer or the default sdl2 renderer
     */
    constexpr bool useOpenGL = false;
    if (!useOpenGL)
    {
        SDLView view(&model,&controller);
        model.setView(&view);
        view.run();
    }
    else 
    {
        ViewWithOpenGlRendering view(&model,&controller);
        model.setView(&view);
        view.run();
    }
    return 0;
}
