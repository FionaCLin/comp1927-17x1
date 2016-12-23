#include <stdio.h>
#include <stdlib.h>

int binarySearch(int a[],int n,int key);

int main(void){
    int size;
    int key;
    int i;
    printf("Enter number of elements:");
    scanf("%d",&size);
    //printf("Enter key to search for:");
    //scanf("%d",&key);
    key = -99;
    
    int * a = malloc(size * sizeof(int));   
    printf("Enter elements:\n"); 
    for(i=0;i<size;i++){
	    scanf("%d",&a[i]);
    }
    printf("Binary search\n");   
    int result = binarySearch(a,size,key);
    if(result != -1){
        printf ("Found at index %d\n",result);
    }else{
	printf ("Did not find element\n");
    }
    return 0;
}

//An iterative binary search
int binarySearch(int a[],int n,int key){
   int r = n-1;
   int l = 0;
   int result = -1; //-1 indicates not found
   while(r >= l && result == -1){
      int mid = (l+r)/2;
      if(key == a[mid]){
          result = mid;
      } else {
          if(key < a[mid]){
              r = mid-1;
          } else {
              l = mid+1;
          }
      }
   }
   return result; 
}
