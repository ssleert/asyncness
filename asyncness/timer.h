#pragma once
#ifndef _TIMER_H_
#define _TIMER_H_

#ifdef _WIN32
#	include <windows.h>
#else
#	include <unistd.h>
#	include <sys/time.h>
#endif

#include <stdbool.h>

#include "async.h"

static int get_time(void)

typedef struct {
	int start;
	int interval;
} timer_t;

inline bool timer_expired(timer_t *t) {
	return get_time() - t->start >= t->interval;
}

inline void timer_set(timer_t *t, int interval) {
	t->interval = interval;
	t->start = get_time();
}

static int get_time(void) {
#ifdef _WIN32
	return (int)GetTickCount();
#else
	struct timeval tv;
	struct timezone tz;   
	gettimeofday(&tv, &tz); 
	return tv.tv_sec * 1000 + tv.tv_usec / 1000;
#endif
}

