/*
 * TestModule.h
 *
 *  Created on: 2015-7-30
 *      Author: fyliu
 */

#ifndef TESTMODULE_H_
#define TESTMODULE_H_

#include "TaskInterface.h"

class CTestModule: public CTaskInterface
{
public:
	CTestModule();
	~CTestModule();
public:
	virtual unsigned int RegisterNeedNotifyes();
	virtual unsigned int OnNotify(unsigned int cmd, void *lparam, void *wparam);
	virtual unsigned int StartWork();
	virtual unsigned int FrequentCall(unsigned int second);
private:
	unsigned int HandlePrintInfo(char *lparam, char *wparam);
	unsigned int HandlePrintName(char *lparam, char *wparam);

private:
	unsigned int m_Second;

};


#endif /* TESTMODULE_H_ */
