#ifndef SEQUENCE_CONTAINER_HELPERS_HPP
#define SEQUENCE_CONTAINER_HELPERS_HPP

#include <vector>
#include <type_traits>

#include "serialization_concepts.hpp"

//-----------------------------------------------------------------------------
template <class Container>
concept has_emplace_front = requires(Container a)
{
    requires any_container<Container>; // Любой контейнер
    a.emplace_front(typename Container::value_type{});
};
//-----------------------------------------------------------------------------
template <class Container>
concept has_emplace_back = requires(Container a)
{
    requires any_container<Container>; // Любой контейнер
    a.emplace_back(typename Container::value_type{});
};
//-----------------------------------------------------------------------------
template <class Container>
concept has_emplace = requires(Container a)
{
    requires any_container<Container>; // Любой контейнер
    a.emplace(typename Container::value_type{});
};
//-----------------------------------------------------------------------------
///
/// \brief The add_helper struct - add_helper - Вспомогательный шаблон, для добавления данных
/// в контенер (на подобии std::array)
///
template<class Container, class Enable = void>
struct add_helper
{
    std::vector<typename Container::value_type> v;
    Container& ref;

    add_helper(Container& inContainer) : ref(inContainer)
    {}
    void add(typename Container::value_type&& inData)
    { v.emplace_back(inData); }
    void flush()
    { copy(v.begin(), v.end(), ref.begin()); }
};
//-----------------------------------------------------------------------------
template<class Container>
struct add_helper<Container, typename std::enable_if<has_emplace_front<Container> && !has_emplace_back<Container> >::type>
{
    Container& ref;

    add_helper(Container& inContainer) : ref(inContainer)
    {};
    void add(typename Container::value_type&& inData)
    { ref.emplace_front(inData); }
    void flush()
    { ref.reverse(); };
};
//-----------------------------------------------------------------------------
template<class Container>
struct add_helper<Container, typename std::enable_if<has_emplace_front<Container> && has_emplace_back<Container> >::type>
{
    Container& ref;

    add_helper(Container& inContainer) : ref(inContainer)
    {};
    void add(typename Container::value_type&& inData)
    { ref.emplace_back(inData); }
    void flush()
    { };
};
//-----------------------------------------------------------------------------
template<class Container>
struct add_helper<Container, typename std::enable_if<!has_emplace_front<Container> && has_emplace_back<Container> >::type>
{
    Container& ref;

    add_helper(Container& inContainer) : ref(inContainer)
    {};
    void add(typename Container::value_type&& inData)
    { ref.emplace_back(inData); }
    void flush()
    { };
};
//-----------------------------------------------------------------------------

#endif // SEQUENCE_CONTAINER_HELPERS_HPP
