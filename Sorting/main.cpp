//
//  main.cpp
//  Sort
//
//  Created by Иван Медведев on 02/03/2019.
//  Copyright © 2019 Medvedev. All rights reserved.
//

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <chrono>

using namespace std;

template < typename T >
void bubbleSort(T* arr, int size)
{
    T tmp;
    
    for(int i = 0; i < size - 1; ++i)
    {
        for(int j = 0; j < size - 1; ++j)
        {
            if (arr[j + 1] < arr[j])
            {
                tmp = arr[j + 1];
                arr[j + 1] = arr[j];
                arr[j] = tmp;
            }
        }
    }
}

template< typename T >
void selectSort(T* arr, int size)
{
    T tmp;
    for(int i = 0; i < size; ++i)
    {
        int pos = i;
        tmp = arr[i];
        for(int j = i + 1; j < size; ++j)
        {
            if (arr[j] < tmp)
            {
                pos = j;
                tmp = arr[j];
            }
        }
        arr[pos] = arr[i];
        arr[i] = tmp;
    }
}

template< typename T >
void insertSort(T* a, int size)
{
    T tmp;
    for (int i = 1, j; i < size; ++i) // цикл проходов, i - номер прохода
    {
        tmp = a[i];
        for (j = i - 1; j >= 0 && a[j] > tmp; --j) // поиск места элемента в готовой последовательности
            a[j + 1] = a[j];    // сдвигаем элемент направо, пока не дошли
        a[j + 1] = tmp; // место найдено, вставить элемент
    }
}

//SHELL
int increment(long inc[], long size)
{
    int p1, p2, p3, s;
    p1 = p2 = p3 = 1;
    s = -1;
    do
    {
        if (++s % 2)
        {
            inc[s] = 8*p1 - 6*p2 + 1;
        }
        else
        {
            inc[s] = 9*p1 - 9*p3 + 1;
            p2 *= 2;
            p3 *= 2;
        }
        p1 *= 2;
    }
    while(3*inc[s] < size);
    
    return s > 0 ? --s : 0;
}


template< typename T >
void shellSort(T a[], long size)
{
    long inc, i, j, seq[40];
    int s;
    
    s = increment(seq, size); // вычисление последовательности приращений
    while (s >= 0)  // сортировка вставками с инкрементами inc[]
    {
        inc = seq[s--];
        for (i = inc; i < size; ++i)
        {
            T temp = a[i];
            for (j = i; (j >= inc) && (temp < a[j-inc]); j -= inc) {
                a[j] = a[j - inc];
            }
            a[j] = temp;
        }
    }
}

//SHELL

template<typename T>
void quickSort(T* a, long N) {
    
    long i = 0, j = N;
    T temp, p;
    
    p = a[ N>>1 ];
    

    do {
        while ( a[i] < p ) i++;
        while ( a[j] > p ) j--;
        
        if (i <= j) {
            temp = a[i]; a[i] = a[j]; a[j] = temp;
            i++; j--;
        }
    } while ( i<=j );
    
    if ( j > 0 ) quickSort(a, j);
    if ( N > i ) quickSort(a+i, N-i);
}

//TournamentSort

//TournamentSort

//HeapSort
template< typename T >
void downHeap(T a[], long k, long n)
{
    //  процедура просеивания следующего элемента
    //  До процедуры: a[k+1]...a[n]  - пирамида
    //  После:  a[k]...a[n]  - пирамида
    T new_elem;
    long child;
    new_elem = a[k];
    
    while(k <= n/2) // пока у a[k] есть дети
    {
        child = 2*k;
        
        if( child < n && a[child] < a[child+1] ) //  выбираем большего сына
            child++;
        if( new_elem >= a[child] )
            break;
        // иначе
        a[k] = a[child];    // переносим сына наверх
        k = child;
    }
    a[k] = new_elem;
}

template< class T >
void heapSort(T a[], long size)
{
    long i;
    T temp;
    
    // строим пирамиду
    for(i = size / 2 - 1; i >= 0; --i)
        downHeap(a, i, size-1);
    
    // теперь a[0]...a[size-1] пирамида
    
    for(i=size-1; i > 0; --i)
    {
        // меняем первый с последним
        temp = a[i];
        a[i] = a[0];
        a[0] = temp;
        // восстанавливаем пирамидальность a[0]...a[i-1]
        downHeap(a, 0, i-1);
    }
}
//HeapSort

