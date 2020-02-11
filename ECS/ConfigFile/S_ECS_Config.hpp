#pragma once

#ifndef MAX_ENTIES_COUNT
#define MAX_ENTIES_COUNT 24
#endif

#ifndef MIN_COMPONET_TYPES
#define MIN_COMPONET_TYPES 10
#endif
#include "../glm/glm.hpp"
namespace S_ECS
{
using Entity = unsigned int;  //Enity本质上不用对象代表 全部都是数据组成 然后
using Version = unsigned int; //用于检查
const static Entity null_Entity = 0;

struct Object
{
    glm::vec3 Position;
    glm::vec4 Color;
};
struct Scale
{
    glm::vec3 scale;
};
struct Position
{
    float x;
    float y;
    float z;
};
} // namespace S_ECS