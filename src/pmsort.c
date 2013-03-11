#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include "common.h"

#define NUM 1000000
#define DEBUG 0
#define Int32   int
#define UInt32  unsigned int
#define Char    char
#define UChar   unsigned char
#define Int16   short
#define UInt16  unsigned short
#define Bool    char

#define THRESH 1000

typedef int cmp_func (UChar *tblock, Int32 tlast,
		      UInt16 *tquadrant, Int32 *tworkDone,
		      Int32 a, Int32 b);

void df_simpleSort ( UChar *block, Int32 last, Int32 *zptr, UInt16 *quadrant,
		     Int32 *workDone_p, Int32 workLimit, Bool firstAttempt,
		     Int32 lo, Int32 hi, Int32 d );

int cmp (UChar *tblock, Int32 tlast,
	 UInt16 *tquadrant, Int32 *tworkDone,
	 Int32 a, Int32 b)
{
  return a>b;
}

void merge_sort_serial (Int32 *A, Int32 left, Int32 right, UChar *tblock, Int32 tlast,
			UInt16 *tquadrant, Int32 *tworkDone, cmp_func cmp, Int32 d)
{
  if (right <= left) return;

  Int32 mid = (left+right)/2;

  merge_sort_serial (A, left, mid, tblock, tlast, tquadrant, tworkDone, cmp, d);
  merge_sort_serial (A, mid+1, right, tblock, tlast, tquadrant, tworkDone, cmp, d);

  merge (A, left, mid+1, right, tblock, tlast, tquadrant, tworkDone, cmp, d);
}

void merge_sort_parallel (Int32 *A, Int32 left, Int32 right, UChar *tblock, Int32 tlast,
			  UInt16 *tquadrant, Int32 *tworkDone, cmp_func cmp, Int32 d)
{
#pragma omp parallel shared (A)
  {
#pragma omp single
    {
      merge_sort_parallel_1 (A, left, right, tblock, tlast, tquadrant, tworkDone, cmp, d);
    }
  }
}

void merge_sort_parallel_1 (Int32 *A, Int32 left, Int32 right, UChar *tblock, Int32 tlast,
			  UInt16 *tquadrant, Int32 *tworkDone, cmp_func cmp, Int32 d)
{
  if (right-left <= THRESH)
    {
      Bool flag;
      int wlim = 1000000000;
      //df_qSort3 ( tblock, tlast, A, tquadrant, tworkDone, 1000000, 0, left, right, 0 );
      df_simpleSort ( tblock, tlast, A, tquadrant, tworkDone, 1000000, 0, left, right, 0 );
      //merge_sort_serial (A, left, right, tblock, tlast, tquadrant, tworkDone, cmp, d);
      return;
    }
  //if (right <= left) return;

  Int32 mid = (left+right)/2;

#pragma omp task shared (A)
    merge_sort_parallel_1 (A, left, mid, tblock, tlast, tquadrant, tworkDone, cmp, d);

#pragma omp task shared (A)
    merge_sort_parallel_1 (A, mid+1, right, tblock, tlast, tquadrant, tworkDone, cmp, d);

#pragma omp taskwait
  merge (A, left, mid+1, right, tblock, tlast, tquadrant, tworkDone, cmp, d);
}

void merge (Int32 *A, Int32 left, Int32 mid, Int32 right, UChar *tblock, Int32 tlast,
	    UInt16 *tquadrant, Int32 *tworkDone, cmp_func cmp, Int32 d)
{
  int i, left_end, num_elements, tmp_pos;

  left_end = mid - 1;
  tmp_pos = 0;
  num_elements = right - left + 1;

  if (DEBUG)
    printf("left=%d,right=%d,mid=%d\n",left,right,mid);

  int *temp = (int *)malloc (num_elements*sizeof(int));

  if (!temp)
    {
      printf ("Insufficient memory!x");
      return;
    }

  while ((left <= left_end) && (mid <= right))
  {
    //if (A[left] <= A[mid])
    if (!cmp (tblock, tlast, tquadrant, tworkDone, A[left], A[mid]))
    {
      temp[tmp_pos] = A[left];
      tmp_pos = tmp_pos + 1;
      left = left +1;
    }
    else
    {
      temp[tmp_pos] = A[mid];
      tmp_pos = tmp_pos + 1;
      mid = mid + 1;
    }
  }

  while (left <= left_end)
  {
    temp[tmp_pos] = A[left];
    left = left + 1;
    tmp_pos = tmp_pos + 1;
  }

  while (mid <= right)
  {
    temp[tmp_pos] = A[mid];
    mid = mid + 1;
    tmp_pos = tmp_pos + 1;
  }

  int temp_len = num_elements-1;
  
  for (i=0; i < num_elements; i++)
  {
    A[right] = temp[temp_len];
    right = right - 1;
    temp_len = temp_len-1;
  }

  if (DEBUG)
    {
      for (i = 0; i < num_elements; i++)
	printf ("%d,",A[i]);
      printf ("\n");
    }
  
  if (!temp)
    free (temp);

  return 0;
}

#define printarray(A) do{		     \
  fprintf (stderr, "===print array===\n");   \
  int i;				     \
  for (i=0; i < sizeof(A)/sizeof(A[0]); i++) \
    fprintf (stderr, "%d,", A[i]);	     \
  fprintf (stderr, "\n");		     \
  }while (0);

/* int main (int argc, char **argv) */
/* { */
/*   Int32 A[NUM]={0}; */
/*   int i; */
  
/*   for (i = 0; i < NUM; i++) A[i]=i*1023%97; */
/*   //printarray(A); */

/*   struct timeval *start = (struct timeval *) malloc (sizeof (struct timeval)); */
/*   struct timeval *end = (struct timeval *) malloc (sizeof (struct timeval)); */
/*   gettimeofday (start, NULL); */
/*   merge_sort_parallel (A, 0, sizeof (A)/sizeof(A[0])-1, NULL, 0, NULL, NULL, cmp, 0); */
/*   gettimeofday (end, NULL); */
/*   fprintf (stderr, "** [parallel version]: execution time: %.5f seconds\n", tdiff (end,start)); */

/*   gettimeofday (start, NULL); */
/*   merge_sort_serial (A, 0, sizeof (A)/sizeof(A[0])-1, NULL, 0, NULL, NULL, cmp, 0); */
/*   gettimeofday (end, NULL); */
/*   fprintf (stderr, "** [serial version]: execution time: %.5f seconds\n", tdiff (end,start)); */

/*   //printarray(A); */
/*   fprintf (stderr, "\n"); */
/* } */
