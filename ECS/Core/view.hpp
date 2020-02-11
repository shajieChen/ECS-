#pragma once
#include "../ConfigFile/S_ECS_Config.hpp"
#include "../Core/System.hpp"
namespace S_ECS
{
/*View 作为与多个Entiteis相关联的Componennts集合 */
template<typename... VarType>
class View
{
public:
    View(const VarType&... varType ) : m_matchingComponents(varType...){}
    ~View(){};
    //测试Lambda方法
    template <typename T>
    void each(T &&Func)
    {
        Func() ;
    }

private:
    std::tuple<VarType...> m_matchingComponents ; 
};
} // namespace S_ECS