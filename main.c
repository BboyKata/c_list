#include <stdio.h>
#include <stdlib.h>
#include "list.h"

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

struct entry* popMiddle(struct entry* head, int pos){
	/* possibili posizioni:
	|0| |1| |2| |3|	
	*/
	if(pos>=listLen(head)){
		printf("Index out of bound!\n");
		return head;
	}else if(pos == 0) head = popLeft(head);
	else if(pos == listLen(head)-1) head = popRight(head);
	else{
		struct entry* cursor = head;
		for(int c = 0;c<pos-1;c++)cursor = cursor->next;
		struct entry* temp = cursor->next;
		cursor->next = temp->next;
		free(temp);
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
		struct entry* temp = cursor->next;
		cursor->next = new;
		cursor = cursor->next;
		cursor->next = temp;
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

int contains(struct entry* head,int what){
	if(head == NULL){
		return 0;
	}else{
		if(head->value == what)return 1;
		else contains(head->next,what);
	}
}

struct entry* sort(struct entry* head){
	if(listLen(head)>=2){
		for(int z=0;z<listLen(head);z++){
			struct entry* i = head; struct entry* j = head->next;
			while(i->next != NULL){
				if(i->value > j->value){
					int temp = i->value;
					i->value = j->value;
					j->value = temp;
				}
				i = i->next; 
				j=j->next;
			}
		}			

	}
	return head;
}

struct entry *shiftToLeft(struct entry* head,int shift){
	for(int i=0;i<shift;i++){
		int temp = head->value;
		head = popLeft(head);
		head = addRight(temp,head);
	}
	return head;
}

struct entry* arrToList(int arr[],int size){
	struct entry* list = NULL;
	for(int i=0;i<size;i++){
		list = addRight(arr[i],list);
	}
	return list;
}

int valueAtPos(struct entry* head,int pos){
	struct entry* cursor = head;
	for(int i=0;i<pos;i++)cursor = cursor->next;
	return cursor->value; 
}

struct entry* reverse(struct entry* head){
	/*
	|0|->|1|->|2|->|3|->|4|
	 |
	|4|->|0|->|1|->|2|->|3|
	      |
	|4|->|3|->|0|->|1|->|2|
	      	   |
	|4|->|3|->|2|->|0|->|1|
	...
	*/
	int len = listLen(head);
	int temp = valueAtPos(head,len-1);
	head = popRight(head);
	head = addLeft(temp,head);
	for(int i=0;i<len-1;i++){
		temp = valueAtPos(head,len-1);
		head = popRight(head);
		head = addMiddle(temp,head,i+1);
	}
	return head;
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
	printf("%i\n",contains(list,888));
	list = sort(list);
	printList(list);
	list = shiftToLeft(list,3);
	printList(list);
	int arr[] = {1,2,3,4,5,6,7,8,9,10};
	struct entry* list2 = arrToList(arr,10);
	printList(list2);
	printList(list);
	list = reverse(list);
	printList(list);
	list = popMiddle(list,2);
	printList(list);
return 0;
}
