#ifndef SERIALIZATION_TOOLS_H
#define SERIALIZATION_TOOLS_H

#include <type_traits>
#include <iterator>

//-----------------------------------------------------------------------------

///
/// \brief The is_specialization struct - Шаблон, оправергающий, что T является специализацийей шаблона Template
/// \tparam T - Проверяемый (спцифицированный) тип
/// \tparam Template - Исходный (специфицируемый) шаблон
///
/// Содержит false для всех не специфицированных типов
///
template <class T, template <class...> class Template>
struct is_specialization : std::false_type {};

///
/// \brief The is_specialization struct - Шаблон, подтверждающий, что T является специализацийей шаблона Template
/// \tparam T - Проверяемый (спцифицированный) тип
/// \tparam Template - Исходный (специфицируемый) шаблон
///
/// Содержит true для всех специфицированных типов
///
template <template <class...> class Template, class... Args>
struct is_specialization<Template<Args...>, Template> : std::true_type {};

///
/// \brief The is_specialization_v struct - Упрощение доступа к значению специализации шаблона
/// \tparam T - Проверяемый (спцифицированный) тип
/// \tparam Template - Исходный (специфицируемый) шаблон
///
template <typename T, template <typename...> typename Template>
inline constexpr bool is_specialization_v = is_specialization<T, Template>::value;

//-----------------------------------------------------------------------------

///
/// \brief The non_const_container_val - Шаблон, возвращающий не константный тип хранящийся в контейнере
/// Реализация для всех контейнеров, кроме ассоциативных с отдельно хранящимся ключём
/// \tparam Container - Тип контенера
/// \tparam Enable - Условие активации данной специализации (дефолтная)
///
template<class Container, class Enable = void>
struct non_const_container_val
{ using type = Container::value_type; };

///
/// \brief The non_const_container_val - Шаблон, возвращающий не константный тип хранящийся в контейнере
/// Реализация для ассоциативных контейнеров с отдельно хранящимся ключём
/// \tparam Container - Тип контенера
/// \tparam Enable - Условие активации данной специализации
///
template<class Container>
struct non_const_container_val<Container, typename std::enable_if<is_specialization<typename Container::value_type, std::pair>::value >::type>
{ using type = typename std::pair<typename Container::key_type, typename Container::mapped_type>; };

///
/// \brief The non_const_container_val_t - Шаблон, возвращающий не константный тип хранящийся в контейнере
/// \tparam Container - Тип контенера
/// \tparam Enable - Условие активации специализацииа
///
template <typename Container, typename Enable = void>
using non_const_container_val_t = typename non_const_container_val<Container, Enable>::type;

//-----------------------------------------------------------------------------



#endif // SERIALIZATION_TOOLS_H
