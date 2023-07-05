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
semaphore_t *semaphore_new(uint_fast32_t c) {
	semaphore_t sem = {
		._count = c,
	};
	return &sem;
}

// Signal to semaphore.
//
// @param sem Ptr to semaphore_t.
inline void semaphore_signal(semaphore_t *sem) {
	++(sem)->_count;
}

// Wait until semaphore is free.
//
// @param sem Ptr to semaphore_t
#define semaphore_wait(sem) do {  \
	await((sem)->_count > 0); \
	--(sem)->_count;          \
} while (0)

#endif
