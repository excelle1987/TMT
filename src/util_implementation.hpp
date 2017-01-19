#ifndef UTIL_IMPLEMENTATION_H
#define UTIL_IMPLEMENTATION_H

#include <vector>
#include <string>
#include <type_traits>
#include <iterator>

template<class Type, class Translator>
std::vector<Type> split_aux(const std::string& s,char delim, Translator, std::true_type)
{
    std::vector<Type> result;
    size_t start = 0, find;
    while((find = s.find(delim, start)) != std::string::npos)
    {
        result.push_back(s.substr(start, find - start));
        start = find + 1;
    }
    result.push_back(s.substr(start));
    return result;
}

template<class Type, class Translator>
std::vector<Type> split_aux(const std::string& s, char delim, Translator tr, std::false_type)
{
    std::vector<Type> result;
    size_t start = 0, find = 0;
    while((find = s.find(delim, start)) != std::string::npos)
    {
        result.push_back(tr(s.substr(start, find - start)));
        start = find + 1;
    }
    result.push_back(tr(s.substr(start)));
    return result;
}

template<class Type, class Translator>
std::vector<Type> split(const std::string& s, char delim, Translator tr /*= nullptr*/)
{
    typedef typename std::is_same<Translator, std::nullptr_t>::type is_nullptr_t;
    return std::forward<std::vector<Type>>(split_aux<Type>(s, delim, tr, is_nullptr_t()));
}

//template<class Translator>
//std::vector<std::string> split(const string& s, char delim, Translator tr)
//{
//    std::vector<std::string> result;
//    size_t start = 0, find = 0
//}

//std::vector<std::string> split(const std::string& s, char delim) 
//{
//    std::vector<std::string> result;
//    size_t start = 0, find = 0;
//    while((find = s.find(delim, start)) != std::string::npos)
//    {
//        result.push_back(s.substr(start, find - start));
//        start = find + 1;
//    }
//    result.push_back(s.substr(start));
//    return result;
//}

template<class Iterator>
std::string join_aux(Iterator first, Iterator last, char delim, std::true_type)
{
    std::string result;
    for(; first != last; ++first)
    {
        result += *first;
        result.push_back(delim);
    }
    result.pop_back();
    return result;
}

template<class Iterator>
std::string join_aux(Iterator first, Iterator last, char delim, std::false_type)
{
    std::string result;
    for(; first != last; ++first)
    {
        result += std::to_string(*first);
        result.push_back(delim);
    }
    result.pop_back();
    return result;
}

template<class Iterator>
std::string join(Iterator first, Iterator last, char delim)
{
    typedef typename std::iterator_traits<Iterator>::value_type value_type;
    typedef typename std::is_same<value_type, std::string>::type is_string_type;
    return std::forward<std::string>(join_aux(first, last, delim, is_string_type()));
}

//template<class T>
//std::string join(T* first, T* last, char delim)
//{
//    std::string result;
//    for(; first != last; ++first)
//    {
//        result += std::to_string(*first);
//        result.push_back(delim);
//    }
//    result.pop_back();
//    return result;
//}

//template<>
//std::string join(std::string* first, std::string* last, char delim)
//{
//    std::string result;;
//    for(; first != last; ++first)
//    {
//        result += *first;
//        result.push_back(delim);
//    }
//    result.pop_back();
//    return result;
//}

#endif  /*UTIL_IMPLEMENTATION_H*/
