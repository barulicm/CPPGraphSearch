#include <iostream>
#include <string>

#include <graphsearch/GraphSearch.hpp>

#include "Location.hpp"
#include "Move.hpp"
#include "PrintFunctions.hpp"

int main()
{
  // Define starting and ending positions
  Location startLoc{0,0};
  Location goalLoc{5,5};

  // Create a map to be navigated
  int map[11][11];
  for(int x = 0; x < 11; x++)
      for(int y = 0; y < 11; y++)
          map[x][y] = 0;
  map[0][1] = 1;
  map[1][1] = 1;
  map[2][1] = 1;
  map[3][1] = 1;
  map[4][1] = 1;
  map[5][1] = 1;
  map[6][1] = 1;

  // Define a function to evaluate when the goal is reached
  auto goalFunction = [goalLoc](const Location& x) { return x == goalLoc; };

  // Define a function to return allowed actions from any state
  auto getActions = [map](Location state)
  {
    std::vector<Move> acts;
    if(state.y < 10 && map[state.x][state.y+1] != 1)
      acts.emplace_back(Move::EAST);
    if(state.y > 0 && map[state.x][state.y-1] != 1)
      acts.emplace_back(Move::WEST);
    if(state.x < 10 && map[state.x+1][state.y] != 1)
      acts.emplace_back(Move::SOUTH);
    if(state.x > 0 && map[state.x-1][state.y] != 1)
      acts.emplace_back(Move::NORTH);
    return acts;
  };

  // Define a function that returns the next state given the previous state and action
  auto transitionFunction = [](Location state, Move action)
  {
    switch(action.dir) {
      case Move::EAST:
        return Location(state.x, state.y+1);
      case Move::WEST:
        return Location(state.x, state.y-1);
      case Move::SOUTH:
        return Location(state.x+1, state.y);
      case Move::NORTH:
        return Location(state.x-1, state.y);
    }
  };

  // Define a function that gives the cost of an action
  auto stepCostFunction = [](const Location &state, const Move &action)
  {
    //All actions move one unit
    return 1;
  };

  // Define a function that gives a heuristic value for a given state
  auto heuristicFunction = [](const Location &state)
  {
    //Manhatten distance
    return abs(state.x - 5) + abs(state.y - 5);
  };

  std::cout << "Map to navigate: " << std::endl;
  print_map(map, startLoc, goalLoc);

  {
    // A-Star
    auto path = GraphSearch::AStar<Location, Move>(startLoc, goalFunction, getActions, transitionFunction, stepCostFunction, heuristicFunction);

    if(path) {
      std::cout << "A* path:" << std::endl;
      print_map_and_path(map, path.value());
    } else {
      std::cout << "A* could not find a path!" << std::endl;
    }
  }

  {
    // BFS
    auto path = GraphSearch::BFS<Location, Move>(startLoc, goalFunction, getActions, transitionFunction);

    if(path) {
      std::cout << "BFS path:" << std::endl;
      print_map_and_path(map, path.value());
    } else {
      std::cout << "BFS could not find a path!" << std::endl;
    }
  }

  {
    // DFS
    auto path = GraphSearch::DFS<Location, Move>(startLoc, goalFunction, getActions, transitionFunction);

    if(path) {
      std::cout << "DFS path:" << std::endl;
      print_map_and_path(map, path.value());
    } else {
      std::cout << "DFS could not find a path!" << std::endl;
    }
  }

  return 0;
}
