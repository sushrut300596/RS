#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

#define MALLOC 1024

#define MEMORY_CAPACITY 1000000

void *memory[MEMORY_CAPACITY] = {0};

typedef long Align;

typedef union header {
	struct {
		union header *next;
		int size;
	}s;
	Align x;
}Header;

static Header base;
static Header *freep = NULL;

static Header *morememory(int);
void *myMalloc(size_t);
void myFree(void *);
void *pbreak(int);

void *myMalloc(size_t size) {
	Header *p, *prevp;
	int nunits;

	nunits = (size + sizeof(Header) - 1) / sizeof(Header) + 1;
	if((prevp = freep) == NULL) {
		base.s.next = freep = prevp = &base;
		base.s.size = 0;
	}
	for(p = prevp->s.next; ; prevp = p, p = p->s.next) {
		if(p->s.size >= nunits) {
			if(p->s.size == nunits) {
				prevp->s.next = p->s.next;
			}
			else {
				p->s.size -= nunits;
				p += p->s.size;
				p->s.size = nunits;
			}
			freep = prevp;
			return (void *)(p + 1);
		}
		if(p == freep) {
			if((p = morememory(nunits)) == NULL) {
				return NULL;
			}
		}
	}
}

static Header *morememory(int nu) {
	char *cp;
	Header *up;

	if(nu < MALLOC) {
		nu = MALLOC;
	}
	cp = pbreak(nu * sizeof(Header));
	if(cp == (char *) - 1) {
		return NULL;
	}
	up = (Header *)cp;
	up->s.size = nu;
	myFree((void *)(up + 1));
	return freep;
}

void *pbreak(int increment) {
	static char *p_break = (char *)memory;

    char *const limit = (char *)memory + MEMORY_CAPACITY;
    char *const original = p_break;

    if (increment < (char *)memory - p_break  ||  increment >= limit - p_break) {
        errno = ENOMEM;
        return (void*)-1;
    }
    p_break += increment;

    return original;
}

void myFree(void *ap) {
	Header *bp, *p;

	bp = (Header *)ap - 1;
	for(p = freep; !(bp > p && bp < p->s.next); p = p->s.next) {
		if(p >= p->s.next && (bp > p || bp < p->s.next)) {
			break;
		}
	}
	if(bp + bp->s.size == p->s.next) {
		bp->s.size += p->s.next->s.size;
		bp->s.next = p->s.next->s.next;
	}
	else {
		bp->s.next = p->s.next;
	}
	if(p + p->s.size == bp) {
		p->s.size += bp->s.size;
		p->s.next = bp->s.next;
	}
	else {
		p->s.next = bp;
	}
	freep = p;
}

//////////////////////// Structure Node ///////////////////

typedef struct Node {
	int item;
	struct Node *next;
}Node;

///////////////////////////////////////////////////////////

////////////// Build Function for Linked List /////////////

Node *build() {
	Node *node = NULL, *prev = NULL;
	Node *head = NULL;
	for(int i = 0; i <= 100; i++) {
		node = myMalloc(sizeof(struct Node));
		node->item = i;
		if(i == 0) {
			head = node;
		}
		else {
			prev->next = node;
		}
		prev = node;
	}
	return head;
}

///////////////////////////////////////////////////////////

//////////////////// Print Linked List ////////////////////

void print(Node *head) {
	struct Node *node1 = head;
  	while(node1 != NULL) {
    	printf("%d ", node1->item);
    	node1 = node1->next;
  	}
  	printf("\n");
}

///////////////////////////////////////////////////////////

int main() {
	char *a = (char *)myMalloc(5 * sizeof(char));
	int *b = (int *)myMalloc(5 * sizeof(int));
	if(a == NULL)
		printf("n\n");
	
	for(int i = 97; i < 102; i++) {
		printf("%c ", a[i] = (char)i);
	}
	printf("\n");

	for(int i = 10; i < 15; i++) {
		printf("%d ", b[i] = i);
	}
	printf("\n");


	/*for(int i = 0; i < 10000; i++) {
		printf("%d ", memory[i]);
	}
	printf("\n");*/
	
	Node *head = build();
	print(head);

	for(int i = 0; i < 10000; i++) {
		if(memory[i] != 0)
		printf("i = %d -- mem = %d\n",i, memory[i]);
	}
	printf("\n");	
}