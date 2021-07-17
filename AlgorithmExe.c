/*
	대 소문자를 구분없이 알파벳을 입력하면 대,소문자를 판별하여 분류하고, 사전순으로 정렬하여 출력하는 프로그램
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct cnode{	// 구조체 선언 요소는 문자와 다음 노드를 가리키는 포인터
	char letter;
	struct cnode* link;
} CNode;

typedef struct {		// 헤드 노드 구조체
	CNode* head;
} HeadNode;
	
HeadNode* create_head();												// 헤드노드를 만드는 함수 선언
void create_node(HeadNode* puhead, HeadNode* plhead, char data);		// 노드를 생성하는 함수 선언
void list_ary(HeadNode* puhead, HeadNode* plhead, char* ary, int sz);	// 배열을 입력 받고 연결리스트를 생성하는 함수 선언
void insertion_short(HeadNode* phead);									// 삽입 정렬 함수 선언
void print_node(HeadNode* phead);										// 노드를 출력하는 함수 선언
int count_node(HeadNode* phead);										// 노드의 갯수를 카운트하는 함수 선언
void free_node(HeadNode* phead, int sz);								// 동적 메모리 할당 해제 함수 선언

int main()
{
	char input_ary[10];										// 저장할 배열 변수
	int size = sizeof(input_ary) / sizeof(input_ary[0]);	// 배열의 크기
	int u_size, l_size;

	HeadNode* h_upper = create_head();						// 대문자 헤드 포인터
	HeadNode* h_lower = create_head();						// 소문자 헤드 포인터

	list_ary(h_upper, h_lower, input_ary, size);							

	puts("정렬 전");											// 정렬 하기 전 배열
	puts("[대문자]");
	print_node(h_upper);
	puts("[소문자]");
	print_node(h_lower);

	puts("정렬 후");											// 정렬 후 배열
	insertion_short(h_upper);								// 대문자를 삽입 배열 실행
	insertion_short(h_lower);								// 소문자를 삽입 배열 실행
	puts("[대문자]");
	print_node(h_upper);
	puts("[소문자]");
	print_node(h_lower);

	u_size = count_node(h_upper);							// 대문자를 data로 가지고 있는 노드들의 SIZE를 판단
	l_size = count_node(h_lower);							// 소문자를 data로 가지고 있는 노드들의 SIZE를 판단
	free_node(h_upper, u_size);
	free_node(h_lower, l_size);

	return 0;
}

HeadNode* create_head()										// 헤드노드 생성 함수 정의
{
	HeadNode* h = (HeadNode*)malloc(sizeof(HeadNode));		// 동적 메모리할당
	if (h == NULL) {
		printf("[head] 동적 메모리 할당을 받지 못 했습니다.");	// 동적 메모리 할당이 실패하면 뜨는 에러메시지
	}
	else {
		h->head = NULL;										// 헤드가 NULL을 가리키게 함
	}
	return h;
}

void create_node(HeadNode* puhead, HeadNode* plhead, char data)		// 노드를 생성하는 함수 정의
{
	CNode* n_node = (CNode*)malloc(sizeof(CNode));					// 노드 동적 메모리 할당

	if (n_node == NULL) {
		printf("[new node] 동적 메모리 할당을 받지 못 했습니다.");		// 할당 받지 못했을 때 띄우는 에러 메시지
		exit(1);	
	}
	else if (data >= 'A' && data <= 'Z') {							// 소문자일 때 동적 메모리 할당 했을 경우
		n_node->link = puhead->head;								// link는 다음 노드를 가리킬 수 있도록 헤드 포인터의 값을 대입
		puhead->head = n_node;										// 헤드 포인터가 새로 만든 노드를 가리키도록 한다.
	}
	else if (data >= 'a' && data <= 'z') {
		n_node->link = plhead->head;														
		plhead->head = n_node;
	}
	n_node->letter = data;											// 새 노드의 요소에 data값을 입력받음														
}

void list_ary(HeadNode* puhead, HeadNode* plhead, char* ary, int sz)	// 값을 입력받고 배열, 연결리스트를 만드는 함수 정의
{
	int i;
	printf("알파벳을 입력하세요\n");
	for (i = 0; i < sz; i++) {																	
		printf("[%d] : ", i);
		scanf(" %c", &ary[i]);											// 배열에 값을 입력받음
		create_node(puhead, plhead, ary[i]);							// 입력받은 배열의 값을 연결리스트로 연걸
	}
}

void insertion_short(HeadNode* phead)			// 삽입 정렬 함수 정의
{
	CNode* p = NULL;							// 초기 p(비교 기준)를 2번째 노드를 가리키도록 한다.
	CNode* curr;
	char temp;
	if (phead->head == NULL) {					// 노드가 없을 경우 정렬을 하지 않는다
		return;
	}
	p = phead->head->link;						// 처음 비교할 때 기준 p에  2번째 노드의 주소를 가리킨다.
	while (p != NULL) {							// P가 null일 때까지 반복
		curr = phead->head;						// curr을 처음 노드로 지정
		while (p != curr) {						// p와 curr가 만나는 시점에서 반복 종료
			if (p->letter < curr->letter) {		// 기준 p를 변하는 curr와 비교한다.
				temp = p->letter;				// 스왑으로 값을 서로 바꾼다.
				p->letter = curr->letter;
				curr->letter = temp;
			}
			curr = curr->link;					// curr를 다음 노드로 이동시킨다.
		}
		p = p->link;							// p와 curr이 만나면 기준 p를 다음 노드로 옮겨서 정렬을 한다.
	}
}

void print_node(HeadNode* phead)		// 노드 출력 함수 정의
{
	CNode* curr = phead->head;			// 순환 변수 선언, 헤드의 값을 직접 바꿀 수 없기 때문
	if (curr == NULL) {
		printf("노드가 없습니다.");
	}
	while (curr != NULL)				// NULL이 나올 때 까지 명령문 반복
	{
		printf("%c  ", curr->letter);	// 노드에 저장된 문자를 출력
		curr = curr->link;				// 순환 포인터 변수를 다음 노드를 가리키도록 한다.
	}
	printf("\n");
}

int count_node(HeadNode* phead)			// 노드의 갯수를 구하는 함수 정의
{
	int cnt = 0;																					
	CNode* curr = phead->head;															
	while (curr != NULL) {				// NULL을 만날 때까지 반복한다.
		cnt++;							// 노드가 존재하면 카운드 수를 증가시킨다.
		curr = curr->link;
	}
	return cnt;
}

void free_node(HeadNode* phead, int sz)		// 동적 메모리 할당 해제 함수 정의
{
	CNode* temp = phead->head;				// 임시 순환 포인터 변수 temp 선언, temp가 노드를 옮겨다니면서 동적 메모리를 해제한다.
	for (int i = 0; i < sz; i++) {
		phead->head = temp->link;			// 헤드를 다음 노드를 가리키도록 한다.
		free(temp);							// 동적 할당 해제
		temp = phead->head;					// temp에 헤드에 저장된 값(다음 노드의 주소)을 대입한다.
	}
	free(phead);							// 노드의 동적 할당 해제가 끝나면 헤드도 해제를 한다.
}