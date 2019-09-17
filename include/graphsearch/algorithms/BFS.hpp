#ifndef GRAPHSEARCH_BFS_HPP
#define GRAPHSEARCH_BFS_HPP

#include <set>
#include <queue>
#include <optional>
#include <functional>

#include "graphsearch/Path.hpp"

namespace GraphSearch {

/** Runs Breadth-First graph on the given search problem */
template<class StateType, class ActionType>
std::optional<Path<StateType, ActionType>>
BFS(StateType &startState, std::function<bool(const StateType &)> isGoal,
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

        Path<StateType, ActionType> newPath(path);
        newPath.push_back(action, nextState);
        frontier.push(newPath);
      }
    }
  }
  return {};
}

}

#endif //GRAPHSEARCH_BFS_HPP
