# SmartVacuumCleaner - Deterministic smart agent
Smart agent following the BDI model architecture for AI course at UQAC. 

The goal of this project was to make a smart agent which could move around in an obstructed environement.
Based on his knowledge, the agent will compute the best/shortest path in order to maximize a performance metric.

As a secondary goal of this project was to handle multi-threading, the agent behaviour and thinking process is isolated in a thread, and the map obstacle generation is in another one.

## Obstacles
The agent will encounter dust and jewelry which are generated continuously, with probability rates, in a different thread.
The goal will be to avoid vacuuming jewelry (gives a penalty) and focus on dust (gives points).

## Abilities
The agent is able to:

* Move around independently
* Compute a path using BFS or A* algorithm.
* Vacuum a cell.

## Current state
The project is functionning, and we added an optional training period at the beginning in order to fix a refresh rate of the agent's knowledge.
A choice will be presented in order to pick an algorithm with a pre-selected rate, or an option for live training.

## Concepts used
Dynamic environment generation with obstacles
Multi-threading
BDI model architecture for the agent

## How to run
Once the source code downloaded, it can be run with your IDE of choice with CMAKE see [CMakeLists.txt](CMakeLists.txt)

