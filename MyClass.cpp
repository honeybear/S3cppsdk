/**
 * This is a sample code for S3cppsdk project,all participants should obey rules shown below:)  
 */

#include <iostream>
#include <Windows.h>
#include "foo.h"

using namespace std;

#define LOOP_NUM	100

/**
 *	routine description here
 */
void MyClass::Function()
{
	// define local vars
	bool bLocalVarName;
	int	iLocalVarName;
	
	// DON'T use magic number in loops
	for (int i=0; i<LOOP_NUM; i++)
	{
		// DON'T use C-style printf()
		cout << "Hi there!!" << endl;
	}
}

/**
 *	routine description here
 */
int MyClass::FuncitonWithArgs(int argName1, bool argName2)
{
	return 0;
}
