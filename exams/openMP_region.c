#include <omp.h>
#include <stdio.h>

int main(int argc, char const *argv[]){

  omp_set_num_threads(4);

  #pragma omp parallel
  {
  const int num_threads = omp_get_num_threads();
  const int my_id = omp_get_thread_num();

  for (size_t i = 0; i < 5; i++)
    printf("hello from thread %d/%d: %zu\n", my_id, num_threads, i);

  #pragma omp barrier
  #pragma omp for
  for (size_t i = 0; i < 4; i++)
    printf("%zu hello from thread %d\n", i, my_id);
  }

  return 0;
}