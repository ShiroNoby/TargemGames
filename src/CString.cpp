#include <cassert>
#include <utility>

#include "CString.h"

using namespace CS;


//////////////////////////////////////////
// utility
//////////////////////////////////////////


inline size_t CS::CStrlen( const char* data )
{
  	assert( data && "data is null" );

	size_t sum = 0;
	size_t i = 0;
	while ( data[ i ] ) { ++sum; ++i; }
	return sum;
}


inline size_t CS::CalcMemLoc( size_t size )
{
    size_t resoult = size;
    
    if( size != SBlock ) 
    {
        size_t tmp = size / SBlock;
        resoult = ( tmp + 1 ) * SBlock;
    }
    
    return resoult;
}


//////////////////////////////////////////
// функция сравнения левой строки с правой
// LStr > RStr     return -1
// LStr < RStr     return 1
// LStr == RStr    return 0
//
// /param LStr - left string
//        RStr - right string
//          
// /return -1 0 1
//////////////////////////////////////////
inline int CS::comp( const String &LStr, const String &RStr )
{
    if( LStr.data() == RStr.data() ) return 0;
    
    size_t Llength = LStr.length();
    size_t Rlength = RStr.length();    
    size_t low = ( Llength <= Rlength )? Llength : Rlength;
    
    for( size_t index = 0; index < low ; ++index )
    {
        if( LStr[ index ] > RStr[ index ] ) return -1;      // LStr > RStr
        if( LStr[ index ] < RStr[ index ] ) return 1;       // LStr < RStr
    }
 
    if( Llength > Rlength ) return -1;                  // LStr > RStr
    if( Llength < Rlength ) return 1;                   // LStr < RStr
    
    return 0;                                           // LStr == RStr
}


//////////////////////////////////////////
// class Buff
//////////////////////////////////////////


Buff::Buff( size_t size ) : m_data( new char[ CalcMemLoc( size ) ] ), m_size( CalcMemLoc( size ) )
{  
    m_data[ 0 ] = '\0'; 
}


Buff::Buff( const Buff& buffer ) : m_data( new char[ buffer.m_size ] ), m_size( buffer.m_size )
{   
    m_data[ 0 ] = '\0';
    
    size_t length = CStrlen( buffer.data() );
    append( buffer.data(), length );
    m_data[ length ] = '\0';
}


Buff::Buff( Buff&& buffer ) noexcept : m_data( buffer.m_data ), m_size( buffer.m_size )
{
    buffer.m_data = nullptr;
    buffer.m_size = 0;
} // destr tmp


Buff::~Buff()
{
    delete[] m_data;
}


//////////////////////////////////////////
// buff::operator=
//////////////////////////////////////////


Buff& Buff::operator=( const Buff& buffer )
{
    if( buffer.data() == m_data ) return *this;
    
    Buff tmp( buffer ); // call constr
    tmp.swap( *this );
    
    return *this;
} //dest tmp


Buff& Buff::operator=( Buff&& buffer ) noexcept ///потеря памяти
{        
   if( m_data == buffer.m_data ) return *this;
   
   CS::Buff tmp( std::move( *this ) ); // this -> tmp  | this is Null
   
   m_data = buffer.m_data;
   m_size = buffer.m_size;

   buffer.m_data = nullptr;
   buffer.m_size = 0;
   
   return *this;
} //dest tmp


//////////////////////////////////////////
// buff::operator[]
//////////////////////////////////////////


char& Buff::operator[] ( size_t index )
{    
    return m_data[ index ];    
}


const char& Buff::operator[] ( size_t index ) const
{    
    return m_data[ index ];
}


//////////////////////////////////////////
// buff::utility
//////////////////////////////////////////


void Buff::swap( Buff& buffer )
{
    Buff tmp( std::move(buffer) );  // buffer -> tmp
    buffer = std::move( *this );    // this -> buffer
    *this = std::move( tmp );       // tmp -> this
} 


size_t Buff::resize( size_t size )
{
    Buff tmp( size ); // call constr
    
    size_t length = CStrlen( m_data );
    tmp.append( m_data, length ); // copy *this -> tmp 
    
    tmp.swap( *this ); // *this <--> tmp
    return length; 
} //dest tmp


size_t Buff::append( const char* data , size_t count )
{
    if ( !count ) count = CStrlen( data );    
   
    if( !m_size ) 
    {
        CS::Buff tmp( count );
        tmp.swap( *this );
    }   //destr tmp
    
    size_t length = CStrlen( m_data );

    if( ( m_size - length ) <= count ) length = resize( m_size + count );
    
    for( size_t index = 0; index < count; ++length, ++index ) 
    {
        m_data[ length ] = data[ index ];
    }    
    
    m_data[ length ] = '\0';
    return length;
} //destr tmp


size_t Buff::size() const 
{
    return m_size;
}


