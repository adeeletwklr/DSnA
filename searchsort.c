#include <stdio.h>
#include <stdlib.h>

struct list {
	int val;
	struct list *next;
	struct list *prev;
};

struct list *head = NULL;
struct list *cur = NULL;

void add(int n){
struct list *l;
	if(head == NULL){
		l = (struct list *)malloc(sizeof(struct list));
		l->val = n;
		l->next = NULL;
		l->prev = NULL;
		head = cur = l;		
	}
	else{	
		l = (struct list *)malloc(sizeof(struct list));
		l->val = n;
		l->next = NULL;
		l->prev = cur;
		cur->next = l;
		cur = l;		
	}
}

void free_list(struct list *l){
struct list *tmp;
	while(l != NULL){
		tmp = l->next;		
		free(l);		
		l = tmp;
	}	
}

void traverse(struct list *l){
struct list *t;
	for(t = l; t != NULL; t = t->next){
		printf("%d ", t->val);
	}
	printf("\n");
}

void bubble_sort(struct list *l){
struct list *b,*bb;
int tval, n = 0;
	for(bb = l; bb->next != NULL; bb = bb->next){
		for(b = l; b->next != NULL; b = b->next){
			if(b->val > b->next->val){
				tval = b->next->val;
				b->next->val = b->val;
				b->val = tval;
			}
			n++;
		}
	}
	printf("Bubble Sort: Complexity is On2(nxn) => Iterations %d \n", n);
}

/* find least min in list
   put it on the beginning	
   64 25 12 22 11 
   11 64 25 12 22
   11 12 64 25 22
   11 12 22 64 25
   11 12 22 25 64   */
void selection_sort(struct list *l){
struct list *o,*i,*tmp;
int min, tval;
	o = l;
	i = l->next;
	while(o != NULL){
		/* suppose first element is min value */
		min = o->val;
		/* find least min value in the list */
		while(i != NULL) {			
			/* If we have a new min value */		   
			if(i->val < min){
				/* set new min value */
				min = i->val;
				/* store node to use in swapping later */
				tmp = i;
			}
			i = i->next;
		}
		/* If we have a new min value */		   
		if(min != o->val){
			/* Swap current value with new min */
			tval = o->val;
			o->val = min;
			tmp->val = tval;
		}
		o = o->next;
		i = o;
	}
}

int main(){
int i;

	for(i = 0; i < 10; i++)
		add(random() % 100);
	traverse(head);
	selection_sort(head);
	traverse(head);
	
	free_list(head);
	return 0;
}