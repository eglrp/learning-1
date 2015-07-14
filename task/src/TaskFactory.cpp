/*
 * TaskFactory.cpp
 *
 *  Created on: 2015-7-30
 *      Author: fyliu
 */

#include <string.h>
#include "TaskFactory.h"
#include "TestModule.h"

CTaskFactory::CTaskFactory()
{
	m_ptrTaskArray = NULL;
}
CTaskFactory::~CTaskFactory()
{
	_TASK_ARRAY_ *pTemp = NULL;
	while(m_ptrTaskArray)
	{
		pTemp = m_ptrTaskArray;
		m_ptrTaskArray = m_ptrTaskArray->pNextTask;
		delete pTemp;
	}
}

CTaskInterface * CTaskFactory::GetTask(const char *task_name)
{
	CTaskInterface *pRetTask = this->FindTask(task_name);
	if(!pRetTask)
	{
		pRetTask = this->CreateTask(task_name);
	}

	return pRetTask;
}

unsigned int CTaskFactory::StartAllTasks()
{
	_TASK_ARRAY_ *pTempTask = m_ptrTaskArray;
	while(pTempTask)
	{
		//printf("Begin start: %s\n", pTempTask->szTaskName);
		pTempTask->pTask->StartWork();
		//printf("End\n");


	}
}

void CTaskFactory::TaskFrequentCall()
{

}

CTaskInterface *CTaskFactory::CreateTask(const char *task_name)
{
	CTaskInterface *pRetTask = NULL;
	if(strncmp(task_name, "TestMode", 32) == 0)
	{
		pRetTask = new CTestModule();
	}
	else
	{
		//coding
	}

	if(pRetTask)
	{
		_TASK_ARRAY_ *pAddTask = new _TASK_ARRAY_;
		pAddTask->pTask = pRetTask;
		pAddTask->pNextTask = NULL;
		strncpy(pAddTask->szTaskName, task_name, 32);
		//add tail
		if(m_ptrTaskArray)
		{
			_TASK_ARRAY_ *pTempTask = m_ptrTaskArray;
			while(pTempTask)
			{
				if(!pTempTask->pNextTask)
				{
					pTempTask->pNextTask = pAddTask;
					break;
				}
				pTempTask = pTempTask->pNextTask;
			}
			pTempTask->pNextTask = m_ptrTaskArray;
		}
		else
		{
			m_ptrTaskArray = pAddTask;
		}
	}

	return pRetTask;
}

CTaskInterface *CTaskFactory::FindTask(const char *task_name)
{
	_TASK_ARRAY_ * pTempTask = m_ptrTaskArray;
	while(pTempTask)
	{
		if(strncmp(pTempTask->szTaskName, task_name, 32) == 0)
		{
			return pTempTask->pTask;
		}
		pTempTask = pTempTask->pNextTask;
	}
	return NULL;
}
