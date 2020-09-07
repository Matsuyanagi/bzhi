#include <intrin.h>
#include <string.h>

#include <string>
/**
 * 任意の型の値を2進数文字列へ変換する
 */
template <typename T>
std::string binstr( T reg, const char *splitter = "-" ) {
	const int splitter_length = strlen( splitter );
	const int buffer_length = sizeof( T ) * 8 + ( ( sizeof( T ) * 8 - 1 ) / 8 ) * splitter_length + 1;
	char *const buffer = static_cast<char *>( _malloca( buffer_length ) );
	char *pbuffer = buffer;

	const int64_t mask = 0x01010101'01010101;
	const uint8_t *preg = reinterpret_cast<uint8_t *>( &reg ) + sizeof( T ) - 1;

	bool flag_first = true;
	for ( size_t i = 0; i < sizeof( T ); i++ ) {
		if ( flag_first ) {
			flag_first = false;
		} else {
			memcpy( pbuffer, splitter, splitter_length );
			pbuffer += splitter_length;
		}
		uint64_t v = *preg;
		preg--;

		int64_t b = _pdep_u64( v, mask );
		b += 0x30303030'30303030;
		b = _byteswap_uint64( b );
		memcpy( pbuffer, &b, sizeof( b ) );
		pbuffer += sizeof( b );
	}
	*pbuffer = '\0';
	std::string result( buffer );
	_freea( buffer );
	return result;
}
