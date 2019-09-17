#ifndef CPPGRAPHSEARCH_PATH_HPP
#define CPPGRAPHSEARCH_PATH_HPP

#include <cassert>

namespace GraphSearch {

/**
 * @brief The Path class wraps a series of states and the actions needed to achieve them.
 * @tparam StateType A type for representing states in your search problem
 * @tparam ActionType A type for representing actions in your search problem
 */
template<class StateType, class ActionType>
class Path {
public:
  Path() = default;

  Path(const Path<StateType, ActionType> &p)
      : states_(p.states_),
        actions_(p.actions_) {
  }

  Path(std::vector<StateType> &&states, std::vector<ActionType> &&actions)
      : states_(states), actions_(actions) {

  }

  /**
   * @brief Appends the given state to the Path's state series.
   *
   * This should only be used to give the starting state to an empty Path
   *
   * @param state The state to append
   */
  void push_back(StateType state) {
    assert(states_.empty());
    states_.push_back(state);
  }

  /**
   * @brief Appends the given action and state to the Path
   *
   * This should only be used to extend a non-empty Path. The given action
   * should be the one necessary to get from the last state in this path to
   * the given state.
   *
   * @param action The action to append
   * @param state The state to append
   */
  void push_back(ActionType action, StateType state) {
    assert(!states_.empty());
    states_.push_back(state);
    actions_.push_back(action);
  }

  /**
   * @brief Offers read-only access to the series of states for this Path
   * @return This Path's series of states
   */
  const std::vector<StateType> &states() const {
    return states_;
  }

  /**
   * @brief Offers read-only access to the series of actions for this Path
   * @return This Path's series of actions
   */
  const std::vector<ActionType> &actions() const {
    return actions_;
  }

  /**
   * @brief A convenience function for getting the last state in this Path
   * @return The state at the end of this Path's series of states
   */
  const StateType &last_state() const {
    return states_.back();
  }

private:
  std::vector<StateType> states_;
  std::vector<ActionType> actions_;
};

}

#endif //CPPGRAPHSEARCH_PATH_HPP
