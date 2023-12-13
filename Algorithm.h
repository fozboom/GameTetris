#ifndef TETRIS_ALGORITHM_H
#define TETRIS_ALGORITHM_H

#include <algorithm>
#include <random>
#include "List.h"

template<typename T>
class Algorithm
{
public:

    //сортировка
    static void sort(List<T>& list)
    {
        std::vector<T> tmp(list.size());
        std::copy(list.begin(), list.end(), tmp.begin());
        std::sort(tmp.begin(), tmp.end());
        std::copy(tmp.begin(), tmp.end(), list.begin());
    }

    //поиск
    static typename List<T>::iterator find(List<T>& list, const T& value)
    {
        return std::find(list.begin(), list.end(), value);
    }

    //фильтрация
    static List<T> filter(const List<T>& list, std::function<bool(const T&)> condition)
    {
        List<T> result;
        std::copy_if(list.begin(), list.end(), std::back_inserter(result), condition);
        return result;
    }

    //перемешивание
    static void shuffle(List<T>& list)
    {
        std::vector<T> tmp(list.size());
        std::copy(list.begin(), list.end(), tmp.begin());
        auto rng = std::default_random_engine{};
        std::shuffle(tmp.begin(), tmp.end(), rng);
        std::copy(tmp.begin(), tmp.end(), list.begin());
    }

    //реверс листа
    static void reverse(List<T>& list) {
        std::reverse(list.begin(), list.end());
    }

    //удаление дубликатов
    static void remove_duplicates(List<T>& list) {
        std::sort(list.begin(), list.end());
        auto it = std::unique(list.begin(), list.end());
        list.erase(it, list.end());
    }

    //разделение списка на больше и меньше pivot
    static std::pair<List<T>, List<T>> partition(const List<T>& list, const T& pivot)
    {
        List<T> less;
        List<T> greater;

        for (const auto& item : list)
        {
            if (item < pivot)
            {
                less.push_back(item);
            }
            else
            {
                greater.push_back(item);
            }
        }

        return {less, greater};
    }
};
#endif //TETRIS_ALGORITHM_H