#pragma once
#ifndef _ASYNC_H_
#define _ASYNC_H_

#include <stdbool.h>
#include <stdint.h>

// Async coroutine computation status.
typedef enum COROUTINE_STATES {
	COROUTINE_CONTINUE = false,
	COROUTINE_DONE     = true,
} async;

// Add async state field to user structs.
// Example:
//    typedef struct {
//        async_struct;
//        int32_t first;
//        int32_t second;
//    } user_t;
#define async_struct \
     uint_fast32_t _async_state

// Default async state type, optional to use.
typedef struct {
	async_struct;
} async_t;

// Set default async state to async struct.
// Example: 
//    async_t async_var(state);
//
// @param var Any struct with _async_state field.
#define async_new()                                      \
	&(async_t){                                      \
		._async_state = COROUTINE_CONTINUE,      \
	}
   
// Example:
//    async_t async_state;
//    async_init(async_state)
//
// @param state Any struct with _async_state field.
#define async_init(state) do {                           \
	(state)->_async_state = COROUTINE_CONTINUE;      \
} while (0)

// Mark the start of an async coroutine.
//
// @param state Any struct with _async_state field.
#define async_begin(state)                               \
	uint_fast32_t *_async_state = &(state)->_async_state; \
	switch (*_async_state) {                         \
	default:

// Mark the end of an async coroutine.
//
// @param state Any struct with _async_state field.
#define async_end                                        \
	*_async_state = COROUTINE_DONE;                  \
	case COROUTINE_DONE:                             \
		return COROUTINE_DONE;                   \
	}

// Switch to another coroutine.
#define async_sched                                      \
	*_async_state = __LINE__;                        \
	return COROUTINE_CONTINUE;                       \
	case __LINE__:

// Block progress until cond is true.
// Example:
//    await(io_completed() || timer_expired())
//
// @param cond Any bool value.
#define await(cond) \
	await_while(!(cond))

// Block progress until cond is false.
// Example:
//    await(io_not_completed() || timer_not_expired())
//
// @param cond Any bool value.
#define await_while(cond)                                \
	*_async_state = __LINE__;                        \
	case __LINE__:                                   \
		if (cond)                                \
			return COROUTINE_CONTINUE

// Exit from async coroutine
#define async_exit do {                                  \
	*_async_state = COROUTINE_DONE;                  \
	return COROUTINE_DONE;                           \
} while (0)

// Check if async coroutine done.
//
// @param state Any struct with _async_state field.
#define async_done(state) (                              \
	(state)->_async_state == COROUTINE_DONE          \
)

// Resume a running async coroutine and check for completion.
//
// @param f The async coroutine name.
// @param state Any struct with _async_state field.
#define async_call(f, state) (                           \
	async_done(state) || (f)(state)                  \
)

// Resume a running async coroutine with args and check for completion.
//
// @param f The async coroutine name.
// @param state Any struct with _async_state field.
#define async_call_vargs(f, state, ...) (                \
	async_done(state) || (f)(state, __VA_ARGS__)     \
)

#endif /* _ASYNC_H_ */
