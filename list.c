#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h> 

struct list {
	int val;
	struct list *next;
	struct list *prev;	/* Insertion sort needs it for reverse iteration, */
};

static struct list *head;
static struct list *cur;
static int ins_sort_n;
static int mrg_sort_n;

struct list *add_list(unsigned int n)
{
	int i;
	struct list *l;

	if (head == NULL) {
		head = (struct list *)malloc(sizeof(struct list));
		head->val = n;
		head->next = NULL;
		head->prev = NULL;
		cur = head;
	}
	else {
		l = (struct list *)malloc(sizeof(struct list));
		l->val = n;
		l->next = NULL;		
		l->prev = cur;		
		cur->next = l;
		cur = l;
	}

	return cur;
}

traverse_list(struct list *l)
{
	int i = 0;

	while(l != NULL) {
		printf("val[%d] = %d \n", i++, l->val);
		l = l->next;
	}
	
}

/* My implementation using one while loop 
   but complex logic + involved debuging */
sort_list(struct list *l) 
{
	int x;
	struct list *tmp;
	int swapped = 1;
	int done = 0;
	int n = 0;

	while (done == 0) {	
		//swapped = 0;
		n++;
		if ((l->next != NULL) && (l->val > l->next->val)) {	// Perform Swap like Bubble Sort
			x = l->next->val;
			l->next->val = l->val;					
			l->val = x;
			swapped = 0;			
		}
		if (l->next == NULL) {
			if (swapped == 0) {
				l = head;
				swapped = 1;
			} else
				done = 1;
		} else
			l = l->next;		
	}
	printf("Complexity of algorithm: Times=%d Space=O(n)\n", n);
}

/* Standard implementation using two loops
   simple + no debugging invlovded. Run on
   1st time */
bubble_sort_list(struct list *l)
{
	int x,y;
	struct list *tmp;
	int swapped = 1;
	int n = 0;
	time_t t1, t2;
	int elapsedTime;

	t1 = time(NULL);	
	/* Complexity of algorithm = Outer loop n times + inner loop n times
	   Avg/Best/Worst complexity is O(n2) because it iterates n x n times */
	while (swapped != 0) {
		swapped = 0;
		for (y = 1, l = head; l->next != NULL; y++, l=l->next) {
			n++;
			if (l->val > l->next->val) {	// Perform Swap like Bubble Sort
				x = l->next->val;
				l->next->val = l->val;
				l->val = x;
				swapped = 1;
			}
		}
	}
	t2 = time(NULL);
	
	// compute and print the elapsed time in millisec
	elapsedTime = (t2 - t1) % 60;	//sec
	elapsedTime = elapsedTime * 1000;	//msec
	printf("Complexity of bubble sort algorithm: Times=%d Space=O(n) ElapsedTime=%d ms\n", n, elapsedTime);
}

/* Standard implementation of Selection sort
   Fewer swaping/writes than insertion sort  */
selection_sort(struct list *l)
{
	int min,n = 0;
	struct list *tmp, *outer;

	outer = head;
	/* Complexity of algorithm = Outer loop n times + inner loop n,n-1,n-2.. times
	   Theoratical complexity would be O(n2) because then it would be equation invloving n,n-1,n-2...
	   Selection sort is better than bubble sort since it perform less iteration */
	while( outer != NULL ) {
		min = outer->val;
		l = outer;
		while ( l->next != NULL ) {
			n++;
			l = l->next;
			if (l->val < min) {
				min = l->val;
				tmp = l;
			}		
		}
		if (min != outer->val) {	/* If new value is less than min then swap */
			tmp->val = outer->val;
			outer->val = min;	
		}
		outer = outer->next;
	}
	printf("Complexity of selection sort algorithm: Times=%d Space=O(n)\n", n);
}

/* My implementation using single endded linked list took days 
   complex logic + involved debuging + one following problem */

/* One problem it always check inserted value with all elements 
   But insertion sort only check inserted value with previous 
   element.If it is greater than prev value then it stop and
   check next element.If it is less then it check all 
   previous element and perform the shift. */

