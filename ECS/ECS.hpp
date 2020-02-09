#pragma once
#include <array>
#include <vector>
namespace ECS
{
using Entity = uint32_t;  
using Version = uint32_t;  //用于检查


class ISystem
{
public:
    ISystem() {}  ;
};
/** 处理监听事件 
 * 遍历所有的Sys
*/
template <class T>
class CSystemHandler : public ISystem
{
public:
    CSystemHandler() {} ;
private:
    std::array<T, 24> components ; 
};



/** 用于管理 Entity 和Component的
 * 实现装配 监听等功能
*/
class Register
{
public:
    Register(){};
    ~Register(){
        //释放Sys内存避免内存泄漏 
        for(auto handler : m_ComponentsHandlers)
        {
            delete handler ; 
        }
    };

    /*增删查检Entity */
    //创建Entity
    Entity Create() 
    {
        return 0 ; 
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
    template<typename T> 
    void View() 
    {
        //TODO: 获取与T类型相关的Component
    }
    /*监听Component 方法/成员方法*/

    /*其他特殊方法： 清空所有的Entity/ 或者已经知道的Component */
    template<typename T> 
    void assign(Entity id) 
    {
        auto test = new CSystemHandler<T>();  
        m_ComponentsHandlers.push_back(test);  
    }
private:
    uint32_t m_intEntityCount;
    std::vector<ISystem*> m_ComponentsHandlers ;
};
} // namespace ECS