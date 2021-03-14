#include <cassert>
#include <iostream>
#include <vector>
#include <algorithm>
// Boost include
#include <boost/polymorphic_cast.hpp>
// App. includes
#include "testClassB.h"
#include "Btl_IAnotherInterface.h"
#include "IUpdateable.h"

namespace aa
{
	class JeanCls : public IUpdateable 
	{
	public:
		// implement the update method
		void update() override
		{
			std::cout << "we are in JeanCls::update()\n";
		}
		// some method provided
		void print(std::iostream &aIO) {}
		void conv2str(Btl::IAnotherInterface *aInterface)
		{ /*to be completed*/}
	private:
		float m_fval;
	};

	class JeanType : public IUpdateable  
	{
	public:
		// implement base class method
		void update() override
		{
			std::cout << "We re in JeanType::update()\n";
		}
		// overriden by subclass
		virtual int checkRet()
		{
			std::cout << "returning a int\n";
			return 1;
		}

	private:
		std::string m_name;
	};

	class JeanBase : public IUpdateable 
	{
	public:
		// default ctor
		JeanBase()             { std::cout << "JeanBase default ctor\n";}
		void update() override { std::cout << "We are JeanBase::update()\n";}
		virtual void getStr()  { std::cout << "JeanBase::getStr()\n";}
	private:
	};
	class JeanD : public JeanBase
	{
	public:
		JeanD( std::string aName) 
		: JeanBase(), 
		  m_name(aName) 
		{ 
			std::cout << "JeanD conversion ctor\n";
		}
		void update() override { std::cout << "JeanD::update()\n";}
		void Dmethod() {std::cout << "JeanD::Dmethod()\n";}
	private:
		std::string m_name;
	};

  class myAbstractClass 
  {
  public:
    myAbstractClass() {std::cout << "Base Abstract Class\n";}
    virtual void abstractethod()=0;
  private:
    std::string m_name;
  };

  class testCastBase2Derived : public myAbstractClass 
  {
  public:
    void abstractethod() override
    {
      std::cout << "AbstractMethod of Derive class\n";
    }
    void derivedMethod()
    {
      std::cout << "DerivedMethod of derived class\n";
    }
  private:
  };

  void testAbstract2Drived( testCastBase2Derived* aPtr2Derived)
  {
    std::cout << "Calling abstract method\n";
    aPtr2Derived->abstractethod();
    aPtr2Derived->derivedMethod();
  }

