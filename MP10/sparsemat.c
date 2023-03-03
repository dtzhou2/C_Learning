#include "sparsemat.h"

#include <stdio.h>
#include <stdlib.h>


sp_tuples * load_tuples(char* input_file)
{

    FILE *fp;
    long rows;
    long cols;
    long row;
    long col;
    double val;

    fp = fopen(input_file, "r");
    sp_tuples * o_sp_tuple = (sp_tuples*)malloc(sizeof(sp_tuples));

    if (o_sp_tuple == NULL) {
        printf("Allocation failed");
        return NULL;
    }

    fscanf(fp, "%ld %ld\n", &rows, &cols);

    o_sp_tuple->m=rows;
    o_sp_tuple->n=cols;
    o_sp_tuple->nz = 0;
    o_sp_tuple->tuples_head=NULL;
    printf("31");
    while(fscanf(fp, "%ld %ld %lf\n", &row, &col, &val) == 3){
        set_tuples(o_sp_tuple, row, col, val);
    }

    fclose(fp);

    return o_sp_tuple;

}



double gv_tuples(sp_tuples * mat_t,int row,int col)
{
    
    return up_val(mat_t, row, col, 0);

}



double up_val(sp_tuples * mat_t, int row, int col, double val){

    if(mat_t == NULL) return -1; 
    sp_tuples_node * temp = mat_t->tuples_head;

    while( temp != NULL){
        // Check if the node has the right coordinates
        if(temp->row == row && temp->col == col){
            if(val != 0) temp->value = val;
            return temp->value;
        }
        // Advance the node
        temp = temp->next;
    
    }
       
    // Since the node is not on the list / it means the node has empty value
    return 0;
}


void set_tuples(sp_tuples * mat_t, int row, int col, double value)
{
    if(!value){
        delete_tuple(mat_t, row, col);
        return;
    } 

    // You check that the node already exists and has a value
    if(!up_val(mat_t, row, col, value)){
        
        if(mat_t == NULL ) return;  
        sp_tuples_node * forward = mat_t->tuples_head;
        sp_tuples_node * prev = NULL;
        sp_tuples_node * node = (sp_tuples_node*)malloc(sizeof(sp_tuples_node));
       
        node->row = row;
        node->col = col;
        node->value = value;
        node->next = NULL;
        // Since we know that we have to add a node now we increment nz count
        mat_t->nz += 1;
        
        // Checks if list is empty if so adds it
        if(forward == NULL) {
            mat_t->tuples_head = node;
            return;
        }
        
        while(forward!=NULL){
            if(sort_tuples(forward, node)){
                if(prev == NULL){
                    node->next = forward;
                    mat_t->tuples_head = node;
                }
                else{
                    prev->next = node;
                    node->next = forward;
                }
                return;

            }  

            prev = forward;
            forward = forward->next;
        }
        // if (prev == NULL) return;
        prev->next = node;
        
        return;
    }

    return;
}

// Determines whether one node should be before the other
// First sorts the rows (row major) then cols
// Returns 1 if node1 > node2 if opposite return 0
// Returns -2 if something is broken
int sort_tuples(sp_tuples_node* one, sp_tuples_node* two) {
    if ((one->row) != (two->row)) return ((one->row) > (two->row));
    else return ((one->col) > (two->col));
    return -2;
}


void delete_tuple(sp_tuples * mat_t, int row, int col){
    
    sp_tuples_node * curr = mat_t->tuples_head;
    sp_tuples_node * prev = NULL;

    if(curr!=NULL){
        while( curr != NULL ){
            if(curr->row == row && curr->col == col){
                if(prev==NULL) mat_t->tuples_head = curr->next;
                else prev->next = curr->next;
                mat_t->nz -= 1;
                free(curr);
                return;
            }
            //Increments the loop forward
            prev = curr;
            curr = curr->next;
        }
    }

    return;

}


void save_tuples(char * file_name, sp_tuples * mat_t)
{
    FILE* fptr = fopen(file_name, "w");

    fprintf(fptr, "%d %d\n", mat_t->m, mat_t->n);

    sp_tuples_node* node = mat_t->tuples_head;
    while (node != NULL) {
        fprintf(fptr, "%d %d %lf\n", node->row, node->col, node->value);
        node = node->next;
    }

    fclose(fptr);
	return;
}



sp_tuples * add_tuples(sp_tuples * matA, sp_tuples * matB){

    sp_tuples * matC = (sp_tuples*)malloc(sizeof(sp_tuples));
    sp_tuples_node * currA = matA->tuples_head;
    sp_tuples_node * currB = matB->tuples_head;
    matC->m = matA->m;
    matC->n = matA->n;
    matC->nz = 0;
    matC->tuples_head = NULL;
    double val = 0;

    while (currA != NULL) {
        set_tuples(matC, currA->row, currA->col, currA->value);
        currA = currA->next;
    }

    while (currB != NULL) {
        if((val = gv_tuples(matC, currB->row, currB->col)) == currB->value)
          set_tuples(matC, currB->row, currB->col, val);
        else set_tuples(matC, currB->row, currB->col, currB->value);
        currB = currB->next;
    }

	return matC;
}



sp_tuples * mult_tuples(sp_tuples * matA, sp_tuples * matB){

    if(matA->n != matB->m) return NULL;
    sp_tuples * matC = (sp_tuples*)malloc(sizeof(sp_tuples));
    sp_tuples_node * currA = matA->tuples_head;
    sp_tuples_node * currB = matB->tuples_head;
    matC->m = matA->m;
    matC->n = matB->n;
    matC->nz = 0;
    matC->tuples_head = NULL;
    double value = 0;

    while (currA != NULL) {
        int jA = currA->col;
        while (currB != NULL){
            if(currB->row == jA) {
                double C = gv_tuples(matC, currA->row, currB->col);
                double A = gv_tuples(matA, currA->row, currA->col);
                double B = gv_tuples(matB, currB->row, currB->col);
                value = (A*B)+C;
                set_tuples(matC, currA->row, currB->col, value);
            }
            else if(currB->row > currA->col) break;

            currB = currB->next;
        }
        currA = currA->next;
    }

    return matC;

}



void destroy_tuples(sp_tuples * mat_t){
    sp_tuples_node * temp = mat_t->tuples_head;
    sp_tuples_node * next = NULL;
    while(temp != NULL){
        next = temp->next;
        free(temp);
        temp = next;
    }
    free(mat_t);
    return;
}


