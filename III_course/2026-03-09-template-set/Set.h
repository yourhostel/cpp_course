//
// Created by tysser on 09.03.26.
//

#ifndef CPP_COURSE_SET_H
#define CPP_COURSE_SET_H


#ifndef SET_H
#define SET_H

#include <vector>
#include <initializer_list>
#include <cstddef>

template<typename T>
class Set
{
private:
    std::vector<T> elements;

public:
    Set();
    Set(std::initializer_list<T> values);
    Set(const Set<T>& other);
    Set(Set<T>&& other);

    void add(const T& value);
    bool contains(const T& value) const;
    bool remove(const T& value);

    std::size_t size() const;
    bool empty() const;
    void clear();

    void print(std::ostream& os = std::cout) const;

    Set<T> unite(const Set<T>& other) const;
    Set<T> intersect(const Set<T>& other) const;
    Set<T> difference(const Set<T>& other) const;

    // Повертають ітератори початку і кінця контейнера.
    // Потрібні для підтримки range-based for:
    // for (const T& element : set)
    typename std::vector<T>::const_iterator begin() const;
    typename std::vector<T>::const_iterator end() const;
};

#include "Set.tpp"

#endif


#endif //CPP_COURSE_SET_H