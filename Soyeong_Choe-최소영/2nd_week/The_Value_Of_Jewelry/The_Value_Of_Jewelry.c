#include <stdio.h>

int main() {
	int num, sum, i, j; //num: 몇개의 코인을 받을지		sum: 몇원을 만들지 
	int numArr[1001] = { 0, }, sumArr[100001] = { 0, }; //numarr: 주어진 코인		sumarr: 경우의 수 (5번 배열에 있는 경우의 수는 5원의 경우의수)
	
	scanf("%d %d", &num, &sum);
	
	for (i=1; i<=num; i++) //숫자를 입력받는다 
	{
		scanf("%d", &numArr[i]);
	}
	
	sumArr[0] = 1;	//0원을 만드는 경우의 수는 언제나 1개이기 때문 
	
	for (i=1; i<=num; i++) //숫자갯수만큼 반복 
	{
		for (j=numArr[i]; j<=sum; j++) //숫자부터 합까지 반복 
		{
			sumArr[j] += sumArr[j - numArr[i]];	// 5원을 만드는 경우의 수는 5,4+1,3+2이다
												// 이 경우의 수를 경우의 수에 넣는다 
		}
	}
	
	printf("%d", sumArr[sum]);
}
