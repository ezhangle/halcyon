// This file is part of the uSTL library, an STL implementation.
//
// Copyright (c) 2005 by Mike Sharov <msharov@users.sourceforge.net>
// This file is free software, distributed under the MIT License.

#ifndef ULIST_H
#define ULIST_H

#include "ustl/vector.h"
#include "ustl/ctralgo.h"

namespace ustl {

/// \class list ulist.h ustl.h
/// \ingroup Sequences
///
/// \brief Linked list, defined as an alias to vector.
///
template <typename T>
class list : public vector<T> {
public:
    typedef typename vector<T>::size_type       size_type;
    typedef typename vector<T>::iterator        iterator;
    typedef typename vector<T>::const_iterator  const_iterator;
    typedef typename vector<T>::reference       reference;
    typedef typename vector<T>::const_reference const_reference;
public:
    inline                      list ()                     : vector<T> () {}
    inline explicit             list (size_type n)              : vector<T> (n) {}
    inline                      list (size_type n, const T& v)  : vector<T> (n, v) {}
    inline                      list (const list<T>& v)         : vector<T> (v) {}
    inline                      list (const_iterator i1, const_iterator i2)     : vector<T> (i1, i2) {}
    inline size_type            size () const               { return (vector<T>::size()); }
    inline iterator             begin ()                    { return (vector<T>::begin()); }
    inline const_iterator       begin () const              { return (vector<T>::begin()); }
    inline iterator             end ()                      { return (vector<T>::end()); }
    inline const_iterator       end () const                { return (vector<T>::end()); }
    inline void                 push_front (const T& v)         { insert (begin(), v); }
    inline void                 pop_front ()                { erase (begin()); }
    inline const_reference      front () const              { return (*begin()); }
    inline reference            front ()                    { return (*begin()); }
    inline void                 remove (const T& v)             { ::ustl::remove (*this, v); }
    inline void                 unique ()                   { ::ustl::unique (*this); }
    inline void                 sort ()                     { ::ustl::sort (*this); }
    void                        merge (list<T>& l);
    void                        splice (iterator ip, list<T>& l, iterator first = NULL, iterator last = NULL);
};

/// Merges the contents with \p l. Assumes both lists are sorted.
template <typename T>
void list<T>::merge (list& l)
{
    insert_space (begin(), l.size());
    ::ustl::merge (iat(l.size()), end(), l.begin(), l.end(), begin());
}

/// Moves the range [first, last) from \p l to this list at \p ip.
template <typename T>
void list<T>::splice (iterator ip, list<T>& l, iterator first, iterator last)
{
    if (!first)
        first = l.begin();
    if (!last)
        last = l.end();
    insert (ip, first, last);
    l.erase (first, last);
}

#define deque list ///< list has all the functionality provided by deque

}

#endif