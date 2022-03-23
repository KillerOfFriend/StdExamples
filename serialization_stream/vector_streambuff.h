#ifndef VECTOR_STREAMBUFF_H
#define VECTOR_STREAMBUFF_H

#include <iosfwd>
#include <vector>
#include <cstring>
#include <cassert>

#ifdef _MSC_VER
// Disable the warning about inheriting from std::iostream 'via dominance' since this warning is a warning about
// visual studio conforming to the standard and is ignorable.  See http://connect.microsoft.com/VisualStudio/feedback/details/733720/inheriting-from-std-fstream-produces-c4250-warning
// for further details if interested.
#pragma warning(disable : 4250)
#endif // _MSC_VER

namespace serialization
{
//-----------------------------------------------------------------------------
///
/// \brief The vector_streambuf class
/// \tparam CharType - Единица данных
///
template<typename CharType>
class vector_streambuf : public std::basic_streambuf<CharType>
{
    typedef typename std::basic_streambuf<CharType>::pos_type 		pos_type;
    typedef typename std::basic_streambuf<CharType>::off_type 		off_type;
    typedef typename std::basic_streambuf<CharType>::int_type 		int_type;
    typedef typename std::vector<CharType>::size_type               size_type;

private:

    size_type m_read_pos = 0;           ///< Текущая позиция чтения
    std::vector<CharType>& m_buffer;    ///< Ссылка на буфер

public:

    ///
    /// \brief vector_streambuf - Инициализирующий конструктор
    /// \param inBuff - Используемый буфер
    ///
    vector_streambuf(std::vector<CharType>& inBuff);

    ///
    /// \brief ~vector_streambuf - Дефолтный деструктор
    ///
    ~vector_streambuf() override = default;

    ///
    /// \brief seekg - Метод установитт позициб чтения
    /// \param pos - Новая позиция чтения
    ///
    void seekg(size_type pos);

protected:

    ///
    /// \brief seekpos - Метод установит абсолютную позицию потока
    /// \param pos - Новая позиция
    /// \param mode - Тип позиции (входня\выходная)
    /// \return Вернёт абсолютную позицию
    ///
    pos_type seekpos(pos_type pos, std::ios_base::openmode mode = std::ios_base::in | std::ios_base::out) override;

    ///
    /// \brief seekoff - Метод установит относительную позицию потока
    /// \param off - Значение смещения
    /// \param dir - Тип смещения (от начала\отконца\от текущей позиции)
    /// \param mode - Тип позиции (входня\выходная)
    /// \return Вернёт опзицию
    ///
    pos_type seekoff(off_type off, std::ios_base::seekdir dir,
                     std::ios_base::openmode mode = std::ios_base::in | std::ios_base::out) override;

    ///
    /// \brief overflow - Метод гарантирует наличие места в области размещения по крайней мере для одного символа
    /// \param c - Символ
    /// \return Признак успешности операции
    ///
    int_type overflow(int_type c) override;

    ///
    /// \brief xsputn - Метод запишет последовательность данных, начиная с указанной позиции
    /// \param s - Последовательность данных
    /// \param num - Начальная позиция записи
    /// \return Вернёт количество успешно записанных символов
    ///
    std::streamsize xsputn(const CharType* s, std::streamsize num) override;

    ///
    /// \brief underflow - Метод извлечёт текущий элемент из потока (не изменит текущую позицию)
    /// \return Вернёт текущий элемент или EOF
    ///
    int_type underflow() override;

    ///
    /// \brief uflow - Метод извлечёт текущий элемент из потока (сместит текущую позицию на 1 элемент)
    /// \return Вернёт текущий элемент или EOF
    ///
    int_type uflow() override;

    ///
    /// \brief pbackfail - Метод запишет элемент в поток (установит на него текущую позицию)
    /// \param c - Записываемый элемент
    /// \return При ошибке вернёт EOF, в противном случаи что то ещё
    ///
    int_type pbackfail(int_type c) override;

