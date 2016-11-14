cmake_minimum_required(VERSION 3.1)
project("DungeonCrawlerBots")

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/external/cmake_modules)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -L/opt/local/lib -L/usr/lib/i386-linux-gnu")

set(RLTK external/rltk/rltk/rltk.cpp
        external/rltk/rltk/texture_resources.cpp
        external/rltk/rltk/color_t.cpp
        external/rltk/rltk/virtual_terminal.cpp
        external/rltk/rltk/rng.cpp
        external/rltk/rltk/geometry.cpp
        external/rltk/rltk/input_handler.cpp
        external/rltk/rltk/font_manager.cpp
        external/rltk/rltk/gui.cpp
        external/rltk/rltk/layer_t.cpp
        external/rltk/rltk/gui_control_t.cpp
        external/rltk/rltk/virtual_terminal_sparse.cpp
        external/rltk/rltk/ecs.cpp
        external/rltk/rltk/perlin_noise.cpp
        external/rltk/rltk/rexspeeder.cpp
        external/rltk/rltk/xml.cpp
)

# Require SFML
find_package(SFML 2 COMPONENTS system window graphics REQUIRED)
include_directories(${SFML_INCLUDE_DIR})

# Add all of the example executables and their library dependency
set(SOURCE_FILES main.cpp components/Position_c.cpp components/Position_c.h components/Renderable_c.cpp components/Renderable_c.h utility/navigator_helper.cpp utility/navigator_helper.h Game.cpp Game.h World.cpp World.h rng.cpp rng.h components/Brain_c.cpp components/Brain_c.h components/Neuron_c.cpp components/Neuron_c.h settings.h systems/BrainSystem.cpp systems/BrainSystem.h components/Agent_c.cpp components/Agent_c.h)
add_executable(DungeonCrawlerBots ${SOURCE_FILES} ${RLTK})
target_link_libraries(DungeonCrawlerBots ${SFML_LIBRARIES})

# Require Boost
set(Boost_USE_STATIC_LIBS      OFF) # only find static libs
set(Boost_USE_MULTITHREADED    ON)
set(Boost_USE_STATIC_RUNTIME   OFF)
find_package(Boost COMPONENTS filesystem system REQUIRED)
if(Boost_FOUND)
	include_directories(${Boost_INCLUDE_DIRS})
	target_link_libraries(DungeonCrawlerBots ${Boost_LIBRARIES})
endif()

# We depend upon zlib
find_package(ZLIB REQUIRED)
if (ZLIB_FOUND)
	include_directories(${ZLIB_INCLUDE_DIRS})
	target_link_libraries(DungeonCrawlerBots ${ZLIB_LIBRARIES})
endif()

FILE(COPY assets DESTINATION /)