/*Dr. Pettey's fun with void pointers*/
#include <stdio.h>
void test(char c, void* x)
{
	int a;
	float b;
	if(c=='i')
	{
		a = *((int*)x);	
		printf("%d is an integer\n",a);
	}
	else
	{
		b = *((float*)x);
		printf("%f is a float\n",b);
	}

	return;
}

int main()
{
	int i=7;
	float j=88.2;
	test('i',(void*)&i);
	test('f',(void*)&j);
	return 0;
}
