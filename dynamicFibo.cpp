#include <iostream>
#include <vector>

std::vector<int> sequence = {0}; //fibo sequence needs to be primed with 0 (0th digit of fibo is 0)
int dynamicFibo(int n){
    if(n <= 1){                                 // base case
        if (sequence.size() >= n+1) {             // if vector has answer
            return sequence[n];                       // return it
        } else {                                    // otherwise, calculate it
            sequence.insert(sequence.begin()+n, n); // and put it at the nth place
            return sequence[n]; // return the number after inserting it
        }
    }else{                           // recursive case
        if(sequence.size() >= n+1){  // if vector has answer
            return sequence[n];            // return it, no need to calculate again
        }else{                         // otherwise, calculate it
            int left = dynamicFibo(n - 1); // recursive call to get previous number
            int right = dynamicFibo(n - 2); // recursive call to get previous number (this is where the main benefit of dynamic programming comes in)
            sequence.insert(sequence.begin() + n, left + right); // add number at nth place
            return sequence[n];            // return it
        }
    }
}

int main() {
    srand(time(0));
    int result = dynamicFibo(32);
    std::cout << "Result: " << result << std::endl; 
    return 0;
}