#include<stdio.h>

int main()
{
	int N,M;	// ����:M, ����:N
	int result;	// ��� 
	
	printf("���ο� ������ ���̸� �Է����ּ���\n");
	scanf("%d %d",&M,&N);
	
	result = N*M-1;		// N�� ������ ������ �ڸ��� Ƚ���� N-1�̴�
						// �׷��� �ɰ��� ������ ���η� �ڸ��� Ƚ���� N*(M-1)�̴�
						// �� �� Ƚ���� N-1 + M*(N-1) = N-1 + NM -N = NM -1
	
	printf("%d", result);
	   
}