//MergeSort
void mergeSort(int *a, int n)
{
    int step = 1;  // шаг разбиения последовательности
    int *temp = new int[n]; // дополнительный массив
    while (step < n)  // пока шаг меньше длины массива
    {
        int index = 0;    // индекс результирующего массива
        int l = 0;      // левая граница участка
        int m = l + step;  // середина участка
        int r = l + step * 2;  // правая граница участка
        do
        {
            m = m < n ? m : n;  // сортируемый участок не выходит за границы последовательности
            r = r < n ? r : n;
            int i1 = l, i2 = m; // индексы сравниваемых элементов
            for (; i1 < m && i2 < r; ) // пока i1 не дошёл до середины и i2 не дошёл до конца
            {
                if (a[i1] < a[i2]) { temp[index++] = a[i1++]; } // заполняем участок результирующей последовательности
                else { temp[index++] = a[i2++]; }
            }
            // Или i1 < m или i2 < r - только один из операторов while может выполниться
            while (i1 < m) temp[index++] = a[i1++]; // заносим оставшиеся элементы сортируемых участков
            while (i2 < r) temp[index++] = a[i2++]; // в результирующий массив
            l += step * 2; // перемещаемся на следующий сортируемый участок
            m += step * 2;
            r += step * 2;
        } while (l < n); // пока левая граница сортируемого участка - в пределах последоватльности
        for (int i = 0; i < n; i++) // переносим сформированный массив обратно в a
            a[i] = temp[i];
        step *= 2; // увеличиваем в 2 раза шаг разбиения
    }
    delete [] temp;
}
//MergeSort

void binSort(int * A, int n)
{
    int x;
    int left;
    int  right;
    int sred;
    for (int i = 1;  i < n; i++)
        if (A[i-1] > A[i]){
            x = A[i];
            left = 0;
            right = i-1;
            do {
                sred = (left + right)/2;
                if  (A[sred] < x ) left = sred + 1;
                else  right = sred - 1;
            } while (left <= right);
            for (int j = i-1; j>=left; j--)
                A[j+1] = A[j];
            A[left] = x;
        }
}

void chelnochSort(int *a ,long N)
{
    for(int j=0;j<N-1;j++)
    {
        if(a[j]>a[j+1])
        {
            a[j]=a[j]+a[j+1];
            a[j+1]=a[j]-a[j+1];
            a[j]=a[j]-a[j+1];
            for(int i=j;i>0;i--)
            {
                if(a[i]<a[i-1])
                {
                    a[i]=a[i]+a[i-1];
                    a[i-1]=a[i]-a[i-1];
                    a[i]=a[i]-a[i-1];
                }
                else break;
            }
        }
    }
}



int main(int argc, const char * argv[]) {

    srand((unsigned int)time(0));
    typedef std::chrono::high_resolution_clock Clock;
    typedef std::chrono::microseconds microseconds;
    
    
    int n;
    cout << "Enter number of elements: ";
    cin >> n;
    cout << endl;
    int arr[n];
    for(int i=0;i<n;i++)
    {
        arr[i] = rand()%10+1;
    }
    
    for(int i=0;i<9;i++)
    {
        Clock::time_point start;
        Clock::time_point end;
        microseconds ms;
        switch (i) {
            case 0:
                start = Clock::now();
                bubbleSort(arr, n);
                end = Clock::now();
                ms = std::chrono::duration_cast<microseconds>(end - start);
                cout << "Bubble sort: " << fixed << (double)ms.count()/1000000  << " s" << endl;
                break;
            case 1:
                start = Clock::now();
                selectSort(arr, n);
                end = Clock::now();
                ms = std::chrono::duration_cast<microseconds>(end - start);
                cout << "Selection sort: " << fixed << (double)ms.count()/1000000  << " s" << endl;
                break;
            case 2:
                start = Clock::now();
                insertSort(arr, n);
                end = Clock::now();
                ms = std::chrono::duration_cast<microseconds>(end - start);
                cout << "Insertion sort: "<< fixed << (double)ms.count()/1000000  << " s" << endl;
                break;
            case 3:
                start = Clock::now();
                shellSort(arr, n);
                end = Clock::now();
                ms = std::chrono::duration_cast<microseconds>(end - start);
                cout << "Shell sort: " << fixed << (double)ms.count()/1000000  << " s" << endl;
                break;
            case 4:
                start = Clock::now();
                quickSort(arr, n);
                end = Clock::now();
                ms = std::chrono::duration_cast<microseconds>(end - start);
                cout << "Quick sort: " << fixed << (double)ms.count()/1000000  << " s" << endl;
                break;
            case 5:
                start = Clock::now();
                heapSort(arr, n);
                end = Clock::now();
                ms = std::chrono::duration_cast<microseconds>(end - start);
                cout << "Heap sort: " << fixed << (double)ms.count()/1000000  << " s" << endl;
                break;
            case 6:
                start = Clock::now();
                mergeSort(arr, n);
                end = Clock::now();
                ms = std::chrono::duration_cast<microseconds>(end - start);
                cout << "Merge sort: " << fixed << (double)ms.count()/1000000 << " s" << endl;
                break;
            case 7:
                start = Clock::now();
                binSort(arr, n);
                end = Clock::now();
                ms = std::chrono::duration_cast<microseconds>(end - start);
                cout << "Binary sort: "<< fixed << (double)ms.count()/1000000 << " s" << endl;
                break;
            case 8:
                start = Clock::now();
                chelnochSort(arr, n);
                end = Clock::now();
                ms = std::chrono::duration_cast<microseconds>(end - start);
                cout << "Chelnochnaya sort: " << fixed << (double)ms.count()/1000000 << " s"  << endl;
                break;
            default:
                break;
        }
    }
    /*
    for(int i=0;i<n;i++)
    {
        cout << arr[i] << endl;
    }
    */
    
    return 0;
}
