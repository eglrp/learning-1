#include <stdio.h>
#include <string.h>

//reverse the memory block
//goal: |12345| -> |54321|
void *reverseMemory(void *memory, const size_t memsize)
{
	if(memory == NULL)
		return memory;
	if(memsize < 2)
		return memory;

	char *beg = (char *)memory;
	char *end = beg + memsize - 1;

	for(; beg < end; ++beg, --end)
	{
		char temp = *beg;
		*beg = *end;
		*end = temp;
	}

	return memory;
}


/*
*假设有连续的内存块M和N形如：|----M---|--------N---------|
*首先反转内存块M：M’=reverse(M)
*反转内存块N：N’=reverse(N)
*对整个内存块M’ N’进行反转：(M’N’)’ = NM
*/

// swap two adjacent memory block
// goal: |*****|######|  -> |######|*****|

void *swapAdjacentMemory(void *memory, const size_t headsize, const size_t totalsize)
{
	if(memory == NULL)
		return memory;
	if(totalsize < 2)
		return memory;
	if(headsize >= totalsize)
		return memory;
	char *ptr = (char *)memory;
	reverseMemory(ptr, headsize);
	reverseMemory(ptr + headsize, totalsize - headsize);
	reverseMemory(ptr, totalsize);

	return ptr;
}

/*
*形如：有内存MAN三块：|----M---|----A----|-----N------|，我们要交换M，N，保持A不动。
*
*反转内存块M：M’=reverse(M)
*反转A：A’=reverse(A)
*反转N：N’=reverse(N)
*反转M’A’N’：(M’A’N’)’=NAM
*/

// swap two nonadjacent memory block
// goal: |*****|$$$$|######|  -> |######|$$$$|*****|
void *swapNonAdjacentMemory(void *memory, const size_t headsize, const size_t endsize, const size_t totalsize)
{
	if(memory == NULL)
		return memory;
	if(totalsize < 3)
		return memory;
	if(headsize + endsize > totalsize )
		return memory;
	if(headsize >= totalsize || endsize >= totalsize)
		return memory;

	char *ptr = (char *)memory;

	reverseMemory(ptr, headsize);
	reverseMemory(ptr + headsize, totalsize - endsize - headsize);
	reverseMemory(ptr + totalsize - endsize, endsize);
	reverseMemory(ptr, totalsize);

	return ptr;
}


//goal: "hello world fyliu." -> "fyliu. world hello"
//采用分治的思想处理

void reverseLenWords(char *s, const size_t slen)
{
	if(s == NULL)
		return;
	if(slen < 2)
		return;
	for(size_t index = 0; index < slen; index++)
	{
		if(s[index] == ' ')
		{
			reverseLenWords(s + index + 1, slen - index - 1);
			swapNonAdjacentMemory(s, index, slen - index - 1, slen);
			break;
		}
	}

}

void reverseWords(char *s)
{
	size_t len = strlen(s);
	reverseLenWords(s, len);
}


int main(int argc, char const *argv[])
{
	//printf("%s\n", "hello world");
	//char test[] = "hello12345";
	//reverseMemory(test, 10);
	//swapAdjacentMemory(test, 5, 10);
	//printf("%s\n", test);

	//char test2[] = "helloxxxyy12345";
	//swapNonAdjacentMemory(test2, 5, 5, 15);
	//printf("%s\n", test2);

	char test3[] = "hello world fyliu";
	reverseWords(test3);
	printf("%s\n", test3);
	return 0;
}
