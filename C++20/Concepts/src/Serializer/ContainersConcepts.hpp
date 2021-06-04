#ifndef CONTAINERSCONCEPTS_HPP
#define CONTAINERSCONCEPTS_HPP

#include <string>
#include <utility> // std::pair
#include <iterator>
#include <type_traits> // std::is_same_v

#include "ISerializeble.hpp"

//-----------------------------------------------------------------------------
/**
 * @brief The is_specialization struct - Шаблон, оправергающий, что T является специализацийей шаблона Template
 * @tparam T - Проверяемый (спцифицированный) тип
 * @tparam Template - Исходный (специфицируемый) шаблон
 *
 * Содержит false для всех не специфицированных типов
 */
template <class T, template <class...> class Template>
struct is_specialization : std::false_type {};
/**
 * @brief The is_specialization struct - Шаблон, подтверждающий, что T является специализацийей шаблона Template
 * @tparam T - Проверяемый (спцифицированный) тип
 * @tparam Template - Исходный (специфицируемый) шаблон
 *
 * Содержит true для всех специфицированных типов
 */
template <template <class...> class Template, class... Args>
struct is_specialization<Template<Args...>, Template> : std::true_type {};
//-----------------------------------------------------------------------------
/**
 * @brief StdString - Концепт наследника от ISerializeble
 * @tparam T - Сопоставляемый тип
 */
template<typename T>
concept SerializebleHeir = std::is_base_of<T, ISerializeble>::value;
//-----------------------------------------------------------------------------
/**
 * @brief StdString - Концепт стандартной строки (любая спецификация std::basic_string)
 * @tparam StringType - Сопоставляемый тип
 */
template<typename StringType>
concept StdString = is_specialization<StringType, std::basic_string>::value;
//-----------------------------------------------------------------------------
/**
 * @brief StdContainer - Концепт контейнера стандартной библиотеки (Не являющегося строкой)
 * @tparam ContainerType - Сопоставляемый тип
 */
template <class ContainerType>
concept StdContainer = !StdString<ContainerType> && requires(ContainerType a, const ContainerType b)
{
    requires std::regular<ContainerType>;
    requires std::swappable<ContainerType>;
    requires std::destructible<typename ContainerType::value_type>;
    requires std::same_as<typename ContainerType::reference, typename ContainerType::value_type &>;
    requires std::same_as<typename ContainerType::const_reference, const typename ContainerType::value_type &>;
    requires std::forward_iterator<typename ContainerType::iterator>;
    requires std::forward_iterator<typename ContainerType::const_iterator>;
    requires std::signed_integral<typename ContainerType::difference_type>;
    requires std::same_as<typename ContainerType::difference_type, typename std::iterator_traits<typename ContainerType::iterator>::difference_type>;
    requires std::same_as<typename ContainerType::difference_type, typename std::iterator_traits<typename ContainerType::const_iterator>::difference_type>;
    { a.begin() } -> std::convertible_to<typename ContainerType::iterator>;
    { a.end() } -> std::convertible_to<typename ContainerType::iterator>;
    { b.begin() } -> std::convertible_to<typename ContainerType::const_iterator>;
    { b.end() } -> std::convertible_to<typename ContainerType::const_iterator>;
    { a.cbegin() } -> std::convertible_to<typename ContainerType::const_iterator>;
    { a.cend() } -> std::convertible_to<typename ContainerType::const_iterator>;
    { a.size() } -> std::convertible_to<typename ContainerType::size_type>;
    { a.max_size() } -> std::convertible_to<typename ContainerType::size_type>;
    { a.empty() } -> std::convertible_to<bool>;
};
//-----------------------------------------------------------------------------
/**
 * @brief SequenceStdContainer - Концепт последовательного контейнера (std::vector, std::list, ...)
 * @tparam ContainerType - Сопоставляемый тип
 */
template<typename ContainerType>
concept SequenceStdContainer = StdContainer<ContainerType> &&
    requires (ContainerType a, typename ContainerType::size_type count)
{
    { a.resize(count) } -> std::convertible_to<void>;
};
//-----------------------------------------------------------------------------
/**
 * @brief AssociativeStdContainer - Концепт ассоциотивного контейнера (std::map, std::set, std::unordered_map, ...)
 * @tparam ContainerType - Сопоставляемый тип
 */
template<typename ContainerType>
concept AssociativeStdContainer = StdContainer<ContainerType> && requires (ContainerType a)
{
    typename ContainerType::key_type;
};
//-----------------------------------------------------------------------------
/**
 * @brief StdString - Концепт стандартной пары
 * @tparam PairType - Сопоставляемый тип
 */
template<typename PairType>
concept StdPair = is_specialization<PairType, std::pair>::value;
//-----------------------------------------------------------------------------

#endif // CONTAINERSCONCEPTS_HPP
