AdvThreadPool
=============

Qt-based advanced thread pool

Main features in compare with QThreadPool: 

1. put all tasks in the queue, does not block main app. when number of tasks > number of threads. 

2. thread priority can be changed for any job

3. 2 modes of the work: 
   FIFO - first in, first out
   PRIO - execute job in the internal queue in the order of priority
