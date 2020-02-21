#include <stdio.h>
#include <string.h>
extern void f1(char * );
extern void f2(char *);

int check(char num[], int len){
	int i = 0;
	int k, z, s;
	z = 0;
	s = 0;
	while (i <= len) {
	    k = num[i];
	    if ((65 <= k) && ( k<= 90)){
	    	z++;
	    }
	    else if ((97 <= k) && ( k <= 122)){
	    	s++;
	    }
	    i++;
	}
	if (s == z){
		return (1);
	}
	else {
		return (2);
	}
}

int main() {
	char str[100];
	scanf("%s", &str);
	printf("%s\n", str);
	int k = 0;
	int l = 0;
	while (l < 100){
		if (str[l] == 46){
			break;
		}
		l++;
	}
	k = check(str, l);
	printf("правило преобразования текста %d\n", k);
	if (k == 1 ){
	   f1(str);
	}
	else{
	   f2(str);
	}
	printf("%s\n", str);
	return 0;
}