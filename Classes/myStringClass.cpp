// C includes
#include <string.h> // strlen
#include <cstring>  //memcpy
// app include
#include "myStringClass.h"

namespace vs15 
{
    myStringClass::myStringClass()
    : m_data{nullptr}
    { 
       // create a string of one character
       m_data = new char[1];
       m_data[0]='\0'; // null terminated string character
    }

    myStringClass::myStringClass( const myStringClass& aOther)
    {
        std::cout << "myStringClass Copy ctor myStringClass\n";

        // leave room for null terminated
        m_data = new char[aOther.length()+1];
        // copy data from source to destination, need to provide the size of dest
        ::strcpy_s( m_data, sizeof(aOther.m_data), aOther.m_data);
    }

    myStringClass& myStringClass::operator= (const myStringClass& aOther)
    {
        std::cout << "myStringClass assignment ctor myStringClass\n";

        // check for self-assignment
        if( this != &aOther)
        {
            /* code */
            if( nullptr != m_data)
            {
                /* code */
                delete [] m_data;
            }
            
            // allocate resources
            auto w_lengthOrg = ::strlen( aOther.m_data+1);
            m_data = new char[w_lengthOrg];
            // i am not sure if sizeof() is appropriate here
            // because below   
            ::strcpy_s( m_data, sizeof(aOther.m_data), aOther.m_data);
        }

        return *this;
    }

    myStringClass::myStringClass( const char* aCharStr)
    { 
        std::cout << "myStringClass const char* ctor\n";

        auto w_chkLch = ::strlen(aCharStr)+1;
        auto objSiz = sizeof(aCharStr);

        // don't forget the null terminated string
        m_data = new char[ ::strlen(aCharStr)+1];
        auto dad = sizeof(m_data); // size of the pointer!!! which is 8 on x64
        // NOTE sizeof m_data return 8, sizeof a pointer on x64
        ::strcpy_s( m_data, ::strlen(aCharStr)+1, aCharStr); // copy memory character
    }

    myStringClass::myStringClass( myStringClass&& aOther)
    {
       std::cout << "myStringClass move copy ctor\n";

       m_data = aOther.m_data;
       aOther.m_data=nullptr;
    }

    myStringClass::~myStringClass() 
    {
        std::cout << "myStringClass dtor\n";

        if( nullptr != m_data)
        {
            delete [] m_data;
            m_data = nullptr;
        }
    }
} // End of namespace