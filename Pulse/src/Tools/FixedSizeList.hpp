/* Copyright © 2015 Pierre Schefler <pierre.schefler@oxbern.com>
* This work is free. You can redistribute it and / or modify it under the
* terms of the Do What The Fuck You Want To Public License, Version 2,
* as published by Sam Hocevar.See the LICENSE file for more details.
*/

#ifndef FIXEDSIZELIST_HPP_INCLUDED
#define FIXEDSIZELIST_HPP_INCLUDED

//This class is a std::list that cannot exceed _size elements.

template <typename T>
class FixedSizeList : public std::list<T>
{
    public:

        FixedSizeList(size_t maxSize = 0)
         : std::list<T>(), _size(maxSize)
        {
            for (unsigned i=0 ; i<_size ; i++)
                this->emplace_back();
        }

        void add_front(T const& val)
        {
            if (_size > 0)
            {
                this->pop_back();
                this->push_front(val);
            }
        }

        void add_back(T const& val)
        {
            if (_size > 0)
            {
                this->pop_front();
                this->push_back(val);
            }
        }

        void replace_front(T const& val)
        {
            if (_size > 0)
            {
                this->pop_front();
            }
            this->push_front(val);
        }

        //Access array element.
        T & operator[](size_t index)
        {
            auto it = this->begin();
            std::advance(it, index);
            return *it;
        }

		//Const access to array element.
        T const& operator[](size_t index) const
        {
            auto it = this->begin();
            std::advance(it, index);
            return *it;
        }


    private:

        size_t _size;
};


#endif // FIXEDSIZELIST_HPP_INCLUDED
