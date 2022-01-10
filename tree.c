#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct tree {
	int val;
	struct tree *left;
	struct tree *right;
};

struct tree *cur;
struct tree *root;

void make_tree(int e) {
	struct tree *tmp,*tmp2;
	bool firstElement = (root == NULL) ? true : false;

	cur = root;	
	while (cur != NULL) {
		tmp2 = cur;
		if (e < cur->val) 
			cur = cur->left;
		else
			cur = cur->right;
	}

	tmp = (struct tree *)malloc(sizeof(struct tree));
	tmp->val = e;
	tmp->left = NULL;
	tmp->right = NULL;
	if (firstElement == false) {
		if (e < tmp2->val)
			tmp2->left = tmp;
	        else
        	        tmp2->right = tmp;
	}
	else
		root = tmp;
}

struct treeArr{
	int a[10];
	int b[10];
	int c[10];
};

void print_tree(struct tree *t, int pos) {
	static int cnt;	
	static struct treeArr tA;
	int i,j;

	/* Pre-order traverse: root,left,right */	
	if (t) {
                printf("%d ", t->val);
                print_tree(t->left,1);
                print_tree(t->right,2);
        }

/* Unsuccessful try of printing nodes as Tree */
#ifdef NEVER 
	if (t) {
		tA.a[cnt] = t->val;	
		tA.b[cnt] = pos;	
		tA.c[cnt] = cnt;	
		cnt++;
		print_tree(t->left,1);
		print_tree(t->right,2);
	}	
	else if (cnt == 10)
		for (i = 0; i < 10; j=5, i++) {
			if (tA.b[i] == 0)	
				printf(" %d \n", tA.a[i]);
			else if (tA.b[i] == 1) {
				printf("%d \n", tA.a[i]);
				while (j < 10 && tA.b[j++] == 2)
					printf("      %d\n", tA.a[j]);						
			}
			else if (tA.b[i] == 2)
				printf(" %d\n", tA.a[i]);	
		}
#endif
	//printf("\n");
	/*printf("Right tree:\n");
	for (t = root; t != NULL; t = t->right )
		print_tree(t);*/
}

int search_tree(struct tree *t, int v) {
	
	while (t != NULL) {
		printf("->%d", t->val);
		if (v == t->val)
			return 1;
		if (v > t->val)
			t = t->right;
		else
			t = t->left;
	}
	return 0;
}
int main() {
	int i;
	int val,shift,gefunden;

	val = 2;
	for (i = 0; i < 10; i++) {
		//val = random() % 10; /* I will use LFSR u ass hole */
		/* Tree has problems with duplicate values
		   Therefore we used LFSR which gurantees no dulplicates */
		//shift = ((val & 0x03) == 3) ? 0 : (val & 0x01) || (val & 0x02); /* = Xor logic, also correct */
		shift = (val & 0x01) ^ ((val >> 1) & 0x01); /* bit2 xor bit1 */
		val = val >> 0x01;	/* shift values to 1-bit right */
		val = (val & 0xf) | (shift << 4); /* set xor result in 4th-bit */
		printf(" %d ", val);
                make_tree(val);
	}
	printf("\n");
	print_tree(root,0);
	printf("\n");
	
	gefunden = search_tree(root, 26);
	if (gefunden)
		printf(" => v found in tree\n");
	else
		printf(" => v not found in tree\n");
	
}
