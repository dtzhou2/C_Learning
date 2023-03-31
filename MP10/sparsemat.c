#include "sparsemat.h"

#include <stdio.h>
#include <stdlib.h>

/* Daniel Zhou - MP10
 * This MP helps perform various operations on a sparse marix of elements
    load_tuples - loads the sparse matrix from an input file, calling set_tuples to 
    sort the matrix in row major order
    set_tuples (helper function) takes in an inpu tuple from load tuples and updates the matrix with
    the tuple, adding or deleting tuples as necessary to create a row major order sorted tuple list. 
    Calls del_tuple to delete_tuples if necessary
    del_tuple (helper function) deletes tuple at the specified row and col, making sure to free it to prevent
    memory leaks
    sort_tuple (helper function) given two tuples, evaluates which one should come first using row/major
    order
    gv_tuple - gets the value of a tuple in the array by calling up_val
    up_val (helper function) takes in a value and updates the row/col in the array with that value
    if the value taken in is 0, does no modify array and only returns value found
    add_tuples - adds two matrices together using the matrix addition algorithm 
    mut_tup`les - multiplies two matrices together using the matrix multiplication algorithm
 */

// Loads the sp_tuples data structure from an input file
sp_tuples * load_tuples(char* input_file)
{
    // Basic Definition of Variables 
    FILE *fp;
    sp_tuples * o_sp_tuple = (sp_tuples*)malloc(sizeof(sp_tuples));
    o_sp_tuple->nz = 0;
    o_sp_tuple->tuples_head=NULL;
    long row;
    long col;
    double val;

    fp = fopen(input_file, "r");

    // Warns if it cannot allocate the struct
    if (o_sp_tuple == NULL) {
        printf("Allocation failed");
        return NULL;
    }

    // Uses fscanf to scan in the first two nubers of file as row and column
    fscanf(fp, "%d %d\n", &o_sp_tuple->m, &o_sp_tuple->n);

    // Calls Set Tuples on every following line in file to scan in data
    while(fscanf(fp, "%ld %ld %lf\n", &row, &col, &val) == 3){
        set_tuples(o_sp_tuple, row, col, val);
    }

    // Closes the file structure to not leave dangling memory pointers
    fclose(fp);

    return o_sp_tuple;

}


// Returns the value at a given row and col
double gv_tuples(sp_tuples * mat_t,int row,int col)
{
    // Calls customised version of gv_tuples that is more useful for MP
    return up_val(mat_t, row, col, 0);

}


// Modified version of gv_val. Has an extra input parameter in order to set the value of the linked list at a point to that value
// Avoids an extra traversal of the list in set_tuples
// Returns 0 if node is not on the list, otherwise returns the value found at row, col
// Updates the value at row, col if val!=0, otherwise only searches 
double up_val(sp_tuples * mat_t, int row, int col, double val){
   
    // Exits with error if input matrice is NULL
    if(mat_t == NULL) return -1;
    sp_tuples_node * temp = mat_t->tuples_head;

    while( temp != NULL){
        // Check if the node has the right coordinates
        if(temp->row == row && temp->col == col){
            // If node has right coordinates, update val if val != 0 
            if(val != 0) temp->value = val;
            // Finally, return specified value, indicating success
            return temp->value;
        }
        // Advance the node
        temp = temp->next;
    
    }
       
    // Since the node is not on the list / it means the node has empty value
    return 0;
}


// Adds a tuple with a given row and col to the row, insertion sorting it
void set_tuples(sp_tuples * mat_t, int row, int col, double value)
{
    // Checks that the input struct is valid
    if(mat_t == NULL ) return;  
    // Checks if the input value is 0 and delete tuple if so
    if(delete_tuple(mat_t, row, col, value)) return;
    // You check that the node already exists and has a value
    if(up_val(mat_t, row, col, value)) return;    
    // Createes a new node to be added to the set 
    sp_tuples_node * forward = mat_t->tuples_head;
    sp_tuples_node * prev = NULL;
    sp_tuples_node * node = (sp_tuples_node*)malloc(sizeof(sp_tuples_node));
    // Allocates basic information to the node  structure based on inputs
    node->row = row;
    node->col = col;
    node->value = value;
    node->next = NULL;
    // Since we know that we have to add a node now we increment nz count
    mat_t->nz += 1;
    // Checks if list is empty if so adds new node to head 
    if(forward == NULL) {
        mat_t->tuples_head = node;
        return;
    }
    // Creates loop that increments till tail of tuple structure
    while(forward!=NULL){
        // Compares current tuple with input tuple
        if(!sort_tuples(forward, node)){
            // If current tuple greater than input tuple 
            // Place input tuple in place of current tuple and exit function
            prev = forward;
            forward = forward->next;
            continue;
        } 
        if(prev == NULL){
            // If previous tuple is NULL, it indicates that node should be added 
            // to tuple after head node
            node->next = forward;
            mat_t->tuples_head = node;
        }
        else{
            // Increments loop forward 
            prev->next = node;
            node->next = forward;
        }
        return;
    }
    prev->next = node;
    
    return;

}

