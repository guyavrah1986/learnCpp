#include <iostream>
using namespace std;

static void print_object(const char *name, void *this_, size_t size)
{
	void** tmp = reinterpret_cast<void**>(this_);
	size_t i;
	printf("created %s at address %p of size %zu\n", name, this_, size);
	for(i = 0 ; i < size / sizeof(void*) ; ++i)
	{
		printf("  pointer[%zu] == %p\n", i, tmp[i]);
	}
}

void foo(int i)
{
	cout << "foo - i is:" << i << endl;
}

void bar(int i)
{
	cout << "bar - i is:" << i << endl;
}

int main(int argc, char** argv)
{
	cout << "main - start" << endl;

	// early (static) binding:
	bar(15);

	// late binding
	void (*funcPointer)(int) = &foo;
	(*funcPointer)(17);

	cout << "main - end" << endl;
	return 0;
}
