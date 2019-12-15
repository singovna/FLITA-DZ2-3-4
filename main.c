#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    int number;
    printf("Enter the number of edges: ");
    scanf("%d", &number);
    
    int **arr = calloc(number, sizeof(int*));
    
    printf("For each enter any number to connect the edges\n");
    printf("\t0 - edges not connected\n");
    printf("\t1 and more - edges connected with 'N' ribs\n");
    for(int i=0; i<number; i++){
        arr[i] = calloc(number, sizeof(int));
        for(int j=0; j<number; j++){
            printf("%d->%d: ",i, j);
            scanf("%d", &arr[i][j]);
        }
    }
    
    printf("\nPrinting graph:\n");
    int flag1 = 1;
    for(int i=0; i<number; i++){
        int flag2 = 0;
        for(int j=0; j<number; j++){
            if(arr[i][j] == 1)
                flag2 = 1;
            if(arr[j][i] == 1)
                flag2 = 1;
        }
        if(flag2 == 0)
            flag1=0;
    }
    if(flag1 == 0){
        printf("unrelated graph\n");
    } else {
        printf("related graph\n");
    }
    
    printf("* |");
    for(int i=0; i<number; i++)
        printf(" %d", i);
    
    printf("\n- +");
    for(int i=0; i<number; i++)
        printf(" -");
    printf("\n");
    
    for(int i=0; i<number; i++){
        printf("%d |", i);
        for(int j=0; j<number; j++){
            printf(" %d", arr[i][j]);
        }
        printf("\n");

    }
    
    for(int i=0; i<number; i++)
        if(arr[i][i] > 0)
            printf("Edge '%d' have %d loop(s)\n", i, arr[i][i]);
        
    FILE *fp=fopen("graph.dot", "w");
    if(fp == NULL) {
        printf("Unable to create file\n");
        exit(0);
    }

    fputs("digraph G {", fp);
    for(int i=0; i<number; i++){
        fputc(i+'0', fp);
        fputs("; ", fp);
    }
    for(int i=0; i<number; i++){
        for(int j=0; j<number; j++){
            for(int k=0; k<arr[i][j]; k++){
                fputc(i+'0', fp);
                fputs("->", fp);
                fputc(j+'0', fp);
                fputs("; ", fp);
            }
        }
    }
    fputs("}", fp);
    fclose(fp);
    
    free(arr);
    return 0;
}
