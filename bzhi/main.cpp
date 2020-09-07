#include <intrin.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <string>
#include <vector>

#include "binstr.h"

int main() {
	uint64_t a = 0xFFFF'FFFF'FFFF'FFFF;

	for ( size_t i = 0; i < 64; i++ ) {
		uint64_t result = _bzhi_u64( a, i );

		std::string result_str = binstr( result );
		printf( "%2d : %016llx : %s\n", i, result, result_str.c_str() );
	}
}
