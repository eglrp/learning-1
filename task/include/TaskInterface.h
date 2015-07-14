/*
 * TaskInterface.h
 *
 *  Created on: 2015-7-30
 *      Author: fyliu
 */

#ifndef TASKINTERFACE_H_
#define TASKINTERFACE_H_

class CTaskInterface
{
public:
	CTaskInterface();
	virtual ~CTaskInterface();
public:
	virtual unsigned int RegisterNeedNotifyes()	= 0;
	virtual unsigned int OnNotify(unsigned int cmd, void *lparam, void *wparam) = 0;
	virtual unsigned int StartWork() = 0;
	virtual unsigned int FrequentCall(unsigned int second) = 0;
public:
	void RegisterNotify(unsigned int cmd);
	unsigned int SendNotify(unsigned int cmd,void *lparam, void *wparam);
	void UnRegisterNotify(unsigned int cmd);
public:
	void SetNotifyer(void *ptrNotifyer);
private:
	void *	m_ptrNotifyer;
};


#endif /* TASKINTERFACE_H_ */
