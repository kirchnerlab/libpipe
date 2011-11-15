/*
 * getTimeOfDay.h
 *
 * Copyright (c) 2011 David Sichau
 *                    Marc Kirchner
 */

#ifndef GETTIMEOFDAY_H_
#define GETTIMEOFDAY_H_


#ifdef _WIN32
#include <time.h>
#include <windows.h> //I've ommited this line.
#if defined(_MSC_VER) || defined(_MSC_EXTENSIONS)
#define DELTA_EPOCH_IN_MICROSECS  11644473600000000Ui64
#else
#define DELTA_EPOCH_IN_MICROSECS  11644473600000000ULL
#endif

struct timezone
{
    int tz_minuteswest; /* minutes W of Greenwich */
    int tz_dsttime; /* type of dst correction */
};

int gettimeofday(struct timeval *tv, struct timezone *tz);

#else
#include <sys/time.h>
#endif

#endif /* GETTIMEOFDAY_H_ */
