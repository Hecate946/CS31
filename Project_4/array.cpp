#include <iostream>
#include <string>
using namespace std;

int appendToAll(string a[], int n, string value) {
    if (n < 0) { // n must be greater than zero
        return -1;
    }
    for (int i = 0; i < n; i++) { // iterate through array
        a[i] += value; // append value to each element in array
    }
    return n;
}

int lookup(const string a[], int n, string target) {
    if (n < 0) { // n must be greater than zero
        return -1;
    }
    for (int i = 0; i < n; i++) { // iterate through array
        if (a[i] == target) { // match found, return index
            return i;
        }
    }
    return -1; // no match found.
}

int positionOfMax(const string a[], int n) {
    if (n <= 0) // negative n not allowed, n = 0 is no interesting elements.
        return -1;
    int maxElementIndex = 0; // store index of max element, start from first elem.
    for (int i = 0; i < n; i++) { // iterate through array
        if (a[i] >= a[maxElementIndex]) { // found a max element
            maxElementIndex = i; // store then continue checking the array.
        }
    }
    return lookup(a, n, a[maxElementIndex]); // return first occurence of the max element.
}

int rotateLeft(string a[], int n, int pos) {
    if (pos > n - 1 || n <= 0) // we only are looking at n elements, so pos must be <= n-1.
        return -1; // if n <= 0, position is negative, so not valid.
    string lastElem = a[pos]; // store popped element.
    for (int i = pos; i < (n - 1); i++) {
        a[i] = a[i + 1]; // move each element one spot to the left
    }
    a[n-1] = lastElem; // replace popped element
    return pos;
}

int countRuns(const string a[], int n){
    if (n < 0) // n must be positive.
        return -1;
    int counter = (n == 0) ? n : 1; // if n is zero, counter is zero, else first item increments.
    string identicalItem = a[0];
    for (int i = 0; i < n; i++) {
        if (identicalItem != a[i]) {
            counter++; // found a new item, increase counter.
            identicalItem = a[i];
        }
    }
    return counter;
}

int flip(string a[], int n) {
    if (n < 0) // n must be positive.
        return -1;
    if (n == 0) // no items to flip
        return 0;
    // start and end indexes
    int start = 0;
    int end = n - 1;
    while (start < end) { // move through array, swapping front and back elements.
        string temp = a[start];
        a[start] = a[end];
        a[end] = temp;
        start++;
        end--;
    }
    return n;
}


int differ(const string a1[], int n1, const string a2[], int n2) {
    if (n1 < 0 || n2 < 0) // n's must be positive.
        return -1;
    int n = (n1 < n2) ? n1 : n2; // use smallest n
    for (int i = 0; i < n; i++) {
        if (a1[i] != a2[i])
            return i; // found differing item, return index
    }
    return n; // no differing items, return smallest n
}


int subsequence(const string a1[], int n1, const string a2[], int n2) {
    if (n1 < 0 || n2 < 0)
        return -1;
    if (n2 == 0)
        return 0;
    if (n2 > n1)
        return -1;
    int returnIndex = -1;
    for (int i = 0; i < n1; i++) {
        if (a1[i] == a2[0]) {// found a match item
            returnIndex = i; // store index
            for (int j = 0; j < n2; j++) { // check remaining items in a2 to ensure subsequence
                if (a2[j] != a1[i + j]) // item match failed, no subsequence found.
                    returnIndex = -1; // reset index
            }
            if (returnIndex != -1) // subsequence found.
                break;
        }

    }
    return returnIndex;
}

int lookupAny(const string a1[], int n1, const string a2[], int n2) {
    if (n1 <= 0 || n2 <= 0) // n1 and n2 must be positive
        return -1;
    for (int i = 0; i < n1; i++) { // iterate through both arrays
        for (int j = 0; j < n2; j++) {
            if (a1[i] == a2[j]) // found a match! return index.
                return i;
        } 
    }
    return -1; // no match found :(
}

int split(string a[], int n, string splitter) {
    if (n < 0) // n must be positive
        return -1;
    string temp;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j + 1 < n - i; j++) {
            if (a[j] > a[j + 1]) {
                    temp = a[j];
                    a[j] = a[j + 1];
                    a[j + 1] = temp;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        if (a[i] >= splitter)
            return i;
    }
    return n;
}

int main() {}