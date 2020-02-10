#pragma once
#include <array>
#include <vector>
#include <__hash_table>
#include <iostream>
#include <string>
#include <map>
#include <unordered_map>
#include <typeinfo>

#ifndef MAX_ENTIES_COUNT
#define MAX_ENTIES_COUNT 24
#endif
namespace ECS
{
using Entity = uint32_t;
using Version = uint32_t; //用于检查

class ISystem
{
public:
    ISystem(){};
    virtual ~ISystem(){};
};
/** 处理监听事件 
 * 遍历所有的Sys
*/
template <class T>
class CSystemHandler : public ISystem
{
public:
    CSystemHandler(T component)
    {
        components.at(0) = component;
    };
    virtual ~CSystemHandler(){};
    std::array<T, MAX_ENTIES_COUNT> GetComponets()
    {
        return components;
    }

private:
    std::array<T, MAX_ENTIES_COUNT> components;
};

/** 用于管理 Entity 和Component的
 * 实现装配 监听等功能
*/
class Register
{
public:
    Register() : m_EntityCount(0){};
    ~Register()
    {
        //释放Sys内存避免内存泄漏
        for (auto const &handler : m_SysHandlers)
        {
            delete handler;
        }
    };

    /*增删查检Entity */
    //创建Entity
    Entity Create()
    {
        return ++m_EntityCount;
    }
    //判断当前Entity是否合法
    bool Valid(Entity target)
    {
        return false;
    }
    //删除
    void Destroy(Entity target)
    {
    }
    //获取当前Entity版本
    Version Current(Entity target)
    {
        return 0;
    }
    /*对Entity & Components 进行分配使用*/
    template <typename T>
    void View()
    {
        //TODO: 获取与T类型相关的Component
    }
    /*监听Component 方法/成员方法*/

    /*其他特殊方法： 清空所有的Entity/ 或者已经知道的Component */
    /** 添加对象Component到列表中
     * 如果没有找到 则添加到新的队列里面 
     * 如果找到的情况下， 依据类型名获取特定行 然后依据EntityID 获取特定数据 (看博客教程)
     */
    template <typename T>
    void assign(Entity in_intEntityId, T in_TData)
    {
        const std::type_info &type = typeid(T);

        if (m_SysHandlerIndices.find(type.name()) != m_SysHandlerIndices.end())
        {
            unsigned int sysHandlerIndex = m_SysHandlerIndices[type.name()];
            CSystemHandler<T> *SysHandlers = reinterpret_cast<CSystemHandler<T> *>(m_SysHandlers.at(sysHandlerIndex)); //Get Corresponding Handlers
            SysHandlers->GetComponets().at(in_intEntityId) = in_TData;                                                 //Set Correspoonding Location Data
        }
        else
        {
            CSystemHandler<T> *sysHandler = new CSystemHandler<T>(in_TData);
            m_SysHandlers.push_back(sysHandler);
            m_SysHandlerIndices[type.name()] = static_cast<unsigned int>(m_SysHandlers.size() - 1); //
        }
    }
    /*获取制定Component 和Entity 上的Component */
    template <typename T>
    T get(Entity in_intEntityId)
    {
        const std::type_info &type = typeid(T);
        if (m_SysHandlerIndices.find(type.name()) != m_SysHandlerIndices.end())
        {
            unsigned int sysHandlerIndex = m_SysHandlerIndices[type.name()] ; 
            return reinterpret_cast<CSystemHandler<T> *>(m_SysHandlers.at(sysHandlerIndex))->GetComponets().at(in_intEntityId);
        }
        std::throw_with_nested(in_intEntityId);
    }

private:
    uint32_t m_EntityCount;
    std::vector<ISystem *> m_SysHandlers;
    std::vector<Entity> m_deletedEntites;
    std::unordered_map<std::string, unsigned int> m_SysHandlerIndices;
};
} // namespace ECS