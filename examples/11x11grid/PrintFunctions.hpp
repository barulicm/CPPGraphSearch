#ifndef GRAPHSEARCH_PRINTFUNCTIONS_HPP
#define GRAPHSEARCH_PRINTFUNCTIONS_HPP

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

#endif //GRAPHSEARCH_PRINTFUNCTIONS_HPP
