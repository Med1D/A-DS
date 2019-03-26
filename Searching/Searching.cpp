//
//  main.cpp
//  Lab2
//
//  Created by Иван Медведев on 26/03/2019.
//  Copyright © 2019 Medvedev. All rights reserved.
//

#include <iostream>
#include <chrono>
#include <string.h>
#include <ctime>
#include <stdlib.h>

# define NO_OF_CHARS 256
#define tonum(c) (c >= 'A' && c <= 'Z' ? c - 'A' : c - 'a' + 26)

using namespace std;

//KMP
void preKMP(string pattern, int f[])
{
    int m = pattern.length(), k;
    f[0] = -1;
    for (int i = 1; i < m; i++)
    {
        k = f[i - 1];
        while (k >= 0)
        {
            if (pattern[k] == pattern[i - 1])
                break;
            else
                k = f[k];
        }
        f[i] = k + 1;
    }
}

//check whether target string contains pattern
bool KMP(string pattern, string target)
{
    int m = pattern.length();
    int n = target.length();
    int f[m];
    preKMP(pattern, f);
    int i = 0;
    int k = 0;
    while (i < n)
    {
        if (k == -1)
        {
            i++;
            k = 0;
        }
        else if (target[i] == pattern[k])
        {
            i++;
            k++;
            if (k == m)
                return 1;
        }
        else
            k = f[k];
    }
    return 0;
}
//KMP

//BM
// A utility function to get maximum of two integers
int max(int a, int b)
{
    return (a > b) ? a : b;
}

// The preprocessing function for Boyer Moore's bad character heuristic
void badCharHeuristic(char *str, int size, int badchar[NO_OF_CHARS])
{
    int i;
    
    // Initialize all occurrences as -1
    for (i = 0; i < NO_OF_CHARS; i++)
        badchar[i] = -1;
    
    // Fill the actual value of last occurrence of a character
    for (i = 0; i < size; i++)
        badchar[(int) str[i]] = i;
}

int BM(char *txt, char *pat)
{
    int m = strlen(pat);
    int n = strlen(txt);
    
    int badchar[NO_OF_CHARS];
    
    badCharHeuristic(pat, m, badchar);
    
    int s = 0; // s is shift of the pattern with respect to text
    while (s <= (n - m))
    {
        int j = m - 1;
        
        while (j >= 0 && pat[j] == txt[s + j])
            j--;
        
        if (j < 0)
        {
            //printf("\npattern occurs at shift = %d\n", s);
            return s;
            
            s += (s + m < n) ? m - badchar[txt[s + m]] : 1;
            
        }
        
        else
            s += max(1, j - badchar[txt[s + j]]);
    }
    return 0;
}
//BM

//RK
int mod(int a,int p,int m)
{
    if (p == 0)
        return 1;
    int sqr = mod(a,p/2,m) % m;
    
    if (p & 1)
        return ((a % m) * sqr) % m;
    else
        return sqr;
}

int RabinKarpMatch(char *T,char *P,int d,int q)
{
    int i,j,p,t,n,m,h,found;
    n = strlen(T);
    m = strlen(P);
    h = mod(d,m-1,q);
    p = t = 0;
    
    for (i=0; i<m; i++)
    {
        p = (d*p + tonum(P[i])) % q;
        t = (d*t + tonum(T[i])) % q;
    }
    
    for (i=0; i<=n; i++)
    {
        if (p == t)
        {
            found = 1;
            for (j=0; j<m; j++)
                if (P[j] != T[i+j])
                {
                    found = 0;
                    break;
                }
            if (found)
                return i+1;
        }
        else
        {
            t = (d*(t - ((tonum(T[i])*h) % q)) + tonum(T[i+m])) % q;
        }
    }
    return -1;
}
//RK






int main(int argc, const char * argv[]) {
    
    srand(time(0));
    typedef std::chrono::high_resolution_clock Clock;
    typedef std::chrono::microseconds microseconds;
    Clock::time_point start;
    Clock::time_point end;
    microseconds ms;
    
    
    
    int numberOfElements = 1000000;
    
    char text[numberOfElements];
    char pattern[] = "abba";
    double sumTime = 0;
    
    for(int i=0;i<numberOfElements;i++) {
        if(rand()%2) {
            text[i] = 'a';
        }
        else {
            text[i] = 'b';
        }
    }
    
    
    for(int i=0;i<numberOfElements;i++) {
        start = Clock::now();
        KMP(pattern, text);
        end = Clock::now();
        ms = std::chrono::duration_cast<microseconds>(end - start);
        sumTime += (double)ms.count()/1000000;
    }
    cout <<"KMP: " << fixed << sumTime/(double)numberOfElements << " s\n";
    
    sumTime = 0;
    
    for(int i=0;i<numberOfElements;i++) {
        start = Clock::now();
        BM(text, pattern);
        end = Clock::now();
        ms = std::chrono::duration_cast<microseconds>(end - start);
        sumTime += (double)ms.count()/1000000;
    }
    cout <<"BM: " << fixed << sumTime/(double)numberOfElements << " s\n";
    
    sumTime = 0;
    
    for(int i=0;i<numberOfElements;i++) {
        start = Clock::now();
        RabinKarpMatch(text, pattern, 1, 1000);
        end = Clock::now();
        ms = std::chrono::duration_cast<microseconds>(end - start);
        sumTime += (double)ms.count()/1000000;
    }
    cout <<"RK: " << fixed << sumTime/(double)numberOfElements << " s\n";
    
    
//    for(int i=0;i<numberOfElements;i++) {
//        cout << text[i];
//    }
    
    
    
    return 0;
}