// Determines whether one node should be before the other
// First sorts the rows (row major) then cols
// Returns 1 if node1 > node2 if opposite return 0
// Returns -2 if something is broken
int sort_tuples(sp_tuples_node* one, sp_tuples_node* two) {
    // Explained by above comments 
    if ((one->row) != (two->row)) return ((one->row) > (two->row));
    else return ((one->col) > (two->col));
    return -2;
}

// Deletes a specific tuple at a set row and col
int delete_tuple(sp_tuples * mat_t, int row, int col, double value){
    // Errors out if it is deleting a non-zero tuple
    if(value != 0 ) return 0;
    sp_tuples_node * curr = mat_t->tuples_head;
    sp_tuples_node * prev = NULL;
    // Errors out if deletion is performed on an empty linked list
    if(curr==NULL) return 0;

    while( curr != NULL ){
        // Loops until it hits head node of linked list 
        if(curr->row == row && curr->col == col){
            // If val && row matches specified value and row, delete the node
            // If it is the head node make sure to change head nodes
            if(prev==NULL) mat_t->tuples_head = curr->next;
            else prev->next = curr->next;
            // Change count to reflect deletion
            mat_t->nz -= 1;
            // Prevents dangling pointers by freeing the node
            free(curr);
            return 1;
        }
        //Increments the loop forward
        prev = curr;
        curr = curr->next;
    }

    return 1;
}


// Stores the entire sp_tuple data structure into an output file
void save_tuples(char * file_name, sp_tuples * mat_t)
{
    // Creates a file pointer to write into 
    FILE* fptr = fopen(file_name, "w");
    sp_tuples_node* curr = mat_t->tuples_head;
    // Writes in the dimensions of the matrix
    fprintf(fptr, "%d %d\n", mat_t->m, mat_t->n);
    // Increments until you hit the tail node
    while (curr != NULL) {
        //Writes in the row col and value of the current array
        fprintf(fptr, "%d %d %lf\n", curr->row, curr->col, curr->value);
        curr = curr->next;
    }

    // Makes sure there arent any dangling file pointers
    fclose(fptr);

	return;
}


//Adds two tuples together and stores the result in output matrix c
sp_tuples * add_tuples(sp_tuples * matA, sp_tuples * matB){

    // Erorrs out if the two matrices are not the same size
    if(matA->m != matB->m || matA->n != matB->n) return NULL;
    // Allocates two head nodes since we need to loop through both linked-lists
    sp_tuples * matC = (sp_tuples*)malloc(sizeof(sp_tuples));
    sp_tuples_node * currA = matA->tuples_head;
    sp_tuples_node * currB = matB->tuples_head;

    // Sets the new dimensions identical to the input matrices 
    matC->m = matA->m;
    matC->n = matA->n;
    matC->nz = 0;
    matC->tuples_head = NULL;
    double val = 0;

    // Loops through the first list 
    while (currA != NULL) {
        // Sets the tuples in the output matrix = to the tuples in matrix A
        set_tuples(matC, currA->row, currA->col, currA->value);
        currA = currA->next;
    }

    while (currB != NULL) {
        // Gets the value in the output matrix and adds it to the value in matB
        val = gv_tuples(matC, currB->row, currB->col);
        set_tuples(matC, currB->row, currB->col, (currB->value)+val);
        currB = currB->next;
    }

	return matC;
}


//Multiplies two tuples together and stores the result in output matrix c
sp_tuples * mult_tuples(sp_tuples * matA, sp_tuples * matB){
    // Makes sure the matrices meet the dimensionality requirements
    if(matA->n != matB->m) return NULL;
    sp_tuples * matC = (sp_tuples*)malloc(sizeof(sp_tuples));
    sp_tuples_node * currA = matA->tuples_head;
    sp_tuples_node * currB = matB->tuples_head;
    // Sets the output matrix dimesnsions
    matC->m = matA->m;
    matC->n = matB->n;
    matC->nz = 0;
    matC->tuples_head = NULL;
    double value = 0;

    // Loops to tail node of matA
    while (currA != NULL) {
        // Advances Curr B until it matches Curr A's Col
        while (currB->row != currA->col) currB = currB->next;
        // Do the fancy multiply algo
        double C = gv_tuples(matC, currA->row, currB->col);
        double A = gv_tuples(matA, currA->row, currA->col);
        double B = gv_tuples(matB, currB->row, currB->col);
        value = (A*B)+C;
        set_tuples(matC, currA->row, currB->col, value);
        currA = currA->next;
    }

    return matC;

}


// Frees all memory associated with the linked list structure without leaving
// Pointers
void destroy_tuples(sp_tuples * mat_t){
    sp_tuples_node * temp = mat_t->tuples_head;
    sp_tuples_node * curr = NULL;
    // Stores the current node and a temp node
    // Loops through the list, freeing the current node while always
    // holding the temp node as the next node for a reference
    while(temp != NULL){
        curr = temp->next;
        free(temp);
        temp = curr;
    }
    // After All nodes are freed, free the actual matrix
    free(mat_t);
    return;
}


