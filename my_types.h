#ifndef MY_TYPES_H
#define MY_TYPES_H

#include <vector>
#include <utility>
#include <glm/glm.hpp>

namespace my{

typedef glm::vec3  Point; /**< Represents geometrical a point, defined by it's 3 coordinates */
typedef glm::vec3  Vector; /**< Represents a vector, defined by it's 3 coordinates */
typedef glm::vec4 Color; /**< Represents a color, defined by it's 4 float components RGBA */

typedef glm::vec3  Vertex; /**< Represents a vertex in a scene, defined by it's 3 coordinates*/
typedef glm::vec3  Normal; /**< Represents a surface normal, defined by it's 3 coordinates */
typedef std::vector<int> Triangle; /**< Represents a triangle, a list of 3 distinct vertices */
typedef std::pair<float,float> Parameters; /**< Represents a couple of parameters of a paramtric equation*/
typedef std::pair<int,int> Range; /**< represents a range of integers */
typedef std::pair<int,int> Edge; /**< represents an edge, by it's starting and ending vertices indices */

typedef enum{CLOCKWISE, COUNTER_CLOCKWISE} Orientation; /**< Represents the orientation of a polygon or an angle */
}

#endif // MY_TYPES_H