	// some test
	void testCastOperation()
	{
        using namespace std;

		// vector of base type
		vector<IUpdateable*> w_vecofBase;
		w_vecofBase.reserve(3);

		// fill vector with derived type
		JeanCls* w_ptr2Jean = new JeanCls;      // default ctor
		w_vecofBase.push_back( w_ptr2Jean );    //
		IUpdateable* w_testupd = new JeanType; //
		w_vecofBase.push_back( w_testupd);
		JeanBase* w_jbase=new JeanBase;
		w_vecofBase.push_back( w_jbase);
		JeanBase* w_jbptr=new JeanD( std::string("jean"));
		w_vecofBase.push_back(w_jbptr);   // pushing JeanBase ptr
		JeanD* w_jd=new JeanD( std::string("jeanD"));
		w_vecofBase.push_back(w_jd);

		// now let's test some cast operation
		// the problem with using the static cast, it won't 
		// complaint if the cast fail, it hasn't mechanism to 
		// tell you if the cast succeed or not. If we use 
		// static_cast to point in class tree, user have to 
		// make sure that the cast is valid. Here we try to 
		// cast base to another type (both support IUpdateable).
		JeanBase* w_checkCast = static_cast<JeanBase*>(w_vecofBase.front());
		
		// this cast return what? null if it doesn't succeed
		// anyway this cast is not valid
		// i think it return garbage, no it doesn't return garbage.
		// it return a pointer to JeanCls (actually it doesn't cast)
		// it just return the pointer (vector element returned by front)
		if( w_checkCast==nullptr) // it is not nullptr
		{
			std::cout << "Cast succeed\n";
		}
		else
			// it return JeanCls update(), because no cast was done  
			w_checkCast->update();

        // if we use the dynamic_cast operator, and type is polymorphic
		// it guarantee that if the cast doesn't succeed it returns nullptr
		// otherwise it returns a complete (cast will fail because of 
		// incompatible type, returns null) 
		w_checkCast = dynamic_cast<JeanBase*>(w_vecofBase.front());
		if( w_checkCast==nullptr)
		{
			std::cout << "Dynamic cast failed with correct behavior\n";
		}

		// let's do some other cast, this time i am sure that the cast
		// is valid since all type support IUpdateable
		// surprise this cast is not valid, it returns a null ptr
		// is that because IUpdateable is an interface or polymorphic?
		// What we do here, we downcast an use a static pointer because
		// we are sure that cast will succeed (first element is JeanCls)
		// otherwise we should use dynamic cast to test cast
		JeanCls* w_checkPtr = static_cast<JeanCls*>(w_vecofBase.front());
		assert(w_checkPtr!=nullptr);
		w_checkPtr->update();
		// without cast it won't compile because conversion (base to derived) 
		// from IUpadateable to JeanCls (need to cast)
		//JeanCls* w_checkValid = w_vecofBase.front();

		// don't need to cast since we have a vector of IUpdateable*
		IUpdateable* w_castValid = w_vecofBase.front();
		if( w_castValid==nullptr)
		{
			std::cout << "Static cast return a nullptr\n";
		}
		else
		{
			w_castValid->update(); // ... never get here
		}

		// what i do i just downcasting, that's what i do
		JeanD* w_dptr=static_cast<JeanD*>(w_vecofBase[3]);
		w_dptr->update();
		JeanBase* w_ptr2B=static_cast<JeanBase*>(w_vecofBase[3]);
        w_ptr2B->update();
		JeanBase* w_ptr2Bs=dynamic_cast<JeanBase*>(w_vecofBase[3]);
		w_ptr2Bs->update();
		JeanBase* w_jbp=static_cast<JeanBase*>(w_vecofBase[2]);
		w_jbp->update();
		JeanD* w_cast2der=static_cast<JeanD*>(w_vecofBase[2]);
		w_cast2der->update();
		w_cast2der=dynamic_cast<JeanD*>(w_vecofBase[2]);
		if (w_cast2der==nullptr)
		{
			std::cout << "Could perform downcast\n";
		}
		else
		{
			w_cast2der->update();
		}
	
		JeanBase* w_cast1=new JeanBase;
		// downcast, is it?? would it work? i think it doesn't make sense!!
		// why would i want toi cast a base pointer to derived type??
		// this type has no information about derived type
		JeanD* w_cdown=dynamic_cast<JeanD*>(w_cast1);
		if( w_cdown==nullptr)
		{
			std::cout << "I don't understand downcast\n";
		}
		JeanD* w_tryC=new JeanD("aaa");
		JeanBase* w_justDoit=dynamic_cast<JeanBase*>(w_tryC);
		JeanBase* w_aas=new JeanD("aas");
		// i don't have access to JeanD method
		// if i want access to Jean method i have to cast
		w_aas->update();
		w_aas->getStr();
		// could i use static cast?
		JeanD* w_dynC=dynamic_cast<JeanD*>(w_aas);
		if (w_dynC==nullptr)
		{
			std::cout << "Could downcast to JeanD\n";
		}
		else
		{
			// cast succeed so let's call some method
			w_dynC->Dmethod();
			w_dynC->getStr();
		}

		// before we go out of scope let's clean-up
		for_each( w_vecofBase.begin(),w_vecofBase.end(),
		[]( IUpdateable* aPtr2Base)
		{
			// delete the pointer
			delete aPtr2Base;
			aPtr2Base=nullptr;
		});
		unsigned i=0;
		if( !w_vecofBase.empty())
		{
			assert( w_vecofBase[i]==nullptr);
			w_vecofBase.clear();
		}

		std::cout << "Exiting of the testcast function\n";
	}

  void testSomeFuncArg( const IUpdateable& aAu2date)
  {
    std::cout << "We are in testSomeFuncArg function\n";
    myAbstractClass* w_absTRactCls = new testCastBase2Derived;
    testAbstract2Drived( static_cast<testCastBase2Derived*>(w_absTRactCls));

    std::cout << "Just want to test some function argument\n";
  }
} // End of namespace