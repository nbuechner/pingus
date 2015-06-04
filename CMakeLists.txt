# Pingus - A free Lemmings clone
# Copyright (C) 2015 Ingo Ruhnke <grumbel@gmail.com>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

cmake_minimum_required(VERSION 3.0)
project(pingus)

find_package(Threads REQUIRED)
find_package(PkgConfig REQUIRED)
find_package(OpenGL REQUIRED)

pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
pkg_search_module(SDL2MIXER REQUIRED SDL2_mixer>=2.0.0)
pkg_search_module(PNG REQUIRED libpng)
pkg_search_module(JSONCPP REQUIRED jsoncpp)

file(GLOB PINGUS_SOURCES_CXX RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
  src/editor/*.cpp
  src/engine/display/*.cpp
  src/engine/display/delta/*.cpp
  src/engine/display/opengl/*.cpp
  src/engine/gui/*.cpp
  src/engine/input/*.cpp
  src/engine/resource/*.cpp
  src/engine/screen/*.cpp
  src/engine/sound/*.cpp
  src/engine/system/*.cpp
  src/lisp/*.cpp
  src/math/*.cpp
  src/pingus/*.cpp
  src/pingus/actions/*.cpp
  src/pingus/colliders/*.cpp
  src/pingus/components/*.cpp
  src/pingus/movers/*.cpp
  src/pingus/particles/*.cpp
  src/pingus/screens/*.cpp
  src/pingus/worldmap/*.cpp
  src/pingus/worldobjs/*.cpp
  src/util/*.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic -Wall -Wextra -Wnon-virtual-dtor -Weffc++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wconversion -Wold-style-cast -Werror -Wshadow -Wcast-qual")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Winit-self -Wno-unused-parameter")

include_directories(
  ${SDL2_INCLUDE_DIRS}
  ${SDL2IMAGE_INCLUDE_DIRS})

include_directories(
  src/
  external/tinygettext/include/
  external/logmich/include/)

file(GLOB TINYGETTEXT_SOURCES_CXX RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
  external/tinygettext/src/*.cpp)
add_library(tinygettext STATIC ${TINYGETTEXT_SOURCES_CXX})

file(GLOB LOGMICH_SOURCES_CXX RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
  external/logmich/src/*.cpp)
add_library(logmich STATIC ${LOGMICH_SOURCES_CXX})

add_library(libpingus STATIC ${PINGUS_SOURCES_CXX})
set_target_properties(libpingus PROPERTIES OUTPUT_NAME pingus)
target_compile_definitions(libpingus PUBLIC -DVERSION="0.8.0")
target_link_libraries(libpingus PUBLIC
  logmich
  tinygettext
  ${SDL2_LIBRARIES}
  ${SDL2IMAGE_LIBRARIES}
  ${SDL2MIXER_LIBRARIES}
  ${PNG_LIBRARIES}
  ${JSONCPP_LIBRARIES}
  ${OPENGL_LIBRARIES})
target_include_directories(libpingus SYSTEM PUBLIC
    ${JSONCPP_INCLUDE_DIRS})

add_executable(pingus src/main.cpp)
target_link_libraries(pingus
  libpingus)

file(GLOB PINGUS_TEST_SOURCES_CXX RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
  test/*_test.cpp)
foreach(TEST_SOURCE ${PINGUS_TEST_SOURCES_CXX})
  string(REGEX REPLACE ".*/\([^/]*\).cpp" "\\1" TEST_EXE ${TEST_SOURCE})
  add_executable(${TEST_EXE} ${TEST_SOURCE})
  set_target_properties(${TEST_EXE} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "test/")
  target_link_libraries(${TEST_EXE} libpingus)
endforeach(TEST_SOURCE)

file(GLOB PINGUS_UTIL_SOURCES_CXX RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
  test/*_util.cpp)
foreach(UTIL_SOURCE ${PINGUS_UTIL_SOURCES_CXX})
  string(REGEX REPLACE ".*/\([^/]*\).cpp" "\\1" UTIL_EXE ${UTIL_SOURCE})
  add_executable(${UTIL_EXE} ${UTIL_SOURCE})
  set_target_properties(${UTIL_EXE} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "test/")
  target_link_libraries(${UTIL_EXE} libpingus)
endforeach(UTIL_SOURCE)

file(GLOB PINGUS_EXTRA_SOURCES_CXX RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
  extra/*.cpp)
foreach(EXTRA_SOURCE ${PINGUS_EXTRA_SOURCES_CXX})
  string(REGEX REPLACE ".*/\([^/]*\).cpp" "\\1" EXTRA_EXE ${EXTRA_SOURCE})
  add_executable(${EXTRA_EXE} ${EXTRA_SOURCE})
  set_target_properties(${EXTRA_EXE} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "extra/")
  target_link_libraries(${EXTRA_EXE} libpingus)
endforeach(EXTRA_SOURCE)

if(BUILD_TESTS)
  # Note: include directories must use the absolute path as otherwise SYSTEM
  # bugs out and cmake uses -I instead of -isystem
  add_library(gtest STATIC ${CMAKE_CURRENT_SOURCE_DIR}/external/googletest/src/gtest-all.cc)
  target_include_directories(gtest SYSTEM PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/external/googletest/include/
    ${CMAKE_CURRENT_SOURCE_DIR}/external/googletest/)

  add_library(gtest_main STATIC ${CMAKE_CURRENT_SOURCE_DIR}/external/googletest/src/gtest_main.cc)
  target_include_directories(gtest_main SYSTEM PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/external/googletest/include/
    ${CMAKE_CURRENT_SOURCE_DIR}/external/googletest/)

  file(GLOB TEST_PINGUS_SOURCES_CXX RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    tests/*_test.cpp)
  add_executable(test_pingus ${TEST_PINGUS_SOURCES_CXX})
  target_include_directories(test_pingus PUBLIC src/ tests/)
  target_link_libraries(test_pingus libpingus gtest gtest_main ${CMAKE_THREAD_LIBS_INIT})
endif(BUILD_TESTS)

# EOF #