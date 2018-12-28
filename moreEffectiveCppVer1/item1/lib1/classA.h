// =============================================================================================================================================
/*
*  Item 1: Pointers and references
*  -------------------------------
*  1) Refernce Must always refer to an object which it will always refer to, so:
*  a) We can not declare a refernce without initialize it.
*  1a) # One exception is when we declare a class member as a reference - in this case, in the line where the reference is declared, indeed 
*      we aren't initialize it, YET we MUST do it in the ctor.
*      # Note that assgining is NOT initializing.
*  b) Once the reference is assgined to an object, it will always refer to this object, so if we set the reference to refer to another object
*     the "old value" will be modified, yet the pointer will point to the same address.
*
*  2) For conclusion, you should use:
*  a) pointer - if you wish to have the ability NOT to point to an object (set the pointer to NULL) OR point to a different object.
*  b) reference - if you know in advance that you will always refer to an (valid) object (it can not be NULL) and ONLY to that object.  
*
*/
// =============================================================================================================================================

#include "../lib2/classB.h"

class A
{
	public:
	A(B& b);
	~A();

	B& m_b; // 1a)
};