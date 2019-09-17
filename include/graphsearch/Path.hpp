#ifndef CPPGRAPHSEARCH_PATH_HPP
#define CPPGRAPHSEARCH_PATH_HPP

template<class StateType, class ActionType>
class Path {
public:
  Path() = default;

  Path(const Path<StateType, ActionType> &p) {
    states = std::vector<StateType>(p.states);
    actions = std::vector<ActionType>(p.actions);
  }

  Path(std::vector<StateType> &&states, std::vector<ActionType> &&actions)
    : states(states), actions(actions) {

  }

  void addState(StateType state) {
    states.push_back(state);
  }

  void addAction(ActionType action) {
    actions.push_back(action);
  }

  void setState(StateType state, int index) {
    if (index < 0 || index >= states.size())
      throw "Index out of bounds!";
    states[index] = state;
  }

  void setAction(ActionType action, int index) {
    if (index < 0 || index >= actions.size())
      throw "Index out of bounds!";
    actions[index] = action;
  }

  StateType getState(unsigned int index) {
    if (index < 0 || index >= states.size())
      throw "Index out of bounds!";

    typename std::vector<StateType>::iterator iter = states.begin();
    std::advance(iter, index);
    return *iter;
  }

  ActionType getAction(unsigned int index) {
    if (index < 0 || index >= actions.size())
      throw "Index out of bounds!";
    typename std::vector<ActionType>::iterator iter = actions.begin();
    std::advance(iter, index);
    return *iter;
  }

  std::vector <StateType> *getStates() {
    return &states;
  }

  std::vector <ActionType> *getActions() {
    return &actions;
  }

  StateType getLastState() {
    return states.back();
  }

  int getNumberOfSteps() {
    return actions.size();
  }

  bool containsState(StateType state) {
    return (find(states.begin(), states.end(), state) != states.end());
  }

private:
  std::vector <StateType> states;
  std::vector <ActionType> actions;
};

#endif //CPPGRAPHSEARCH_PATH_HPP
