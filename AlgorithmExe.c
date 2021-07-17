/*
	�� �ҹ��ڸ� ���о��� ���ĺ��� �Է��ϸ� ��,�ҹ��ڸ� �Ǻ��Ͽ� �з��ϰ�, ���������� �����Ͽ� ����ϴ� ���α׷�
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct cnode{	// ����ü ���� ��Ҵ� ���ڿ� ���� ��带 ����Ű�� ������
	char letter;
	struct cnode* link;
} CNode;

typedef struct {		// ��� ��� ����ü
	CNode* head;
} HeadNode;
	
HeadNode* create_head();												// ����带 ����� �Լ� ����
void create_node(HeadNode* puhead, HeadNode* plhead, char data);		// ��带 �����ϴ� �Լ� ����
void list_ary(HeadNode* puhead, HeadNode* plhead, char* ary, int sz);	// �迭�� �Է� �ް� ���Ḯ��Ʈ�� �����ϴ� �Լ� ����
void insertion_short(HeadNode* phead);									// ���� ���� �Լ� ����
void print_node(HeadNode* phead);										// ��带 ����ϴ� �Լ� ����
int count_node(HeadNode* phead);										// ����� ������ ī��Ʈ�ϴ� �Լ� ����
void free_node(HeadNode* phead, int sz);								// ���� �޸� �Ҵ� ���� �Լ� ����

int main()
{
	char input_ary[10];										// ������ �迭 ����
	int size = sizeof(input_ary) / sizeof(input_ary[0]);	// �迭�� ũ��
	int u_size, l_size;

	HeadNode* h_upper = create_head();						// �빮�� ��� ������
	HeadNode* h_lower = create_head();						// �ҹ��� ��� ������

	list_ary(h_upper, h_lower, input_ary, size);							

	puts("���� ��");											// ���� �ϱ� �� �迭
	puts("[�빮��]");
	print_node(h_upper);
	puts("[�ҹ���]");
	print_node(h_lower);

	puts("���� ��");											// ���� �� �迭
	insertion_short(h_upper);								// �빮�ڸ� ���� �迭 ����
	insertion_short(h_lower);								// �ҹ��ڸ� ���� �迭 ����
	puts("[�빮��]");
	print_node(h_upper);
	puts("[�ҹ���]");
	print_node(h_lower);

	u_size = count_node(h_upper);							// �빮�ڸ� data�� ������ �ִ� ������ SIZE�� �Ǵ�
	l_size = count_node(h_lower);							// �ҹ��ڸ� data�� ������ �ִ� ������ SIZE�� �Ǵ�
	free_node(h_upper, u_size);
	free_node(h_lower, l_size);

	return 0;
}

HeadNode* create_head()										// ����� ���� �Լ� ����
{
	HeadNode* h = (HeadNode*)malloc(sizeof(HeadNode));		// ���� �޸��Ҵ�
	if (h == NULL) {
		printf("[head] ���� �޸� �Ҵ��� ���� �� �߽��ϴ�.");	// ���� �޸� �Ҵ��� �����ϸ� �ߴ� �����޽���
	}
	else {
		h->head = NULL;										// ��尡 NULL�� ����Ű�� ��
	}
	return h;
}

void create_node(HeadNode* puhead, HeadNode* plhead, char data)		// ��带 �����ϴ� �Լ� ����
{
	CNode* n_node = (CNode*)malloc(sizeof(CNode));					// ��� ���� �޸� �Ҵ�

	if (n_node == NULL) {
		printf("[new node] ���� �޸� �Ҵ��� ���� �� �߽��ϴ�.");		// �Ҵ� ���� ������ �� ���� ���� �޽���
		exit(1);	
	}
	else if (data >= 'A' && data <= 'Z') {							// �ҹ����� �� ���� �޸� �Ҵ� ���� ���
		n_node->link = puhead->head;								// link�� ���� ��带 ����ų �� �ֵ��� ��� �������� ���� ����
		puhead->head = n_node;										// ��� �����Ͱ� ���� ���� ��带 ����Ű���� �Ѵ�.
	}
	else if (data >= 'a' && data <= 'z') {
		n_node->link = plhead->head;														
		plhead->head = n_node;
	}
	n_node->letter = data;											// �� ����� ��ҿ� data���� �Է¹���														
}

void list_ary(HeadNode* puhead, HeadNode* plhead, char* ary, int sz)	// ���� �Է¹ް� �迭, ���Ḯ��Ʈ�� ����� �Լ� ����
{
	int i;
	printf("���ĺ��� �Է��ϼ���\n");
	for (i = 0; i < sz; i++) {																	
		printf("[%d] : ", i);
		scanf(" %c", &ary[i]);											// �迭�� ���� �Է¹���
		create_node(puhead, plhead, ary[i]);							// �Է¹��� �迭�� ���� ���Ḯ��Ʈ�� ����
	}
}

void insertion_short(HeadNode* phead)			// ���� ���� �Լ� ����
{
	CNode* p = NULL;							// �ʱ� p(�� ����)�� 2��° ��带 ����Ű���� �Ѵ�.
	CNode* curr;
	char temp;
	if (phead->head == NULL) {					// ��尡 ���� ��� ������ ���� �ʴ´�
		return;
	}
	p = phead->head->link;						// ó�� ���� �� ���� p��  2��° ����� �ּҸ� ����Ų��.
	while (p != NULL) {							// P�� null�� ������ �ݺ�
		curr = phead->head;						// curr�� ó�� ���� ����
		while (p != curr) {						// p�� curr�� ������ �������� �ݺ� ����
			if (p->letter < curr->letter) {		// ���� p�� ���ϴ� curr�� ���Ѵ�.
				temp = p->letter;				// �������� ���� ���� �ٲ۴�.
				p->letter = curr->letter;
				curr->letter = temp;
			}
			curr = curr->link;					// curr�� ���� ���� �̵���Ų��.
		}
		p = p->link;							// p�� curr�� ������ ���� p�� ���� ���� �Űܼ� ������ �Ѵ�.
	}
}

void print_node(HeadNode* phead)		// ��� ��� �Լ� ����
{
	CNode* curr = phead->head;			// ��ȯ ���� ����, ����� ���� ���� �ٲ� �� ���� ����
	if (curr == NULL) {
		printf("��尡 �����ϴ�.");
	}
	while (curr != NULL)				// NULL�� ���� �� ���� ��ɹ� �ݺ�
	{
		printf("%c  ", curr->letter);	// ��忡 ����� ���ڸ� ���
		curr = curr->link;				// ��ȯ ������ ������ ���� ��带 ����Ű���� �Ѵ�.
	}
	printf("\n");
}

int count_node(HeadNode* phead)			// ����� ������ ���ϴ� �Լ� ����
{
	int cnt = 0;																					
	CNode* curr = phead->head;															
	while (curr != NULL) {				// NULL�� ���� ������ �ݺ��Ѵ�.
		cnt++;							// ��尡 �����ϸ� ī��� ���� ������Ų��.
		curr = curr->link;
	}
	return cnt;
}

void free_node(HeadNode* phead, int sz)		// ���� �޸� �Ҵ� ���� �Լ� ����
{
	CNode* temp = phead->head;				// �ӽ� ��ȯ ������ ���� temp ����, temp�� ��带 �Űܴٴϸ鼭 ���� �޸𸮸� �����Ѵ�.
	for (int i = 0; i < sz; i++) {
		phead->head = temp->link;			// ��带 ���� ��带 ����Ű���� �Ѵ�.
		free(temp);							// ���� �Ҵ� ����
		temp = phead->head;					// temp�� ��忡 ����� ��(���� ����� �ּ�)�� �����Ѵ�.
	}
	free(phead);							// ����� ���� �Ҵ� ������ ������ ��嵵 ������ �Ѵ�.
}