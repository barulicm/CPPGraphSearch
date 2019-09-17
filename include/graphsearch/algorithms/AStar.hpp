#ifndef GRAPHSEARCH_ASTAR_HPP
#define GRAPHSEARCH_ASTAR_HPP

#include <set>
#include <queue>
#include <optional>
#include <functional>

#include "graphsearch/Path.hpp"

namespace GraphSearch {

/**
 * @brief Runs A* Search on the problem described by the function arguments
 * @tparam StateType A type for representing states in your search problem
 * @tparam ActionType A type for representing actions in your search problem
 * @param startState The state from which the search should start
 * @param isGoal A function which determines whether the given state meets the goal criteria for the search
 * @param getAllowedActions A function which gives the set of allowed actions for a given state
 * @param getNextState A function which gives the state resulting from taking the given action from the given state
 * @param getStepCost A function which gives the cost of taking the given action from the given state
 * @param getHeuristic A function which gives the heuristic cost for the given state
 * @return An optional Path that connects the starts state to a goal state. An empty optional will be returned if no path is possible.
 */
template<class StateType, class ActionType>
std::optional<Path<StateType, ActionType>>
AStar(const StateType &startState, std::function<bool(const StateType &)> isGoal,
      std::function<std::vector<ActionType>(
          const StateType &)> getAllowedActions,
      std::function<StateType(const StateType &,
                              const ActionType &)> getNextState,
      std::function<double(const StateType &, const ActionType &)> getStepCost,
      std::function<double(const StateType &)> getHeuristic) {

  using FrontierEntry = std::pair<Path<StateType, ActionType>, double>;

  auto FrontierEntryComparator = [](FrontierEntry &a, FrontierEntry &b) {
    return a.second > b.second;
  };

  auto getPathCost = [getStepCost, getHeuristic](Path<StateType,ActionType> &path) {
    double cost = 0;
    for(int i = 0; i < path.actions().size(); i++) {
      cost += getStepCost(path.states()[i], path.actions()[i]);
    }
    cost += getHeuristic(path.last_state());
    return cost;
  };

  std::set <StateType> expanded;
  std::priority_queue<FrontierEntry, std::vector<FrontierEntry>, decltype(FrontierEntryComparator)> frontier(
      FrontierEntryComparator);

  Path<StateType, ActionType> initialPath({startState}, {});
  frontier.push({initialPath, getPathCost(initialPath)});

  while (!frontier.empty()) {
    auto [path, cost] = frontier.top();
    frontier.pop();

    auto lastState = path.last_state();

    if (expanded.find(lastState) == expanded.end()) {
      expanded.insert(lastState);

      if (isGoal(lastState)) {
        return path;
      }
      auto allowedActions = getAllowedActions(lastState);

      for(auto &action : allowedActions) {
        auto nextState = getNextState(lastState, action);
        if(expanded.find(nextState) == expanded.end()) {
          Path<StateType, ActionType> newPath(path);
          newPath.push_back(action, nextState);
          frontier.push({newPath, getPathCost(newPath)});
        }
      }
    }
  }

  return {};
}

}

#endif //GRAPHSEARCH_ASTAR_HPP
