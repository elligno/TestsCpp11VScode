
namespace vs11 
{
    /**
     * @brief class GridLattice describes the domain the PDE 
	 *               will be applied to
     */
    class gridLattice 
    {
    public:
        /**
         * @brief Construct a new grid Lattice object
         * 
         */
		gridLattice();
		gridLattice( const gridLattice& aOther) = default;
		gridLattice& operator= ( const gridLattice& aOther) = default;
		gridLattice( gridLattice&& aOther) = default;
		gridLattice& operator= ( gridLattice&& aOther) = default;

        /**
         * @brief Construct a new grid Lattice object
         * 
         * initialize the grid with the following syntax:
		 * d=2 [0,1]x[0,10] [1:30]x[1:300]
         * @param aInitStr 
         */
		gridLattice( const std::string& aInitStr);
		
		// ctor from parameters (not used at the moment in our programming environment)
		gridLattice( int nx, double xmin_, double xmax_);

		int getNoSpaceDim () const;

        double xMin() const;
        double xMax() const;

		// get the total number of points in the grid.
		int getNoPoints() const; 

		double Delta() const;
		
        double getPoint( int index);

		int getBase() const;   // get base values
		int getMaxI() const;   // upper limit of array

		// must be private, access denied to client
		// scan parameters from string
		void scan( const std::string& init_string);  

		// access to private member
		friend std::ostream& operator<< ( std::ostream&, gridLattice&);
    private:
        double m_xmin;
        double m_xmax;
        int m_noPts;
    };
} // End of namespace