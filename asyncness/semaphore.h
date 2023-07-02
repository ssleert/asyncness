#pragma once
#ifndef _SEMAPHORE_H_
#define _SEMAPHORE_H_

#include <stdint.h>
#include "async.h"

typedef struct {
	uint_fast32_t _count;
} semaphore_t;

semaphore_t *semaphore_new(uint_fast32_t c) {
	semaphore_t sem = {
		._count = c,
	};
	return &sem;
}

inline void semaphore_signal(semaphore_t *sem) {
	++(sem)->count;
}

#define semaphore_wait(sem) do { \
	await((sem)->count > 0); \
	--(sem)->count;          \
} while (0)

#endif
