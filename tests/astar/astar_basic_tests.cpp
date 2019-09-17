#include <catch2/catch.hpp>
#include <graphsearch/GraphSearch.hpp>

TEST_CASE( "AStar Anything is the goal", "[bfs]" ) {
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

TEST_CASE( "AStar Unsolvable because no allowed actions", "[bfs]" ) {
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

TEST_CASE( "AStar Find the number 3", "[bfs]" ) {
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
  REQUIRE(result->getLastState() == 3);
  REQUIRE(std::accumulate(result->getActions()->begin(), result->getActions()->end(), 0) == 3);
}
