#pragma once
#include "../ConfigFile/S_ECS_Config.hpp"
#include "../Core/System.hpp"
#include <tuple>
#include <utility>
namespace S_ECS
{
/*View 作为与多个Entiteis相关联的Componennts集合 */
template <typename... VarType>
class View
{
public:
    View(Entity matchingEntitesIndex, Entity *matchingEntites, CSystemHandler<VarType> *... matchingComponets)
        : m_matchingEntites(matchingEntites),m_matchingEntitesIndex(matchingEntitesIndex) ,m_matchingComponents(matchingComponets...)
    {
    }

    ~View(){};
    //测试Lambda方法
    template <typename T>
    void each(T &&Func)
    { 
        for(size_t i = 0 ; i < m_matchingEntitesIndex ; i++)
        { 
             apply(Func, m_matchingEntites[i], m_matchingComponents, std::index_sequence_for<VarType...>{});
        }
    }

private:
    /** 调用上层回调函数 
     * 
     */
    template <typename Func, typename Tuple, std::size_t... T>
    void apply(Func &&callBack,const Entity entity, const Tuple &componetSet, std::index_sequence<T...>)
    {
        callBack(entity, std::get<T>(componetSet)->at(entity)...) ;
    }

private:
    Entity* m_matchingEntites;
    unsigned int m_matchingEntitesIndex ; 
    std::tuple<CSystemHandler<VarType >*...> m_matchingComponents;
};
} // namespace S_ECS