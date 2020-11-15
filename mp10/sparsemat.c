 clu#include "sparsemat.h"

#include <stdio.h>
#include <stdlib.h>

/* partners: sasinkg2 dhruvv2 akshay5 

*/


sp_tuples * load_tuples(char* input_file){
    int rows, cols;
    double value;
    FILE *fptr = fopen(input_file, "r"); //open file for read
    sp_tuples *list = (sp_tuples*)malloc(sizeof(sp_tuples)); //allocate memory
    list->nz = 0;
    list->m = 0;
    list->n = 0;
    list->tuples_head = NULL;
    fscanf(fptr, "%d %d", &list->m, &list->n); //get width and height
    while(fscanf(fptr, "%d %d %lf", &rows, &cols, &value) != EOF){
        set_tuples(list, rows, cols, value); //set tuples from file
    }
    fclose(fptr); //close file
    return list;
}

double gv_tuples(sp_tuples * mat_t,int row,int col){
    sp_tuples_node *current;
    current = mat_t->tuples_head;
    while(current != NULL){
        if(current->row == row && current->col == col){ //find row and col
            return current->value; //return value of node
        }else{
            current = current->next; //search next node
        }
    }
    return 0; //return 0 if node does not exist
}


void set_tuples(sp_tuples * mat_t, int row, int col, double value)
{
    return;
}


void save_tuples(char * file_name, sp_tuples * mat_t){
    if(mat_t == NULL){
        return;
    }else{
        FILE *fptr = fopen(file_name, "w"); //open file for write
        fprintf(fptr, "%d %d\n", mat_t->m, mat_t->n);
        sp_tuples_node* current = mat_t->tuples_head;
        while(current != NULL){
            fprintf(fptr, "%d %d %lf\n", current->row, current->col, current->value);
            current = current->next;
        }
        fclose(fptr); //close file
    }
    return;
}


sp_tuples * add_tuples(sp_tuples * matA, sp_tuples * matB){
    if(matA->n != matB->n || matA->m != matB->m){
        return NULL; // check that matrices are same size for valid input
    }
    sp_tuples *retmat = (sp_tuples*)malloc(sizeof(sp_tuples)); //allocate space
    retmat->n = matB->n;
    retmat->m = matB->m;
    retmat->nz = 0; //duplicate matrix
    sp_tuples_node *matAhead = matA->tuples_head;
    sp_tuples_node *matBhead = matB->tuples_head;
    while(matAhead != NULL){
        set_tuples(retmat, matAhead->row, matAhead->col, matAhead->value);
        matAhead = matAhead->next; //go through matrix A
    }
    while(matBhead != NULL){
        set_tuples(retmat, matBhead->row, matBhead->col, matBhead->value + gv_tuples(retmat, matBhead->row, matBhead->col));
        matBhead = matBhead->next; //go through matrix B and add, saving in retmat
    }
    return retmat;
}

sp_tuples * mult_tuples(sp_tuples * matA, sp_tuples * matB){ 
    return NULL;
}

void destroy_tuples(sp_tuples * mat_t){
    if(mat_t == NULL){
        return;
    }else{
        sp_tuples_node *current = mat_t->tuples_head;
        sp_tuples_node *currentfree;
        while(current != NULL){
            currentfree = current->next;
            free(current); //free space and keep moving through matrix
            current = currentfree;
        }
        free(mat_t); //free struct
        return;
    }   
}  







