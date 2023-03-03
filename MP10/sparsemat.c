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
        // Since we know that we have to add a node now we increment nz count
        mat_t->nz += 1;
        
        // Checks if list is empty if so adds it
        if(forward == NULL) {
            mat_t->tuples_head = node;
            return;
        }
        
        while( forward != NULL ){
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

            // if(prev != NULL) printf("%lf\n", prev->value);

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
    // allocate and initialize new matrix C
    sp_tuples* matC = (sp_tuples*)malloc(sizeof(sp_tuples));
    matC->m = matA->m;
    matC->n = matA->n;
    matC->nz = 0;
    matC->tuples_head = NULL;

    // nodes for traversing A, and B
    sp_tuples_node* nodeA = matA->tuples_head;
    sp_tuples_node* nodeB = matB->tuples_head;

    while (nodeA != NULL) {
        // set the values of matrix C to those of matrix A
        // note that set_tuples handles the case of a null head
        set_tuples(matC, nodeA->row, nodeA->col, nodeA->value);
        nodeA = nodeA->next;
    }
    while (nodeB != NULL) {
        double valueC = gv_tuples(matC, nodeB->row, nodeB->col);
        set_tuples(matC, nodeB->row, nodeB->col, nodeB->value + valueC);
        nodeB = nodeB->next;
    }

	return matC;
}



sp_tuples * mult_tuples(sp_tuples * matA, sp_tuples * matB){
     // matricies must have the proper dimensions to be multiplied
    if (matA->n != matB->m) {
        return NULL;
    }

    // allocate and initialize new matrix C
    sp_tuples* matC = (sp_tuples*)malloc(sizeof(sp_tuples));
    matC->m = matA->m;
    matC->n = matB->n;
    matC->nz = 0;
    matC->tuples_head = NULL;

    // traverse matrix A
    sp_tuples_node* nodeA = matA->tuples_head;
    while (nodeA != NULL) {
        int iA = nodeA->row;
        int jA = nodeA->col;

        // traverse matrix B
        sp_tuples_node* nodeB = matB->tuples_head;
        while (nodeB != NULL) {
            int iB = nodeB->row;
            int jB = nodeB->col;
            // if row of B matches the column of A, accumulate value in C
            if (iB == jA) {
                double valueA = gv_tuples(matA, iA, jA);
                double valueB = gv_tuples(matB, iB, jB);
                double valueC = gv_tuples(matC, iA, jB);
                double newValue = valueC + (valueA * valueB);
                set_tuples(matC, iA, jB, newValue);
            }
            // if we have finished the row, stop traversing B
            else if (iB > jA) {
                break;
            }
            // otherwise move to the next node in B
            nodeB = nodeB->next;
        }
        // after traversing B, move to the next node in A
        nodeA = nodeA->next;
    }

    return matC;
}



void destroy_tuples(sp_tuples * mat_t){
    sp_tuples_node * temp = mat_t->tuples_head;
    sp_tuples_node * next = NULL;
    if(temp != NULL) {
        while(temp->next!=NULL){
            next = temp->next;
            free(temp);
            temp = next;
        }
    }
    free(mat_t);
    return;
}


