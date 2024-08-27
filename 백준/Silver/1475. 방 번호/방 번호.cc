#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int N; // 방 번호
	int num[9] = { 0 }; // 9는 num[6] 배열에 추가
	(void)scanf("%d", &N);

	while (N / 1 > 0) {
		if (N % 10 == 6 || N % 10 == 9) {
			num[6]++;
		}
		else {
			num[N % 10]++;
		}
		N = N / 10;
	}
	
	num[6] = (num[6] + 1) / 2;

	int max = 0;
	for (int i = 0; i < 9; i++) {
		if (max < num[i])
			max = num[i];
	}

	printf("%d", max);

	return 0;
}