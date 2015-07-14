/*
 * TestModule.cpp
 *
 *  Created on: 2015-7-30
 *      Author: fyliu
 */

#include "TestModule.h"
#include <stdio.h>

CTestModule::CTestModule()
{
	m_Second = 0;
}

CTestModule::~CTestModule()
{

}

unsigned int CTestModule::RegisterNeedNotifyes()
{
	this->RegisterNotify(_TMG_PRINT_INFO);
	this->RegisterNotify(_TMG_PRINT_NAME);
}

unsigned int CTestModule::OnNotify(unsigned int cmd, void *lparam, void *wparam)
{
	switch(cmd)
	{
	case _TMG_PRINT_INFO:
		return HandlePrintInfo((char *)lparam, (char *)wparam);
		break;
	case _TMG_PRINT_NAME:
		return HandlePrintName((char *)lparam, (char *)wparam);
		break;
	default:
		printf("error msg.\n");
		break;
	}

	return 0;
}

unsigned int CTestModule::StartWork()
{
	//your startup
	//you can create thread if you want in it.
}

unsigned int CTestModule::FrequentCall(unsigned int second)
{
	if(second != m_Second)
	{
		m_Second = second;
	}
	//your code
}

unsigned int CTestModule::HandlePrintInfo(char *lparam, char *wparam)
{
	printf("It is my information.\n");
	return 0;
}

unsigned int CTestModule::HandlePrintName(char *lparam, char *wparam)
{
	printf("It is my name .\n");
	return 0;
}

