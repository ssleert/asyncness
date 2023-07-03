#pragma once
#ifndef _ASYNC_H_
#define _ASYNC_H_

#include <stdbool.h>
#include <stdint.h>

typedef enum COROUTINE_STATES {
	COROUTINE_CONTINUE = false,
	COROUTINE_DONE     = true,
} async;

#define async_struct \
     uint_fast32_t _async_state

typedef struct {
	async_struct;
} async_t;

#define async_init(state) do {                           \
	(state)->_async_state = COROUTINE_CONTINUE;      \
} while (0)

#define async_var(var)                                   \
	var = {                                          \
		._async_state = COROUTINE_CONTINUE,      \
	}

#define async_begin(state)                               \
	unsigned *_async_state = &(state)->_async_state; \
	switch (*_async_state) {                         \
	default:

#define async_end                                        \
	*_async_state = COROUTINE_DONE;                  \
	case COROUTINE_DONE:                             \
		return COROUTINE_DONE;                   \
	}

#define async_sched                                      \
	*_async_state = __LINE__;                        \
	return COROUTINE_CONTINUE;                       \
	case __LINE__:

#define await(cond) \
	await_while(!(cond))

#define await_while(cond)                                \
	*_async_state = __LINE__;                        \
	case __LINE__:                                   \
		if (cond)                                \
			return COROUTINE_CONTINUE

#define async_exit do {                                  \
	*_async_state = COROUTINE_DONE;                  \
	return COROUTINE_DONE;                           \
} while (0)

#define async_done(state) (                              \
	(state)->_async_state == COROUTINE_DONE          \
)

#define async_call(f, state) (                           \
	async_done(state) || (f)(state)                  \
)

#define async_call_vargs(f, state, ...) (                \
	async_done(state) || (f)(state, __VA_ARGS__)     \
)

#endif
