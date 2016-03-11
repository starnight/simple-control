/*------------------------------------------------------------------------------
  Copyright (c) 2013 The Simple Controller Project. All rights reserved.
  Use of this source code is governed by a BSD-style license that can be found
  in the LICENSE file.
------------------------------------------------------------------------------*/

#include <stdio.h>
#include "controller.h"

#define ShowPID(pid) \
	printf("%f, %f, %f, %f, %f, %f, %f\n", \
		(float)pid.Kp, (float)pid.Ki, (float)pid.Kd, (float)pid.deltaT, \
		(float)pid.err, (float)pid.serr, (float)pid.perr)

#define ShowU(x, y, pid, u) \
	printf("err=%f-%f=%f, u=%f*%f+%f*%f*%f+%f*(%f-%f)/%f=%f\n", \
		(float)x, (float)y, (float)pid.err, (float)pid.Kp, (float)pid.err, \
		(float)pid.Ki, (float)pid.serr, (float)pid.deltaT, \
		(float)pid.Kd, (float)pid.err, (float)pid.perr, (float)pid.deltaT, \
		(float)u)

int main (void) {
	SC_BASIC_DATATYPE u = 0;
	SC_BASIC_DATATYPE x = 2;
	SC_BASIC_DATATYPE y = 6;
	SC_BASIC_DATATYPE dt = 1;
	SC_PID pid;

	/*---------------------------Test PID---------------------------*/
	printf("PID control: ");
	SCInitPID(&pid, 2, 3, 4, dt);

	ShowPID(pid);
	u = SCPIDCon(x, y, &pid);
	ShowU(x, y, pid, u);

	/*---------------------------Test PI----------------------------*/
	printf("PI control: ");
	SCInitPID(&pid, 2, 3, 0, dt);

	ShowPID(pid);
	u = SCPICon(x, y, &pid);
	ShowU(x, y, pid, u);

	/*---------------------------Test PD----------------------------*/
	printf("PD control: ");
	SCInitPID(&pid, 2, 0, 4, dt);

	ShowPID(pid);
	u = SCPDCon(x, y, &pid);
	ShowU(x, y, pid, u);

	/*---------------------------Test ID----------------------------*/
	printf("ID control: ");
	SCInitPID(&pid, 0, 3, 4, dt);

	ShowPID(pid);
	u = SCIDCon(x, y, &pid);
	ShowU(x, y, pid, u);

	/*---------------------------Test P-----------------------------*/
	printf("P control: ");
	SCInitPID(&pid, 2, 0, 0, dt);

	ShowPID(pid);
	u = SCPDCon(x, y, &pid);
	ShowU(x, y, pid, u);

	/*---------------------------Test upper-------------------------*/
	u = SCUpBandCon(x, y);
	printf("Upper bound control: ul=%f, vaule=%f, u=%f\n", x, y, u);

	/*---------------------------Test lower-------------------------*/
	u = SCLowBandCon(x, y);
	printf("Lower bound control: dl=%f, vaule=%f, u=%f\n", x, y, u);

	/*---------------------------Test band--------------------------*/
	u = SCBandCon(x, y, 1);
	printf("Band control: ul=%f, dl=%f, vaule=%f, u=%f\n", x, y, 1.0, u);

	return 0;
}
