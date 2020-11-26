#include "Queue.h"
#include <iostream>

/*
Write a program that finds prime numbers using the Sieve of Erastosthenes, an algorithm devised by a Greek mathematician
of the same name who lived in the third century BC. The algorithm finds all prime numbers up to some maximum value n, 
as described by the following pseudocode:

Create a queue of numbers to process.
Fill the queue with the integers 2 through n inclusive
Create an empty result queue to store primes.
Repeat the following steps:
Obtain the next prime p by removing the first value from the queue of numbers.
     Put p into the result queue of primes.
Loop through the queue of numbers, eliminating all numbers that are divisible by p.
while (p is less than the square root of n).

All remaining values in the numbers queue are prime, so transfer them to the result primes queue.

EXAMPLE:
Following are the prime numbers smaller than or equal to 30
2 3 5 7 11 13 17 19 23 29 
*/

Queue <int> SieveOfEratosthenes(int n) {
    // TODO: 
    Queue<int> numbers;
    Queue<int> temp;
    Queue<int> result;
    int i, x, p = 0;
    
    for (i = 2; i <= n; i++)
    {
        numbers.enqueue(i);
    }
    
    while (p * p < n)
    {
        p = numbers.dequeue();
        result.enqueue(p);
        
        while (!numbers.isEmpty())
        {
            x = numbers.dequeue();
            
            if (x % p != 0)
            {
                temp.enqueue(x);
            }
        }
        
        while (!temp.isEmpty())
        {
            numbers.enqueue(temp.dequeue());
        }
    }
    
    while (!numbers.isEmpty())
    {
        result.enqueue(numbers.dequeue());
    }
    
    return result;
}
