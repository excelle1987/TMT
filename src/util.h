#ifndef UTIL_H
#define UTIL_H

#include <vector>
#include <string>

/** Split string with given @delim to desired @type
  * @tr translate functor
  */
template<class Type, class Translator>
std::vector<Type> split(const std::string& s, char delim, Translator tr = nullptr);

//template<class Translator>
//std::vector<std::string> split(const std::string& s, char delim, Translator tr)
//std::vector<std::string> split(const std::string& s, char delim);

/** Specialization of function split */
//template<>
//std::vector<std::string> split<std::string, void*>(const std::string& s, char delim, void* tr);

/** Concat items range from @first to @last, with @delim into string type */
template<class Iterator>
std::string join(Iterator first, Iterator last, char delim);

/** Partial spectialization */
//template<class T>
//std::string join(T* first, T* last, char delim);

/** Spectialization */
//template<>
//std::string join(std::string* first, std::string* last, char delim);
#include "util_implementation.hpp"


#endif  /*UTIL_H*/
