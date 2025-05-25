#include <stdio.h>
int main(){
    float x, y;
    printf("Enter the values of the variables\nFor the example 1.0, 1.0\n");
    scanf("%f,%f", &x,&y);
    if((y<=0 && y>=-2) && (x>=-2 && x<=1))
        printf("The point with the specified coordinates (%f,%f) belongs to the shaded part of the plane\n",x,y);
    else if((y<=1 && y>=0) && (x<=-1 && x>=-2)) 
        printf("The point with the specified coordinates (%f,%f) belongs to the shaded part of the plane\n",x,y);
    else if((y<=-x) && (x>=-1 && x<=0) && (y>=0 && y<=1))
        printf("The point with the specified coordinates (%f,%f) belongs to the shaded part of the plane\n",x,y);
    else 
        printf("The peint with the specified coordinates (%f,%f) does not belong to the shaded part of the plame\n",x,y);
}
