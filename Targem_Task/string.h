#ifndef __STRING_H_
#define __STRING_H_

//
namespace string
{
	//Custom String
	class CString
	{
	public:
		
		///ctor/dtor
							CString();
							~CString();

		explicit			CString( const char* data );	
							CString( const CString& str );
							CString( CString&& str ) noexcept;
						
	
		//operators
		char&				operator[]( int index);
		const char&			operator[]( int index) const;

		CString&			operator=( const char* data );
		CString&			operator=( CString& str );		
		CString&			operator=( CString&& str ) noexcept;

		bool				operator<( const CString& str ) const;
		bool				operator>( const CString& str ) const;
		
		//concatination
		CString&			operator+( CString& str );
		CString&			operator+( const char* data );
		friend CString		operator+( const char* data, string::CString& str2 );
				
		//gets
		const char*			get_char() const;
		int					get_length() const;
		
		//
		void				swap( CString& str );

	private:

		int					m_length;
		char*				m_data; //rework in uniqPointer
	};
} // namespace string

#endif // __STRING_H_