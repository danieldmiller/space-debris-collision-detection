cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(space-debris-collision-detection)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Pthreads
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

# compiles the files defined by SOURCES to generante the executable defined by EXEC
add_executable(space-debris-collision-detection
	Main.cpp
	Space.cpp
	SpaceObject.cpp
	SpacePoint.cpp
	SpaceWriter.cpp
	Clock.cpp
)

target_link_libraries(space-debris-collision-detection Threads::Threads)
