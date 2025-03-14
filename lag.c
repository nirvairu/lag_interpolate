/*
  WARNING: WILL BREAK TERMINALS WHICH DO NOT SUPPORT COMPLEX TEXT LAYOUT (MOST OF THEM)
  I really don't know why some comments are in *Hindi*, but I will be preserving this for
  the sake of history :p
  
  FYI: Code is very messy, Still proud of this project :-) This was during my obsessive
  micro optimisation phase and a lot of engineering was devoted to properly render
  everything in a single array, This was also before I tried using debuggers. 
  */


#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define DEBUG 1
#define perr(args...)                                                          \
  if (DEBUG)                                                                   \
  fprintf(stderr, args)
// n integer का जोड़
#define sum_n(n) ((((n) * (n)) + (n)) / 2)

int ndigit(int num) {
  int count = 0;
  if (num < 0)
    count++;
  while (num > 0) {
    num /= 10;
    count++;
  }
  return count;
}
int maxof(int n, int *y) {
  int max = 0;
  int a;
  for (int i = 0; i < n; i++) {
    a = ndigit(y[i]);
    if (a > max)
      max = a;
  }
  return max + 2;
}
void fillfd(int n, int *y) {
  int max = sum_n(n);
  int cur = n;
  int prev = 0;
  n--;
  while (cur < max) {
    for (int i = 0; i < n; i++) {
      printf("%d, y[%d] = y[%d] - y[%d]\n", i, cur + i, prev + i + 1, prev + i);
      printf("%d = %d - %d\n", y[cur + i], y[prev + i + 1], y[prev + i]);
      y[cur + i] = y[prev + i + 1] - y[prev + i];
    }
    prev = cur;
    printf("%d %d %d\n", n, prev, cur);
    cur += n;
    n--;
  }
}

void printfdtable(int a, int h, int n, int *y) {
  int max = sum_n(n);
  int cur, sub;

  perr("cur = %d, max = %d\n", n, max);

  int width = maxof(max, y);
  if (width < 5)
    width = 5;

  // Column Header

  printf("|%*cx |%*cy |", width - 1, ' ', width - 1, ' ');
  ;
  for (int i = 1; i < n; i++)
    printf("%*cfd%*d |", width - 4, ' ', 2, i);
  puts("");

  for (int i = 0; i < n; i++) {
    cur = n;
    sub = 1;

    printf("|%*d |%*d |", width, a + i * h, width, y[i]);

    while ((i + cur) < max) {
      printf("%*d |", width, y[i + cur]);
      cur += n - sub++;
    }
    // रिक्त स्थान और अंतिम '|'
    for (int j = 0; j + cur < max; j++)
      printf("%*c |", width, ' ');
    puts("");

    max = i + cur - n +
          sub; // previous value of i + cur before final loop iteration
  }
}

int main(int argc, char **argv) {
  if (argc > 256) {
    perr("too many arguements: %d\n", argc - 1);
    return -1;
  }
  if (argc < 4) {
    perr("invalid no of arguements: %d\n", argc - 1);
    return -1;
  }
  /* num = जित्नी संख्या दी गयीं हैं
   * sum_n(num) = १ से num तक का जोड़
   * | y   fd 1  fd 2  fd 3|
   * | x    x     x     x  |
   * | x    x     x        |
   * | x    x              |
   * | x                   |
   *
   * सभी को १ ही array मे डाला गया है
   * यहाँ num ४ हैं और sum_n(num) १० जिस्से सभी संख्या का स्थान हैं
   * */
  int num = argc - 3;
  int a;
  int h;
  int *y = malloc(sum_n(num) * sizeof(int));

  perr("num = %d\nsum_n = %d\n", num, sum_n(num));
  a = strtol(argv[1], NULL, 0);
  h = strtol(argv[2], NULL, 0);

  for (int i = 3; i < argc; i++) {
    y[i - 3] = strtol(argv[i], NULL, 0);
    perr("y[%d] = %d\n", i - 3, y[i - 3]);
  }

  fillfd(num, y);

  for (int i = 0; i < sum_n(num); i++) {
    perr("y[%d] = %d\n", i, y[i]);
  }

  printfdtable(a, h, num, y);
  return 0;
}
