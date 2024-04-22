#include <stdio.h>
#include "time.h"

int main() {
    int sh, sm, eh, em;
    do{
        printf("Input start time: ");
        scanf("%d %d", &sh, &sm );
    }while((sh < 0 || sh > 24) || (sm < 0 || sm > 60) );

    do{
        printf("Input end time: ");
        scanf("%d %d", &eh, &em );
    }while ( (eh < 0 || eh > 24) || (em < 0 || em > 60));

    T start = {sh, sm};
    T end = {eh, em};

    AllTime(start, end);
    return 0;
}