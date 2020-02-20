#include <stdio.h>

int main(void)
{
    FILE *fp = fopen("test.txt","w");
    if(NULL == fp){
        perror("fopen error");
        return -1;
    }

    int arr[5] = {1,2,3,4,5};
    int n = fwrite(arr,4,5,fp);

    printf("write %d number to file \n",n);

    return 0;
}