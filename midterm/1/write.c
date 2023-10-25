#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h> 

int main()
{


    FILE* fp = fopen("out.txt","w"); 

    for (int i = 0; i < 5; i++) {
        scanf("%s\n",fp); 
    }
   scanf("%s\n", fp);
   

    fclose(fp);

    return 0;
}

