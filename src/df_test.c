#define N 100

int A[N], B[N];

int main ()
{
  foo ();
}

void foo ()
{
  int i;
  for (i = 0; i < N; i++){
    A[i] = i*i;
  }
  for (i = 0; i < N; i++){
    B[i] = A[i];
  }
  for (i=0; i < N; i++){
    printf ("%d ", B[i]);
  }
}

void stream_foo ()
{
  int i;

  int serializer __attribute__ ((stream));
  
#pragma omp task output (serializer)
  serializer = 0;

  for (i = 0; i < N; i++){
#omp task output (stream1[i] << x_out)
    x_out = i*i;
  }
  for (i = 0; i < N; i++){
#omp task input (stream1[i] >> y_in) output (stream2[i] << y_out)
    {
      y_out = y_in;
      printf ("%d ", y_out);
    }
  }
  for (i=0; i < N; i++){
#omp task input (stream2[i] >> z_in) input (serializer) output (serializer)    
    printf ("%d ", z_in);
  }
}
