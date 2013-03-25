#ifndef _KERNEL_H_
#define _KERNEL_H_

#define StatusType		(unsigned char)
#define TaskType		(unsigned char)
#define TaskRefType		(TaskType *)
#define TaskStateType		(unsigned char)
#define TaskStateRefType	(TaskStateType *)
#define ResourceType		(unsigned char)
#define EventMaskType		(unsigned char)

#define E_OK			((StatusType)0)
#define E_OS_ACCESS		((StatusType)1)
#define E_OS_CALLEVEL		((StatusType)2)
#define E_OS_ID			((StatusType)3)
#define E_OS_LIMIT		((StatusType)4)
#define E_OS_NOFUNC		((StatusType)5)
#define E_OS_RESOURCE		((StatusType)6)
#define E_OS_STATE		((StatusType)7)
#define E_OS_VALUE		((StatusType)8)

#define RUNNING			((TaskStateType)1)
#define WAITING			((TaskStateType)2)
#define READY			((TaskStateType)3)
#define SUSPENDED		((TaskStateType)4)
#define INVALID_TASK		((TaskStateType)0) /* 未定義 */

/* macro */
#define CHECK_TASKID(TaskID)	

#endif /* _KERNEL_H_ */

