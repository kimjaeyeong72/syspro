#include <stdio.h>
#include <string.h>
#include "Copy.h"

int main()
{
	char str[5][MAXLINE];
	char temp[MAXLINE];

	for (int i = 0; i < 5; i++)
		fgets(str[i], MAXLINE -1, stdin);

	for (int m = 0; m < 4; m++) {
		for (int n = 0; n <4 - m; n++) {
			if (strlen(str[n]) < strlen(str[n + 1]))
			{
				copy(str[n],temp);
				copy(str[n + 1],str[n]);
				copy(temp,str[n + 1]);
			}
		}
	}

	for (int i = 0; i < 5; i++)
		printf("%s",str[i]);
	return 0;
}
