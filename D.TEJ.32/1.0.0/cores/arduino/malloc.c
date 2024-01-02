/* See LICENSE for license details. */

/* These functions are intended for embedded RV32 systems and are
   obviously incorrect in general. */

#include <Arduino.h>
   
#define MUL_NO_OVERFLOW (1UL << (sizeof(size_t) * 4))

void* __wrap_malloc(unsigned long sz)
{
  extern void* sbrk(long);
  void* res = sbrk(sz);
  if ((long)res == -1)
    return 0;
  return res;
}

void __wrap_free(void* ptr)
{
}


void* calloc(size_t num, size_t size)
{
	/* num * size unsigned integer wrapping check */
	if((num >= MUL_NO_OVERFLOW || size >= MUL_NO_OVERFLOW) && num > 0 && SIZE_MAX / num < size)
	{
		return NULL;
	}

	size_t total_size = num * size;
	void* ptr = malloc(total_size);

	if(ptr)
	{
		memset(ptr, 0, total_size);
	}

	return ptr;
}

void* realloc(void* ptr, size_t size)
{
	void* new_data = NULL;

	if(size)
	{
		if(!ptr)
		{
			return malloc(size);
		}

		new_data = malloc(size);
		if(new_data)
		{
			memcpy(new_data, ptr, size); // TODO: unsafe copy...
			free(ptr); // we always move the data. free.
		}
	}

	return new_data;
}

void* reallocf(void* ptr, size_t size)
{
	void* p = realloc(ptr, size);

	if((p == NULL) && (ptr != NULL))
	{
		free(ptr);
	}

	return p;
}
