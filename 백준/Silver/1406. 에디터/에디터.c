#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
int N = 0; // 문자열 수
int M; // 명령 횟수
char* Order;
char* P_Order;

typedef struct DLL* nptr;
typedef struct DLL {
	char data;
	nptr left;
	nptr right;
}Node;

#define MAX_CHAR 600000
char alphabet[MAX_CHAR]; // 입력되는 문자열 배열

nptr Cursor;
nptr Head;

void InputData();
void ListInit();
void PrintNode();

nptr CreateNode(char data, nptr left, nptr right);
//void InsertTail(nptr head, nptr new);
void InsertTail(nptr new);
void L_MoveLeft(nptr* cursor);
void D_MoveRight(nptr* cursor);
void B_Delete(nptr cursor);
void P_Insert(nptr cursor, char data);

int main(void) {
	InputData();
	ListInit();

	for (int i = 0; i < M; i++) {
		if (Order[i] == 'L') L_MoveLeft(&Cursor);
		else if (Order[i] == 'D') D_MoveRight(&Cursor);
		else if (Order[i] == 'B') B_Delete(Cursor);
		else if (Order[i] == 'P') P_Insert(Cursor, P_Order[i]);
	}

	PrintNode();

	free(Order);
	free(P_Order);
	return 0;
}

nptr CreateNode(char data, nptr left, nptr right) {
	nptr new = (nptr)malloc(sizeof(Node));
	new->data = data;
	new->right = right;
	new->left = left;

	return new;
}

void PrintNode() {
	nptr temp = Head;

	for (; temp->right; temp = temp->right) {
		printf("%c", temp->data);
	}
}

// 문자열, 명령어 개수 입력받기
void InputData() {
	// 문자열 입력
	char temp;
	for (int i = 0; i < MAX_CHAR; i++) {
		if (scanf("%1c", &temp) == EOF || temp == '\n') {
			break;
		}
		alphabet[i] = temp;
		N++;
	}

	// 명령 개수 입력
	(void)scanf("%d", &M);

	Order = (char*)malloc(M * sizeof(char));
	P_Order = (char*)malloc(M * sizeof(char));

	// 명령 입력
	for (int i = 0; i < M; i++) {
		(void)scanf(" %c", &Order[i]);
		if (Order[i] == 'P') {
			(void)scanf(" %c", &P_Order[i]);
		}
	}
}

// 커서가 맨 뒤 일때만 사용
void InsertTail(nptr new) {
	Cursor->right = new;
	new->left = Cursor;
	Cursor = new;
}

void ListInit() {
	// 리스트 생성
	Head = CreateNode(alphabet[0], NULL, NULL);
	Cursor = Head;
	for (int i = 1; i < N; i++) {
		InsertTail(CreateNode(alphabet[i], NULL, NULL));
	}
	// tail에 Dummy 노드
	InsertTail(CreateNode(NULL, NULL, NULL));

	// 초기 커서는 문장의 맨 뒤
	nptr temp = Head;
	for (; temp != NULL;) {
		Cursor = temp;
		temp = temp->right;
	}
}

void L_MoveLeft(nptr* cursor) {
	if ((*cursor)->left == NULL) return;
	*cursor = (*cursor)->left;
}

void D_MoveRight(nptr* cursor) {
	if ((*cursor)->right == NULL) return;
	*cursor = (*cursor)->right;
}

void B_Delete(nptr cursor) {
	// 커서가 문장의 맨 앞이면 무시됨
	if (cursor->left == NULL) return;

	nptr temp; // 삭제할 노드
	// 커서의 왼쪽이 head
	if (cursor->left == Head) {
		temp = Head;
		cursor->left = NULL;
		Head = cursor;

		free(temp);
	}
	else {
		temp = cursor->left;
		cursor->left->left->right = cursor;
		cursor->left = temp->left;

		free(temp);
	}
}

void P_Insert(nptr cursor, char data) {
	nptr new = CreateNode(data, NULL, NULL);

	// 커서가 맨 앞
	// new가 Head가 됨
	if (cursor == Head) { // 커서의 위치는 그대로
		new->right = cursor;
		cursor->left = new;
		Head = new;
	}
	else {
		nptr temp = cursor;
		new->right = cursor;
		new->left = cursor->left;
		temp->left->right = new; // 3 을 10으로 // 커서의 위치는 그대로
		cursor->left = new;
	}
}