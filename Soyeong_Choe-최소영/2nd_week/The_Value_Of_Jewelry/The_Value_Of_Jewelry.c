#include <stdio.h>

int main() {
	int num, sum, i, j; //num: ��� ������ ������		sum: ����� ������ 
	int numArr[1001] = { 0, }, sumArr[100001] = { 0, }; //numarr: �־��� ����		sumarr: ����� �� (5�� �迭�� �ִ� ����� ���� 5���� ����Ǽ�)
	
	scanf("%d %d", &num, &sum);
	
	for (i=1; i<=num; i++) //���ڸ� �Է¹޴´� 
	{
		scanf("%d", &numArr[i]);
	}
	
	sumArr[0] = 1;	//0���� ����� ����� ���� ������ 1���̱� ���� 
	
	for (i=1; i<=num; i++) //���ڰ�����ŭ �ݺ� 
	{
		for (j=numArr[i]; j<=sum; j++) //���ں��� �ձ��� �ݺ� 
		{
			sumArr[j] += sumArr[j - numArr[i]];	// 5���� ����� ����� ���� 5,4+1,3+2�̴�
												// �� ����� ���� ����� ���� �ִ´� 
		}
	}
	
	printf("%d", sumArr[sum]);
}
