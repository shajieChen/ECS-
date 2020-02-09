#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include "Lib/catch2/catch.hpp"
#include "ECS.hpp"
#include "glm/glm.hpp"
 
struct Object
{
    glm::vec3 Position;
    glm::vec4 Color;
};

TEST_CASE("Name of the case", "[tag]")
{
    ECS::Register reg;
    // System<Object> obj_Sys; 
    reg.assign<Object>(0); 

    REQUIRE(true);
}
