#ifndef ALGORITHMS_H_INCLUDED
#define ALGORITHMS_H_INCLUDED
#include <utility>

/** Non-modifying sequence operations **/

template<class InputIt, class UnaryFunc>
UnaryFunc for_each(InputIt first, InputIt last, UnaryFunc func)
{
    for (; first != last; ++first)
    {
        func(*first);
    }
    return func;
}

template<class InputIt>
bool equal(InputIt first1, InputIt last1, InputIt first2)
{
    for (; first1 != last1; ++first1, ++first2)
    {
        if (*first1 != *first2)
        {
            return false;
        }
    }
    return true;
}
template<class InputIt, class T>
int count(InputIt first, InputIt last, T& value)
{
    int counter = 0;
    for(; first != last; ++first)
    {
        if(*first == value)
            ++counter;
    }
    return counter;
}

template<class InputIt, class UnaryFunc>
int count_if(InputIt first, InputIt last, UnaryFunc func)
{
    int counter = 0;
    for(; first != last; ++first)
    {
        if(func(*first))
            ++counter;
    }
    return counter;
}

template<class InputIterator, class T>
InputIterator find(InputIterator first,InputIterator last, T& value)
{
    for(; first!= last; ++first)
        if( *first == value)
            return first;
    return last;
}

template<class InputIterator, class UnaryPred>
InputIterator find_if(InputIterator first, InputIterator last, UnaryPred predicate)
{
    for(; first!= last; ++first)
        if( predicate(*first))
            return first;
    return last;
}

template<class InputIterator, class UnaryPred>
InputIterator find_if_not(InputIterator first, InputIterator last, UnaryPred predicate)
{
    for(; first!= last; ++first)
        if( !(predicate(*first)) )
            return first;
    return last;
}

template<class Iter, class UnaryPred>
bool all_of(Iter first, Iter last, UnaryPred pred)
{
    return find_if_not(first, last, pred) == last;
}

template<class Iter, class UnaryPred>
bool any_of(Iter first, Iter last, UnaryPred pred)
{
    return find_if(first, last, pred) != last;
}

template<class Iter, class UnaryPred>
bool none_of(Iter first, Iter last, UnaryPred pred)
{
    return find_if(first, last, pred) == last;
}

template<class Iter1, class Iter2>
Iter1 search(Iter1 first, Iter1 last, Iter2 s_first, Iter2 s_last)
{
    for(;; ++first)
    {
        Iter1 iter = first;
        for(Iter2 s_iter = s_first; ; ++iter, ++s_iter)
        {
            if(s_iter == s_last)
                return first;
            if(iter == last)
                return last;
            if(*iter != *s_iter)
                break;
        }
    }
}

template<class ForwardIterator, class Amount, class T>
ForwardIterator search_n(ForwardIterator first, ForwardIterator last, Amount amount, T value)
{
    for(; first!= last; ++first)
    {
        if(*first != value)
            continue;
        ForwardIterator temp = first;
        Amount counter = 0;
        for(;;)
        {
            ++counter;
            if(counter == amount)
                return temp;

            ++first;
            if(first == last)
                return last;
            if(*first != value)
                break;
        }
    }
    return last;
}

template<class InputIt>
InputIt find_first_of(InputIt first, InputIt last, InputIt first2, InputIt last2)
{
    for (; first != last; ++first)
    {
        for (InputIt i = first2; i != last2; ++i)
        {
            if (*first == *i)
            {
                return first;
            }
        }
    }
    return last;
}

template<class Iter>
Iter adjacent_find(Iter first, Iter last)
{
    if (first == last)
        return last;

    Iter next = first;
    ++next;
    for (; next != last; ++next, ++first)
    {
        if (*first == *next)
            return first;
    }
    return last;
}

/** Modifying sequence operations **/

template<class ForwardIt>
void reverse(ForwardIt first, ForwardIt last)
{
    while((first != last) && (first != --last))
    {
        swap(*first++, *last);
    }
}

template <class ForwardIt>
ForwardIt rotate(ForwardIt first, ForwardIt n_first, ForwardIt last)
{
    if(first == n_first) return last;
    if(n_first == last) return first;

    ForwardIt next = n_first;

    do
    {
        iter_swap(first++, next++);
        if (first == n_first) n_first = next;
    }
    while (next != last);

    ForwardIt ret = first;

    for(next = n_first; next != last; )
    {
        iter_swap(first++, next++);
        if(first == n_first) n_first = next;
        else if(next == last) next = n_first;
    }

    return ret;
}

