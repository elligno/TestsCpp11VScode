#pragma once

// TmxString.h
// C includes
#include <memory>
#include <String.h>

// Jean's code review
//
//  operator= ne retourne pas un const (devrait retourner TmxString&)
//  methode c_str() devrait etre constant -> c_str() const 
//  devrait utilise le type std::string plutot que char*
//  methode size() devrait etre dans un contexte constant -> size() const
//  devrait utilise strcpy_s safe version qui throw an exception
//  operator= devrait checker for self-assignment if(this!=*rhs) {...},
//  puis le le clean-up des ressources free(m_p); et ensuite alloue les ressources 
//  ::strlen() retourne size_t, n'est pas un unsigned int (C++11), warning pour la conversion

namespace vs15 {

    class TmxString
    {
    private:
        char *m_p;

    public:
        TmxString( const char *p = "")
        {
            m_p = strdup(p);
        }
        TmxString( const TmxString &rhs)
        {
            m_p = strdup(rhs.m_p);
        }
        const TmxString& operator= ( const TmxString &rhs)  // no const return
        {
            m_p = new char[::strlen(rhs.m_p) + 1];
            ::strcpy(m_p, rhs.m_p);

            return *this;
        }

        ~TmxString()
        {
            free(m_p);
        }

        unsigned size()   // size() and return size_t not unsigned
        {
            return ::strlen(m_p);
        }
        const char *c_str()  // c_str() const 
        {
            return m_p;
        }
    };
} // End of namespace