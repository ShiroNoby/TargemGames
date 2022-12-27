#include <iostream>
#include <vector>

#include "CString.h"


namespace CCompare{

	inline int comp(const CS::String& LStr, const CS::String& RStr)
	{
		auto script = [](const char &c)
		{
			int icheck = (int)c;
			icheck-= 32;
			return (char)icheck;
		};
		
		
		if (LStr.data() == RStr.data()) return 0;

		size_t Llength = LStr.length();
		size_t Rlength = RStr.length();
		size_t low = ( Llength <= Rlength ) ? Llength : Rlength;

		char check = (char)96; // 97 is 'a'
		for (size_t index = 0; index < low; ++index)
		{
			char left = LStr[index];
			char right = RStr[index];
			
			if( left > check )	left = script(left);
			if( right > check ) right = script(right);

			if ( left > right ) return -1;      // LStr > RStr
			if ( left < right ) return 1;       // LStr < RStr
		}

		if ( Llength > Rlength ) return -1;                  // LStr > RStr
		if ( Llength < Rlength ) return 1;                   // LStr < RStr

		return 0;                                           // LStr == RStr
	}

}; //CSompare


void vector_sort( std::vector<CS::String>& vector )
{	
	size_t size = vector.size();

	for( size_t firth = 0; firth < size; ++firth)
	{
		for( size_t second = firth + 1; second < size; ++second)
		{
			if( CCompare::comp( vector[firth], vector[second] ) == -1 ) 
			{
				vector[firth].swap( vector[second] );
			}
		}
	}
}


int main(int argc, char** argv)
{
	std::vector<CS::String> ArgVector;

	while ( !std::cin.eof() )
	{
		char TMP_ch[120];
		std::cin.getline(TMP_ch, 120);

		if ( TMP_ch[0] == '\0' ) { break; }

		CS::String str(TMP_ch);
		ArgVector.push_back( std::move(str) );
	}

	vector_sort(ArgVector);

	for ( size_t i = 0; i < ArgVector.size(); ++i )
	{
		std::cout << ArgVector[i].c_str() << std::endl;
	}
}