template <class ForwardIter, class OutputIter>
OutputIter rotate_copy(ForwardIter first, ForwardIter n_first, ForwardIter last, OutputIter dest_first)
{
    dest_first = cppy(n_first, last, dest_first);
    return copy(first, n_first, dest_first);
}

template<class InputIt, class OutputIt>
OutputIt copy(InputIt src_first, InputIt src_last, OutputIt dest_first)
{
    //Дорабратать,вызов неправильный
    while (src_first != src_last)
        *dest_first++ = *src_first++;
    return dest_first;
}

template<class InputIt, class OutputIt, class UnaryPred>
OutputIt copy_if(InputIt src_first, InputIt src_last, OutputIt dest_first, UnaryPred pred)
{
    while (src_first != src_last)
    {
        if (pred(*src_first))
            *dest_first++ = *src_first;
        src_first++;
    }
    return dest_first;
}

template<class InputIt, class Size, class OutputIt>
OutputIt copy_n(InputIt first, Size amount, OutputIt dest)
{
    if (amount > 0)
    {
        *dest++ = *first;
        for (Size i = 1; i < amount; ++i)
        {
            *dest++ = *++first;
        }
    }
    return dest;
}

template<class Iter>
Iter copy_backward(Iter first, Iter last, Iter dest_last)
{
    while (first != last)
        *(--dest_last) = *(--last);

    return dest_last;
}

template<class T>
void swap(T& first, T& last)
{
    T temp = first;
    first = last;
    last = temp;
}
template<class T>
void iter_swap(T* first, T* second)
{
    T temp = *first;
    *first = *second;
    *second = temp;
}
/*
template <class ForwardIterator, class _ForwardIterator>
void iter_swap(ForwardIterator a, _ForwardIterator b)
{
    swap(*a, *b);
}*/

template <class ForwardIterator>
ForwardIterator unique(ForwardIterator first, ForwardIterator last)
{
    if(first == last)
        return last;

    ForwardIterator result = first;
    for(; first != last; ++first)
    {
        if (!(*result == *first))
            *(++result) = *first;

    }
    return ++result;
}

template <class ForwardIterator, class OutputIterator>
ForwardIterator unique_copy(ForwardIterator first, ForwardIterator last, OutputIterator _first)
{
    if(first == last)
        return _first;

    *first = *_first;
    for(; first != last; ++first)
    {
        if (!(*_first == *first))
            *(++_first) = *first;
    }
    return _first;
}

template <class T, class ForwardIterator>
ForwardIterator remove(ForwardIterator first, ForwardIterator last, const T& v)
{
    ForwardIterator result = first;
    for(; first != last; ++first)
    {
        if(!(*first == v))
        {
            *result++ = *first;
        }
    }
    return result;
}

template <class UnaryPredicate, class ForwardIterator>
ForwardIterator remove_if(ForwardIterator first, ForwardIterator last, UnaryPredicate pred)
{
    ForwardIterator result = first;
    for(; first != last; ++first)
    {
        if(!pred(*first))
        {
            *result++ = *first;

        }
    }
    return result;
}

template<class ForwardIter, class T>
void fill(ForwardIter first, ForwardIter last, T& value)
{
    for(; first!=last; ++first)
        *first = value;
}

template<class Iterator, class Size, class T>
Iterator fill_n(Iterator first, Size size, T& value)
{
    for(Size i = 0; i < size; ++i)
        *first = value;
    return first;
}

template<class ForwardIterator, class Generator>
void generate(ForwardIterator first, ForwardIterator last, Generator generator)
{
    while (first != last)
    {
        *first++ = generator();
    }
}

template<class Iterator, class Size, class Generator>
Iterator generate_n(Iterator first, Size size, Generator generator)
{
    for(Size i = 0; i < size; i++ )
    {
        *first++ = generator();
    }
    return first;
}

template<class InputIt, class T>
void replace(InputIt first, InputIt last, T old_value, T new_value)
{
    for(; first != last; ++first)
        if(*first == old_value)
            *first = new_value;
}

template<class InputIt, class T, class UnaryPred>
void replace_if(InputIt first, InputIt last, UnaryPred pred, T new_value)
{
    for(; first != last; ++first)
        if(pred(*first))
            *first = new_value;
}

template<class InputIt, class OutputIt, class T>
OutputIt replace_copy(InputIt first, InputIt last, OutputIt dest_first, T old_value, T new_value)
{
    for (; first != last; ++first)
    {
        if(*first == old_value)
        {
            *first = new_value;
            *dest_first++ = *first;
        }
        else *dest_first = *first;
    }
    return dest_first;
}

