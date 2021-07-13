
#pragma once 

// C++ include
#include <iostream>

 // not sure what for?
// _SCL_SECURE_ALWAYS_VALIDATE_RANGE

namespace vs15 
{
    /**
     * @brief Testing some string conversion constructor (implicit conversion)
     * 
     */
    class myStringClass 
    {
        public:
        /**
         * @brief Construct a new my String Class object (default ctor)
         * 
         */
        myStringClass();
        /**
         * @brief Construct a new my String Class object (copy)
         * 
         * @param aOther string to build from
         */
        myStringClass( const myStringClass& aOther);
        /**
         * @brief Construct a new my String Class object (move copy ctor)
         * 
         * @param aOther 
         */
        myStringClass( myStringClass&& aOther);
        /**
         * @brief 
         * 
         * @param aOther string to build from 
         * @return myStringClass& object updated with new content
         */
        myStringClass& operator= (const myStringClass& aOther);
        
        /**
         * @brief Construct a new my String Class object from C string
         * 
         * @param aCharStr 
         */
        myStringClass( const char* aCharStr);
        
        /**
         * @brief Destroy the my String Class object
         * 
         */
        ~myStringClass();

        /**
         * @brief Return length of the string
         * 
         * @return size_t number of bytes (character) returned
         */
        size_t length() const { return ::strlen(m_data);}

        /**
         * @brief 
         * 
         * @return char* 
         */
        char* data() const { return m_data; }
        private:
        char* m_data; /**< Hold string charater*/
    };
}// End of namespace