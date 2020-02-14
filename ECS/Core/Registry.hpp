#pragma once
#include "../Core/System.hpp"
#include "../ConfigFile/S_ECS_Config.hpp"
#include "../Core/View.hpp"
namespace S_ECS
{
int testMatchCount = 2;
//set the Entity
std::array<Entity, MAX_ENTIES_COUNT> m_testMatchingEntites = {};
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
        for (ISystem* handler : m_SysHandlers)
        {
            delete handler;
        }
    };

        /*增删查检Entity */
#pragma region 增删查检Entity
    //创建Entity
    Entity Create()
    {
        assert(testMatchCount < MAX_ENTIES_COUNT && "判断是否到达一个Entity能够创建的Components 数量");
        return ++m_EntityCount;
    }
    //判断当前Entity是否合法是否存在
    bool valid(Entity in_Target)
    {
        return false;
    }
    //判断是否当前Entity 有Component
    template <typename T>
    bool has(Entity in_Target)
    {
        const CSystemHandler<T>* collection = GetComponentsSet<T>() ; 
        return collection->has(in_Target) ; 
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
    // 通过多组件视图
    template <typename VarType, typename... VarTypes>
    View<VarType, VarTypes...> view()
    {
        FillMatchingEntities<VarType>();
        (RemoveUnmatchEntites<VarTypes>(), ...);
        View<VarType, VarTypes...> testView(testMatchCount, m_testMatchingEntites.data(), GetComponentsSet<VarType>(), GetComponentsSet<VarTypes>()...);
        return testView;
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
        const bool hasSystemHandler = (m_SysHandlerIndices.find(type.name()) != m_SysHandlerIndices.end());
        if (hasSystemHandler)
        {
            unsigned int sysHandlerIndex = m_SysHandlerIndices[type.name()];
            CSystemHandler<T> *SysHandlers = static_cast<CSystemHandler<T> *>(m_SysHandlers.at(sysHandlerIndex)); //Get Corresponding Handlers
            // SysHandlers->GetComponets().at(in_intEntityId) = in_TData;                                            //Set Correspoonding Location Data
            SysHandlers->insert(in_intEntityId, in_TData);
        }
        else
        {
            CSystemHandler<T>* collection = new CSystemHandler<T>(in_intEntityId , in_TData);

            m_SysHandlers.push_back(collection);
            m_SysHandlerIndices[type.name()] = static_cast<unsigned int>(m_SysHandlers.size() - 1); //
        }
    }
    /*获取制定Component 和Entity 上的Component */
    template <typename T>
    T &get(const Entity in_intEntityId)
    {
        CSystemHandler<T>* collection = GetComponentsSet<T>() ; 
        return collection->at(in_intEntityId);
    }
#pragma endregion

#pragma region 其他方法
    //销毁当前Entity中所有的Components
    void reset()
    {
    }
#pragma endregion

#pragma region Private Helper Method
private:
    //test
    template <typename VarType>
    void FillMatchingEntities()
    {
        CSystemHandler<VarType> *componentsSet = GetComponentsSet<VarType>();
        testMatchCount = 0;
        for (Entity i = 1; i < componentsSet->GetComponets().size(); ++i)
        {
            if (componentsSet->has(i))
            {
                m_testMatchingEntites.at(testMatchCount) = i;
                testMatchCount++;
            }
        }
    }
    //test
    template <typename VarType>
    void RemoveUnmatchEntites()
    {
        CSystemHandler<VarType> *componentsSet = GetComponentsSet<VarType>();
        for (size_t i = 0; i < testMatchCount; ++i)
        {
            const Entity entity = m_testMatchingEntites.at(i);

            if (!componentsSet->has(i) )
            {
                m_testMatchingEntites.at(i) = m_testMatchingEntites.at(i + 1);
                testMatchCount--;
                i--;
            }
        }
    } 
    template <typename T>
    unsigned int GetSystemIndex()
    {
        const std::type_info &type = typeid(T);
        const bool hasSystemHandler = (m_SysHandlerIndices.find(type.name()) != m_SysHandlerIndices.end());
        if (hasSystemHandler)
        {
            return m_SysHandlerIndices[type.name()];
        }

        assert(false && "doesn't exit");
        return null_Entity ; 
    }
    template <typename VarType>
    CSystemHandler<VarType> *GetComponentsSet()
    {
        return static_cast<CSystemHandler<VarType> *>(m_SysHandlers.at(GetSystemIndex<VarType>()));
    }
#pragma endregion

private:
    Entity m_EntityCount;
    std::vector<Entity> m_deletedEntites;
    std::vector<ISystem *> m_SysHandlers;
    std::unordered_map<std::string, unsigned int> m_SysHandlerIndices;
};
} // namespace S_ECS