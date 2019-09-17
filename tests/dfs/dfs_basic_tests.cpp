#include <catch2/catch.hpp>
#include <graphsearch/GraphSearch.hpp>

TEST_CASE( "Anything is the goal", "[dfs]" ) {
  using StateType = int;
  using ActionType = int;
  StateType startState = 0;
  auto goalFunction = [](const StateType&)->bool { return true; };
  auto allowedActionsFunction = [](const StateType&)->std::vector<StateType> { return {}; };
  auto transitionFunction = [](const StateType&,const ActionType&)->StateType { return 0; };

  auto result = GraphSearch::DFS<StateType,ActionType>(startState, goalFunction, allowedActionsFunction, transitionFunction);

  REQUIRE(result);
}

TEST_CASE( "Unsolvable because no allowed actions", "[dfs]" ) {
  using StateType = int;
  using ActionType = int;
  StateType startState = 0;
  auto goalFunction = [](const StateType&)->bool { return false; };
  auto allowedActionsFunction = [](const StateType&)->std::vector<StateType> { return {}; };
  auto transitionFunction = [](const StateType&,const ActionType&)->StateType { return 0; };

  auto result = GraphSearch::DFS<StateType,ActionType>(startState, goalFunction, allowedActionsFunction, transitionFunction);

  REQUIRE(!result);
}

TEST_CASE( "Find the number 3", "[dfs]" ) {
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

  auto result = GraphSearch::DFS<StateType,ActionType>(startState, goalFunction, allowedActionsFunction, transitionFunction);

  REQUIRE(result);
  REQUIRE(result->getLastState() == 3);
  REQUIRE(std::accumulate(result->getActions()->begin(), result->getActions()->end(), 0) == 3);
}
