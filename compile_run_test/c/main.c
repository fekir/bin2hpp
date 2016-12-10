
// local
#include "res_carray.h"
#include "res_carray.h"

#include "res_carray_enum.h"
#include "res_carray_enum.h"

#include "res_carray_const1.h"
#include "res_carray_const1.h"


// libc
#include <assert.h>
#include <stdio.h>
#include <string.h>

static const char helloworld[] = "Hello World!\n\n"; // 2nd ewline is EOF

#define MYSIZE(x) sizeof(x)/sizeof(x[0])

struct const_arr_size{
	const unsigned char* const p;
	const size_t               size;
};

struct const_arr_size to_const_arr_size(const unsigned char* const p, const size_t size){
	assert(p != NULL);
	assert(size != 0);
	struct const_arr_size s= {.p = p, .size = size};
	return s;
}


#define TO_ARR_WITH_SIZE(x) to_const_arr_size(x, MYSIZE(x))


int compare(const struct const_arr_size t1, const struct const_arr_size t2){
	if(t1.size != t2.size){
		printf("t1.size (%zu) != t2.size (%zu)\n", t1.size, t2.size);
		return 1;
	}
	for(size_t i = 0; i != t1.size; ++i){
		const char c1 = (const char)(t1.p[i]);
		const char c2 = (const char)(t2.p[i]);
		if(c1 != c2){
			printf("t1.p[i] (%c) != t2.p[i] (%c)\n", c1, c2);
			return 1;
		}
	}
	return 0;
}


int main(){
	const size_t helloworldlen = strlen(helloworld);
	int res = 0;
	
	res += compare(to_const_arr_size(helloworld, helloworldlen), TO_ARR_WITH_SIZE(res1_helloworld));
	res += compare(to_const_arr_size(helloworld, helloworldlen), TO_ARR_WITH_SIZE(res2_helloworld));
	res += compare(to_const_arr_size(helloworld, helloworldlen), TO_ARR_WITH_SIZE(res3_helloworld));
	
	if(res == 0){
		puts("All tests passed");
	} else {
		printf("%d test of 3 failed\n", res);
	}
	return res == 0 ? 0 : 1;
}

