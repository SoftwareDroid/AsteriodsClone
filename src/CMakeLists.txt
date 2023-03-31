set(BINARY ${CMAKE_PROJECT_NAME})

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.h *.cpp)

find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

set(SOURCES ${SOURCES})

#add_executable(${BINARY}_run ${SOURCES})
add_executable(${BINARY}_run 
main.cpp
view/sdl_view.cpp
model/game_logic.cpp
view/sdl_gl_view.cpp
controller/sdlcontroller.cpp
share/random.cpp
view/geometry.cpp
model/ufo/ufo.cpp
model/asteriod/asteriod.cpp
model/player/spaceship.cpp
view/gui/letter_line.cpp
view/gui/asteriods_gui.cpp
share/timer/timer.cpp
model/player/missle.cpp
view/objects/ufo_renderable.cpp
view/objects/asteriod_renderable.cpp
view/objects/explosion_renderable.cpp
view/objects/spaceship_renderable.cpp
model/audio/soundmanager.cpp
model/audio/asteriod_sounds.cpp
model/physic_engine/physic_engine.cpp
)
target_link_libraries(${BINARY}_run ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES})


add_library(${BINARY}_lib STATIC ${SOURCES})
