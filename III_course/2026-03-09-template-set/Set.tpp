//
// Created by tysser on 09.03.26.
//

#ifndef SET_CPP
#define SET_CPP

#include "Set.h"
#include <utility>

template<typename T>
Set<T>::Set()
{
}

template<typename T>
Set<T>::Set(std::initializer_list<T> values)
{
    for (const T& value : values)
    {
        add(value);
    }
}

template<typename T>
Set<T>::Set(const Set<T>& other)
    : elements(other.elements)
{
}

template<typename T>
Set<T>::Set(Set<T>&& other)
    : elements(std::move(other.elements))
{
}

template<typename T>
void Set<T>::add(const T& value)
{
    if (!contains(value))
    {
        elements.push_back(value);
    }
}

template<typename T>
bool Set<T>::contains(const T& value) const
{
    for (const T& element : elements)
    {
        if (element == value)
        {
            return true;
        }
    }

    return false;
}

template<typename T>
bool Set<T>::remove(const T& value)
{
    for (std::size_t i = 0; i < elements.size(); ++i)
    {
        if (elements[i] == value)
        {
            elements.erase(elements.begin() + static_cast<std::ptrdiff_t>(i));
            return true;
        }
    }

    return false;
}

template<typename T>
std::size_t Set<T>::size() const
{
    return elements.size();
}

template<typename T>
bool Set<T>::empty() const
{
    return elements.empty();
}

template<typename T>
void Set<T>::clear()
{
    elements.clear();
}

template<typename T>
void Set<T>::print(std::ostream& os) const
{
    os << "{ ";

    bool first = true;

    for (const T& element : elements)
    {
        if (!first) os << ", ";
        os << element;
        first = false;
    }

    os << " }";
}

template<typename T>
Set<T> Set<T>::unite(const Set<T>& other) const
{
    Set<T> result(*this);

    for (const T& value : other.elements)
    {
        result.add(value);
    }

    return result;
}

template<typename T>
Set<T> Set<T>::intersect(const Set<T>& other) const
{
    Set<T> result;

    for (const T& value : elements)
    {
        if (other.contains(value))
        {
            result.add(value);
        }
    }

    return result;
}

template<typename T>
Set<T> Set<T>::difference(const Set<T>& other) const
{
    Set<T> result;

    for (const T& value : elements)
    {
        if (!other.contains(value))
        {
            result.add(value);
        }
    }

    return result;
}

template<typename T>
typename std::vector<T>::const_iterator Set<T>::begin() const
{
    return elements.begin();
}

template<typename T>
typename std::vector<T>::const_iterator Set<T>::end() const
{
    return elements.end();
}

#endif