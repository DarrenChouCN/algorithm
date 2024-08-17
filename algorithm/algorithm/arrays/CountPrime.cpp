#include <iostream>
#include <vector>
using namespace std;

/*
Count Primes

Given an integer n, return the number of prime numbers that are strictly less than n.

Sieve of Eratosthenes Algorithm
1. Create a boolean array 'isPrime' of size n, initialized to true. 'isPrime[i]' will be true if i is a prime number, otherwise false.
2. Start with the first prime number 2. Mark all its multiples as non-prime.
3. Move to next number in the list and repeat the marking process for its multiples. Continue this process until you've processed all numbers up to the square root of n.
4. Finally, count the number of true values in the isPrime array, which represents the prime numbers.

Time Complexity: O(nloglogn)
Space Complexity: O(n)
*/

/*
About Sieve of Eratosthenes Algorithm
1. The Sieve of Eratosthenes initializes an array, assuming all numbers less than n (except 0 and 1) are prime (true). Through multiplication and addition, non-prime numbers are identified and marked as false in the array. This method ensures that every non-prime number is eventually marked, even though the marking process occurs in a non-sequential manner.
2. It is observed that the sum of a prime number and a non-prime number always results in a non-prime number. Therefore, in the early iterations, the marking process (isPrime[j] = false;) is more intensive, with more values being marked. As iterations progress, fewer marking operations are needed, as many values have already been marked false in previous steps, leading to a faster execution in later stages.
*/

int countPrimes(int n) {
    if (n <= 2) return 0;

    vector<bool> isPrime(n, true);
    isPrime[0] = isPrime[1] = false; // 0 and 1 are not prime numbers

    for (int i = 2; i * i < n; ++i) {
        if (isPrime[i]) {
            for (int j = i * i; j < n; j += i) {
                isPrime[j] = false;
            }
        }
    }
    return count(isPrime.begin(), isPrime.end(), true);
}