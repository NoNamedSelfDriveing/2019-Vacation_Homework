#include<stdio.h>

int main()
{
	int N,M;	// 가로:M, 세로:N
	int result;	// 결과 
	
	printf("가로와 세로의 높이를 입력해주세요\n");
	scanf("%d %d",&M,&N);
	
	result = N*M-1;		// N의 높이의 벽돌을 자르는 횟수는 N-1이다
						// 그렇게 쪼개진 벽돌을 가로로 자르는 횟수는 N*(M-1)이다
						// 즉 총 횟수는 N-1 + M*(N-1) = N-1 + NM -N = NM -1
	
	printf("%d", result);
	   
}
