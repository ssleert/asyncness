#pragma once
#ifndef _SEMAPHORE_H_
#define _SEMAPHORE_H_

#include <stdint.h>
#include "async.h"

// Semaphore type.
typedef struct {
	uint_fast32_t _count;
} semaphore_t;

// Make new ptr to semaphore_t with passed count.
// Example:
//    semaphore_t *sem = semaphore_new(7);
//
// @param c Count for semaphore.
#define semaphore_new(c)           \
	&(semaphore_t){            \
		._count = c,       \
	}

// Signal to semaphore.
//
// @param sem Ptr to semaphore_t.
#define semaphore_signal(sem) do { \
	++(sem)->_count;           \
} while (0)

// Wait until semaphore is free.
//
// @param sem Ptr to semaphore_t
#define semaphore_wait(sem) do {   \
	await((sem)->_count > 0);  \
	--(sem)->_count;           \
} while (0)

#endif /* _SEMAPHORE_H_ */
