#pragma once
#include "../Core/System.hpp"
#include "../ConfigFile/S_ECS_Config.hpp"
#include "../Core/View.hpp"
namespace S_ECS
{

/** 用于管理 Entity 和Component的
 * 实现装配 监听等功能
*/
class Register
{
public:
    Register() : m_EntityCount(0)
    {
        m_SysHandlers.reserve(MIN_COMPONET_TYPES);
    };
    ~Register()
    {
        //释放Sys内存避免内存泄漏
        for (auto const &handler : m_SysHandlers)
        {
            delete handler;
        }
    };

        /*增删查检Entity */
#pragma region 增删查检Entity
    //创建Entity
    Entity Create()
    {
        return ++m_EntityCount;
    }
    //判断当前Entity是否合法是否存在 
    bool valid(Entity in_Target)
    {
        return false;
    }
    //判断是否当前Entity 有Component
    template<typename T >
    bool has(Entity in_Target)
    {
        return true ; 
    }
    //依据给定的Component类型和Entity 来删除对象
    template <typename T>
    void Remove(Entity in_Target)
    {
    }
    //删除
    void Destroy(Entity in_Target)
    {
    }
    //获取当前Entity版本
    Version current(Entity in_Target)
    {
        return 0;
    }
#pragma endregion

#pragma region 分配Components 与Entity
    /*对Entity & Components 进行分配使用*/
    //通过视图View 依据指定要求的Component ， 获取相关的Entities
    // template <typename... T>
    // View view(Entity in_Target)
    // {
    //     // View view ; 
    //     // return view ; 
    // }
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
        const bool hasSystemHandler = (m_SysHandlerIndices.find(type.name()) != m_SysHandlerIndices.end());
        if (hasSystemHandler)
        {  
            unsigned int sysHandlerIndex = m_SysHandlerIndices[type.name()];
            CSystemHandler<T> *SysHandlers = reinterpret_cast<CSystemHandler<T> *>(m_SysHandlers.at(sysHandlerIndex)); //Get Corresponding Handlers
            SysHandlers->GetComponets().at(in_intEntityId) = in_TData;                                                 //Set Correspoonding Location Data
            SysHandlers->GetHandlerListStatus().at(in_intEntityId) = true;
        }
        else
        {  
            CSystemHandler<T> *sysHandler = new CSystemHandler<T>();
            sysHandler->GetComponets().at(in_intEntityId) = in_TData;
            sysHandler->GetHandlerListStatus().at(in_intEntityId) = true;

            m_SysHandlers.push_back(sysHandler);
            m_SysHandlerIndices[type.name()] = static_cast<unsigned int>(m_SysHandlers.size() - 1); //
        }
    }
    /*获取制定Component 和Entity 上的Component */
    template <typename T>
    T &get(Entity in_intEntityId)
    {
        const std::type_info &type = typeid(T);
        if (m_SysHandlerIndices.find(type.name()) != m_SysHandlerIndices.end())
        {
            unsigned int sysHandlerIndex = m_SysHandlerIndices[type.name()];
            return reinterpret_cast<CSystemHandler<T> *>(m_SysHandlers.at(sysHandlerIndex))->GetComponets().at(in_intEntityId);
        }
        std::throw_with_nested(in_intEntityId);
    }
#pragma endregion

#pragma region 其他方法
    //销毁当前Entity中所有的Components 
    template<typename T>
    void reset()
    {

    }
#pragma endregion

private:
    Entity m_EntityCount;
    std::vector<Entity> m_deletedEntites;
    std::vector<ISystem *> m_SysHandlers;
    std::unordered_map<std::string, unsigned int> m_SysHandlerIndices;
};
} // namespace S_ECS