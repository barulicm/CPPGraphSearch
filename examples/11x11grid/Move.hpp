#ifndef GRAPHSEARCH_MOVE_HPP
#define GRAPHSEARCH_MOVE_HPP

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

#endif //GRAPHSEARCH_MOVE_HPP
