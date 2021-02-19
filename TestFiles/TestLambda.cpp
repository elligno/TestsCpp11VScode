
// C++ include
#include <iostream>

namespace cpp11 
{
	// typedef pointer-2-function 
	typedef double (*ptrfunc)(double);

  // declare a function
	double myfunc(double aDbl) // my algorithm
	{
		return 3.;
	}

	// expect a pointer-2-function as argument
	// typical C API in scientific programming 
	// or physics modeling 
	double derivative( ptrfunc aPtr2Func, double x, double epsilon)
	{
		// compute something for this algorithm
    // that function calculate a derivative 
    // at a given order
//     int w_retCode = aPtr2Func(); // call function pointer
//     if (w_retCode==0)
//     {
//       return nullptr;
//     }
// 
//     struct RHS {int m_intVal;}w_rhs;
//     return (nullptr_t)w_rhs; // RHS some struct that hold data
    return 1.; // debugging purpose
	}

  // A Note About Function Pointers and C++11 lambda
	void testBasicLambda()
	{
    // If you have a lambda with an empty capture specification i.e. "[]", 
		// then it can be treated like a regular function and assigned to a function pointer. 
		// An example of using a function pointer with a capture-less lambda:
		ptrfunc lambda_f = [] (double aVal) -> double { double dx=2.;return (2.*aVal)/dx;};
		lambda_f(2.); // call lambda
		
    // This works because a lambda that doesn't have a capture group doesn't need its own class--
		// it can be compiled to a regular old function, allowing it to be passed around just like 
		// a normal function. 
		derivative(lambda_f, 1.2, 0.0001); // lambda pass as a function-ptr
		derivative(myfunc, 0.2,0.002);   // normal function 
	}
} // End of namespace