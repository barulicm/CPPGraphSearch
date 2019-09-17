#ifndef GRAPHSEARCH_LOCATION_HPP
#define GRAPHSEARCH_LOCATION_HPP

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

#endif //GRAPHSEARCH_LOCATION_HPP
