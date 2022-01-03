#include <omp.h>

#include "max.hpp"

int main(int argc, char **argv)
{

  float max = -1.0f;

  double begin_t = omp_get_wtime();
  InitData();
  double finish_t = omp_get_wtime();

  printf("init time consumption is %f s \r\n", finish_t - begin_t);

  begin_t = omp_get_wtime();
  max = Max(rawFloatData, DATANUM);
  finish_t = omp_get_wtime();

  printf("------------------------\r\n");
  printf("max number is %.2f \r\n", max);
  printf("last number is %.2f \r\n", rawFloatData[DATANUM - 1]);
  printf("Max() time consumption is %f s \r\n", finish_t - begin_t);

  begin_t = omp_get_wtime();
  max = MaxSpeedUpOmp(rawFloatData, DATANUM);
  finish_t = omp_get_wtime();

  printf("------------------------\r\n");
  printf("max number is %.2f \r\n", max);
  printf("last number is %.2f \r\n", rawFloatData[DATANUM - 1]);
  printf("MaxSpeedUpOmp() time consumption is %f s \r\n", finish_t - begin_t);

  begin_t = omp_get_wtime();
  max = MaxSpeedUpAvx(rawFloatData, DATANUM);
  finish_t = omp_get_wtime();

  printf("------------------------\r\n");
  printf("max number is %.2f \r\n", max);
  printf("last number is %.2f \r\n", rawFloatData[DATANUM - 1]);
  printf("MaxSpeedUpAvx() time consumption is %f s \r\n", finish_t - begin_t);

  begin_t = omp_get_wtime();
  max = MaxSpeedUpAvxOmp(rawFloatData, DATANUM);
  finish_t = omp_get_wtime();

  printf("------------------------\r\n");
  printf("max number is %.2f \r\n", max);
  printf("last number is %.2f \r\n", rawFloatData[DATANUM - 1]);
  printf("MaxSpeedUpAvxOmp() time consumption is %f s \r\n", finish_t - begin_t);

  InitialCuda(0);

  begin_t = omp_get_wtime();
  MaxWithCuda(&max, rawFloatData, DATANUM);
  finish_t = omp_get_wtime();

  ReleaseCuda();

  printf("------------------------\r\n");
  printf("max number is %.2f \r\n", max);
  printf("last number is %.2f \r\n", rawFloatData[DATANUM - 1]);
  printf("MaxWithCuda() time consumption is %f s \r\n", finish_t - begin_t);

  return 0;
}