#include <stdlib.h>
#include "TASK/task.h"
void taskStart() _task_ 0
{ 
	setup();
	blink(4);
	
	os_delete_task(0);
	
}
