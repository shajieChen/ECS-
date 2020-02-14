#pragma once
#include <array>
#include <vector>
#include <__hash_table>
#include <iostream>
#include <string>
#include <map>
#include <unordered_map>
#include <typeinfo>
#include "../ConfigFile/S_ECS_Config.hpp"
namespace S_ECS
{

class ISystem
{
public:
    ISystem(){
        handlerList.fill(0); 
    };
    virtual ~ISystem(){};
    inline std::array<Entity , MAX_ENTIES_COUNT> GetHandlerListStatus() {return handlerList ;} 
private : 
    std::array<Entity , MAX_ENTIES_COUNT> handlerList;  
};
/** 处理监听事件 
 * 遍历所有的Sys
*/
template <class T>
class CSystemHandler : public ISystem
{
public:
    CSystemHandler() {
        components.reserve(10) ; 
    } 
    virtual ~CSystemHandler(){};
    std::vector<T> GetComponets()
    {
        return components;
    }

private:
    std::vector<T> components;
};

} // namespace S_ECS