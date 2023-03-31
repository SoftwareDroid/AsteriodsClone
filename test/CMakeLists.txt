set(BINARY ${CMAKE_PROJECT_NAME}_test)

#file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false *.h *.cpp)
#add_executable(ExampleProject main.cpp )
#set(TEST_SOURCES )
#set(SOURCES ${TEST_SOURCES})

#add_executable(${BINARY} ${TEST_SOURCES})

# SDL is used in the intersection part
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
set(SOURCES ${SOURCES})


add_executable(${BINARY} main.cpp  transformation_test.cpp
1sound_test.cpp
model_test.cpp
full_game_test.cpp
transformation_test.cpp
../src/model/game_logic.cpp
../src/model/ufo/ufo.cpp
../src/model/player/missle.cpp
../src/model/player/spaceship.cpp
../src/model/asteriod/asteriod.cpp
../src/model/audio/soundmanager.cpp
../src/model/physic_engine/physic_engine.cpp

../src/share/random.cpp
../src/share/timer/timer.cpp


)

add_test(NAME ${BINARY} COMMAND ${BINARY})

target_link_libraries(${BINARY} PUBLIC ${SDL2_LIBRARIES} ${CMAKE_PROJECT_NAME}_lib gtest)
