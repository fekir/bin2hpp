
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
#include <limits.h>

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


#define ARR_TO_ARR(x) to_const_arr_size(x, MYSIZE(x))
#define STR_TO_ARR(x) to_const_arr_size(x, strlen(x))

enum binary_blob_size{ blob_size = UCHAR_MAX*2};

const unsigned char* create_binary_blob(){
	static unsigned char tmp[blob_size];
	unsigned char c = '\0';
	for(int i = 0; i != blob_size; ++i, ++c){
		tmp[i] = c;
	}
	return tmp;
}

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
	//const size_t helloworldlen = strlen(helloworld);

	const unsigned char* blob = create_binary_blob();
	int res = 0;

	res += compare(to_const_arr_size(blob, blob_size), ARR_TO_ARR(res1_bin2hppbinarydata_dat));
	res += compare(to_const_arr_size(blob, blob_size), ARR_TO_ARR(res2_bin2hppbinarydata_dat));
	res += compare(to_const_arr_size(blob, blob_size), ARR_TO_ARR(res3_bin2hppbinarydata_dat));

	if(res == 0){
		puts("All tests passed");
	} else {
		printf("%d test of 3 failed\n", res);
	}
	return 0;
}

