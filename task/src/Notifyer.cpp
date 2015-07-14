/*
 * Notifyer.cpp
 *
 *  Created on: 2015-7-30
 *      Author: fyliu
 */
#include <stdlib.h>
#include "Notifyer.h"
#include "TaskCommon.h"

CNotifyer::CNotifyer()
{
	m_TaskArrayCount = 50;
	m_TaskArrayUsed  = 0;
	m_stuTaskArray   = new _NOTIFY_ARRAY_[m_TaskArrayCount];
}

CNotifyer::~CNotifyer()
{
	_SAFE_DELETE_ARRAY_(m_stuTaskArray);
}

void CNotifyer::RegisterNotify(unsigned int cmd, CTaskInterface *obj)
{
	m_stuTaskArray[m_TaskArrayUsed].cmd = cmd;
	m_stuTaskArray[m_TaskArrayUsed].obj = obj;

	m_TaskArrayUsed++;
	if(m_TaskArrayUsed == m_TaskArrayCount)
	{
		m_TaskArrayCount += 10;
		_NOTIFY_ARRAY_ *pTempArray = new _NOTIFY_ARRAY_[m_TaskArrayCount];
		memcpy(pTempArray, m_stuTaskArray, sizeof(_NOTIFY_ARRAY_) * m_TaskArrayUsed);
		_SAFE_DELETE_ARRAY_(m_stuTaskArray);
		m_stuTaskArray = pTempArray;
	}

	this->SortNotify();
}

void CNotifyer::UnRegisterNotify(unsigned int cmd, CTaskInterface *obj)
{
	int index = -1;
	for(int i = 0; i < m_TaskArrayUsed; i++)
	{
		if(cmd == m_stuTaskArray[i].cmd && obj == m_stuTaskArray[i].obj)
		{
			index = i;
		}
	}

	if(index != -1)
	{
		for(int i = index + 1; i < m_TaskArrayUsed; i++)
		{
			m_stuTaskArray[i - 1].cmd = m_stuTaskArray[i].cmd;
			m_stuTaskArray[i - 1].obj = m_stuTaskArray[i].obj;
		}
		m_TaskArrayUsed--;
		if(m_TaskArrayUsed < m_TaskArrayCount - 10)
		{
			_NOTIFY_ARRAY_ *pTempArray = new _NOTIFY_ARRAY_[m_TaskArrayUsed];
			memcpy(pTempArray, m_stuTaskArray, sizeof(_NOTIFY_ARRAY_) *m_TaskArrayUsed);
			_SAFE_DELETE_ARRAY_(m_stuTaskArray);
			m_stuTaskArray = pTempArray;
		}
	}
}

unsigned int CNotifyer::Notify(unsigned int cmd, void *lparam, void *wparam)
{
	unsigned int result = 0;
	for(int i = 0; i < m_TaskArrayUsed; i++)
	{
		if(m_stuTaskArray[i].cmd == cmd)
		{
			result += m_stuTaskArray[i].obj->OnNotify(cmd,lparam, wparam);
		}
	}

	return result;
}

unsigned int CNotifyer::SortNotify()
{
	return 0;
}
