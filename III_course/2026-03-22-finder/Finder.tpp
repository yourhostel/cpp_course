#pragma once

template<typename T>
auto Finder<T>::find_first(const T& key) const
{
    return std::ranges::find(data_, key);
}

template<typename T>
template<typename Predicate>
auto Finder<T>::find_first_if(Predicate pred) const
{
    return std::ranges::find_if(data_, pred);
}

template<typename T>
template<typename Predicate>
std::vector<T> Finder<T>::find_all_if(Predicate pred) const
{
    std::vector<T> result;
    for (const auto& value : data_)
    {
        if (pred(value))
        {
            result.push_back(value);
        }
    }
    return result;
}

template<typename T>
auto Finder<T>::begin() const
{
    return data_.begin();
}

template<typename T>
auto Finder<T>::end() const
{
    return data_.end();
}