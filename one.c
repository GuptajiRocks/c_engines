/*
 * ********************************************************
 * **************** Regression Module *********************
 * ************ Written by - Arihant Gupta ****************
 * **************** Date: 9th Apr, 2026 *******************
 * ********************************************************
 */

#include <stdio.h>
#include <stdlib.h>

// two variable read_csv
// this is being done, so as to design a basic regression engine implementing simple regression function

struct reg_props {
  int len;
  int* arr1;
  int* arr2;
  int tot_x1, tot_x2;
  double m_x1, m_x2;
  double numer, denom;
};


struct reg_props read_csv(char* arr) {
  struct reg_props s = {0, NULL, NULL, 0, 0, 0.0, 0.0, 0.0, 0.0};
  char buffer[100];
  int x1, x2 = 0;

  FILE* fptr = fopen(arr, "r");

  while (fgets(buffer, sizeof(buffer), fptr)) {
    s.len++;
  }

  rewind(fptr);

  s.arr1 = malloc(sizeof(int) * s.len);
  s.arr2 = malloc(sizeof(int) * s.len);

  for (int i = 0; i < s.len; i++) {
    fscanf(fptr,"%d,%d", &x1, &x2);
    printf("%d,%d\n", x1, x2);
    s.arr1[i] = x1;
    s.arr2[i] = x2;
    s.tot_x1 += x1;
    s.tot_x2 += x2;
  }
  fclose(fptr);

  s.m_x1 = (s.tot_x1) / (s.len);
  s.m_x2 = (s.tot_x2) / (s.len);

  return s;
}

double eqn(struct reg_props val) {
  for (int i = 0; i < val.len; i++) {
    val.numer += ((val.arr2[i] - val.m_x2) * (val.arr1[i] - val.m_x1));
  }
  //printf("Numerator: %.2f\n", val.numer);

  for (int i = 0; i < val.len; i++) {
    val.denom += ((val.arr1[i] - val.m_x1) * (val.arr1[i] - val.m_x1));
  }

  return val.numer/val.denom;
}



int main() {
  struct reg_props main = {0, NULL, NULL, 0, 0, 0.0, 0.0, 0.0, 0.0};
  main = read_csv("sal_dat.txt");

  printf("Mean of X1: %.2f\n", main.m_x1);
  printf("Mean of X2: %.2f\n", main.m_x2);

  double m_val = eqn(main);
  printf("value of m: %.2f\n", m_val);
  return 0;
}

