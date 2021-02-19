// C++ includes
#include <cassert>
#include <memory>
#include <string>
#include <iostream>
// STL includes
#include <list>
#include <vector>
#include <numeric>    // numeric library
#include <algorithm>  // stl algorithm
#include <functional> // placeholders and ...
// Boost includes
#include <boost/assign/std/vector.hpp> // bring into scope operator '+='
#include <boost/assign/list_of.hpp>
#include <boost/assert.hpp>
#include <boost/operators.hpp> // Boost sfx development

namespace tst 
{
//   template<typename Range>  //compute first order, not sure but i think so
//   boost::iterator_range<typename Range::iterator> computeDU( const Range& aRng)
//   {
//     assert(101==aRng.size());
//     std::vector<double> w_tmpdUi;
//     w_tmpdUi.reserve(aRng.size());  //i am not sure about this one??
//     
//     //w_vDU.resize(w_vecU.size()); // NbSections=101, but return 100
//     std::adjacent_difference( aRng.begin(), aRng.end(), std::back_inserter(w_tmpdUi));
// 
//     // what is the size of DU?
//     assert(101==w_tmpdUi.size());
//     
//     // do i return a temporary?? or a copy of it? not sure (remove 1 element)
//     return boost::make_iterator_range( w_tmpdUi.begin()+1,w_tmpdUi.end());
//   }

  std::vector<double> computeDU( const std::vector<double>& aRng)
  {
    assert(101==aRng.size());
    std::vector<double> w_tmpdUi;
    w_tmpdUi.reserve(aRng.size());  //i am not sure about this one??

    //w_vDU.resize(w_vecU.size()); // NbSections=101, but return 100
    std::adjacent_difference( aRng.begin(), aRng.end(), std::back_inserter(w_tmpdUi));

    // what is the size of DU?
    assert(101==w_tmpdUi.size());

    // do i return a temporary?? or a copy of it? not sure (remove 1 element)
    return std::vector<double>( w_tmpdUi.begin()+1,w_tmpdUi.end());
  }

  // some scientific algorithm that i want to test
	struct  testCellFace
	{
		// default ctor for use with stl container
		testCellFace(); 
		// 
		testCellFace(unsigned aId,float aX);
		float m_xCoord; // cell coord??? or  
		// temporary fix for now (cellFace concept)
		std::pair<float,float> m_cellFaceX;
	};

	struct testCell : boost::equality_comparable<testCell> // strickly comparable 
	{                                                      // ==, != operator
		// no default ctor provide (create a vector of type must be an error!!)
		testCell( unsigned aID, const float aXcoord, std::string aName) 
		: m_ID(aID),m_xCoord(aXcoord), m_name(aName), m_isTied(true) 
		{ std::cout << ""; /*m_cellFaceLR=std::make_pair(0.f,0.f);*/} 
		~testCell() {std::cout << "testErse dtor\n";} // shouldn't be called
		unsigned m_ID; 
		std::string m_name;
		bool m_isTied;
		float m_xCoord; // cell coord??? or  
		// temporary fix for now (cellFace concept)
		std::pair<testCellFace,testCellFace> m_cellFaceLR;
	};

	// provide the implementation for equality, boost "equaliy_comparable"
	// will implement the operator!= ... TO BE COMPLETED
	bool operator== ( const testCell& aType1, const testCell& aType2)
	{
		return (aType1.m_ID==aType2.m_ID && aType1.m_name==aType2.m_name);
	}

	// limiter function
	double testminmod( const double a, const double b)
	{
		double Resultat;
		if (a*b <= 0.)
			Resultat = 0.;
		else if ((fabs (a) < fabs (b)) && (a*b > 0.))
			Resultat = a;
		else if ((fabs (b) < fabs (a)) && (a*b > 0.))
			Resultat = b;
		else if (fabs (b) == fabs (a))		//	ATTENTION, mis pour vérification !!!!
			Resultat = a;
		else
		{
			printf( "Fonction MINMOD: situation ne correspondant pas a celle attendue\n");
			exit(101);
		}

		return (Resultat);
	}

