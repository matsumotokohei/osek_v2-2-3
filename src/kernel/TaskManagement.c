#include <kernel.h>

struct TCB tcb[ 128 ] = {0};
struct TCB * current = 0;
TaskType queue[ 128 ] = { INVALID_TASK };

extern void dispatch( struct TCB * oldp, struct TCB * newp );
StatusType Schedule(void);

static TaskType get_ready_queue(void)
{
	TaskType top = queue[ 0 ];
	int i = 0;

	if ( top == INVALID_TASK ) {
		return INVALID_TASK;
	}

	/* ソート */
	for ( i=1; i < 128; i++ ) {
		queue[ i-1 ] = queue[ i ]; 
		if ( queue[ i-1 ] == INVALID_TASK ) {
			break;
		}
	}
	queue[ 128 ] = INVALID_TASK;

	return top;
}

static void insert_ready_queue( TaskType TaskID )
{
	int i, j;

	for ( i = 0; i < 128; i++ ) {
		if ( queue[ i ] == INVALID_TASK ) {
			queue[ i ] = TaskID;
			break;
		}
		else if ( tcb[ queue[ i ] ].priority < tcb[ TaskID ].priority ) {
			for ( j=i + 1; j < 128; j++ ) {
				queue[ j ] = queue[ i ]; 
			}
			queue[ i ] = TaskID;
			break;
		}
	}
}

static StatusType activate(TaskType TaskID)
{
	StatusType ercd = E_OK;
	struct TCB * tcbp = &tcb[ TaskID ];

	switch ( tcbp->state ) {
	case SUSPENDED:
		tcbp->state = READY;
		insert_ready_queue( TaskID );
		break;

	case RUNNING:
		if (  tcbp->active_count >= 255 ) {
			ercd = E_OS_LIMIT;
		}
		else {
			tcbp->active_count++;
		}
		break;

	default:
		break;
	}

	return ercd;
}

static StatusType start(TaskType TaskID)
{
	StatusType ercd = E_OK;
	struct TCB * tcbp = &tcb[ TaskID ];

	switch ( tcbp->state ) {
	case READY:
		delete_ready_queue( tcbp );
		tcbp->state = RUNNING;
		break;

	default:
		break;
	}

	return ercd;
}

static StatusType preempt(TaskType TaskID)
{
	StatusType ercd = E_OK;

	switch ( tcb[ TaskID ].state ) {
	case RUNNING:
		tcb[ TaskID ].state = READY;
		insert_ready_queue( TaskID );
		break;
	default:
		break;
	}
	
	return ercd;
}

static StatusType terminate(void)
{
	StatusType ercd = E_OK;

	switch ( current->state ) {
	case RUNNING:
		current->state = SUSPENDED;
		if ( current->active_count >= 2 ) {
			--(current->active_count);
			activate( current->id );
		}
		break;

	default:
		break;
	}

	return ercd;
}

/*

*/
StatusType ActiveTask(TaskType TaskID)
{
	StatusType ercd = E_OK;

#ifdef EXTENDED
	CHECK_TASKID(TaskID);
#endif

	ercd = activate(TaskID);
	if ( ercd != E_OK ) {
		ErrorHook();
		return ercd;
	}

	ercd = Schedule();
	if ( ercd != E_OK ) {
		ErrorHook();
		return ercd;
	}

	return ercd;
}

/*

*/
StatusType TerminateTask(void)
{
	StatusType ercd = E_OK;

	ercd = terminate();
	if ( ercd != E_OK ) {
		ErrorHook();
		return ercd;
	}

	ercd = Schedule();
	if ( ercd != E_OK ) {
		ErrorHook();
		return ercd;
	}

	return ercd;
}

/*

*/
StatusType ChainTask(TaskType TaskID)
{
	StatusType ercd = E_OK;

	ercd = terminate();
	if ( ercd != E_OK ) {
		ErrorHook();
		return ercd;
	}

	ercd = activate(TaskID);
	if ( ercd != E_OK ) {
		ErrorHook();
		return ercd;
	}

	ercd = Schedule();
	if ( ercd != E_OK ) {
		ErrorHook();
		return ercd;
	}

	return ercd;
}

/*

*/
StatusType Schedule(void)
{
	StatusType ercd = E_OK;
	TaskType NextTaskID = INVALID_TASK;
	struct TCB * next = 0;

	NextTaskID = get_ready_queue();

	if ( NextTaskID == INVALID_TASK ) {
		return ercd;
	}

	next = &tcb[ NextTaskID ];

	if ( current->priority < next->priority ) {
		preempt( current->id );
		start( next->id );

		dispatch( current, next );

		/* 更新 */
		current = next;
	}

	return ercd;
}

/*

*/
StatusType GetTaskID(TaskRefType TaskID)
{
	StatusType ercd = E_OK;

	*TaskID = current->id;

	return ercd;
}

/*

*/
StatusType GetTaskState(TaskType TaskID, TaskStateRefType State)
{
	StatusType ercd = E_OK;

	*State = tcb[ TaskID ].state;

	return ercd;
}

