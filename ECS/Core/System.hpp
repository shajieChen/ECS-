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
        hasHandlerList.fill(false);
    };
    virtual ~ISystem(){};
    inline std::array<bool , MAX_ENTIES_COUNT> GetHandlerListStatus() {return hasHandlerList ;} 
private : 
    std::array<bool , MAX_ENTIES_COUNT> hasHandlerList;  
};
/** 处理监听事件 
 * 遍历所有的Sys
*/
template <class T>
class CSystemHandler : public ISystem
{
public:
    CSystemHandler() {} 
    virtual ~CSystemHandler(){};
    std::array<T, MAX_ENTIES_COUNT> GetComponets()
    {
        return components;
    }

private:
    std::array<T, MAX_ENTIES_COUNT> components;
};

} // namespace S_ECS