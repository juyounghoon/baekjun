#include <stdio.h>

int main() {
	int paper[100][100] = { 0 }; // 10*10 도화지
	int num; // 색종이 수
	int left; // 색종이의 왼쪽 변과 도화지 왼쪽 변 사이의 거리
	int bottom; // 색종이의 아래쪽 변과 도화지 아래쪽 변 사이의 거리 
	int cnt = 0; // 색칠 된 영역 카운트
	(void)scanf("%d", &num);
	for (int k = 0; k < num; k++) {
		(void)scanf("%d %d", &left, &bottom);
		for (int i = left; i < left + 10; i++) {
			for (int j = bottom; j < bottom + 10; j++) {
				paper[i][j]++;
			}
		}
	}

	for (int i = 0; i < 10000; i++) {
		if (*(*paper+i) != 0) cnt++;
	}
	printf("%d", cnt);
	
	return 0;
}