#include <iostream>
#include <string>

#include <graphsearch/GraphSearch.hpp>

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
    friend std::ostream &operator<< (std::ostream &stream, const Location &loc)
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
        else if(x == other.x && y < other.y)
        {
            return true;
        }
        return false;
    }
};

class Move
{
public:
  enum Direction {
    NORTH,
    EAST,
    SOUTH,
    WEST
  } dir;

  Move() = default;

  explicit Move(Direction d) : dir(d) {}

  friend std::ostream &operator<< (std::ostream &stream, const Move &move)
  {
      stream << move.to_string();
      return stream;
  }

  bool operator == (const Move &other)
  {
      return (dir == other.dir);
  }

  std::string to_string() const {
    switch(dir) {
      case NORTH:
        return "N";
      case EAST:
        return "E";
      case SOUTH:
        return "S";
      case WEST:
        return "W";
    }
  }
};

void print_map(const int map[11][11], const Location &start, const Location &goal) {
  for(int x = 0; x < 11; x++)
  {
    for(int y = 0; y < 11; y++)
    {
      if(x == start.x && y == start.y)
      {
        std::cout << "S" << " ";
      }
      else if(x == goal.x && y == goal.y)
      {
        std::cout << "*" << " ";
      }
      else
      {
        std::cout << map[x][y] << " ";
      }
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

void print_map_and_path(const int map[11][11], const Path<Location, Move> &path) {
  char pathMap[11][11];
  for(int x = 0; x < 11; x++)
    for(int y = 0; y < 11; y++)
      pathMap[x][y] = map[x][y] + 48;

  for(int i = 0; i < path.actions().size(); i++)
  {
    Location loc = path.states()[i];
    Move m = path.actions()[i];
    pathMap[loc.x][loc.y] = m.to_string()[0];
  }

  Location dest = path.last_state();
  pathMap[dest.x][dest.y] = '*';

  for(int x = 0; x < 11; x++)
  {
    for(int y = 0; y < 11; y++)
    {
      std::cout << pathMap[x][y] << " ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

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
      acts.emplace_back(Move::EAST);
    if(state.y > 0 && map[state.x][state.y-1] != 1)
      acts.emplace_back(Move::WEST);
    if(state.x < 10 && map[state.x+1][state.y] != 1)
      acts.emplace_back(Move::SOUTH);
    if(state.x > 0 && map[state.x-1][state.y] != 1)
      acts.emplace_back(Move::NORTH);
    return acts;
  };

  auto getResult = [](Location state, Move action)
  {
    switch(action.dir) {
      case Move::EAST:
        return Location(state.x, state.y+1);
      case Move::WEST:
        return Location(state.x, state.y-1);
      case Move::SOUTH:
        return Location(state.x+1, state.y);
      case Move::NORTH:
        return Location(state.x-1, state.y);
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

  std::cout << "Map to navigate: " << std::endl;
  print_map(map, startLoc, goalLoc);

  {
    // A-Star
    auto path = GraphSearch::AStar<Location, Move>(startLoc, goalFunction, getActions, getResult, getStepCost, getHeuristicCost);

    if(path) {
      std::cout << "A* path:" << std::endl;
      print_map_and_path(map, path.value());
    } else {
      std::cout << "A* could not find a path!" << std::endl;
    }
  }

  {
    // BFS
    auto path = GraphSearch::BFS<Location, Move>(startLoc, goalFunction, getActions, getResult);

    if(path) {
      std::cout << "BFS path:" << std::endl;
      print_map_and_path(map, path.value());
    } else {
      std::cout << "BFS could not find a path!" << std::endl;
    }
  }

  {
    // DFS
    auto path = GraphSearch::DFS<Location, Move>(startLoc, goalFunction, getActions, getResult);

    if(path) {
      std::cout << "DFS path:" << std::endl;
      print_map_and_path(map, path.value());
    } else {
      std::cout << "DFS could not find a path!" << std::endl;
    }
  }

  return 0;
}
