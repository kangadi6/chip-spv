#include <iostream>
#include <math.h>
#include <cuda_runtime.h>

//#include <helper_cuda.h>
// CUDA kernel to add elements of two arrays
__global__
void add(int n, float *x, float *y)
{
  int index = blockIdx.x * blockDim.x + threadIdx.x;
  int stride = blockDim.x * gridDim.x;
  for (int i = index; i < n; i += stride)
    y[i] = x[i] + y[i];
}

int main(void)
{
  int N = 1<<20;
  float *x, *y;

  // Allocate Unified Memory -- accessible from CPU or GPU
  cudaMallocManaged((void**)&x, N*sizeof(float));
  cudaMallocManaged((void**)&y, N*sizeof(float));

  // initialize x and y arrays on the host
  for (int i = 0; i < N; i++) {
    x[i] = 1.0f;
    y[i] = 2.0f;
  }

  // Launch kernel on 1M elements on the GPU
  int blockSize = 256;
  int numBlocks = (N + blockSize - 1) / blockSize;
  int devId;

  cudaGetDevice(&devId);

  cudaMemPrefetchAsync(y, N*sizeof(float), devId);

  cudaMemAdvise(x, N*sizeof(float), cudaMemAdviseSetReadMostly, devId);
  cudaMemPrefetchAsync(x, N*sizeof(float), devId);

  add<<<numBlocks, blockSize>>>(N, x, y);

  // Wait for GPU to finish before accessing on host
  cudaDeviceSynchronize();

  // Check for errors (all values should be 3.0f)
  float maxError = 0.0f;
  for (int i = 0; i < N; i++)
    maxError = fmax(maxError, fabs(y[i]-3.0f));
  std::cout << "Max error: " << maxError << std::endl;

  // Free memory
  cudaFree(x);
  cudaFree(y);

  std::cout<<"free complete"<<std::endl;
  return 0;
}