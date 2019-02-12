#include <stdio.h>

int main() {
	int num, sum, i, j; //NUM = 보석의 개수 SUM = 만들어야 하는 가치의 합 I, J = 반복변수
	int numArr[1001] = { 0, }, sumArr[100001] = { 0, }; //NUMARR =  보석을 담는 배열 SUMARR = 가치의 합을 만드는 경우의 수를 담는 배열
	
	scanf("%d %d", &num, &sum); //보석의 개수와 가치의 합을 입력받음
	
	for (i=1; i<=num; i++) { //보석의 가치를 입력받음
		scanf("%d", &numArr[i]);
	}
	
	sumArr[0] = 1; //보석으로 0을 만들 경우의 수는 1 이므로 초기화
	
	for (i=1; i<=num; i++) { //보석의 갯수만큼 FOR문을 돌림
		for (j=numArr[i]; j<=sum; j++) { //보석의 합만큼 FOR문을 돌림
			sumArr[j] += sumArr[j - numArr[i]]; //점화식 [N-1] + [N-2] + [N-5] 를 통합한 점화식
		}
	}
	
	printf("%d", sumArr[sum]); //보석의 가치 출력
}
