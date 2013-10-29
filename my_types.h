#ifndef MY_TYPES_H
#define MY_TYPES_H

#include <vector>
#include <utility>
#include <glm/glm.hpp>

namespace my{

typedef glm::vec3  Point;
typedef glm::vec3  Vector;
typedef glm::vec4 Color;

typedef glm::vec3  Vertex;
typedef glm::vec3  Normal;
typedef std::vector<int> Triangle;
typedef std::pair<float,float> Parameters;
typedef std::pair<int,int> Range;

typedef enum{CLOCKWISE, COUNTER_CLOCKWISE} Orientation;
}

#endif // MY_TYPES_H
