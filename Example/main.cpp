#include <iostream>
#include <string>

#include "SearchProblem.hpp"
#include "GraphSearch.hpp"
#include <set>

class Location
{
public:
    int x, y;
    Location(){ }
    Location(int _x, int _y)
    {
        x = _x;
        y = _y;
    }
    friend ostream &operator<< (ostream &stream, Location &loc)
    {
        stream << "(" << loc.x << "," << loc.y << ")";
        return stream;
    }
    bool operator == (const Location &other)
    {
        return (x == other.x) && (y == other.y);
    }
    bool operator < (const Location &other) const
    {
//        std::cout << "( (" << x << "," << y << ") < (" << other.x << "," << other.y << ") )";
        if(x < other.x)
        {
//            cout << "\tTrue" << endl;
            return true;
        }
        else if(y < other.y)
        {
//            cout << "\tTrue" << endl;
            return true;
        }
//        cout << "\tFalse" << endl;
        return false;
    }
};

class Move
{
public:
    string dir;
    Move(){ }
    Move(string d)
    {
        dir = d;
    }
    friend ostream &operator<< (ostream &stream, Move &move)
    {
        stream << move.dir;
        return stream;
    }
    bool operator == (const Move &other)
    {
        return (dir == other.dir);
    }
};

class Problem : public SearchProblem<Location, Move>
{
public:
    int map[11][11];
    Location getStartState()
    {
        Location loc;
        loc.x = 0;
        loc.y = 0;
        return loc;
    }
    std::list<Move> getActions(Location state)
    {
        std::list<Move> acts;
        if(state.y < 10 && map[state.x][state.y+1] != 1)
            acts.push_back(Move("E"));
        if(state.y > 0 && map[state.x][state.y-1] != 1)
            acts.push_back(Move("W"));
        if(state.x < 10 && map[state.x+1][state.y] != 1)
            acts.push_back(Move("S"));
        if(state.x > 0 && map[state.x-1][state.y] != 1)
            acts.push_back(Move("N"));
        return acts;
    }
    Location getResult(Location state, Move action)
    {
        if(action.dir == "E")
        {
            return Location(state.x, state.y+1);
        }
        else if (action.dir == "W")
        {
            return Location(state.x, state.y-1);
        }
        else if (action.dir == "S")
        {
            return Location(state.x+1, state.y);
        }
        else if (action.dir == "N")
        {
            return Location(state.x-1, state.y);
        }
        else
        {
            return state;
        }
    }
    bool isGoal(Location state)
    {
        //Destination is (5,5)
        return (state.x == 5) && (state.y == 5);
    }
    double getStepCost(Location state, Move action)
    {
        //All actions move one unit
        return 1;
    }
    double getHeuristicCost(Location state)
    {
        //Manhatten distance
        return abs(state.x - 5) + abs(state.y - 5);
    }
};

int main()
{
    Problem problem;

    for(int x = 0; x < 11; x++)
        for(int y = 0; y < 11; y++)
            problem.map[x][y] = 0;
    problem.map[0][1] = 1;
    problem.map[1][1] = 1;
    problem.map[2][1] = 1;
    problem.map[3][1] = 1;
    problem.map[4][1] = 1;
    problem.map[5][1] = 1;
    problem.map[6][1] = 1;

    for(int x = 0; x < 11; x++)
    {
        for(int y = 0; y < 11; y++)
        {
            if(x == 0 && y == 0)
            {
                cout << "S" << " ";
            }
            else if(x == 5 && y == 5)
            {
                cout << "*" << " ";
            }
            else
            {
                cout << problem.map[x][y] << " ";
            }
        }
        cout << endl;
    }
    cout << endl;

    Path<Location, Move> path = GraphSearch::AStar(problem);

    cout << "Found path of length " << path.getNumberOfSteps() << ":" << endl;

    char pathMap[11][11];
    for(int x = 0; x < 11; x++)
        for(int y = 0; y < 11; y++)
            pathMap[x][y] = problem.map[x][y] + 48;

    for(int i = 0; i < path.getNumberOfSteps(); i++)
    {
        Location loc = path.getState(i);
        Move m = path.getAction(i);
        pathMap[loc.x][loc.y] = m.dir[0];
    }

    Location dest = path.getLastState();
    pathMap[dest.x][dest.y] = '*';

    for(int x = 0; x < 11; x++)
    {
        for(int y = 0; y < 11; y++)
        {
            cout << pathMap[x][y] << " ";
        }
        cout << endl;
    }

//    list<Location>* locations = path.getStates();
//    for(list<Location>::iterator it = locations->begin(); it != locations->end(); it++)
//    {
//        Location loc = *it;
//        cout << loc << ", ";
//    }
//    cout << endl << endl;
//
//    list<Move>* moves = path.getActions();
//    for(list<Move>::iterator it = moves->begin(); it != moves->end(); it++)
//    {
//        Move m = *it;
//        cout << m << ", ";
//    }
//    cout << endl;

    return 0;
}
