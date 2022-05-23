#include "stdio.h"
#include "stdlib.h"

int printvec_i(int *y, int N)
{
    printf("(");
    for (size_t i = 0; i < N-1; i++) {
        printf("%4d, ", y[i]);
    }
    printf("%4d", y[N-1]);
    printf(")\n");
    return 0;
}

void merge(int m, int *sorted_list1, int *sorted_list2, int *merge_list) {
  int i = 0;
  int j = 0;
  int k = 0;

  while (i<m && j<m){
    if (sorted_list1[i] <= sorted_list2[j])
    {
      merge_list[k] = sorted_list1[i];
      i++;
    }

    else
    {
      merge_list[k] = sorted_list2[j];
      j++;
    }
    k++;
  }

  // might be missing the last elements from one of the lists

  for (i; i<m; i++){
    merge_list[k] = sorted_list2[i];
    k++;
  }

  for (j; j<m; j++){
    merge_list[k] = sorted_list2[j];
    k++;
  }

  printvec_i(merge_list, 2*m);
}


int main(int argc, char const *argv[]) {
  int m = 10;

  int *sorted_list1 =  malloc(m*sizeof(int));
  for (size_t i = 0; i < m; i++)
    sorted_list1[i] = i;
  printvec_i(sorted_list1, m);

  int *sorted_list2 =  malloc(m*sizeof(int));
  for (size_t i = 0; i < m; i++)
    sorted_list2[i] = 2*i;
  printvec_i(sorted_list2, m);

  int *merge_list = malloc(2*m*sizeof(int));
  for (size_t i = 0; i < 2*m; i++)
    merge_list[i] = 0;
  printvec_i(merge_list, 2*m);

  merge(m, sorted_list1, sorted_list2, merge_list);

  return 0;
}



