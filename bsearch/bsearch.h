/**
 * int bsearch(int[] arr, val, int f, int l);
 * returns: index of the found element or -1 if not found
 * arr: array to search in
 * val: value to search
 * f: first index of search range
 * l: last index of search range
 * 
 * bsearch should return the index where the element was found OR
 * the index where to insert if the element was not found.
 * 
 * Proof of correctness:
 * 1. The algo will find the value if it exists.
 * -> In every iteration, we eliminate the parts of array which cannot have the value and keep
 * on searching in remaining part of the array. To do this, array is divided into 3 parts
 * a. array[f] to array[mid-1]
 * b. array[mid+1] to array[l]
 * c array[mid]
 * Assuming array is sorted with no duplicate elements, the value can fall in ONLY one of the 3 parts.
 * Rest 2 can be discarded.
 * To identify which one, we compare the value with the mid element. Only 1 of the following 3 is possible:
 * A. value < middle element
 * B. value > middle element
 * C. value == middle element
 * 
 * <a1, a2, a3, a4, ... , an>, <middle element c>, <b1, b2, b3, ... , bm>
 * Since the array is sorted in ascending order, all the elements in part (a) of the array are less than middle element.
 * And all the elements in part (b) are greater than middle element.
 * 
 * Therefore,
 * If the value is less than middle element, it can only be found in part (a) of array.
 * If the value is greater than middle element, it can only be found in part (b) of array.
 * If the value is equal to middle element, we already found the element and discard both (a) and (b) and return the mid index.
 * If the size of the part we are searching in is 0, we can conclude that the value does not exist. In the implementation,
 * we identify the size 0 of any part in the next recusion by comparing f and l. Size is calculated as (l - f + 1).
 * Since size is integer, size<=0 is equivalent to size < 1, 
 *     (l - f + 1) < 1
 *     l - f < 0
 *     l < f
 * 
 * 2. The algo will return the expected position if the value does not exist.
 * -> For the cases where the value does not exist in the array, irrespective of the initial size of the array,
 * it is reduced to one of following scenarios:
 * a. f == l  => 1 element to search in
 * b. f == l-1  => 2 elements to search in
 * All other scenarios are reduced to one of these 2 scenarios because in all those scenarios, middle element is not same as f or l.
 * For (a) since there is only 1 element, f, l, and mid all point to same element. There are 2 cases which might follow:
 * (a.1) value < array element  =>  the value should be inserted in place of array element
 * (a.2) value > array element  =>  value should be inserted to right of array element
 * Depending on which one is the case above, the value of f in the next recursive call will be 
 * (a.1) f = f  =>  value inserted in place of first element
 * (a.2) f = mid+1  =>  f = f+1  =>  value inserted to right of first element
 * 
 * For (b), mid is always same as f due to integer arithmatic.
 * (b.1) value < middle element (first element)  =>  the value should be inserted in place of first element
 * (b.2) value > middle element (first element)  =>  the value should be inserted to right of first element
 * Depending on which one is the case above, the value of f in the next recursive call will be 
 * (b.1) f = f  =>  value inserted in place of array element
 * (b.2) f = mid + 1  => f = f + 1  =>  value inserted to right of first element
 * 
 * Therefore, in all cases (a.1, a.2, b.1 and b.2), the index represented by f points to the index where 
 * the value should be inserted. Hence, returning f will return the index where to insert the new element.
 * */

template <typename T>
long bsearch(T arr[], T val, long f, long l){
    if(f > l) return f;
    long mid = static_cast<long>((f/2.0)+(l/2.0));
    if(arr[mid] == val) return mid;
    if(arr[mid] > val) return bsearch(arr, val, f, mid - 1);
    else return bsearch(arr, val, mid + 1, l);
}