template<class InputIt, class OutputIt, class T, class UnaryPred>
OutputIt replace_copy_if(InputIt first, InputIt last, OutputIt dest_first, UnaryPred pred, T new_value)
{
    for (; first != last; ++first)
    {
        if(pred(*first))
        {
            *first = new_value;
            *dest_first++ = *first;
        }
        else *dest_first = *first;
    }
    return dest_first;
}

/** Operations max/min **/

template<class T>
T max(T& first, T& second)
{
    if(first > second)
        return first;
    return second;
}

template<class InputIterator>
InputIterator max_element(InputIterator first, InputIterator last)
{
    if(first == last)
        return last;
    InputIterator max_value = first;
    ++first;
    for(; first < last; ++first)
    {
        if(*max_value < *first)
            max_value = first;
    }
    return max_value;
}

template<class T>
T min(T& first, T& second)
{
    if(first < second)
        return first;
    return second;
}

template<class InputIt>
InputIt min_element(InputIt first, InputIt last)
{
    if(first == last)
        return last;
    InputIt min_value = first;
    ++first;
    for(; first < last; ++first)
    {
        if(*min_value > *first)
            min_value = first;
    }
    return min_value;
}

template<class T>
std::pair<const T&, const T&> minmax( const T& a, const T& b )
{
    if(b < a)
        return std::pair<const T&, const T&>(b, a);
    else
        return std::pair<const T&, const T&>(a, b);
}

template<class T, class Compare>
std::pair<const T&, const T&> minmax( const T& a, const T& b, Compare comp )
{
    if comp(b, a)
        return std::pair<const T&, const T&>(b, a);
    else
        return std::pair<const T&, const T&>(a, b);
}


/** Sorting operations **/

template<class InputIt>
InputIt is_sorted_until(InputIt first, InputIt last)
{
    if(first != last)
    {
        auto i = first;
        for(i; i <= last; ++i)
        {
            if(*i < *first)
            {
                return --i;
            }
            first = i;
        }
    }
    return last;
}

template<class InputIt>
bool is_sorted(InputIt first, InputIt last)
{
    return is_sorted_until(first, last) == last;
}

template<class InputIt>
void sort(InputIt first, InputIt last)//придумать более красивую реализацию
{
    int size = 0;
    for(auto n = first; n < last; ++n, ++size);//узнаю размер от first до last
    for(auto i = last; i > first; --i,--size)
    {
        for(int j = 0; j != size-1; ++j)
            if(*(first+j) > *(first+j+1))
                swap(*(first+j),*(first+j+1));
    }
}

/**Set operations (on sorted ranges)**/


template<class InputIt>
bool includes(InputIt first, InputIt last, InputIt first2, InputIt last2)
{
    for (; first2 != last2; ++first)
    {
        if (first == last || *first2 < *first)
            return false;
        if ( !(*first < *first2) )
            ++first2;
    }
    return true;
}


/** Numeric operations **/

template<class ForwardIterator, class T>
void iota(ForwardIterator first, ForwardIterator last, T value)
{
    while(first != last)
    {
        *first ++;
        *first = value;
        ++value;
        std::cout << *first << std::endl;
    }
}


template<class InputIterator, class T>
T accumulate(InputIterator first, InputIterator last, T init)
{
    for(; first != last; ++first)
    {
        init += *first;
    }
    return init;
}

template<class InputIt, class T>
T inner_product(InputIt first, InputIt last, InputIt first2, InputIt last2, T value)
{
    for(; first!=last; ++first, ++first2)
    {
        value += (*first) * (*first2);
    }
    return value;
}

/** Operations on uninitialized memory **/

template <class T>
void destroy_at(T* p)
{
    p->~T();
}

/** Permutation operations **/

template<class BidirIterator>
bool next_permutation(BidirIterator first, BidirIterator last)
{
    if (first == last) return false;
    BidirIterator i = last;
    if (first == --i) return false;

    for(;;)
    {
        BidirIterator i1;
        BidirIterator i2;

        i1 = i;
        if (*--i < *i1)
        {
            i2 = last;
            while(!(*i < *--i2))//???

                iter_swap(i, i2);
            reverse(i1, last);
            return true;
        }

        if (i == first)
        {
            reverse(first, last);
            return false;
        }
    }
}


#endif // ALGORITHMS_H_INCLUDED
