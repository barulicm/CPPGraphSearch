#ifndef GRAPHSEARCH_BFS_HPP
#define GRAPHSEARCH_BFS_HPP

#include <set>
#include <queue>
#include <optional>
#include <functional>

#include "graphsearch/Path.hpp"

namespace GraphSearch {

/**
 * @brief Runs Breadth-First Search on the problem described by the function arguments
 * @tparam StateType A type for representing states in your search problem
 * @tparam ActionType A type for representing actions in your search problem
 * @param startState The state from which the search should start
 * @param isGoal A function which determines whether the given state meets the goal criteria for the search
 * @param getAllowedActions A function which gives the set of allowed actions for a given state
 * @param getNextState A function which gives the state resulting from taking the given action from the given state
 * @return An optional Path that connects the starts state to a goal state. An empty optional will be returned if no path is possible.
 */
template<class StateType, class ActionType>
std::optional<Path<StateType, ActionType>>
BFS(const StateType &startState, std::function<bool(const StateType &)> isGoal,
    std::function<std::vector<ActionType>(const StateType &)> getAllowedActions,
    std::function<StateType(const StateType &,
                            const ActionType &)> getNextState) {
  std::set<StateType> expanded;
  std::queue<Path<StateType, ActionType> > frontier;

  frontier.push(Path<StateType, ActionType>({startState}, {}));

  while (!frontier.empty()) {
    auto path = frontier.front();
    frontier.pop();

    auto lastState = path.last_state();

    if (expanded.find(lastState) == expanded.end()) {

      expanded.insert(lastState);

      if (isGoal(lastState)) {
        return path;
      }

      auto allowedActions = getAllowedActions(lastState);

      for (auto &action : allowedActions) {
        auto nextState = getNextState(lastState, action);
        if(expanded.find(nextState) == expanded.end()) {
          Path<StateType, ActionType> newPath(path);
          newPath.push_back(action, nextState);
          frontier.push(newPath);
        }
      }
    }
  }
  return {};
}

}

#endif //GRAPHSEARCH_BFS_HPP
