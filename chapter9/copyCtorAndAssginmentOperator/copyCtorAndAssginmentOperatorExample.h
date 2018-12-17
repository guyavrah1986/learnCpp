#include <ostream>



class A 
{

public:
	A(int a, const char* str);

	A();
	~A();

	A(const A& other);
	A& operator=(const A& rhs);

	friend std::ostream& operator<<(std::ostream& out, const A& obj);

private:
	size_t getStrLen(const char* str) const;

public:
	int m_a;
	char* m_cstr;
};
 




