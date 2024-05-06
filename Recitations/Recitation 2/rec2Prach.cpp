#include <iostream>
#include <chrono>
using namespace std::chrono;
using namespace std;

void mergeSort(double*, int, int);
void merge(double*, int, int, int);
void insertionSort(double*, int);
void selectionSort(double*, int);
void quickSort(double*, int , int);
int partition(double*, int, int);

// Insertion Sort

void insertionSort(double* arr, int arr_size){
    double key;
    int j;
    for(int i = 0; i < arr_size; i++)
    {
        key = arr[i];
        j = i-1;
        while(j >= 0 && arr[j] > key){
            arr[j+1] = arr[j];
            j -= 1;
        }
        arr[j+1] = key;
    }
}

// Merge Sort

void mergeSort(double* arr, int p, int r)
{
    if(p < r)
    {
        int q =  (p+(r-1))/2;
        mergeSort(arr,p,q);
        mergeSort(arr,q+1,r);
        merge(arr,p,q,r);
    }
    return;
}

void merge(double* arr, int p, int q, int r)
{
    // Size of left side of array
    int n1 = q - p + 1;
    // Size of right side of array
    int n2 = r - q;

    // Initializing new arrays of corresponding sizes of the left and right
    double* left = new double[n1];
    double* right = new double[n2];

    for(int i = 0; i < n1; i++)
    {
        left[i] = arr[p+i];
    }

    for(int j = 0; j < n2; j++)
    {
        right[j] = arr[q+j+1];
    }

    int i = 0;
    int j = 0;
    int k = p;
    while(i < n1 && j < n2)
    {
        if(left[i] <= right[j])
        {
            arr[k] = left[i];
            i++;
            k++;
        }
        else
        {
            arr[k] = right[j];
            j++;
            k++;
        }
    }
    for(i; i<n1;i++)
    {
        arr[k] = left[i];
        k++;
    }
    for(j; j<n2;j++)
    {
        arr[k] = right[j];
        k++;
    }
}

// Selection Sort
void selectionSort(double* arr, int arr_size)
{
    double temp;
    for(int i = 0; i < arr_size; i++)
    {
        for(int j = i + 1; j < arr_size; j++)
        {
            if(arr[j] < arr[i])
            {
                temp = arr[j];
                arr[j] = arr[i];
                arr[i] = temp;
            }
        }
    }
}

// Quick Sort : r starts at arr_size - 1
void quickSort(double* arr, int p, int r)
{
    if(p < r)
    {
        int q = partition(arr,p,r);
        quickSort(arr,p,q-1);
        quickSort(arr,q+1,r);
    }
}

void exchange(double* val1, double* val2)
{
    double* temp = (double*)malloc(sizeof(double));
    *temp = *val1;
    *val1 = *val2;
    *val2 = *temp;
}

int partition(double* arr, int p, int r)
{
    double temp;
    double x = arr[r];
    int i = p - 1;
    for(int j = p; j < r; j++)
    {
        if(arr[j] <= x)
        {   
            i++;
            exchange(&arr[i],&arr[j]);
            //temp = arr[i];
            //arr[i] = arr[j];
            //arr[j] = temp;
        }
    }
    exchange(&arr[i+1],&arr[r]);
    //temp = arr[i+1];
    //arr[i+1] = arr[r];
    //arr[r] = temp;
    return i+1;
}

double* genRandNums(int size)
{
    int max = 10000;
    int min = 1000;
    srand(time(NULL)+clock());
    double* arr = (double*)malloc(size*sizeof(double));
    for(int i = 0; i < size; i++)
    {
        double random = (rand()%(max-min) + min)/10.0;
        arr[i] = random;
    }
    return arr;
}


int main()
{
    int test_sizes[] = {10000, 25000, 50000, 100000, 150000, 200000};
    int len_test_sizes = sizeof(test_sizes) / sizeof(int);
    double* test_case_arr;
    double* sorted_arr;
    steady_clock::time_point t1;
    steady_clock::time_point t2;
    nanoseconds time_span;
    double* test = genRandNums(10);
    double* res = (double*)malloc(sizeof(double)*10);

    //double* res = (double*)malloc(sizeof(double)*10);
    //memcpy(res,test,sizeof(double)*10);
    //insertionSort(res,10);
    for(int i = 0; i < len_test_sizes; i++)
    {
        cout<< "Test case: n = " << test_sizes[i] << "\n" << endl;
        test_case_arr = genRandNums(test_sizes[i]);
        sorted_arr = (double*)malloc(sizeof(double)*test_sizes[i]);
        memcpy(sorted_arr, test_case_arr,sizeof(double)*test_sizes[i]);

        // Insertion Sort
        t1 = steady_clock::now();
        insertionSort(sorted_arr, test_sizes[i]);
        t2 = steady_clock::now();
        time_span = duration_cast<nanoseconds>(t2 - t1);
        cout << "Insertion sort: " << time_span.count()/1000000 << " ms"<< endl;
        
        memcpy(sorted_arr, test_case_arr,sizeof(double)*test_sizes[i]);
        
        // Merge Sort
        t1 = steady_clock::now();
        mergeSort(sorted_arr, 0, test_sizes[i]);
        t2 = steady_clock::now();
        time_span = duration_cast<nanoseconds>(t2 - t1);
        cout << "Merge sort: " << time_span.count()/1000000 << " ms" << endl;

        memcpy(sorted_arr, test_case_arr,sizeof(double)*test_sizes[i]);

        // Selection Sort
        t1 = steady_clock::now();
        selectionSort(sorted_arr, test_sizes[i]);
        t2 = steady_clock::now();
        time_span = duration_cast<nanoseconds>(t2 - t1);
        cout << "Selection sort: " << time_span.count()/1000000 << " ms" << endl;

        memcpy(sorted_arr, test_case_arr,sizeof(double)*test_sizes[i]);

        // Quick Sort
        t1 = steady_clock::now();
        quickSort(sorted_arr, 0, test_sizes[i]);
        t2 = steady_clock::now();
        time_span = duration_cast<nanoseconds>(t2 - t1);
        cout << "Quick sort: " << time_span.count()/1000000 << " ms\n" << endl;
    

        test_case_arr = NULL;
        sorted_arr = NULL;

    }
}