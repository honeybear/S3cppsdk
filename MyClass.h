/**
 * This is a sample code for S3cppsdk project,all participants should obey rules shown below:)  
 */

// prevent redefinition: _FILENAME_H
#ifndef _MYCLASS_H
#define _MYCLASS_H

// declare a struct. DON'T typedef its pointer, use *
typedef struct _my_struct
{
	int	var_name_xx;
	bool	var_name_yy;
} MY_STRUCT;

// declare a class. avoid declaring multiple classes in one header file.
class MyClass 
{
public:
	// variables
	
	// constructors and destructors
	MyClass(){};
	~MyClass(){};
	
	// functions
	void	Function();
	int	FunctionWithArgs(int argName1, bool argName2);
	
private:	
	// variables
	int			m_iVar;
	char			*m_pVar;
	bool			m_bVar;
	char			m_cVar;
	unsigned		m_uVar;
	ULONG			m_ulVar;
	USHORT		m_usVar;
	MY_STRUCT	m_Var;	// no need to add type before a variable's name if it's not a fundamental data type
	
	// functions
};

#endif
