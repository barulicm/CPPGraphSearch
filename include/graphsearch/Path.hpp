#ifndef CPPGRAPHSEARCH_PATH_HPP
#define CPPGRAPHSEARCH_PATH_HPP

template<class StateType, class ActionType>
class Path {
public:
  Path() = default;

  Path(const Path<StateType, ActionType> &p)
    : states_(p.states_),
      actions_(p.actions_)
  {
  }

  Path(std::vector<StateType> &&states, std::vector<ActionType> &&actions)
    : states_(states), actions_(actions) {

  }

  void push_back(StateType state) {
    if(!states_.empty()) {
      throw std::invalid_argument("When a path is not empty, you must push both a state and the action to get to that state.");
    }
    states_.push_back(state);
  }

  void push_back(ActionType action, StateType state) {
    if(states_.empty()) {
      throw std::invalid_argument("When a path is empty, you must push a starting state without an action.");
    }
    states_.push_back(state);
    actions_.push_back(action);
  }

  const std::vector<StateType> &states() const {
    return states_;
  }

  const std::vector<ActionType> &actions() const {
    return actions_;
  }

  const StateType &last_state() const {
    return states_.back();
  }

private:
  std::vector <StateType> states_;
  std::vector <ActionType> actions_;
};

#endif //CPPGRAPHSEARCH_PATH_HPP
