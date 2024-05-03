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
int contains(struct entry* head,int what);
struct entry* sort(struct entry* head);
struct entry *shift(struct entry* head,int shift);
struct entry* arrToList(int arr[],int size);
int valueAtPos(struct entry* head,int pos);
struct entry* reverse(struct entry* head);
