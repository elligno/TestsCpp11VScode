#pragma once

#include <algorithm>

namespace vs11 
{
    // intro to move semantic 
    //https://www.internalpointers.com/post/c-rvalue-references-and-move-semantics-beginners 

    // Reference for this web site about array class
    // https://www.codeproject.com/articles/397492/move-semantics-and-perfect-forwarding-in-cplusplus

    /**
     * @brief A class which defines an array of double values without move semantics.
     * One issue is particular important when writing a move constructor and a move assignment operator: 
     * the contents of the parameter, which is being moved, should remain valid for its further destruction. 
     * There are two approach es, which can be used here:
     *
     * (1) swapping its contents with the target object (as in case of assignment);
     *
     * (2) setting it contents to a valid empty value, by assigning nullptr to the relevant pointers 
     *     (often used for a move constructor).
     *
     *    In case of a move constructor, swap can also be considered, if the target is set to an empty value first, before the swap.
     */
    class Array
    {
        int m_size;
        double *m_array;

    public:
        /**
         * @brief Construct a new Array object
         * 
         */
        Array() : m_size{0}, m_array{nullptr} {} // empty constructor
        /**
         * @brief Construct a new Array object
         * 
         * @param n 
         */
        explicit Array(int n) : m_size(n), m_array( new double[n]) {}
        /**
         * @brief Construct a new Array object
         * 
         * @param x 
         */
        Array( const Array &x) : m_size(x.m_size), m_array( new double[m_size]) // copy constructor
        {
            std::copy( x.m_array, x.m_array + x.m_size, m_array);
        }

        /**
         * @brief Destroy the Array object
         * 
         */
        virtual ~Array() // destructor
        {
            delete[] m_array;
        }
         /**
          * @brief 
          * 
          * @param y 
          */
        auto Swap(Array &y) -> void
        {
            int n = m_size;
            double *v = m_array;
            m_size = y.m_size;
            m_array = y.m_array;
            y.m_size = n;
            y.m_array = v;
        }
        /**
         * @brief 
         * 
         * @param x 
         * @return Array& 
         */
        auto operator= ( const Array &x) -> Array & // copy assignment
        {
            if( x.m_size == m_size)
            {
                std::copy( x.m_array, x.m_array + x.m_size, m_array);
            }
            else
            {
                Array y(x);
                Swap(y);
            }
            return *this;
        }
        /**
         * @brief 
         * 
         * @param i 
         * @return double& 
         */
        auto operator[](int i) -> double &
        {
            return m_array[i];
        }

        auto operator[](int i) const -> double
        {
            return m_array[i];
        }
        /**
         * @brief 
         * 
         * @return int 
         */
        auto size() const -> int { return m_size; }
        /**
         * @brief 
         * 
         * @param x 
         * @param y 
         * @return Array 
         */
        friend auto operator+ (const Array &x, const Array &y) -> Array // adding two vectors
        {
            int n = x.m_size;
            Array z(n);
            for (int i = 0; i < n; ++i)
            {
                z.m_array[i] = x.m_array[i] + y.m_array[i];
            }

            return z;
        }
    };
} // End of namespace