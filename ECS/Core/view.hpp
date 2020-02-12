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
    View(unsigned int matchingEntitesIndex, Entity *matchingEntites, VarType *... matchingComponets)
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
             apply(Func, m_matchingEntitesIndex, m_matchingComponents, std::index_sequence_for<VarType...>{});
        }
    }

private:
    /** 解除tuple的封装 作为方法的参数 
     * 获取Entity的值
     */
    template <typename Func, typename Tuple, std::size_t... T>
    void apply(Func &&callBack, Entity entity, const Tuple &componetSet, std::index_sequence<T...>)
    {
        callBack(entity, std::get<T>(componetSet)[entity]...);
    }

private:
    Entity* m_matchingEntites;
    unsigned int m_matchingEntitesIndex ; 
    std::tuple<VarType *...> m_matchingComponents;
};
} // namespace S_ECS