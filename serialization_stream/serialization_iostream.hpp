#ifndef SERIALIZATION_IOSTREAM_HPP
#define SERIALIZATION_IOSTREAM_HPP

#include <iosfwd>

namespace serialization
{
//-----------------------------------------------------------------------------
///
/// \brief The serialization_basic_iostream class - Базовый сериализационный поток
/// \tparam CharType - Единица данных
/// \tparam Traits - Свойства единицы данных
///
template<typename CharType, typename Traits = std::char_traits<CharType>>
class serialization_basic_iostream : public std::basic_iostream<CharType, Traits>
{
public:
    //
    typedef CharType                            char_type;
    typedef Traits                              traits_type;
    typedef typename traits_type::int_type 		int_type;
    typedef typename traits_type::pos_type 		pos_type;
    typedef typename traits_type::off_type 		off_type;

    /// This is a non-standard type.
    typedef std::basic_streambuf<char_type, traits_type>            __streambuf_type;
    typedef serialization_basic_iostream<char_type, traits_type>    __ostream_type;
    typedef serialization_basic_iostream<char_type, traits_type>    __istream_type;

    ///
    /// \brief serialization_basic_iostream - Инициализирующий поток
    /// \param inBuff - Буфер данных потока
    ///
    explicit serialization_basic_iostream(__streambuf_type* inBuff)
    : std::basic_iostream<CharType, Traits>(inBuff) { }

    ///
    /// \brief ~serialization_basic_iostream - Деструктор по умолчанию
    ///
    ~serialization_basic_iostream() override = default;

};
//-----------------------------------------------------------------------------
typedef serialization_basic_iostream<char> serial_iostream;
//-----------------------------------------------------------------------------
} // namespace serialization


#endif // SERIALIZATION_IOSTREAM_HPP
