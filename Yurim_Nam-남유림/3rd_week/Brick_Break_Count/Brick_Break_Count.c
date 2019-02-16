#include <stdio.h>

int main() {
	int n, m; // 가로, 세로를 담을 변수
	
	scanf("%d %d", &n, &m); // 가로, 세로를 입력
	
	printf ("%d", n*m-1); // 가로를 1로 만드는데에 드는 횟수는 n-1, 세로를 1로 만드는데에 드는 횟수는 n*m-1 총 횟수는 n-1+n*m-n, 정리하면 n*m-1
}