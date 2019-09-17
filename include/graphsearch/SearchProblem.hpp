#ifndef SEARCHPROBLEM_HPP_INCLUDED
#define SEARCHPROBLEM_HPP_INCLUDED

#include <list>
#include <algorithm>
#include <iterator>

template <class StateType, class ActionType>
class SearchProblem
{
public:
    virtual StateType getStartState() = 0;
    virtual std::list<ActionType> getActions(StateType state) = 0;
    virtual StateType getResult(StateType state, ActionType action) = 0;
    virtual bool isGoal(StateType tate) = 0;
    virtual double getStepCost(StateType state, ActionType action) { (void)state; (void)action; return 1; }
    virtual double getHeuristicCost(StateType state) { (void)state; return 0; }
    double getPathCost(Path<StateType, ActionType>* path)
    {
        double cost = 0;

        for(int i=0; i < path->getNumberOfSteps(); i++)
        {
            cost += getStepCost(path->getState(i), path->getAction(i));
        }

        return cost;
    }
};

#endif // SEARCHPROBLEM_HPP_INCLUDED
