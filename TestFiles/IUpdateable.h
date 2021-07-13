
#pragma once


// some basic guids for testing (unsigned)
#define IID_IUpdateable   1111
#define IID_IDisplayable  2222
#define IID_IConservative 3333
#define IID_IType         4444

// some basic macro
#define SFX_IDENTITY(aType) IID_##aType 

namespace aa 
{
	/**
	 * @brief Interface for COM mechanism support.
	 * 
	 */
	class ITestAccess 
	{
	public:
		virtual void* getInterface( const unsigned aGuid)=0;
        virtual void* getInterface( const std::string& aInterface)=0;
	};

	/**
	 * @brief Implement property that is updateable
	 * 
	 */
	class IUpdateable
	{
	public:
		virtual void update()=0;
    // if you don't make it virtual and add it to the collection 
    // of the stl for example, you run through an error (derived 
    // class dtor call then the base class dtor is call, but if 
    // don't exist you have an error).
    virtual ~IUpdateable() { std::cout << "IUpdateable dtor\n";}
	protected:
	private:
    };

	/**
     * @brief Implement property that is displayeable
     * 
    */
	class IDisplayable
	{
	public:
		virtual void display() = 0; 
	private:
	};

    /**
     * @brief Implement property that is conservative 
     * 
    */
	class IConservative 
	{
	public:
		virtual void calculFF() = 0; 
	private:
	};

    /**
     * @brief System simulation type
     * 
     */
	class IType 
	{
	public:
		virtual void type() const = 0;
    virtual ~IType() { std::cout << "IType dtor\n";} 
	protected:
	private:
	};
} // End of namespace