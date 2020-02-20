#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    FILE *fp = fopen("test.txt","rb");
    if(NULL == fp){
        perror("fopen error");
        exit(1);
    }

    char arr[5] = {0};
    int n = fread(arr,sizeof(arr[0]),5,fp);
    printf("read %d data\n",n);

    int i;
    for(i = 0;i < 5;i++){
        printf("%c\t",arr[i]);
    }

    fclose(fp);

    exit(0);
}