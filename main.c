#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

char *InfinityArray(void){
    int array_size=1;
    char *arr,c;
    arr = calloc(array_size+1, sizeof(char));

    int i = 0;
    while((c=getchar()) != ';'){
        if( ('0' <= c && c <= '9') || ('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z')){ //[a-zA-Z0-9]
            char *temp_arr;
            temp_arr = calloc(array_size+1, sizeof(char));
            
            for(int cl = 0; cl < array_size; cl++){
                temp_arr[cl] = arr[cl];
            }
            
            arr[array_size-1]=c;
            array_size++;
            i++;
            free(temp_arr);
        }
        else if(c == '\n'){
            return arr;
            
        }
    }
    arr[array_size-1]='\0';
    return arr;
}

int main(){
    int digraph = -1;
    
    char temp_graph[64] = {0};
    
    while(digraph == -1){
        printf("Use graph or digraph:\n> ");
        scanf("%s", temp_graph);
        if( strcmp(temp_graph, "graph") == 0){
            digraph = 0;
        } else if( strcmp(temp_graph, "digraph") == 0) {
            digraph = 1;
        } else {
            printf("Enter valid parameter\n");
        }
    }
    
    printf("Enter amount of elements:\n> ");
    int amount;
    scanf("%d",&amount);
    if (amount <= 0)
        exit(9);
    
    printf("Enter amount of ribs:\n> ");
    int ribs;
    scanf("%d",&ribs);
    if (ribs <= 0)
        exit(9);

    
    printf("Enter names of elements separated by ';':\n");
    printf("! You could enter characters [a-zA-Z] and numbers [0-9]\n");
    printf("! All another symbols will be ignored)\n");

    
    char *name_elements[amount];
    int conn_elements[amount][amount];
    int matrx_elements[amount][ribs];
    for(int i=0; i<amount; i++){
        for(int j=0; j<amount; j++){
            conn_elements[i][j] = 0;
        }
        for(int j=0; j<ribs; j++){
            matrx_elements[i][j] = 0;
        }
    }
    
    _Bool flag_one=1;
    getchar();
    while(flag_one){
        printf("> ");
        int duplicate = 0;
        for(int i=0; i<amount; i++){
            name_elements[i] = InfinityArray();
        }
        
        for(int i=0; i<amount; i++){
            for (int j=0; j<amount; j++){
                if( strcmp(name_elements[i], name_elements[j]) == 0 && i != j ){
                    duplicate++;
                }
            }
        }
        
        if(duplicate != 0){
            printf("[Error] You enter 2 or more identical elements\n Retype it...\n");
        } else {
            flag_one=0;
        }
    }
    
    printf("Enter matrix\n");
    
    for(int i=0; i<amount; i++){
        printf("%s\t", name_elements[i]);
        for(int j=0; j<ribs; j++){
            scanf("%d", &matrx_elements[i][j]);
        }
    }
    
    int error = 0;
    for(int j=0; j<ribs; j++){
        int first_element = -1, second_element = -1;
        int temp1 = 0, temp2 = 0;
        for(int i=0; i<amount; i++){
            if(matrx_elements[i][j] != 0){
                if(first_element == -1){
                    first_element = i;
                    temp1 = matrx_elements[i][j];
                } else if(second_element == -1){
                    second_element = i;
                    temp2 = matrx_elements[i][j];
                } else {
                    error = 1;
                    j = ribs;
                    i = amount;
                }
            }
        }
        if(first_element != -1 && second_element == -1 && temp1 == 2 && temp2 == 0){
            conn_elements[first_element][first_element] += 2;
        } else if(first_element != -1 && second_element != -1 && temp1 == 1 && temp2 == -1){
            conn_elements[first_element][second_element] += 1;
        } else if(first_element != -1 && second_element != -1 && temp1 == -1 && temp2 == 1){
            conn_elements[second_element][first_element] += 1;
        } else {
            error = 1;
            j = ribs;
        }
    }
    if(error){
        printf("matrix not valid\n");
        exit(9);
    }

    
    
    /*
    getchar();
    printf("Enter for each one connection separated by ';', for input press enter:\n");
    for(int i=0; i<amount; i++){
        printf("'%s'> ",name_elements[i]);
        _Bool flag=1;
        while(flag){
            char *compare;
            compare = InfinityArray();
            
            for(int j=0; j<amount; j++){
                if( strcmp(compare, name_elements[j]) == 0){
                    conn_elements[i][j]++;
                }
//                if(i==j){
//                    conn_elements[i][j] = '-';
//                }

            }

            if(strcmp(compare, "") == 0){
                flag = 0;
            }
            free(compare);
        }
    }
    */
    _Bool flag=1;
    while(flag){
        printf("Print Table? (y/n)\n");
        char answer;
        scanf("%c",&answer);getchar();
        if(answer == 'y' || answer == 'Y'){
            printf("--------------------\n"); //related graph / unrelated graph
            _Bool relat_graph = 1; //
            for(int i=0; i<amount; i++){
                _Bool temp_relat_graph = 0; // 0 - no conn
                for(int j=0; j<amount; j++){
                    if(conn_elements[i][j] == 1)
                        temp_relat_graph = 1;
                    
                    if(conn_elements[j][i] == 1)
                        temp_relat_graph = 1;
                }
                if(temp_relat_graph == 0)
                    relat_graph=0;
            }
            if(relat_graph == 0){
                printf("unrelated graph\n");
            } else {
                printf("related graph\n");

            }
            printf("--------------------\n\t");

            for(int i=0;i<amount;i++){
                printf("%c%c%c.\t",name_elements[i][0], name_elements[i][1], name_elements[i][2]);
            }
            printf("\n");
            for(int i=0; i<amount; i++) {
                printf("%s\t", name_elements[i]);
                for (int j=0; j<amount; j++) {
                    printf("%d\t", conn_elements[i][j]);
                }
                printf("\n");
            }
 
            flag=0;
        } else if (answer == 'n' || answer == 'N'){
            flag=0;
        } else {
            printf("Enter valid parameter\n");
        }
    }
    
    
    FILE *fp=fopen("graph.dot", "w");
    if(fp == NULL) {
        printf("Unable to create file\n");
        exit(0);
    }
    
    char *string;
//    string = (char*)malloc(sizeof(char));
    string = calloc(2048, sizeof(char));
    char arrow[3] = "";
    if(digraph == 1){
        strcat(string, "digraph G {");
        strcat(arrow, "->");
    } else {
        strcat(string, "graph G {");
        strcat(arrow, "--");
    }
    for(int i=0; i<amount; i++){
        strcat(string, name_elements[i]);
        strcat(string, "; ");
    }
    for(int i=0; i<amount; i++){
        for(int j=0; j<amount; j++){
            for(int k=0; k<conn_elements[i][j]; k++){
                strcat(string, name_elements[i]);
                strcat(string, arrow);
                strcat(string, name_elements[j]);
                strcat(string, "; ");
            }
        }
    }
    strcat(string, "}");

    fputs(string, fp);
    fclose(fp);
    free(string);
    
    
    
    printf("\nBYE...\n");
    return 0;
}
