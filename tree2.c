#include <stdio.h>
#include <stdlib.h>

struct tree {
    int val;
    struct tree *left;
    struct tree *right;
};

struct tree *head;
struct tree *cur;

void make_tree(int e) {
    struct tree *t,*tmp;
    
    t = (struct tree *)malloc(sizeof(struct tree));
    t->val = e;
    t->left = NULL;
    t->right = NULL;
    
    if(head == NULL) {
        head = t;       
    }
    else {
        cur = head;
        while(cur != NULL) {
            tmp = cur;
            if(e < cur->val)
                cur = cur->left;
            else
                cur = cur->right;
        }
    }
        
    if(e < tmp->val)
        tmp->left = t;
    else
        tmp->right = t;
    
}

void print_tree(struct tree *t) {
    
    if(t) {
        printf("%d ", t->val);
        print_tree(t->left);
        print_tree(t->right);
    }
    
}

main()
{
   int val = 2;
   int xbit;
   int i;
   
   for(i = 0; i < 20; i++) {
    xbit = (val & 1) ^ ((val>>1) & 1);    // bit1 xor bit2
    val = val >> 1;
    val = (val & 0xff) | (xbit << 4);
   
    //printf("%d %d %d\n", (val & 0x01), (val & 0x02), ((val >> 1) & 0x01));
    printf(" %d ", val);
    make_tree(val);
   }
   printf("\n");
   
   print_tree(head);
   return 0;
}

/*
output:
	vals: 17  24  12  6  19  9  20  10  21  26  29  30  31  15  7  3  1  16  8  4 
tree: 17 12 6 3 1 4 9 7 8 10 15 16 24 19 20 21 26 29 30 31 

NOT YET CLEAR

                                17
								
                    12      	                24

					
                6         15	   	       19          26
            
			
            3       9              		16   20          29
            
			
        1       7       10              	    21          30

		
          4       8                         	               31
                    
                    
                    



*/


