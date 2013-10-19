/*------------------------------------------------------------------------------
  Copyright (c) 2013 The Simple Controller Project. All rights reserved.
  Use of this source code is governed by a BSD-style license that can be found
  in the LICENSE file.
------------------------------------------------------------------------------*/

#ifndef __SIMPLE_CONTROL_H__
#define __SIMPLE_CONTROL_H__

#include <stdint.h>

/* Define basic data type for controlling.*/
#ifndef SC_BASIC_DATATYPE
#define SC_BASIC_DATATYPE int16_t
#endif

/* Force inline. */
#if SC_ALWAYSINLINE == 1
#define _SC_ALWAYSINLINE __attribute__((always_inline))
#else
#define _SC_ALWAYSINLINE
#endif

/* Define the base PID structure. */
typedef struct _SC_pid {
	SC_BASIC_DATATYPE Kp;
	SC_BASIC_DATATYPE Ki;
	SC_BASIC_DATATYPE Kd;
	SC_BASIC_DATATYPE err;
	SC_BASIC_DATATYPE serr;
	SC_BASIC_DATATYPE perr;
} SC_PID;

/* Initial the PID. */
inline void SCInitPID (
	SC_PID *pid,
	SC_BASIC_DATATYPE p,
	SC_BASIC_DATATYPE i,
	SC_BASIC_DATATYPE d) {
	/* Set PID factors. */
	pid->Kp = p;	pid->Ki = i;	pid->Kd = d;
	/* Zero the initial values. */
	pid->err = 0;	pid->serr = 0;	pid->perr = 0;
	return;
}

/* PID control. */
inline _SC_ALWAYSINLINE SC_BASIC_DATATYPE SCPIDCon(
	SC_BASIC_DATATYPE x,
	SC_BASIC_DATATYPE y,
	SC_PID *pid ) {
	/* Move the previous error. */
	pid->perr = pid->err;
	/* Have the current error. */
	pid->err = y - x;
	/* Summarize the error. */
	pid->serr += pid->err;
	return pid->Kp*pid->err + pid->Ki*pid->serr + pid->Kd*(pid->err-pid->perr);
}

/* PI control. */
inline _SC_ALWAYSINLINE SC_BASIC_DATATYPE SCPICon(
	SC_BASIC_DATATYPE x,
	SC_BASIC_DATATYPE y,
	SC_PID *pid) {
	/* Have the current error. */
	pid->err = y - x;
	/* Summarize the error. */
	pid->serr += pid->err;
	return pid->Kp * pid->err + pid->Ki * pid->serr;
}

/* PD control. */
inline _SC_ALWAYSINLINE SC_BASIC_DATATYPE SCPDCon(
	SC_BASIC_DATATYPE x,
	SC_BASIC_DATATYPE y,
	SC_PID *pid) {
	/* Move the previous error. */
	pid->perr = pid->err;
	/* Have the current error. */
	pid->err = y - x;
	return pid->Kp * pid->err + pid->Kd * (pid->err - pid->perr);
}

/* ID control. */
inline _SC_ALWAYSINLINE SC_BASIC_DATATYPE SCIDCon(
	SC_BASIC_DATATYPE x,
	SC_BASIC_DATATYPE y,
	SC_PID *pid) {
	/* Move the previous error. */
	pid->perr = pid->err;
	/* Have the current error. */
	pid->err = y - x;
	/* Summarize the error. */
	pid->serr += pid->err;
	return pid->Ki * pid->serr + pid->Kd * (pid->err - pid->perr);
}

/* P control. */
inline _SC_ALWAYSINLINE SC_BASIC_DATATYPE SCPCon(
	SC_BASIC_DATATYPE x,
	SC_BASIC_DATATYPE y,
	SC_PID *pid) {
	/* Have the current error. */
	pid->err = y - x;
	return pid->Kp * pid->err;
}

/* Up bound control. */
#define SCUpBandCon(ul, v) ((ul > v) ? v : ul)
/* Lower bound control. */
#define SCLowBandCon(dl, v) ((dl < v) ? v : dl)
/* Band control. */
#define SCBandCon(ul, dl, v) (SCUpBandCon(ul, SCLowBandCon(dl, v)))

#endif
