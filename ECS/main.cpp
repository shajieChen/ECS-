#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
// #include "Lib/catch2/catch.hpp" 
#include "Lib/catch2/catch.hpp"
#include "glm/glm.hpp"
#include "Core/System.hpp"
#include "Core/Registry.hpp"

struct Object
{
    glm::vec3 Position;
    glm::vec3 Color;
};
#define TestEntity 0
TEST_CASE("测试基本方法", "[Func1]")
{
    S_ECS::Register registry;
    // System<Object> obj_Sys;
    Object obj;
    obj.Position = glm::vec3(0.0f, 0.0f, 0.0f);
    obj.Color = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
    auto Entity = registry.Create();
    registry.assign<Object>(Entity, obj);
    auto testResult = registry.get<Object>(Entity);


    obj.Position = glm::vec3(1.0f, 1.0f, 1.0f);
    obj.Color = glm::vec4(0.0f, 1.0f , 1.0f, 1.0f) ; 
    auto Entity2 = registry.Create();
    registry.assign<Object>(Entity2, obj); 
    auto testResult2 = registry.get<Object>(Entity2);
    REQUIRE(typeid(testResult2) == typeid(Object)) ; 
    REQUIRE(typeid(testResult) == typeid(Object));
    REQUIRE(true);
}
