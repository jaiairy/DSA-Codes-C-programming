//Enter marks of 20 student and print the sum
//Author: Jai Airy ; Date: 09/01/2025

#include<stdio.h>
int main(){
int sum=0;
int a[20];
for(int i=0;i<20;i++){
printf("Enter the marks of student:");
scanf("%d",&a[i]);
sum+=i;
}
printf("Sum of the marks of students is: %d",sum);
}