	// Omega concept (computational domain)
	// In this case testErase is similar at cell (aggregate of 2-cell face)
	// Usage:
	//   
	void testReconstr( /*std::list<testCell>& aOmega*/) // pass by-ref!!! can change the cont
	{
		using namespace std;
		using namespace std::placeholders;
		using namespace boost::assign;

		// this is set to 100+1 the extra node is not part of the domain
		// added for the sole purpose of gradient computation dU (MUSCL)
		// last face of the grid node need a right neighbour which is set
		// by boundary condition from characteristics equations.
		// UR=U_i+1 - dU_i+1 at (i+1/2). dU_i=minmod();
		const unsigned NbSections = 101;

		// Initializing some fields for testing the numerical algorithm
		// initialize 5 elements with value step function
		vector<double> U1( (NbSections-1)/2, 1.f); // first field (A)
		push_back(U1).repeat( (NbSections/2)+1, 0.5f); // step function
		
    BOOST_ASSERT( U1.size()==101 && "Wetted area size is wrong");
// 		vector<double> U2(10,0.);   // second field (Q) 
// 		BOOST_ASSERT( U2.size()==101 && "Discharge size is wrong");
		//U2.reserve(NbSections);

		// initialize to 0 (default value)
		vector<double> dU1(NbSections);
		vector<double> dU2(NbSections);

    // make sure they are all 0!!!
    if(!all_of( dU1.begin(),dU1.end(), bind(equal_to<double>(),_1,0.)))
		{
      std::cerr << "U1 not all equal to zero\n";
		}
    if(!all_of(dU2.begin(),dU2.end(), bind(equal_to<double>(),_1,0.)))
    {
      std::cerr << "";
    }

		//	Calculs préalables: évaluation des éléments du vecteur dU
		dU1[0] = testminmod( U1[1]-U1[0], 0.f); // i=0 bnd node
	//	dU2[0] = testminmod( U2[1]-U2[0], 0.f); // no left neighbor node, =0.

		// inside node
		for (unsigned i = 1; i < NbSections-1; ++i) // NbSections-1=99 (computational domain)
		{
			dU1[i] = testminmod( U1[i+1]-U1[i], U1[i]-U1[i-1]);
//			dU2[i] = testminmod( U2[i+1]-U2[i], U2[i]-U2[i-1]);
		}

		// consider the case with i=100 (far right boundary node)
		// no right neighbor node, -0. 
		int i=100; // right or ghost node, only purpose is for dU computation

    // compute the boundary value for the ghost node and set this node
		// ... i am not sure how i will implement it, but at some point i need this value. 
		// retrieve list of section (Observer that is notify by the simulator)
		// create a type call say BndNodeSetter (Characteristic solver) that compute
		// those values based on the characteristic equation solution (setSection(100) and
		// setSection(99)) and call getBndNodeVal(); and we are done
		// each section has the state variable updated, at the end of each simulation loop
		// simulator notify all registered observe that are interested when state variable 
		// has changed   
		// Here the pseudo-code for the algorithm (push_back mean resizing 
		// which can be very expensive specially for large sized array).
		// std::pair<U1,U2> w_bndNodeVal=getBndNodeVal(aval);
		// U1.push_back(get<0>(w_bndNodeVal)); // i=100 (ghost node)
		// U2.push_back(get<1>(w_bndNodeVal)); // i=100 (ghost node)
		// BOOST_ASSERT( U1.size()==101 && "Wetted area size is wrong");
		dU1[i] = testminmod( 0.f, U1[i]-U1[i-1]); // U[i] is the ghost node
//		dU2[i] = testminmod( 0.f, U2[i]-U2[i-1]); // ....

    // want to check
    typedef boost::iterator_range<vector<double>::iterator> rng_iter;
    vector<double> w_rngU1 = computeDU(U1);
    
    //rng_iter::size_type w_chec = w_rngU1.size();
    
    // for the sole purpose of our test (range ctor)
    deque<double> w_dU11(w_rngU1.begin(),w_rngU1.end());
//     w_dU11.reserve(w_rngU1.size());
//     copy(w_rngU1.begin(),w_rngU1.end(),back_inserter(w_dU11));
    assert(100==w_dU11.size());
    w_dU11.push_front(0.); // 101
  //  w_dU11.insert(w_dU11.begin(),0.);
    w_dU11.push_back(0.); // 102
   
    deque<double> w_dOut;
   // w_dOut.reserve(102);
    // applying the algorithm
    adjacent_difference(w_dU11.begin(),w_dU11.end(),back_inserter(w_dOut),
      bind(&testminmod,_1,_2));
    w_dOut.pop_front();

    // check for equality

    // now use those differential for computing our minmod limiter function
    //wdU1[0] = testminmod( U1[1]-U1[0], 0.f); // i=0 bnd node

		// loop on cell face of each cell
    const double w_cte = 0.5f;
		for( unsigned i=0;i<NbSections-1;++i) // cell face
		{             
      // which is equal to number of grid node 
			double UL = U1[i]+w_cte*dU1[i];   // of the computational domain
			double UR = U1[i+1]-w_cte*dU1[i+1]; // both have 100 elements 
		}             

		// Using the STL adjacent numerical algorithm 
		// can be done in these steps 
		// IMPORTANT
		//   don't really need to use the deque container, just use a 
		//   vector will do the job perfectly.
		double w_tmpdU1_0 = testminmod( U1[1]-U1[0], 0.); // i=0 bnd node
//		double w_tmpdU2_0 = testminmod( U2[1]-U2[0], 0.); // no left neighbor node, =0.
		
    deque<double> w_dU1(NbSections);
		BOOST_ASSERT(w_dU1.size()==101 && "Deque wrong size");
// 		deque<double> w_dU2((NbSections));
// 		BOOST_ASSERT(w_dU2.size()==101 && "Deque wrong size");
		
    // computational interior node
		adjacent_difference(U1.begin()+1,U1.end(),w_dU1.begin());
//		adjacent_difference(U2.begin()+1,U2.end(),w_dU2.begin());
	
    // don't need those first node, not relevant, replace their value
		// 		w_dU1.pop_front();
		// 		w_dU1.push_front(dU1[0]);
		w_dU1[0]=w_tmpdU1_0; // simpler
	//	w_dU2[0]=w_tmpdU2_0; // overwrite
		// 		w_dU2.pop_front();
		// 		w_dU2.push_front(dU2[0]);
	
    BOOST_ASSERT(i==100 && "Wrong boundary index");
		w_dU1[i] = testminmod( 0., U1[i]-U1[i-1]); // U[i] is the ghost node
//		w_dU2[i] = testminmod( 0., U2[i]-U2[i-1]); // now we are done! gradient

		// first state variable and left state variable at second order???
		transform(w_dU1.begin(),w_dU1.end(),w_dU1.begin(),
			bind(multiplies<double>(),_1,0.5f));
		// 0,...,99 (left state)
		auto w_Uleft=boost::make_iterator_range(U1.begin(),U1.end()-1);
		auto w_dUleft=boost::make_iterator_range(w_dU1.begin(),w_dU1.end()-1);
		// add both and save result 
		// loop on cell face and set left and right state (UL,UR)
		vector<double> w_vecUL;
		w_vecUL.reserve(NbSections-1); // number of face for our discretization 
		transform(w_Uleft.begin(),w_Uleft.end(),w_dUleft.begin(),
			back_inserter(w_vecUL),bind(plus<double>(),_1,_2)); // UL=U+0.5*dU

		// right state for the first variable at which order?
		// 1,...,100 (left state)
		auto w_Uright=boost::make_iterator_range(U1.begin()+1,U1.end());
		auto w_dUright=boost::make_iterator_range(w_dU1.begin()+1,w_dU1.end());

		// loop on cell face and set left and right state (UL,UR)
		vector<double> w_vecUR;
		w_vecUR.reserve(NbSections-1); // number of face for our discretization 
		transform(w_Uright.begin(),w_Uright.end(),w_dUright.begin(),
			back_inserter(w_vecUR),bind(minus<double>(),_1,_2)); // UL=U+0.5*dU
		
		// compare the both dU from original code and this new code
		std::cout << "Test Domain cell iterator\n";
	}

    // use case ...to be completed
	void UseCase1()
	{
		// some usage of our concept like creating cell 
		// then add it to the domain
	}
} // end of namepsace