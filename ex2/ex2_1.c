#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define CLOCKS_TO_MILLISEC(t) (t*1000)/CLOCKS_PER_SEC

int main(int argc, char const *argv[]) {
  clock_t start, stop, ascii_read_timer, ascii_write_timer, bin_read_timer, bin_write_timer;

  int n = 1e5
  double *data, *fromfile;
  FILE *binfile, asciifile;

  data = (double *)malloc(n * sizeof(double));

  // Write to ASCII file
  asciifile = fopen("data.txt", "w");

  start = clock();
  for (int i = 0; i < n; i ++)
    fprint(asciifile, "%lf\n", data[i])
  stop = clock();
  ascii_write_timer = stop - start;

  fclose(asciifile);

  // Read from ASCII file
  asciifile = fopen("data.txt", "r")
  fromfile = (double *)malloc(n * sizeof(double))

  start = clock();
  for (int i = 0; i < n; i ++)
    fscan(asciifile, "%lf", &fromfile[i])
  stop = clock();
  ascii_read_timer = stop - start;
  return 0;

  fclose(asciifile);
  free(fromfile);

  // Write to bin file
  binfile = fopen("data.bin", "wb");

  start = clock();
  fwrite(data, sizeof(double), n, binfile);
  stop = clock();
  bin_write_timer = stop - start;

  fclose(binfile);

  // Read to bin file
  fromfile = (double *)malloc(n * sizeof(double));
  binfile = fopen("data.bin", "rb");

  start = clock();
  fread(fromfile, sizeof(double), n, binfile);
  stop = clock();
  bin_read_timer = stop - start;

  fclose(binfile);
  free(fromfile);

print("Time writing to ASCII file: &lu ms.\n", CLOCKS_TO_MILLISEC(ascii_write_timer));
print("Time reading ASCII file: &lu ms.\n", CLOCKS_TO_MILLISEC(ascii_read_timer));
print("Time writing to binary file: &lu ms.\n", CLOCKS_TO_MILLISEC(bin_write_timer));
print("Time reading binary file: &lu ms.\n", CLOCKS_TO_MILLISEC(bin_read_timer));
}
