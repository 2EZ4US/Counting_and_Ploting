#ifndef _HEAP
#define _HEAP

typedef struct HEAP{
	Generic *arr;
	Integer size;
	Integer max_size;

	Generic (*cmp_func)();
}HEAP;

Generic HEAP_Create(Integer size, Generic (*cmp_func)()){
	HEAP *new_heap = (HEAP *) malloc(sizeof(HEAP));
	new_heap->arr = (Generic *) calloc(size + 1, sizeof(Generic));
	new_heap->size = 0;
	new_heap->max_size = size;
	new_heap->cmp_func = cmp_func;

	return new_heap;
}

Generic HEAP_Get_Parent(Integer child){
	return child>>1;
}

Generic HEAP_Get_Left(Integer parent){
	return parent<<1;
}

Generic HEAP_Get_Right(Integer parent){
	return (parent<<1)+1;
}

Generic HEAP_Is_Empty(HEAP *heap){
	return heap->size == 0;
}

Generic HEAP_Comparison(HEAP *heap, Integer i, Integer j){
	return heap->cmp_func(heap->arr[i], heap->arr[j]);
}

Generic HEAP_Swap(HEAP *heap, Integer i, Integer j){
	Generic auxiliar = heap->arr[i];
	heap->arr[i] = heap->arr[j];
	heap->arr[j] = auxiliar;
}

Generic HEAP_Heapify(HEAP *heap, Integer index, Integer *comparisons){
	Integer swap_index = index;
	Integer left_index = HEAP_Get_Left(index);
	Integer right_index = HEAP_Get_Right(index);

	if(left_index <= heap->size && HEAP_Comparison(heap, left_index, swap_index)){
		swap_index = left_index;
	}
	if(right_index <= heap->size && HEAP_Comparison(heap, right_index, swap_index)){
		swap_index = right_index;
	}
	if(swap_index != index){
		HEAP_Swap(heap, swap_index, index); (*comparisons)++;
		HEAP_Heapify(heap, swap_index, comparisons);
	}
}

Generic HEAP_Enqueue(HEAP *heap, Generic element, Integer *comparisons){
	if(heap->size == heap->max_size){
		return 0;
	}

	heap->arr[++heap->size] = element;

	Integer child = heap->size;
	Integer parent = HEAP_Get_Parent(child);

	while(parent >= 1 && HEAP_Comparison(heap, child, parent)){
		HEAP_Swap(heap, child, parent); (*comparisons)++;
		child = parent;
		parent = HEAP_Get_Parent(child);
	}
}

Generic HEAP_Peek(HEAP *heap){
	if(HEAP_Is_Empty(heap)){
		return 0;
	}

	return heap->arr[1];
}

Generic HEAP_Pop(HEAP *heap, Integer *comparisons){
	if(HEAP_Is_Empty(heap)){
		return 0;
	}
	
	Generic dequeued = heap->arr[1];
	HEAP_Swap(heap, 1, heap->size--);  (*comparisons)++;
	HEAP_Heapify(heap, 1, comparisons);

	return dequeued;
}

Generic HEAP_Destroy(HEAP *heap){
	free(heap->arr);
	free(heap);
}

#endif