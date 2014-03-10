#ifndef SPECIALSORT_H
#define SPECIALSORT_H

template <typename T>
class specialSort
{
    public:
        inline bool operator()( const T &t1, const T &t2 ) const
        {
            return( t2.section( '|', -1 ).toInt() < t1.section( '|', -1 ).toInt() );
        }
};

#endif // SPECIALSORT_H
