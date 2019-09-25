cmake_minimum_required(VERSION 3.14)
project(mahisim)

set(CMAKE_CXX_STANDARD 14)

include_directories(${CMAKE_SOURCE_DIR}/gymsim/include)

file(GLOB SOURCES "src/*.cpp")
file(GLOB LIBRARIES "${CMAKE_SOURCE_DIR}/gymsim/lib/*.dylib")
message("LIBRARIES = ${LIBRARIES}")

set(libs)
# Qt5
find_package(Qt5 COMPONENTS Core Network Gui REQUIRED)
list(APPEND libs Qt5::Core Qt5::Network Qt5::Gui)


add_executable(mahisim ${SOURCES})
target_link_libraries(mahisim ${LIBRARIES} ${libs})