const char* Buff::data() const
{
    if( !m_size ) return "\0";
    
    return m_data;
}


//////////////////////////////////////////
// Class String;
//////////////////////////////////////////


String::String( const char* data ) : m_buffer( CStrlen( data ) ), m_length( 0 )
{   
    assert( m_buffer.size() && "String(const char*): empty buffer" ); //?
    
    m_length = m_buffer.append( data, CStrlen( data ) );
}


String::String( size_t size ) : m_buffer( size ), m_length( 0 ) {}


String::String( const String& str ) : m_buffer( str.size() ), m_length(0)
{
    assert( m_buffer.size() && "String(const String&): empty buffer" ); //?
    
    m_length = m_buffer.append( str.data(), str.length() );
}


String::String( String&& str ) noexcept : m_buffer( std::move( str.m_buffer ) ), m_length( str.length() )
{
    str.m_length = 0;   
}


String::String() : m_buffer(), m_length( 0 ) {}


//////////////////////////////////////////
// String::operator=
//////////////////////////////////////////


String& String::operator= ( const char* data )
{
    if( m_buffer.data() == data ) return *this;
    
    String tmp( data ); // call constr
    tmp.swap( *this );
        
    m_length = CStrlen( m_buffer.data() );
    return *this;
} //dest tmp


String& String::operator= ( const String& str ) 
{
    if( m_buffer.data() == str.data() ) return *this;
        
    String tmp( str ); // call construct
    tmp.swap( *this );
    
    return *this;
} // tmp destruct


String& String::operator= ( String&& str ) noexcept
{
    m_buffer = std::move( str.m_buffer );
    m_length = str.m_length;

    str.m_length = 0;
    
    return *this;
} //dest tmp


//////////////////////////////////////////
// String::operator+=
//////////////////////////////////////////


String& String::operator+= ( char ch )
{
    m_length = m_buffer.append( &ch, 1 );
    
    return *this;
}


String& String::operator+= ( const char* data )
{
    m_length = m_buffer.append( data );
    
    return *this;
}


String& String::operator+= ( const String& str )
{
    m_length = m_buffer.append( str.data(), str.length() );
    
    return *this;
}


//////////////////////////////////////////
// String::access
//////////////////////////////////////////


char& String::operator[]( size_t index )
{
    return m_buffer[ index ];
}


const char& String::operator[]( size_t index ) const
{
    return m_buffer[ index ];
}


//////////////////////////////////////////
// String::utility
//////////////////////////////////////////


void String::swap( String& str )
{
    String tmp( std::move( str ) );     // str -> tmp   | str is str()
    str = std::move( *this );           // this -> str  | our is str()
    *this = std::move( tmp );           // tmp -> this  | tmp is str()
}


size_t String::append( const char* data, size_t count ) 
{    
    m_length = m_buffer.append( data, count );
    
    return m_length;
}


const char* String::data() const
{
    return m_buffer.data();
}


const char* String::c_str() const 
{
    return m_buffer.data(); 
}


size_t String::length() const 
{
    return m_length;
} 


size_t String::size() const 
{
    return m_buffer.size();
}


//////////////////////////////////////////
// string::ex::operator
//////////////////////////////////////////


String CS::operator+( const String &str1, const String &str2 )
{
    String tmp( str1.length() + str2.length() );
    
    tmp.append( str1.data(), str1.length() );
    tmp.append( str2.data(), str2.length() );
    
    return tmp;
}


String CS::operator+( const String &str1, const char* str2 )
{
    size_t length = CStrlen( str2 );
    String tmp( str1.length() + length );
    
    tmp.append( str1.data(), str1.length() );
    tmp.append( str2, length );
    
    return tmp;
}


String CS::operator+( const char *str1  , const String &str2 )
{
    size_t length = CStrlen( str1 );
    String tmp( str2.length() + length );

    tmp.append( str1 );
    tmp.append( str2.data(), str2.length() );
    
    return tmp;
}


bool CS::operator<( const String &str1, const String &str2 )
{
    return ( comp( str1, str2 ) == 1 ) ? true : false;
}


bool CS::operator>( const String &str1, const String &str2 )
{
    return ( comp( str1, str2 ) == -1 ) ? true : false;
}


bool CS::operator==( const String &str1, const String &str2 )
{
    return ( comp( str1, str2 ) == 0 ) ? true : false;
}


bool CS::operator!=( const String &str1, const String &str2 )
{
    return ( comp( str1, str2 ) ) ? true : false;
}


bool CS::operator<=( const String &str1, const String &str2 )
{
    int resoult = comp( str1, str2 );
    return ( resoult == 1 || resoult == 0 ) ? true : false;
}


bool CS::operator>=( const String &str1, const String &str2 )
{
    int resoult = comp( str1, str2 );
    return ( resoult == -1 || resoult == 0 ) ? true : false;
}