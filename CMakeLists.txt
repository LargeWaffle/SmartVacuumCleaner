cmake_minimum_required(VERSION 3.23)
project(AgentProject)

set(CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")

add_executable(AgentProject
        main.cpp Map.cpp Map.h Sensor.cpp Sensor.h
        Effector.cpp Effector.h Agent.cpp Agent.h Graph.cpp Graph.h)