insertion_sort(int ins)
{
	int c = 0,save = 0;
	struct list *tmp,*tmp2;

	tmp = head;

	/* Search inserted value position in list */
	/* Loop until inserted value is less than current value of list */
	while (tmp != cur && ins >= tmp->val ) {
		tmp = tmp->next;
		ins_sort_n++;
	}
	
	/* Starting from inserted value position shift list till inserted value */
	if (tmp != cur) {
		tmp2 = tmp;
		/* Shift in sinle ended linked list starting from head (b=save, a=>b||save=>b)  */
		while (tmp != cur) {
			save = tmp->next->val;
			if (c == 0)
				tmp->next->val = tmp->val;
			else 
				tmp->next->val = c;
			tmp = tmp->next;
			c = save;
			ins_sort_n++;
		}
		/* Copy inserted value @ inserted value position */
		tmp2->val = save;
	}
	
	/* Traverse list i.e. from 3rd element....last element */
	if (cur->next != NULL) {
		cur = cur->next;		
		insertion_sort(cur->val);
	}
	else
		printf("Complexity of algorithm: Times=%d Space=O(n)\n", ins_sort_n);

}

/* Standard implementation using one loop
   simple + no debugging invlovded. */

reverse_insertion_sort(int ins)
{
	int c = 0,save = 0;
	struct list *tmp,*tmp2;
	int shft = 0;

	tmp = cur->prev;

	/* Search inserted value position in list */
	/* Loop until inserted value is less than prev element of list */
	while (tmp != NULL && ins < tmp->val ) {
		tmp->next->val = tmp->val;
		tmp = tmp->prev;
		ins_sort_n++;
		shft = 1;
	}
	
	if (shft) {
		if (tmp == NULL)
			head->val = ins;
		else
			tmp->val = ins;
	}
	
	/* Traverse list i.e. from 3rd element....last element */
	if (cur->next != NULL) {
		cur = cur->next;		
		ins_sort_n++;
		reverse_insertion_sort(cur->val);
	}
	else
		printf("Complexity of insertion sort algorithm: Times=%d Space=O(n)\n", ins_sort_n);
}

/* merge the lists.. */
struct list *merge(struct list *head_one, struct list *head_two) {
	struct list *head_three;

	//mrg_sort_n++;
	if(head_one == NULL) 
		return head_two;

	if(head_two == NULL) 
		return head_one;

	if(head_one->val < head_two->val) {
		head_three = head_one;
		head_three->next = merge(head_one->next, head_two);
	} else {
		head_three = head_two;
		head_three->next = merge(head_one, head_two->next);
	}

	return head_three;
}


struct list *merge_sort(struct list *h)
{
	struct list *slow;
	struct list *fast;

	if((h == NULL) || (h->next == NULL)) 
		return h;

	slow = h;
	fast = h->next;
	/* Make last two nodes seperate by breaking next link with NULL 
	   1->2->3->4->5 => 1->2->3->4 5 ...=> 1 2 3 4 5	*/
	while((fast != NULL) && (fast->next != NULL)) {
		mrg_sort_n++;
		h = h->next;
		fast = h->next->next;
	}
	fast = h->next;
	h->next = NULL;

	return merge(merge_sort(slow), merge_sort(fast));			
}



main() 
{
	struct list *l;
	int i;
	
	printf("Welcome to the re-vival of Link Lists...\n");
	for (i = 0; i < 5; i++)
		l = add_list(random() % 100);
	traverse_list(head);
	
	/* start with val, swap with next val, stop when no swap  */
	//bubble_sort_list(head); 
	
	/* start with min, find new min, swap new min with min => 4,3,2,1 -> 1,3,2,4 -> 1,2,3,4 */ 
	//selection_sort(head); 	
	
	/* start with val, find its position, put at its position */
	//cur = head->next;
	//insertion_sort(head->next->val);
	//cur = head->next;
	//reverse_insertion_sort(head->next->val); 

	head = merge_sort(head);
	printf("Complexity of merge sort algorithm: Times=%d Space=O(n)\n", mrg_sort_n);
	printf(" Sorted List Oh la la...\n");
	traverse_list(head);
}
