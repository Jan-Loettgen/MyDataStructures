
//#include "queueFIFO.h"
#include "queueFILO.h"
#include "queueFIFO.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void deallocate(queue** q, int queue_type){

    if (queue_type == 1){
        queue_FIFO_destroy(q);
    }
    else {
        queue_FILO_destroy(q);
    };
}

void print_options1(){
    printf("\n Enter 1 for First in First out queue");
    printf("\n Enter 2 for First in Last out queue");
    printf("\n or enter 3 to exit: ");
}

void print_options2(){
    printf("\n Enter the maximum number of elements to be stored in queue: ");
}

void print_options3(){
    printf("\n Enter 1 to add an item to queue");
    printf("\n Enter 2 to get next item in queue");
    printf("\n or Enter 3 to exit: ");
}

int main(){
    
    system("cls");
    queue* q = NULL;
    char buffer[1024];
    char* str;
    int queue_type = 0;
    int queue_size = 0;

    print_options1();
    while (fgets(buffer, 1024, stdin) != NULL){
        if (atoi(buffer) == 1 || atoi(buffer) == 2 || atoi(buffer) == 3){
            queue_type = atoi(buffer);
            break;
        }
        else{
            printf(" please enter 1, 2 or 3: ");
        }
    }

    if (queue_type==3){ return 0; }

    print_options2();
    while (fgets(buffer, 1024, stdin) != NULL){
        if (atoi(buffer)){
            queue_size = atoi(buffer);
            break;
        }
        print_options2();
    }

    if (queue_type == 1) {
        q = queue_FIFO_create(queue_size);

    } else if (queue_type == 2){
        q = queue_FILO_create(queue_size);
    }

    if (q  == NULL){
        printf("unable to create queue \n");
        return -1;
    }

    system("cls");
    print_options3();
    while (fgets(buffer, 1024, stdin) != NULL){
        
        if (atoi(buffer) == 1){
            printf("Enter an item: ");
            fgets(buffer, 1024, stdin);
            str = (char*)malloc(1024);
            strncpy_s(str, 1024, buffer, 1024);

            if(queue_type == 1){
                queue_FIFO_add(&q, str);
                printf("%s\n", str);
            }
            else {
                queue_FILO_add(&q, str);
                printf("%s\n", str);
            }
            system("cls");
        }
        else if(atoi(buffer) == 2){
            if(queue_type == 1){
                char* str_ptr = (char *)queue_FIFO_pop(&q);
                system("cls");
                if (str_ptr != NULL) {printf("Retrived item: %s", str_ptr);}
            }
            else {
                char* str_ptr = (char *)queue_FILO_pop(&q);
                system("cls");
                if (str_ptr != NULL) {printf("Retrived item: %s", str_ptr);}
            }
        }
        else if(atoi(buffer) == 3){
            deallocate(&q, queue_type);
             return 0; }

        print_options3();
    }
}