    ///
    /// \brief xsgetn - Метод извлечёт элементы из потока
    /// \param s - Принимающий буфер
    /// \param n - Количество считываемых элементов
    /// \return Вернёт количество считанных элементов
    ///
    std::streamsize xsgetn(CharType* s, std::streamsize n);

};
//-----------------------------------------------------------------------------
template<typename CharType>
vector_streambuf<CharType>::vector_streambuf(std::vector<CharType>& inBuff) :
    m_read_pos(0),
    m_buffer(inBuff)
{}
//-----------------------------------------------------------------------------
template<typename CharType>
void vector_streambuf<CharType>::seekg(size_type pos)
{
    m_read_pos = pos;
}
//-----------------------------------------------------------------------------
template<typename CharType>
vector_streambuf<CharType>::pos_type vector_streambuf<CharType>::seekpos(pos_type pos, std::ios_base::openmode mode)
{
    return seekoff(pos - pos_type(off_type(0)), std::ios_base::beg, mode);
}
//-----------------------------------------------------------------------------
template<typename CharType>
vector_streambuf<CharType>::pos_type vector_streambuf<CharType>::seekoff(off_type off, std::ios_base::seekdir dir, std::ios_base::openmode mode)
{
    assert(mode == std::ios_base::in && "vectorstream does not support std::ios_base::out");

    switch (dir)
    {
    case std::ios_base::beg:
        m_read_pos = off;
        break;
    case std::ios_base::cur:
        m_read_pos += off;
        break;
    case std::ios_base::end:
        m_read_pos = m_buffer.size() + off;
        break;
    default:
        break;
    }

    return pos_type(m_read_pos);
}
//-----------------------------------------------------------------------------
template<typename CharType>
vector_streambuf<CharType>::int_type vector_streambuf<CharType>::overflow ( int_type c)
{
    if (c != std::char_traits<CharType>::eof()) m_buffer.push_back(static_cast<char>(c));
    return c;
}
//-----------------------------------------------------------------------------
template<typename CharType>
std::streamsize vector_streambuf<CharType>::xsputn (const CharType* s, std::streamsize num)
{
    m_buffer.insert(m_buffer.end(), s, s+num);
    return num;
}
//-----------------------------------------------------------------------------
template<typename CharType>
vector_streambuf<CharType>::int_type vector_streambuf<CharType>::underflow()
{
    if (m_read_pos < m_buffer.size())
        return static_cast<unsigned char>(m_buffer[m_read_pos]);
    else
        return std::char_traits<CharType>::eof();
}
//-----------------------------------------------------------------------------
template<typename CharType>
vector_streambuf<CharType>::int_type vector_streambuf<CharType>::uflow()
{
    if (m_read_pos < m_buffer.size())
        return static_cast<unsigned char>(m_buffer[m_read_pos++]);
    else
        return std::char_traits<CharType>::eof();
}
//-----------------------------------------------------------------------------
template<typename CharType>
vector_streambuf<CharType>::int_type vector_streambuf<CharType>::pbackfail(int_type c)
{
    // if they are trying to push back a character that they didn't read last
    // that is an error
    const auto prev = m_read_pos - 1;

    if (c != std::char_traits<CharType>::eof() && prev < m_buffer.size() &&
            c != static_cast<unsigned char>(m_buffer[prev]))
    {
        return std::char_traits<CharType>::eof();
    }

    m_read_pos = prev;
    return 1;
}
//-----------------------------------------------------------------------------
template<typename CharType>
std::streamsize vector_streambuf<CharType>::xsgetn (CharType* s, std::streamsize n)
{
    if (m_read_pos < m_buffer.size())
    {
        const size_type num = std::min<size_type>(n, m_buffer.size() - m_read_pos);
        std::memcpy(s, &m_buffer[m_read_pos], num);
        m_read_pos += num;
        return num;
    }
    return 0;
}
//-----------------------------------------------------------------------------
} // namespace serialization


#endif // VECTOR_STREAMBUFF_H
