#ifndef _KERNEL_H_
#define _KERNEL_H_

typedef unsigned char		StatusType;
typedef unsigned char		TaskType;
typedef TaskType *		TaskRefType;
typedef unsigned char		TaskStateType;
typedef TaskStateType *		TaskStateRefType;
typedef unsigned char		ResourceType;
typedef unsigned char		EventMaskType;
typedef unsigned char		Priority;

#define E_OK			((StatusType)0)
#define E_OS_ACCESS		((StatusType)1)
#define E_OS_CALLEVEL		((StatusType)2)
#define E_OS_ID			((StatusType)3)
#define E_OS_LIMIT		((StatusType)4)
#define E_OS_NOFUNC		((StatusType)5)
#define E_OS_RESOURCE		((StatusType)6)
#define E_OS_STATE		((StatusType)7)
#define E_OS_VALUE		((StatusType)8)

#define INVALID_TASK		((TaskType)0) /* 未定義 */

#define RUNNING			((TaskStateType)1)
#define WAITING			((TaskStateType)2)
#define READY			((TaskStateType)3)
#define SUSPENDED		((TaskStateType)0)


/* macro */
#define CHECK_TASKID(TaskID)	

struct TCB {
	TaskType id;
	TaskStateType state;
	unsigned char active_count;
	Priority priority;
	void * pc;
	void * sp;
};

#endif /* _KERNEL_H_ */

