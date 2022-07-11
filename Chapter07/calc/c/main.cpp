#include <stdio.h>
int calc(int a)
{
    if(a == 0)
        {
        throw 42;
        }else{
            return 3/a;
        }
}
int main()
{
    printf("Enter a value for a:");
    int a = 0;
    scanf("%d",&a);
    int r = 0;
    try{
        r = calc(a);
        printf("The result is: %d\n",r);
    }catch(int e)
    {
    printf("Divide by zero!\n");
    }
    
    return 0;
}


