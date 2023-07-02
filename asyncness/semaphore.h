#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include <stdint.h>
#include "async.h"

typedef struct {
	uint_fast32_t _count;
} semaphore_t;

semaphore_t *semaphore_new(uint_fast32_t c) {
	semaphore_t sem = {
		._count = c,
	};
	return &sem
}

void semaphore_signal(semaphore_t *sem) {
	++(sem)->count
}

#define await_sem(s) do {      \
	await((s)->count > 0); \
	--(s)->count;          \
} while (0)

#endif
