#ifndef GRAPHSEARCH_MAP2D_H
#define GRAPHSEARCH_MAP2D_H

#include <vector>

struct Location2d {
  int x;
  int y;
  bool operator == (const Location2d &other) const
  {
    return (x == other.x) && (y == other.y);
  }
  bool operator < (const Location2d &other) const
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

struct Move2d {
  enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
  } direction;
  bool operator == (const Move2d &other)
  {
    return (direction == other.direction);
  }
  char to_char() const {
    switch(direction) {
      case UP:
        return 'U';
      case DOWN:
        return 'D';
      case LEFT:
        return 'L';
      case RIGHT:
        return 'R';
    }
  }
};

Location2d transitionFunction2d(const Location2d &location, const Move2d &move);

int manhattenDistance(const Location2d &a, const Location2d &b);

class Map2d {
public:
  explicit Map2d(int width, int height);

  enum CellType {
    OPEN,
    BLOCKED
  };

  void setCells(const std::vector<int> &cells);

  void setCell(const Location2d &location, const CellType &type);

  CellType getCell(const Location2d &location) const;

  std::vector<Move2d> getAllowedActions(const Location2d &location) const;

private:
  int width;
  int height;
  std::vector<CellType> data;

  size_t indexFromLocation(const Location2d &location) const;

};


#endif //GRAPHSEARCH_MAP2D_H
