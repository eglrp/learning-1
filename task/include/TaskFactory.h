/*
 * TaskFactory.h
 *
 *  Created on: 2015-7-30
 *      Author: fyliu
 */

#ifndef TASKFACTORY_H_
#define TASKFACTORY_H_

class CTaskInterface;
class CTaskFactory
{
public:
	CTaskFactory();
	~CTaskFactory();
public:
	CTaskInterface * GetTask(const char *task_name);
	unsigned int StartAllTasks();
	void TaskFrequentCall();
private:
	CTaskInterface *CreateTask(const char *task_name);
	CTaskInterface *FindTask(const char *task_name);
private:
	struct _TASK_ARRAY_ {
		char szTaskName[32];
		CTaskInterface *pTask;
		_TASK_ARRAY_ *pNextTask;
	}* m_ptrTaskArray;
};

#endif /* TASKFACTORY_H_ */
