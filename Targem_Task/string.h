#ifndef __STRING_H_
#define __STRING_H_

#include <cstdint>
#include <cassert>


namespace string
{
    //Custom String
    class CString
    {
    public:

        ///ctor/dtor
                            CString() :m_length(0), m_data(nullptr){}
                            ~CString();

	explicit	    CString( const char* );
                            CString( const CString& );
                            CString( CString&& ) noexcept;

	CString&            operator=(CString&);
	CString&            operator=(CString&&) noexcept;


    private:

	//
	explicit	    CString(uint32_t);

	//new
	void		    Allocate( uint32_t );

	//m_data[] = data[]
	void                Access( const char* );

	public:
	
        //operators whithouth range check
        char&		    operator[]( uint32_t );
	const char&         operator[]( uint32_t ) const;

	//operators whith range chek
	char&               at(uint32_t);
	const char&         at(uint32_t) const;

	bool		    operator<( const CString& ) const;
	bool		    operator>( const CString& ) const;
	bool                operator==( const CString& ) const;
		
	//concatination
	friend CString	    operator+( const CString&, const CString&);
	friend CString	    operator+( const CString& ,const char* );
	friend CString	    operator+( const char* , const CString& );
				
	//gets
	const char*	    c_str() const;
	uint32_t            length() const;
	bool                empty() const;

	//swap str1 <-> str2
	void		    swap( CString& str );

	private:

	uint32_t	    m_length;
	char*		    m_data;
	};

	//concatination
	CString		    operator+(const CString&, const CString&);
	CString		    operator+(const CString&, const char*);
	CString		    operator+(const char*, const CString&);
} // namespace string

#endif // __STRING_H_
