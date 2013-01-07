CPPGraphSearch
==============

Matthew Barulic
2013

A C++ implementation of common graph/tree search algorithms. Currently includes: DFS, BFS, and A*

To use:
- Create a class that represents a state in your search problem.
- Create a class that represents an action in your search problem.
- Create a subclass of SearchProblem (typed with your state and action types) and define all inherited pure-virtual methods.
    NOTE: getStepCost() and getHeuristicCost() only need to be overridden when using AStar search.

See Example/main.cpp for an example use case.
