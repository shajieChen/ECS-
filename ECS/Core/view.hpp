#pragma once
#include "../ConfigFile/S_ECS_Config.hpp"
namespace S_ECS
{   
class View
{
public:
    View(){};
    ~View(){};
    //测试Lambda方法
    template <typename T>
    void each(T &&exp)
    {
        for (unsigned int i = 0; i < 3; i++)
        {
            exp();
        }
    }

private:
};
} // namespace S_ECS