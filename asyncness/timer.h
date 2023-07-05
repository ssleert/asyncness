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

// Get current time in seconds.
static int _get_time(void)

// Timer type.
typedef struct {
	int start;
	int interval;
} timer_t;

// Check if time expired.
//
// @param t Ptr to timer_t.
inline bool timer_expired(timer_t *t) {
	return _get_time() - t->start >= t->interval;
}

// Set timer to interval in miliseconds
//
// @param t Ptr to timer_t.
// @param interval Interval in miliseconds.
inline void timer_set(timer_t *t, int interval) {
	t->interval = interval;
	t->start = _get_time();
}

static inline int _get_time(void) {
#ifdef _WIN32
	return (int)GetTickCount();
#else
	struct timeval tv;
	gettimeofday(&tv, NULL); 
	return tv.tv_sec * 1000 + tv.tv_usec / 1000;
#endif
}

