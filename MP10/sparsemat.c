#include "sparsemat.h"

#include <stdio.h>
#include <stdlib.h>

/* MP10 - Eric Roch
 * This program stores a matrix as a linked list of non-zero elements.
 * This is a useful way to save space when dealing with larger matricies
 * that have a large number of empty elements, as a linked list grows
 * with the number of non-zero elements, as opposed to being fixed by the
 * matrix dimensions.  To create the list, we read a file that specifies
 * the width and height of the matrix, followed by a list of x,y coordinates
 * and values (not including empty elements). The bulk of this program is
 * in set_tuples(), which handles five separate cases when setting the value
 * of an element in the matrix.  If the matrix is empty, i.e. the list head
 * is null, we create a node and set it as the head.  Otherwise, if the value
 * to be set is zero, we remove the corresponding node if it exists or ignore
 * it otherwise.  If the value is non-zero, we either must update an existing
 * node or create a new one and insert it at the proper location.
 *
 * This program also contains functions to perform basic matrix operations
 * and to print a list of coordinates and values in the list.
 */



sp_tuples * load_tuples(char* input_file)
{

    int rows;
    int cols;

    sp_tuples* ptr = (sp_tuples*)malloc(sizeof(sp_tuples));

    FILE* fptr = fopen(input_file, "r");
    if (fptr == NULL) {
        printf("Error: %s not found", input_file);
        return NULL;
    }

    fscanf(fptr, "%d %d\n", &rows, &cols);

    ptr->m = rows;
    ptr->n = cols;
    ptr->nz = 0;
    ptr->tuples_head = NULL;

    int x;
    int y;
    double value;
    while (fscanf(fptr, "%d %d %lf\n", &y, &x, &value) == 3) {
        set_tuples(ptr, y, x, value);
    }

    // if we're not at the end of the file, something went wrong
    if (!feof(fptr)) {
        return NULL;
    }

    fclose(fptr);
    return ptr;
}



double gv_tuples(sp_tuples * mat_t,int row,int col)
{
    sp_tuples_node* node = mat_t->tuples_head;

    // Traverse the list until we reach the last node
    while(node != NULL){
        // if this node is the coordinate we want, return the value
        if (node->row == row && node->col == col) {
            return node->value;
        }
        // otherwise, move to the next node
        node = node->next;
    }
    // if we didn't find the right node, return 0
    return 0;
}



void set_tuples(sp_tuples * mat_t, int row, int col, double value)
{
    if (mat_t->tuples_head == NULL) {
        if (value != 0) {
            // allocate a new node
            sp_tuples_node* head = (sp_tuples_node*)malloc(sizeof(sp_tuples_node));
            // fill the values
            head->row = row;
            head->col = col;
            head->value = value;
            head->next = NULL;
            // point to the new head and incriment non-zero count
            mat_t->tuples_head = head;
            mat_t->nz += 1;
        }
        return;
    }

    // if the list has some nodes, there are four cases:
    // 1) node exists and value is zero --> delete node
    // 2) node exists and value is non-zero --> update node
    // 3) node does not exist and value is zero --> do nothing
    // 4) node does not exist and value is non-zero --> add node

    if (gv_tuples(mat_t, row, col) != 0) {
        // Case 1: delete node
        if (value == 0) {
            sp_tuples_node* previous = NULL;
            sp_tuples_node* node = mat_t->tuples_head;

            while(node != NULL) {
                if (node->row == row && node->col == col) {
                    // Case 1: deleting the head node,
                    // set the new head to be the next node
                    if (previous == NULL) {
                        mat_t->tuples_head = node->next;
                    }
                    // Case 2: deleting middle node,
                    // link the previous node to the next node
                    else {
                        previous->next = node->next;
                    }

                    free(node);
                    mat_t->nz -= 1;
                    return;
                }
                previous = node;
                node = node->next;
            }
        }
        // Case 2: update node
        else {
            sp_tuples_node* node = mat_t->tuples_head;

            while(node != NULL) {
                if (node->row == row && node->col == col) {
                    node->value = value;
                    return;
                }
                node = node->next;
            }
        }
    }
    else {
        // Case 3: do nothing
        if (value == 0) {
            return;
        }
        // Case 4: add node
        else {
            sp_tuples_node* previous = NULL;
            sp_tuples_node* node = mat_t->tuples_head;
            sp_tuples_node* new = (sp_tuples_node*)malloc(sizeof(sp_tuples_node));

            new->row = row;
            new->col = col;
            new->value = value;
            new->next = NULL;
            mat_t->nz += 1;

            while(node != NULL) {
                // if node comes after new...
                if (sort_tuples(node, new)) {
                    // if we are replacing the head...
                    if (previous == NULL) {
                        new->next = node;
                        mat_t->tuples_head = new;
                    }
                    // otherwise insert between nodes
                    else {
                        previous->next = new;
                        new->next = node;
                    }
                    return;
                }
                previous = node;
                node = node->next;
            }
            // append new node to end of list
            previous->next = new;
            return;
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
    sp_tuples_node* node = mat_t->tuples_head;
    sp_tuples_node* next = NULL;
    // traverse the list, saving the next
    // node before freeing the current one
    while (node != NULL) {
        next = node->next;
        free(node);
        node = next;
    }
    // and finally free the matrix itself
    free(mat_t);

    return;
}

// if node1 < node2: return 0
// if node1 > node2: return 1
int sort_tuples(sp_tuples_node* node1, sp_tuples_node* node2) {
    if ((node1->row) != (node2->row)) {
        return ((node1->row) > (node2->row));
    }
    else {
        return ((node1->col) > (node2->col));
    }
    // something went very wrong
    return -1;
}
