#include <stdio.h>
#include <stdlib.h>
#define MAX_NUM 100000


long int sort_and_count(long int *, long int, long int);

long int merge_csplit(long int*, long int, long int, long int);


int main(int argc, char **argv)
{
    FILE *fp;
    fp = fopen("arraylist.txt", "r");
    long int nums[MAX_NUM];
    int i = 0;
    while (!feof(fp)){
		fscanf(fp, "%ld", &nums[i]);
        i++;
    }

    printf("%ld", sort_and_count(nums,0,MAX_NUM-1));

    fclose(fp);

    return 0;
}


long int sort_and_count(long int *nums, long int l, long int r)
{
    long int mid;
    long int splits = 0;
    if (l < r)
    {
        mid = (l+r)/2;
        splits += sort_and_count(nums, l, mid);
        splits += sort_and_count(nums, mid+1, r);

        splits += merge_csplit(nums, l, mid, r);
    }

    return splits;
}


long int merge_csplit(long int *nums, long int l, long int mid, long int r)
{
    long int i, j, k, splits = 0;
    long int n1 = mid - l + 1;
    long int n2 = r - mid;

    long int arrayb[n1];
    long int arrayc[n2];

    for (i = 0; i < n1; i++)
        arrayb[i] = nums[i+l];
    
    for (j = 0; j < n2; j++)
        arrayc[j] = nums[mid+1+j];

    i = 0, j = 0, k = l;

    while (i < n1 && j < n2){

        if (arrayb[i] <= arrayc[j]){
            nums[k] = arrayb[i];
            i++;
        }

        else{
            nums[k] = arrayc[j];
            j++;
            splits += (n1 - i);
        }
        k++;
    }

    while (i < n1)
    {
        nums[k] = arrayb[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        nums[k] = arrayc[j];
        j++;
        k++;
    }
    
    return splits;
}

