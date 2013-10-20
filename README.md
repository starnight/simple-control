Simple Controller
=================

It is a simple controlling library which provides PID and Band control APIs.

Find more information from the [Wiki](https://github.com/starnight/simple-controller/wiki "Simple Controller Wiki").

Have the code
-------------

You can have it from the GitHub: [https://github.com/starnight/simple-controller](https://github.com/starnight/simple-controller "Simple Controller")

Or, clone the source code from GitHub.

```
git clone git://github.com/starnight/simple-controller.git
```

Demo usage
----------

Before compile this library, you must have the compiler, for example GCC, of
course.  There is a demo code which is '[demo.c](demo.c)'.  You can just use the
'make' utility which will compile the codes according to the 'Makefile'.  Then
execute the program 'demo.bin' for demo.  I also use the program to test the
APIs that I wrote working right or wrong.

```
$ make
$ ./demo.bin
```

The program will do the demo many rounds.  
The first round tests the PID control.  
Second round tests the PI control.  
Third round tests the PD control.  
Forth round tests the ID control.  
Fifth round tests the P control.  
Sixth round tests the upper bound control.  
Seventh round tests the lower bound control.  
Eighth round tests the band control.

Quick Start
-----------

This example demos the PID control.
It will initial the pid structure with Kp, Ki, Kd factors.
Then do the PID control algorithm.

Create a C file where the main function located.

```C
#include <stdio.h>
#include "control.h"

int main (void) {
	int16_t u = 0;
	int16_t set = 2;
	int16_t feedback = 6;
	SC_PID pid;

	printf("PID control: ");
	/* Initial the pid with factors. */
	SCInitPID(&pid, 2, 3, 4);

	printf("%d, %d, %d, %d, %d, %d\n",
		(int)pid.Kp, (int)pid.Ki, (int)pid.Kd,
		(int)pid.err, (int)pid.serr, (int)pid.perr);

	/* PID control. */
	u = SCPIDCon(set, feedback, &pid);

	printf("err=%d-%d=%d, u=%d*%d+%d*%d+%d*(%d-%d)=%d\n",
		(int)feedback, (int)set, (int)pid.err, (int)pid.Kp, (int)pid.err,
		(int)pid.Ki, (int)pid.serr,
		(int)pid.Kd, (int)pid.err, (int)pid.perr,
		(int)u);

	return 0;
}
```

License
-------

Simple Controller's code uses the BSD license, see our '[LICENSE.md](https://github.com/starnight/simple-controller/blob/master/LICENSE.md "LICENSE.md")' file.

Reference
---------
* Wiki PID controller: http://en.wikipedia.org/wiki/PID_controller
* ATMEL AVR221: Discrete PID controller: http://www.atmel.com/images/doc2558.pdf
