#include <stdio.h>
#include <stdlib.h>

struct entry{
	int value;
	struct entry* next;
};


void printList(struct entry* head);
struct entry* newEntry(int value);
struct entry* addRight(int value,struct entry* head);
struct entry* addLeft(int value, struct entry* head);
struct entry* addMiddle(int value, struct entry* head, int pos);
struct entry* popRight(struct entry* head);
struct entry* popLeft(struct entry* head);
int listLen(struct entry* head);



void printList(struct entry* head){
	if(head != NULL){
		struct entry* cursor = head;
		while(cursor){
			printf("%i ",cursor->value);
			cursor = cursor->next;
		}
		printf("\n");
	}
	
}

struct entry* newEntry(int value){
	struct entry* new = malloc(sizeof(struct entry));
	new->value = value;
	new->next = NULL;
	return new;
}

struct entry* addRight(int value,struct entry* head){
	struct entry* new = newEntry(value);
	if(head == NULL){
		head = new;
	}else{
		struct entry* cursor = head;
		while(cursor->next)cursor = cursor->next;
		cursor->next = new;
	}
return head;
}

struct entry* addLeft(int value, struct entry* head){
	struct entry* new = newEntry(value);
	if(head == NULL){
		head = new;
	}else{
		new->next = head;
		head = new;
	}
	return head;
}

struct entry* addMiddle(int value, struct entry* head, int pos){
	/* possibili posizioni:
	0 |le| 1 |le| 2 |le| 3 |le| 4	
	*/
	if(pos>listLen(head)){
		printf("Index out of bound!\n");
		return head;
	}else if(pos == 0) head = addLeft(value,head);
	else if(pos == listLen(head)) head = addRight(value,head);
	else{
		struct entry* cursor = head;
		struct entry* new = newEntry(value);
		for(int c = 1;c<pos;c++)cursor = cursor->next;
		cursor->next = new;
	}
	return head;
}

struct entry* popRight(struct entry* head){
	if(head != NULL){
		struct entry* cursor = head;
		struct entry* prev = head;
		while(cursor->next){
			prev = cursor;
			cursor = cursor->next;
		}
		free(cursor);
		prev->next = NULL;
	}
	return head;
}

struct entry* popLeft(struct entry* head){
	if(head != NULL){
		if(head->next == NULL)free(head);
		else{ 
			struct entry* destroy = head;
			head = head->next;
			free(destroy);
		}
	}
	return head;
}

int listLen(struct entry* head){
	if(head == NULL){
		return 0;
	}else{
		return 1 + listLen(head->next);
	}
}

int main(void){
	struct entry* list = NULL;
	list = addRight(10,list);
	list = addRight(11,list);
	list = addRight(12,list);
	list = addLeft(9,list);
	list = addLeft(8,list);
	printList(list);
	printf("%i\n",listLen(list));
	list = popRight(list);
	list = popLeft(list);
	printList(list);
	list = addMiddle(777,list,0);
	list = addMiddle(888,list,listLen(list));
	list = addMiddle(999,list,2);
	printList(list);
return 0;
}
