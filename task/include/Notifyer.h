/*
 * Notifyer.h
 *
 *  Created on: 2015-7-30
 *      Author: fyliu
 */

#ifndef NOTIFYER_H_
#define NOTIFYER_H_

#include "TaskInterface.h"
#include <stdlib.h>
#include <string.h>

class CTaskInterface;
class CNotifyer
{
public:
	CNotifyer();
	~CNotifyer();
public:
	void RegisterNotify(unsigned int cmd, CTaskInterface * obj);
	void UnRegisterNotify(unsigned int cmd, CTaskInterface *obj);
	unsigned int Notify(unsigned int cmd, void *lparam, void *wparam);
	unsigned int SortNotify();
private:
	unsigned int m_TaskArrayCount;
	unsigned int m_TaskArrayUsed;
	struct _NOTIFY_ARRAY_
	{
		unsigned int cmd;
		CTaskInterface *obj;
	} *m_stuTaskArray;
};

#endif /* NOTIFYER_H_ */
