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
    ISystem()
    {
        handlerList.fill(0);
    };
    virtual ~ISystem(){};
    inline std::array<Entity, MAX_ENTIES_COUNT> GetHandlerListStatus() { return handlerList; }

protected:
    std::array<Entity, MAX_ENTIES_COUNT> handlerList;
};
/** 处理监听事件 
 * 遍历所有的Sys
*/
template <class T>
class CSystemHandler : public ISystem
{
public:
    CSystemHandler(Entity target, T& component )
    {
        assert(target!= null_Entity && "Entity不能为Null ") ;
        components.reserve(10);
        components.push_back(component);
        components.push_back(component) ; 
        GetHandlerListStatus().at(target) = components.size() - 1;  
    }
    virtual ~CSystemHandler(){};
    std::vector<T> GetComponets()
    {
        return components;
    }
    void insert(Entity target, T& component)
    {
        assert(target != null_Entity && "Enitty不能为Null");
        components.push_back(component);
        GetHandlerListStatus().at(target) = components.size() - 1;  
    }
    T& at(Entity target)
    {
        assert(target != null_Entity && "Entity不能为Null ");
        return components.at(GetHandlerListStatus().at(target)) ; 
    }
    bool has(Entity target) const
    {
        assert(target != null_Entity && "Entity不能为Null");
        if(handlerList.at(target) != 0)
        {
            return true ; 
        }
        else 
        {
            return false ; 
        }
    }

    size_t size() const
    {
        return components.size() - 1; 
    }
private:
    std::vector<T> components;
};

} // namespace S_ECS