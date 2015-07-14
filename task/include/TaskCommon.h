/*
 * TaskCommon.h
 *
 *  Created on: 2015-7-30
 *      Author: fyliu
 */

#ifndef TASKCOMMON_H_
#define TASKCOMMON_H_

#define	_SAFE_DELETE_ARRAY_(ptr)	do {\
		if(ptr != NULL)\
		{ \
			delete []ptr; \
			ptr = NULL;		\
		} \
	}while(0) \

enum _TASK_MSG_
{
	_TMG_PRINT_INFO,
	_TMG_PRINT_NAME
};

#endif /* TASKCOMMON_H_ */
