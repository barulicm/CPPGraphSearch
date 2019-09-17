#include <cassert>
#include <algorithm>
#include "Map2d.h"

Location2d transitionFunction2d(const Location2d &location, const Move2d &move) {
  switch(move.direction) {
    case Move2d::UP:
      return {location.x, location.y+1};
    case Move2d::DOWN:
      return {location.x, location.y-1};
    case Move2d::LEFT:
      return {location.x-1, location.y};
    case Move2d::RIGHT:
      return {location.x+1, location.y};
  }
}

int manhattenDistance(const Location2d &a, const Location2d &b) {
  return abs(a.x - b.x) + abs(a.y - b.y);
}

Map2d::Map2d(int width, int height)
  : width(width),
    height(height)
{
  data.resize(width*height);
  std::fill(data.begin(), data.end(), OPEN);
}

void Map2d::setCells(const std::vector<int> &cells) {
  assert(cells.size() == data.size());
  std::transform(cells.begin(), cells.end(), data.begin(), [](const int &c){
    return c ? BLOCKED : OPEN;
  });
}

void Map2d::setCell(const Location2d &location, const CellType &type) {
  data[indexFromLocation(location)] = type;
}

Map2d::CellType Map2d::getCell(const Location2d &location) const {
  return data[indexFromLocation(location)];
}

std::vector<Move2d> Map2d::getAllowedActions(const Location2d &location) const {
  std::vector<Move2d> actions;

  if(location.x < (width - 1) && getCell({location.x+1, location.y}) == OPEN)
    actions.push_back({Move2d::RIGHT});
  if(location.x > 0 && getCell({location.x-1, location.y}) == OPEN)
    actions.push_back({Move2d::LEFT});
  if(location.y < (height - 1) && getCell({location.x, location.y+1}) == OPEN)
    actions.push_back({Move2d::UP});
  if(location.y > 0 && getCell({location.x, location.y-1}) == OPEN)
    actions.push_back({Move2d::DOWN});

  return actions;
}

size_t Map2d::indexFromLocation(const Location2d &location) const {
  return (location.y * width) + location.x;
}
