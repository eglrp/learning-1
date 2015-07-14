/*
 * TaskInterface.cpp
 *
 *  Created on: 2015-7-30
 *      Author: fyliu
 */

#include "TaskInterface.h"
#include "TaskCommon.h"

CTaskInterface::CTaskInterface()
{
	m_ptrNotifyer = NULL;
}

CTaskInterface::~CTaskInterface()
{
}

void CTaskInterface::SetNotifyer(void *ptrNotifyer)
{
	if(ptrNotifyer)
	{
		m_ptrNotifyer = ptrNotifyer;
	}
}

void CTaskInterface::RegisterNotify(unsigned int cmd)
{
	if(m_ptrNotifyer)
	{
		((CNotifyer *)m_ptrNotifyer)->RegisterNotify(cmd, this);
	}
}

unsigned int CTaskInterface::SendNotify(unsigned int cmd,void *lparam, void *wparam)
{
	if(!m_ptrNotifyer)
	{
		return -1;
	}

	return ((CNotifyer *)m_ptrNotifyer)->Notify(cmd,lparam, wparam);
}

void CTaskInterface::UnRegisterNotify(unsigned int cmd)
{
	if(m_ptrNotifyer)
	{
		((CNotifyer *)m_ptrNotifyer)->UnRegisterNotify(cmd, this);
	}
}

