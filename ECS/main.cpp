#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file

#include "S_ECS.hpp"

struct Object
{
    glm::vec3 Position;
    glm::vec4 Color;
};
#pragma region 检测System处理问题
SCENARIO("处理大量的Component 和Entity 问题", "[System]")
{
}
#pragma endregion

#pragma region 检测Registry对Entity和Component的处理能力
SCENARIO("Registry管理ENtity 和Component的问题", "[Registry]")
{
    GIVEN("一个空的Registry对象 ")
    {
        S_ECS::Register registry;
        WHEN("请求Registry创建新的Entity")
        {
            S_ECS::Entity entity1 = registry.Create();
            S_ECS::Entity entity2 = registry.Create();
            S_ECS::Entity entity3 = registry.Create();
            THEN("判断三者都不为空ID 并且互相不想等")
            {
                REQUIRE(entity1 != entity2);
                REQUIRE(entity1 != S_ECS::null_Entity);
                REQUIRE(entity2 != entity3);
                REQUIRE(entity2 != S_ECS::null_Entity);
                REQUIRE(entity3 != entity1);
                REQUIRE(entity3 != S_ECS::null_Entity);
            }
        }
        WHEN("对Entites指定Component")
        {
            S_ECS::Entity entity = registry.Create();
            const Object obj{
                glm::vec3(1.0f, 1.0f, 1.0f),
                glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)};   
            registry.assign<Object>(entity, obj);
            THEN("判断Regisry 内部的Handler 数量 ")
            {
                const Object &objGetResult = registry.get<Object>(entity);
                std::cout << objGetResult.Color.x << std::endl;
                REQUIRE(objGetResult.Color.x == 1.0f);
                REQUIRE(objGetResult.Position.x == 1.0f);
            }
            THEN("修改Entity结果")
            {
                Object &objResult = registry.get<Object>(entity);
                objResult.Position.x = 2.0f;

                const Object objTestResult = registry.get<Object>(entity);
                REQUIRE(objResult.Position.x == objTestResult.Position.x);
            }
        }
    }
}
#pragma endregion

#pragma region 普通检测
#define TestEntity 0
TEST_CASE("测试基本方法", "[BasicFunc]")
{
    S_ECS::Register registry;
    // System<Object> obj_Sys;
    Object obj;
    obj.Position = glm::vec3(0.0f, 0.0f, 0.0f);
    obj.Color = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
    auto Entity = registry.Create();
    registry.assign<Object>(Entity, obj);
    auto &testResult = registry.get<Object>(Entity);

    obj.Position = glm::vec3(1.0f, 1.0f, 1.0f);
    obj.Color = glm::vec4(0.0f, 1.0f, 1.0f, 1.0f);
    auto Entity2 = registry.Create();
    registry.assign<Object>(Entity2, obj);
    auto &testResult2 = registry.get<Object>(Entity2);

    REQUIRE(Entity2 != S_ECS::null_Entity);
    REQUIRE(Entity != S_ECS::null_Entity);
    REQUIRE(typeid(testResult2) == typeid(Object));
    REQUIRE(typeid(testResult) == typeid(Object));
    REQUIRE(true);
}
#pragma endregion