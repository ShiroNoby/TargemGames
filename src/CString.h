#ifndef C_STRING
#define C_STRING

#include <cstddef>

#define SBlock 10

namespace CS{
    
    class                   Buff;
    class                   String;
    

    inline size_t           CStrlen( const char* data );


    inline size_t           CalcMemLoc( size_t size );


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
    inline int              comp( const String& LStr, const String& RStr );

	
    class Buff{

    public:

        explicit            Buff( size_t size = SBlock );
        explicit            Buff( const Buff& buffer );
                            Buff( Buff&& buffer ) noexcept;

                            ~Buff();

        Buff&               operator=( const Buff& buffer );            
        Buff&               operator=( Buff&& buffer) noexcept;
        
        char&               operator[] ( size_t index );
        const char&         operator[] ( size_t index ) const;

        void                swap( Buff& buffer );        
        
        //////////////////////////////////////////
        // creates a new buffer and transfers old data to it
        //
        // /param   size - new buf size
        // /return  char sequence length in buffer
        //////////////////////////////////////////
        size_t              resize( size_t size );
             
        //////////////////////////////////////////
        // if there is enough space in the buffer, 
        // adds a certain number of characters to it, 
        // if there is not enough space, causes resize
        //
        // /param   char sequence, which add to buffer
        //          count char, which add to buffer,
        //          count = 0, is count = CStrlen( data )
        //
        // /return  char sequence length in buffer
        //////////////////////////////////////////
        size_t              append( const char* data, size_t count = 0 );
    
        size_t              size() const;

        const char*         data() const; 
        
    private:
        
        size_t              m_size;
        char*               m_data;		
    };
	
	
    class String{

    public:
		
        explicit            String( const char* data );
        explicit            String( size_t size );
                            String( const String& str );	
                            String( String&& str ) noexcept;
                            String();
		
        String&             operator= ( const char* data );
        String&             operator= ( const String& str );
        String&             operator= ( String&& str ) noexcept;
       
        String&             operator+= ( char ch );
        String&             operator+= ( const char* data );
        String&             operator+= ( const String& str );
        
        char&               operator[]( size_t index );
        const char&         operator[]( size_t index ) const;
        
        void                swap( String& str );
        
        size_t              append( const char*, size_t count = 0 );
                       
        const char*         data() const;        
        const char*         c_str() const;  
        
        size_t              length() const; 
        size_t              size() const;    
                
    private:

        Buff                m_buffer;
        size_t              m_length;
    };
	
    
    String                  operator+( const String &str1, const String &str2 );
    String                  operator+( const String &str1, const char* str2 );
    String                  operator+( const char *str1  , const String &str2 );
    
    
    bool                    operator<( const String &str1, const String &str2);
    bool                    operator>( const String &str1, const String &str2);
    bool                    operator==( const String &str1, const String &str2);
    bool                    operator!=( const String &str1, const String &str2);
    bool                    operator<=( const String &str1, const String &str2);
    bool                    operator>=( const String &str1, const String &str2);
}; //CS

#endif // C_STRING

//////////////////////////////////////////
// 
//////////////////////////////////////////