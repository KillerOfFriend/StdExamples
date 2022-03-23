#ifndef CONCEPTS_HPP
#define CONCEPTS_HPP

#include <iterator>
#include <type_traits>

//-----------------------------------------------------------------------------
template<typename Type>
concept std_pair = requires ()
{
    typename Type::first_type;
    typename Type::second_type;
};
//-----------------------------------------------------------------------------
template<typename Type>
concept iterable = requires(Type a, const Type b)
{
    typename Type::iterator;        // Имеет тип "итератор"
    typename Type::const_iterator;  // Имеет тип "константный итератор"

    { a.begin() }   ->  std::convertible_to<typename Type::iterator>;
    { a.end() }     ->  std::convertible_to<typename Type::iterator>;
    { b.begin() }   ->  std::convertible_to<typename Type::const_iterator>;
    { b.end() }     ->  std::convertible_to<typename Type::const_iterator>;
    { a.cbegin() }  ->  std::convertible_to<typename Type::const_iterator>;
    { a.cend() }    ->  std::convertible_to<typename Type::const_iterator>;
};
//-----------------------------------------------------------------------------
template<typename Container>
concept associative_container = requires ()
{
    typename Container::key_type; // Имеет тип "ключа"

    requires std::regular<Container>; // Можно конструировать по умолчанию, копировать и сравнивать
    requires std::swappable<Container>; // Можно поменять местами lvalue выражения
    requires std::destructible<typename Container::value_type>; // Можно безопасно уничтожить

    requires iterable<Container>; // Итерируемый тип
};
//-----------------------------------------------------------------------------
template<typename Container>
concept associative_unordered_container = requires ()
{
    typename Container::hasher;                 // Имеет хеш

    requires associative_container<Container>; // Является асоциативным
};
//-----------------------------------------------------------------------------
template <class Container>
concept sequence_container = requires()
{
    typename Container::value_type;
    typename Container::size_type;
    typename Container::difference_type;
    typename Container::reference;
    typename Container::const_reference;
    typename Container::pointer;
    typename Container::const_pointer;

    requires std::regular<Container>; // Можно конструировать по умолчанию, копировать и сравнивать
    requires std::swappable<Container>; // Можно поменять местами lvalue выражения
    requires std::destructible<typename Container::value_type>; // Можно безопасно уничтожить

    requires iterable<Container>; // Итерируемый тип
    requires !associative_container<Container>; // Не является асоциативным
    requires !associative_unordered_container<Container>; // Не аявляется ассоциативным не упорядоченным
};
//-----------------------------------------------------------------------------
template <class Container>
concept any_container = requires ()
{   // Является последовательным или асоциативным или ассоциотивным не упорядоченным контейнером
    requires sequence_container<Container> ||
        associative_container<Container> ||
        associative_unordered_container<Container>;
};
//-----------------------------------------------------------------------------

#endif // CONCEPTS_HPP
