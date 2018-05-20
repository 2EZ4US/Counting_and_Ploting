#ifndef _LIST
#define _LIST

typedef struct NODE{
	Generic data;

	struct NODE *next;
	struct NODE *previous;
}NODE;

typedef struct LIST{
	Generic (*cmp_func)();

	struct NODE *head;
	struct NODE *tail;
}LIST;

Generic LIST_Create(Generic (*cmp_func)()){
	LIST *new_list = (LIST *) malloc(sizeof(LIST));

	new_list->head = NULL;
	new_list->tail = NULL;
	new_list->cmp_func = cmp_func;

	return new_list;
}

Generic LIST_Is_Empty(LIST *list){
	return (list->head == NULL);
}

Generic LIST_Enqueue(LIST *list, Generic data, Integer *comparisons){
	NODE *new_node = (NODE *) malloc(sizeof(NODE));
	new_node->data = data;

	if(list->head == NULL){
		new_node->next = NULL;
		new_node->previous = NULL;

		list->head = new_node;
		list->tail = new_node;

		(*comparisons)++;
	}
	else{
		if(list->cmp_func(data, list->head->data)){
			list->head->previous = new_node;
			
			new_node->next = list->head;
			new_node->previous = NULL;

			list->head = new_node;

			(*comparisons)++;
		}
		else{
			NODE *curr = list->head->next;

			while(curr != NULL){
				if(list->cmp_func(data, curr->data)){
					new_node->next = curr;
					new_node->previous = curr->previous;

					curr->previous->next = new_node;
					curr->previous = new_node;

					return;
				}

				curr = curr->next;

				(*comparisons)++;
			}

			list->tail->next = new_node;

			new_node->previous = list->tail;
			new_node->next = NULL;

			list->tail = new_node;
		}

	}
}

Generic LIST_Peek(LIST *list){
	return list->head->data;
}

Generic LIST_Pop(LIST *list, Integer *comparisons){
	if(LIST_Is_Empty(list)){
		return 0;
	}

	NODE *dequeued = list->head;

	if(list->head->next == NULL){
		list->head = NULL;
		list->tail = NULL;
	}
	else{
		list->head = list->head->next;
		list->head->previous = NULL;
	}

	(*comparisons)++;

	return dequeued->data;
}


#endif