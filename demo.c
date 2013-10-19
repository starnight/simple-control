/*------------------------------------------------------------------------------
  Copyright (c) 2013 The Simple Controller Project. All rights reserved.
  Use of this source code is governed by a BSD-style license that can be found
  in the LICENSE file.
------------------------------------------------------------------------------*/

#include <stdio.h>
#include "control.h"

#define ShowPID(pid) \
	printf("%d, %d, %d, %d, %d, %d\n", \
		(int)pid.Kp, (int)pid.Ki, (int)pid.Kd, \
		(int)pid.err, (int)pid.serr, (int)pid.perr)

#define ShowU(x, y, pid, u) \
	printf("err=%d-%d=%d, u=%d*%d+%d*%d+%d*(%d-%d)=%d\n", \
		(int)y, (int)x, (int)pid.err, (int)pid.Kp, (int)pid.err, \
		(int)pid.Ki, (int)pid.serr, \
		(int)pid.Kd, (int)pid.err, (int)pid.perr, \
		(int)u)

int main (void) {
	int16_t u = 0;
	int16_t x = 2;
	int16_t y = 6;
	SC_PID pid;

	/*---------------------------Test PID---------------------------*/
	printf("PID control: ");
	SCInitPID(&pid, 2, 3, 4);

	ShowPID(pid);
	u = SCPIDCon(x, y, &pid);
	ShowU(x, y, pid, u);

	/*---------------------------Test PI----------------------------*/
	printf("PI control: ");
	SCInitPID(&pid, 2, 3, 0);

	ShowPID(pid);
	u = SCPICon(x, y, &pid);
	ShowU(x, y, pid, u);

	/*---------------------------Test PD----------------------------*/
	printf("PD control: ");
	SCInitPID(&pid, 2, 0, 4);

	ShowPID(pid);
	u = SCPDCon(x, y, &pid);
	ShowU(x, y, pid, u);

	/*---------------------------Test ID----------------------------*/
	printf("ID control: ");
	SCInitPID(&pid, 0, 3, 4);

	ShowPID(pid);
	u = SCIDCon(x, y, &pid);
	ShowU(x, y, pid, u);

	/*---------------------------Test P-----------------------------*/
	printf("P control: ");
	SCInitPID(&pid, 2, 0, 0);

	ShowPID(pid);
	u = SCPDCon(x, y, &pid);
	ShowU(x, y, pid, u);

	/*---------------------------Test upper-------------------------*/
	u = SCUpBandCon(x, y);
	printf("Upper bound control: ul=%d, vaule=%d, u=%d\n", x, y, u);

	/*---------------------------Test lower-------------------------*/
	u = SCLowBandCon(x, y);
	printf("Lower bound control: dl=%d, vaule=%d, u=%d\n", x, y, u);

	/*---------------------------Test band--------------------------*/
	u = SCBandCon(x, y, 1);
	printf("Band control: ul=%d, dl=%d, vaule=%d, u=%d\n", x, y, 1, u);

	return 0;
}
