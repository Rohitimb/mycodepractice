#include <stdio.h>

void update(int *a,int *b) {
    int atemp = *a,btemp = *b;
    *a =  atemp+ btemp;
    *b=atemp-btemp;
    if(*b <  0)
        *b = -*b;
}

int main() {
    int a, b;
    int *pa = &a, *pb = &b;
    
    scanf("%d %d", &a, &b);
    update(pa, pb);
    printf("%d\n%d", a, b);

    return 0;
}


