#include <stdio.h>
#include <stdbool.h>
#include "../asyncness/async.h"

async coroutine1(async_t *pt) {
	// coz coroutines is stackless
	// we cant save vars on stack
	// all vars that should be saved
	// between scheds must be static
	// or allocated on heap
	static int counter = 0, i;

	// before any async operations
	// u should init coroutine for scheduler
	async_begin(pt);
	for (i = 0; i < 10; i++) {
		puts("from 1 protothread");

		// sched to another coroutine
		async_sched;

		++counter;
		printf("1 counter = %d\n", counter);

		async_sched;
		puts("from 1 protothread after context change");
	}

	puts("coroutine 1 stoped");

	// stop async on coroutine end
	async_end;
}

async coroutine2(async_t *pt) {
	static int counter = 0, i;
	async_begin(pt);
	for (i = 0; i < 10; i++) {
		puts("from 2 protothread");
		async_sched;
		++counter;
		printf("2 counter = %d\n", counter);
		async_sched;
		puts("from 2 protothread after context change");
	}
	puts("coroutine 2 stoped");
	async_end;
}

int main(void) {
	// declare states for coroutines
	// async_var() macros automatically
	// sets zero async state to var
	async_t async_var(pt1), async_var(pt2);

	// also u can use async_init(state)
	// it also useful for own async structs
	async_init(&pt1);
	async_init(&pt2);

	// start loop with concurrent coroutines
	// that sched each other
	while (!(
		// the loop will run until 
		// both coroutines are complete
		coroutine1(&pt1) & coroutine2(&pt2)
		// why do we use a binary operator? 
		// the compiler optimizes boolean operators (||, &&) 
		// and the second coroutine simply will not run 
		// if the first is not completed
		//
		// links:
		//   https://en.wikipedia.org/wiki/Logic_optimization
		//   https://stackoverflow.com/questions/28180294/c-logical-expression-optimization
	));
	return 0;
}
