#include <catch2/catch.hpp>
#include <graphsearch/GraphSearch.hpp>
#include "../Map2d.h"

TEST_CASE( "AStar Anything is the goal", "[astar]" ) {
  using StateType = int;
  using ActionType = int;
  StateType startState = 0;
  auto goalFunction = [](const StateType&)->bool { return true; };
  auto allowedActionsFunction = [](const StateType&)->std::vector<StateType> { return {}; };
  auto transitionFunction = [](const StateType&,const ActionType&)->StateType { return 0; };
  auto stepCostFunction = [](const StateType&, const ActionType&) { return 1; };
  auto heuristicFunction = [](const StateType &x) { return x; };

  auto result = GraphSearch::AStar<StateType,ActionType>(startState, goalFunction, allowedActionsFunction, transitionFunction, stepCostFunction, heuristicFunction);

  REQUIRE(result);
}

TEST_CASE( "AStar Unsolvable because no allowed actions", "[astar]" ) {
  using StateType = int;
  using ActionType = int;
  StateType startState = 0;
  auto goalFunction = [](const StateType&)->bool { return false; };
  auto allowedActionsFunction = [](const StateType&)->std::vector<StateType> { return {}; };
  auto transitionFunction = [](const StateType&,const ActionType&)->StateType { return 0; };
  auto stepCostFunction = [](const StateType&, const ActionType&) { return 1; };
  auto heuristicFunction = [](const StateType &x) { return x; };

  auto result = GraphSearch::AStar<StateType,ActionType>(startState, goalFunction, allowedActionsFunction, transitionFunction, stepCostFunction, heuristicFunction);

  REQUIRE_FALSE(result);
}

TEST_CASE( "AStar Find the number 3", "[astar]" ) {
  using StateType = int;
  using ActionType = int;
  StateType startState = 0;
  auto goalFunction = [](const StateType& x)->bool { return x == 3; };
  auto allowedActionsFunction = [](const StateType& x)->std::vector<StateType> {
    if (x < 5 && x > -5) {
      return {-1, 1};
    } else {
      return {};
    }
  };
  auto transitionFunction = [](const StateType& x,const ActionType& a)->StateType { return x + a; };
  auto stepCostFunction = [](const StateType&, const ActionType&) { return 1; };
  auto heuristicFunction = [](const StateType &x) { return abs(x - 3); };

  auto result = GraphSearch::AStar<StateType,ActionType>(startState, goalFunction, allowedActionsFunction, transitionFunction, stepCostFunction, heuristicFunction);

  REQUIRE(result);
  REQUIRE(result->last_state() == 3);
  REQUIRE(std::accumulate(result->actions().begin(), result->actions().end(), 0) == 3);
}

TEST_CASE( "AStar empty 2D map", "[astar]") {
  Map2d map{5,5};
  Location2d startState{0,0};
  Location2d goalState{4,4};
  auto goalFunction = [goalState](const Location2d &s){ return s == goalState; };
  auto allowedActionsFunction = [map](const Location2d &location){ return map.getAllowedActions(location); };
  auto stepCostFunction = [](const Location2d&, const Move2d&) { return 1; };
  auto heuristicFunction = [goalState](const Location2d &location) { return manhattenDistance(location, goalState); };

  auto result = GraphSearch::AStar<Location2d, Move2d>(startState, goalFunction, allowedActionsFunction, transitionFunction2d, stepCostFunction, heuristicFunction);

  REQUIRE(result);
  REQUIRE(result->last_state() == goalState);
  REQUIRE(result->actions().size() == 8);
}

TEST_CASE( "AStar unsolvable 2D map", "[astar]") {
  Map2d map{5,5};
  map.setCell({0,1}, Map2d::BLOCKED);
  map.setCell({1,0}, Map2d::BLOCKED);
  map.setCell({1,1}, Map2d::BLOCKED);
  Location2d startState{0,0};
  Location2d goalState{4,4};
  auto goalFunction = [goalState](const Location2d &s){ return s == goalState; };
  auto allowedActionsFunction = [map](const Location2d &location){ return map.getAllowedActions(location); };
  auto stepCostFunction = [](const Location2d&, const Move2d&) { return 1; };
  auto heuristicFunction = [goalState](const Location2d &location) { return manhattenDistance(location, goalState); };

  auto result = GraphSearch::AStar<Location2d, Move2d>(startState, goalFunction, allowedActionsFunction, transitionFunction2d, stepCostFunction, heuristicFunction);

  REQUIRE_FALSE(result);
}

TEST_CASE( "AStar hole in the wall 2D map", "[astar]") {
  Map2d map{5,5};
  map.setCells({0, 0, 1, 0, 0,
                0, 0, 1, 0, 0,
                0, 0, 0, 0, 0,
                0, 0, 1, 0, 0,
                0, 0, 1, 0, 0});
  Location2d startState{0,0};
  Location2d goalState{4,4};
  auto goalFunction = [goalState](const Location2d &s){ return s == goalState; };
  auto allowedActionsFunction = [map](const Location2d &location){ return map.getAllowedActions(location); };
  auto stepCostFunction = [](const Location2d&, const Move2d&) { return 1; };
  auto heuristicFunction = [goalState](const Location2d &location) { return manhattenDistance(location, goalState); };

  auto result = GraphSearch::AStar<Location2d, Move2d>(startState, goalFunction, allowedActionsFunction, transitionFunction2d, stepCostFunction, heuristicFunction);

  REQUIRE(result);
  REQUIRE(result->last_state() == goalState);
  REQUIRE(result->actions().size() == 8);
}
