#ifndef GRAPHSEARCH_DFS_HPP
#define GRAPHSEARCH_DFS_HPP

#include <set>
#include <stack>
#include <optional>

#include "graphsearch/Path.hpp"

namespace GraphSearch {

/** Runs Depth-First graph search on the given search problem */
template<class StateType, class ActionType>
std::optional<Path<StateType, ActionType>>
DFS(StateType &startState, std::function<bool(const StateType &)> isGoal,
    std::function<std::vector<ActionType>(const StateType &)> getAllowedActions,
    std::function<StateType(const StateType &,
                            const ActionType &)> getNextState) {

  std::set<StateType> expanded;
  std::stack<Path<StateType, ActionType>> frontier;

  frontier.push(Path<StateType, ActionType>({startState}, {}));

  while (!frontier.empty()) {
    auto path = frontier.top();
    frontier.pop();

    auto lastState = path.getLastState();

    if (expanded.find(lastState) == expanded.end()) {
      expanded.insert(lastState);

      if (isGoal(lastState)) {
        return path;
      }

      auto allowedActions = getAllowedActions(lastState);

      for (auto &action : allowedActions) {
        auto nextState = getNextState(lastState, action);
        Path<StateType, ActionType> newPath(path);
        newPath.addAction(action);
        newPath.addState(nextState);
        frontier.push(newPath);
      }
    }
  }

  return {};
}

}

#endif //GRAPHSEARCH_DFS_HPP
