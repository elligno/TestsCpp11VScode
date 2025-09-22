
#pragma once

#include <string>

#include <vector>

namespace cpp20 
{
    template<typename T>
    class ContOfObj 
    {
        public:
        template<typename U>
        void insert(U&& aObj2Ins)  // Universal/forward reference  
        {
            m_contOfObj.push_back(std::forward<U>(aObj2Ins));
        }
        private:
        std::vector<T> m_contOfObj;
    };

    //
    // NOTE both need to be done outside ofthe class template, very important 
    //

    // Declare (fully specialize)
    template<>
      template<> 
         void ContOfObj<std::string>::insert(std::string&& aObj2Ins)
         {
            m_contOfObj.push_back(std::move(aObj2Ins));
         } 

    template<>
      template<> 
         void ContOfObj<std::string>::insert( const std::string& aObj2Ins)
         {
            m_contOfObj.push_back(std::move(aObj2Ins));
         } 
} // End of namespace