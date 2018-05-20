#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef void* Generic;
typedef long long Integer;

#include "heap.h"
#include "list.h"

int cmp_func(int a, int b){
	return a<b;
}

Integer main(void){
	srand(time(NULL));

	Integer i, size, comparisons = 0;
	printf("Diga o tamanho da fila: \n");
	scanf("%lld", &size);

	HEAP *new_heap = HEAP_Create(size, cmp_func);
	LIST *new_list = LIST_Create(cmp_func);

	FILE *enqueue_heap, *enqueue_list, *dequeue_heap, *dequeue_list;

	enqueue_heap = fopen("enqueue_heap", "w");
	for(i = 0; i < size; ++i){
		comparisons = 0;
		HEAP_Enqueue(new_heap, rand(), &comparisons);
		fprintf(enqueue_heap, "%lld\n", comparisons);
		comparisons = 0;
	}
	fclose(enqueue_heap);

	enqueue_list = fopen("enqueue_list", "w");
	for(i = 0; i < size; ++i){
		comparisons = 0;
		LIST_Enqueue(new_list, rand(), &comparisons);
		fprintf(enqueue_list, "%lld\n", comparisons);
		comparisons = 0;
	}
	fclose(enqueue_list);

	dequeue_heap = fopen("dequeue_heap", "w");
	for(i = 0; i < size; ++i){
		comparisons = 0;
		HEAP_Pop(new_heap, &comparisons);
		fprintf(dequeue_heap, "%lld\n", comparisons);
		comparisons = 0;
	}
	fclose(dequeue_heap);

	dequeue_list = fopen("dequeue_list", "w");
	for(i = 0; i < size; ++i){
		comparisons = 0;
		LIST_Pop(new_list, &comparisons);
		fprintf(dequeue_list, "%lld\n", comparisons);
		comparisons = 0;
	}
	fclose(dequeue_list);

	return 0;
}