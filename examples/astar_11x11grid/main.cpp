#include <iostream>
#include <string>
#include <set>

#include <graphsearch/GraphSearch.hpp>

using namespace std;

class Location
{
public:
    int x, y;
    Location() = default;
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
    bool operator == (const Location &other) const
    {
        return (x == other.x) && (y == other.y);
    }
    bool operator < (const Location &other) const
    {
        if(x < other.x)
        {
            return true;
        }
        else if(y < other.y)
        {
            return true;
        }
        return false;
    }
};

class Move
{
public:
    string dir;
    Move() = default;
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

int main()
{

  Location startLoc{0,0};
  Location goalLoc{5,5};

  int map[11][11];
  for(int x = 0; x < 11; x++)
      for(int y = 0; y < 11; y++)
          map[x][y] = 0;
  map[0][1] = 1;
  map[1][1] = 1;
  map[2][1] = 1;
  map[3][1] = 1;
  map[4][1] = 1;
  map[5][1] = 1;
  map[6][1] = 1;

  auto goalFunction = [goalLoc](const Location& x) { return x == goalLoc; };

  auto getActions = [map](Location state)
  {
    std::vector<Move> acts;
    if(state.y < 10 && map[state.x][state.y+1] != 1)
      acts.emplace_back("E");
    if(state.y > 0 && map[state.x][state.y-1] != 1)
      acts.emplace_back("W");
    if(state.x < 10 && map[state.x+1][state.y] != 1)
      acts.emplace_back("S");
    if(state.x > 0 && map[state.x-1][state.y] != 1)
      acts.emplace_back("N");
    return acts;
  };

  auto getResult = [](Location state, Move action)
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
  };

  auto getStepCost = [](const Location &state, const Move &action)
  {
    //All actions move one unit
    return 1;
  };

  auto getHeuristicCost = [](const Location &state)
  {
    //Manhatten distance
    return abs(state.x - 5) + abs(state.y - 5);
  };

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
              cout << map[x][y] << " ";
          }
      }
      cout << endl;
  }
  cout << endl;

  auto path = GraphSearch::AStar<Location, Move>(startLoc, goalFunction, getActions, getResult, getStepCost, getHeuristicCost);

  if(!path) {
    cout << "Could not find a path!" << endl;
    return 0;
  }

  cout << "Found path of length " << path->getNumberOfSteps() << ":" << endl;

  char pathMap[11][11];
  for(int x = 0; x < 11; x++)
      for(int y = 0; y < 11; y++)
          pathMap[x][y] = map[x][y] + 48;

  for(int i = 0; i < path->getNumberOfSteps(); i++)
  {
      Location loc = path->getState(i);
      Move m = path->getAction(i);
      pathMap[loc.x][loc.y] = m.dir[0];
  }

  Location dest = path->getLastState();
  pathMap[dest.x][dest.y] = '*';

  for(int x = 0; x < 11; x++)
  {
      for(int y = 0; y < 11; y++)
      {
          cout << pathMap[x][y] << " ";
      }
      cout << endl;
  }

  for(auto &loc : *(path->getStates()))
  {
      cout << loc << ", ";
  }
  cout << endl << endl;

  for(auto &m : *(path->getActions()))
  {
      cout << m << ", ";
  }
  cout << endl;

  return 0;
}
