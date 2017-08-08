#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <time.h>
#include <string.h>

int array[] = {123, 145, 512, 627, 800, 933};
int asize = sizeof(array)/sizeof(int);

char strings[][20] = {"some", "example", "strings", "here"};
int strsize = sizeof(strings)/sizeof(strings[0]);

int cmpstr(const void *a, const void *b)
{
    char *p = (char *)a;
    char *q = (char *)b;
    return strcmp(p, q);
}

void testString()
{
    int i;
    char *p = "strings";
    char *q = NULL;
    qsort(strings, sizeof(strings)/sizeof(strings[0]), sizeof(strings[0]), cmpstr);
    for (i = 0; i < strsize; ++i)
        printf("%s\n", strings[i]);
    q = bsearch(p, strings, sizeof(strings)/sizeof(strings[0]), sizeof(strings[0]), cmpstr);
    if(q) printf("%s\n", q);
    else printf("NULL\n");
}


int cmp(const void *a, const void *b)
{
    return *((int *)a) - *((int *)b);
}

void testBsearch()
{
    int i;
    int key;
    for (i = 0; i < asize; ++i) {
        key = array[i];
        assert(array + i == bsearch(&key, array, asize, sizeof(int), cmp));
    }
}



int main()
{
/*    int i, j;
    int n;
    clock_t t1, t2;
    for (i = 10; i < 23; ++i) {
        n = pow(2, i);
        t1 = clock();
        for (j = 0; j < n; ++j)
            testBsearch();
        t2 = clock();
        printf("%8d\t%lf\n", n, (double)(t2 - t1)/CLOCKS_PER_SEC);
    }*/
    testString();
    return 0;
}
