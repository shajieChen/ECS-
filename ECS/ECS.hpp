#pragma once
#include <array>
#include <vector>

namespace ECS
{

#define MAX_ENTIES_COUNT 24
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
    template <typename T>
    void assign(Entity id, T data)
    {
        CSystemHandler<T> *test = new CSystemHandler<T>(data);
        m_SysHandlers.push_back(test);
    }
    /*获取制定Component 和Entity 上的Component */
    template <typename T>
    T get(Entity id)
    {
        return reinterpret_cast<CSystemHandler<T> *>(m_SysHandlers.at(0))->GetComponets().at(id);
    }

private:
    uint32_t m_EntityCount;
    std::vector<ISystem *> m_SysHandlers;
};
} // namespace ECS