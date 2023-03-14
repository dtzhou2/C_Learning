#include "floorplan.h"

int num_modules;                                            // # of input modules.
module_t* modules;                                          // Array for modules.

/* Daniel Zhou - MP11
 * This MP helps perform various operations relating to the laying out and use of a floorplan
    Init_Slicing Tree - Creates an intial slicing tree from the parsed array of modules
    Creates a left skewed slicing tree with all the nodes growing down towards the left
    Is_Leaf - Determines whether a node is a leaf node A.K.A a module 
    Is_Internal - Determines whether a node is a slicing note A.K.A a horizontal/vertical slice
    Is_In_Subtree - Determines whether one root node is part of another root number 
    rotate - Rotates a module, switching its height and length dimensions 
    recut - Rotates an internal node, changing its cutline from a horizontal to a vertical cutline
    swap_module - Swaps two modules with each other, without changing their parent nodes
    swap_topology - Swaps two root nodes, changing the topologies with it 
    get_expression - Prints a postfix expression representing the floorplan calling postfix_traversal 
    as a helper
    postfix_traversal - Recursively traverses through the floorplan, assigning the values to an array,
    used by get_expression to build the postfix expresion
 */

// Procedure: floorplan
// The major procedure of the floorplan. The procedure concists of the following major steps:
// - initialize the slicing tree.
// - print the information of the slicing tree.
// - perform the optimization process.
void floorplan(const char file[]) {

  /*printf("\n********************************** MP11 **********************************\n");

  // Read the modules from the given input file.
  read_modules(file);

  // Initialize the slicing tree.
  node_t* root = init_slicing_tree(NULL, 0);
  int num_nodes = (num_modules << 1) - 1;
  printf("Initial slicing tree: Root=%p, num_nodes=%d, num_modules=%d\n", root, num_nodes, num_modules);

  // Obtain the expression of the initial slicing tree.
  expression_unit_t* expression = (expression_unit_t*)calloc(num_nodes, sizeof(expression_unit_t));
  get_expression(root, num_nodes, expression);
  printf("Initial expression: ");
  pnt_expression(expression, num_nodes);
  double area = packing(expression, num_nodes);
  printf("Initial area: %.5e\n", area);
  draw_modules("init.png");
  free(expression);

  // Perform the optimization process.
  printf("Perform optimization...\n");
  area = optimize(root, num_nodes);
  pnt_modules();
  printf("Packing area = %.5e (has overlapped? %d (1:yes, 0:no))\n", area, is_overlapped());

  // Output your floorplan.
  printf("Draw floorplan to %s\n", outfile);
  draw_modules(outfile);

  printf("********************************** END ***********************************\n");*/
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// FUNCTIONS/PROCEDURES YOU HAVE TO FINISH.                                                      //
///////////////////////////////////////////////////////////////////////////////////////////////////

// Function: is_leaf_node
// Return 1 if the given slicing tree node is a leaf node, and 0 otherwise.
int is_leaf_node(node_t* ptr) {
  return (ptr->left == NULL && ptr->right == NULL);
}

// Function: is_internal_node
// Return 1 if the given slicing tree node is an internal node, and 0 otherwise.
int is_internal_node(node_t* ptr) {
  return (ptr->cutline!=UNDEFINED_CUTLINE);
}

// Function: is_in_subtree
// Return 1 if the given subtree rooted at node 'b' resides in the subtree rooted at node 'a'.
int is_in_subtree(node_t* a, node_t* b) {
    // Keeps on checking node B's parents, seeing if we ever hit node a, if not return 0
    while( b!= NULL && b != a) if ((b = b->parent) == a) return 1;
    return b==a;
}

// Procedure: rotate
// Rotate a module from a given leaf node of the slicing tree by 90 degree. That is, the height
// and the width of the modules are swapped.
void rotate(node_t* ptr) {
  // Creates a temporary int so we dont lose data
  int temp = ptr->module->w;
  ptr->module->w = ptr->module->h;
  ptr->module->h = temp;
}

// Procedure: recut
// Change the cutline of a module in a given internal node of the slicing tree.
// If the original cutline is a vertical cutline, the resulting cutline should be changed to
// horizontal and vice versa.
void recut(node_t* ptr) {
  // Assertions to make sure we dont accidentely segfault something 
  if(!is_internal_node(ptr) && ptr->cutline != UNDEFINED_CUTLINE) return;
  ptr->cutline = (cutline_t)!ptr->cutline;
}

// Procedure: swap_module
// Swap the two modules between two given leaf nodes in the slicing tree.
void swap_module(node_t* a, node_t* b) {
  // Assertions to make sure our inputs are sane 
  assert(a->module != NULL || b->module != NULL) ;
  assert(a->cutline == UNDEFINED_CUTLINE && b->cutline == UNDEFINED_CUTLINE) ;
  if(!is_leaf_node(a) || !is_leaf_node(b)) return;

  // Creates a temporary module so we dont lose data
  module_t* temp = a->module;
  a->module = b->module;
  b->module = temp;
  return;
}

// Procedure: swap_topology
// Swap the topology of two subtrees rooted at two given nodes of the slicing tree.
// The procedure applies "is_in_subtree" first to tell if any of the subtree belongs
// to a part of the other.
void swap_topology(node_t* a, node_t* b) {
  assert(a != NULL && b != NULL);
  assert(a->parent != NULL && b->parent != NULL);
  if(is_in_subtree(a, b)) return;
  
  node_t* temp_a_par = a->parent;
  
  // Swaps the parent nodes
  a->parent = b->parent;
  b->parent = temp_a_par;

  // Check which side of the parent node a was linked to a and set that side equal to b now that its been swapped
  if(temp_a_par->left == a) b->parent->left = b;
  else if (temp_a_par->right == a) b->parent->right = b;

  // Check which side of the parent node b was linked to b and set that side equal to a now that its been swapped
  if(a->parent->left == b) a->parent->left = a;
  else if (a->parent->right == b) a->parent->right = a;
  return;
}

// Procedure: get_expression
// Perform the post-order traversal on the given slicing tree and stores the polish expression
// into the given expression array. You should assume the expression array is pre-allocated with
// size N. In other words, you don't have to perform dynamic memory allocation. In fact, there
// is no need for you to add any code here, but it would be better if you can understand the
// details of this procedure especially the last two lines where the procedure postfix_traversal
// is called internally to obtain the expression.
void get_expression(node_t* root, int N, expression_unit_t* expression) {
  int i;
  // Clear the expression.
  for(i=0; i<N; ++i) {
    expression[i].module = NULL;
    expression[i].cutline = UNDEFINED_CUTLINE;
  }

  // Obtain the expression using the postfix traversal.
  int nth = 0;
  postfix_traversal(root, &nth, expression);

}

// Procedure: postfix_traversal
// Perform the postfix traversal on the slicing tree and store the corresponding polish expression
// to the given expression array. You should use the pointer "nth" to find out the index of the
// expression array and write the data accordingly. Notice that the expression array is a sequence
// of expression units which could be either a module pointer or the cutline type. If the module
// pointer exists in the expression unit, you should set the corresponding cutline type to
// "UNDEFINED_CUTLINE". On the other hand, if the expression unit is a cutline type, you should
// assign NULL to the corresponding module pointer.
void postfix_traversal(node_t* ptr, int* nth, expression_unit_t* expression) {

  // If you have gotten to the end of the tree stop the recursion
  if(ptr == NULL) return;

  // Traverses the left than the right subtrees looking for root nodes
  postfix_traversal(ptr->left, nth, expression);
  postfix_traversal(ptr->right, nth, expression);

  // If it finds a  leaf_node set the expression at n to a module 
  if(is_leaf_node(ptr)) {
    expression[*nth].module = ptr->module;
    expression[*nth].cutline = UNDEFINED_CUTLINE;
  }

  // If it finds an internal_node set the expression at n to a cutline 
  if(is_internal_node(ptr)) {
    expression[*nth].module = NULL;
    expression[*nth].cutline = ptr->cutline;
  }

  // Increment N
  *nth = *nth + 1;
  return;

}

// Procedure: init_slicing_tree
// Initialize the slicing tree by aligning modules along the horizontal line. In this procedure
// you should produce a left-skewed tree. The right child of any internal node should be a leaf
// node and the subtree is recursively expanded down to the left. Take 5 modules for an example.
// The resulting tree should look like:
/*
              root
              /  \
             i1  m0
            /  \
           i2  m1
          /  \
         i3  m2
        /  \
       m4  m3
*/
// where the prefix i denotes an internal node (including root), and the prefix m denotes a leaf
// node. Notice that each node is either an internal in which the cutline type is specified or
// a leaf in which the module pointer is assigned. For an internal node, the value of its module
// pointer should be assigned by NULL. For a leaf node, the value of its cutline type should be
// specified as "UNDEFINED_CUTLINE".
//
// In each recursive step of this function, you are passed by a parent pointer pointing to the
// parent node of which node you will generate at this step, as well as an integer index n
// indicating the depth of the current recursion and the index of the module array to which the
// module pointer of the leaf node should point to.
//
node_t* init_slicing_tree(node_t* par, int n) {
  node_t* c_node = (node_t*)malloc(sizeof(node_t));
  node_t* vert_cutline = (node_t*)malloc(sizeof(node_t));

  // Creates a new internal node with default cutline
  vert_cutline->module = NULL;
  vert_cutline->cutline = V;
  vert_cutline->parent = par;
  vert_cutline->right = c_node;

  // Creates the child node of the internal node, setting it to the right of the internal node
  c_node->left = NULL;
  c_node->right = NULL;
  c_node->cutline = UNDEFINED_CUTLINE;
  c_node->module = &modules[n];
  c_node->parent = vert_cutline;

  // If the internal node only has leaf nodes under it create the leaf modules, end recursion and set neighbors
  if (n+2 == num_modules){
    node_t* c_node_left = (node_t*)malloc(sizeof(node_t));
   
    c_node_left->left = NULL;
    c_node_left->right = NULL;
    c_node_left->cutline = UNDEFINED_CUTLINE;
    c_node_left->module = &modules[n+1];
    c_node_left->parent = vert_cutline;
    vert_cutline->left=c_node_left;
    
    return vert_cutline;

  }

  // Otherwise, set the left neighbor of the internal node equal to the the recursion, one deeper into the tree
  node_t* l_node = (node_t*)malloc(sizeof(node_t));
  l_node = init_slicing_tree(vert_cutline, n+1);

  vert_cutline->left = l_node;

  // Return the vert_cutline, ending the recursion once we hit the bottom 
  return vert_cutline;

}

///////////////////////////////////////////////////////////////////////////////////////////////////
// PREDEFINED FUNCTIONS AND PROCEDURES.                                                          //
// PLEASE DO NOT MODIFY ANY FIELD STARTING HERE.                                                 //
///////////////////////////////////////////////////////////////////////////////////////////////////

// Function: is_overlapped
// Return 1 if any overlaps among modules, and 0 otherwise.
int is_overlapped() {
  int i, j;
  int llxi, llyi, urxi, uryi;
  int llxj, llyj, urxj, uryj;
  int flag = 0;
  for(i=0; i<num_modules; ++i) {
    llxi = modules[i].llx;
    llyi = modules[i].lly;
    urxi = llxi + modules[i].w;
    uryi = llyi + modules[i].h;
    for(j=i+1; j<num_modules; ++j) {
     llxj = modules[j].llx;
     llyj = modules[j].lly;
     urxj = llxj + modules[j].w;
     uryj = llyj + modules[j].h;

     int rxu = MIN(urxi, urxj);
     int ryu = MIN(uryi, uryj);
     int rxl = MAX(llxi, llxj);
     int ryl = MAX(llyi, llyj);

     if(rxu>rxl && ryu>ryl) {
       flag = 1;
       printf("module %d and %d overlaps.\n", modules[i].idx, modules[j].idx);
     }
    }
  }
  return flag;
}

// Procedure: pnt_expression
// Print the expression to the display.
void pnt_expression(expression_unit_t *expression, int N) {

  if(!is_valid_expression(expression, N)) {
    printf("Invalid expression. Can't print. Please check your get_expression procedure.\n");
    return;
  }

  int i;
  for(i=0; i<N; ++i) {
    if(expression[i].cutline == UNDEFINED_CUTLINE) {
      assert(expression[i].module != NULL);
      printf("%d", expression[i].module->idx);
    }
    else {
      assert(expression[i].module == NULL);
      printf("%c", expression[i].cutline == V ? 'V' : 'H');
    }
  }
  putchar('\n');
}

// Procedure: pnt_modules
// Print the coordinates of each module.
void pnt_modules() {
  int i;
  for(i=0; i<num_modules; ++i) {
    printf("Module %d is placed at (%d, %d) with height=%d and width=%d\n",
            modules[i].idx,
            modules[i].llx,
            modules[i].lly,
            modules[i].h,
            modules[i].w);
  }
}

// Procedure: write_modules
// Write the coordinates of each module into a file.
void write_modules(const char file[]) {
  FILE *ofp = fopen(file, "w");
  int i;
  for(i=0; i<num_modules; ++i) {
    printf("%d %d %d %d %d\n",
            modules[i].idx,
            modules[i].llx,
            modules[i].lly,
            modules[i].h,
            modules[i].w);
  }
  fclose(ofp);
}

// Function: get_module
// Return the module pointer to the module with the given idx.
module_t* get_module(int idx) {
  int i;
  for(i=0; i<num_modules; ++i) {
    if(idx == modules[i].idx) return &modules[i];
  }
  return NULL;
}

// Function: packing
// The main procedure of packing modules. The procedure takes the expression from the
// current slicing tree and then compute the coordinate of each module.
double packing(expression_unit_t* expression, int N) {

  if(!is_valid_expression(expression, N)) {
    //printf("Invalid expression. Can't pack. Please check your get_expression procedure.\n");
    return FLT_MAX;
  }

  // Initialize the stack by setting the variable stack_top as zero. The variable stack_top
  // is also denoting the size of the stack.
  int stack_top = 0;
  cluster_t* stack = (cluster_t*)malloc(N*sizeof(cluster_t));

  // Iterates through the expression
  int i, j;
  cluster_t cluster, cluster_l, cluster_r;
  for(i=0; i<N; ++i) {
    // Module
    if(expression[i].module != NULL) {
      assert(expression[i].cutline == UNDEFINED_CUTLINE);

      // Adjust the coordinate of the module.
      expression[i].module->llx = 0;
      expression[i].module->lly = 0;

      // Create a cluster.
      cluster.beg = i;
      cluster.end = i;
      cluster.w = expression[i].module->w;
      cluster.h = expression[i].module->h;
      stack[stack_top++] = cluster;
    }
    // Cutline
    else {
      assert(expression[i].cutline != UNDEFINED_CUTLINE);
      assert(stack_top >= 2);

      // Extract the top two clusters.
      cluster_r = stack[--stack_top];
      cluster_l = stack[--stack_top];

      // Create a new cluster.
      cluster.beg = cluster_l.beg;
      cluster.end = cluster_r.end;

      // Horizontal cutline.
      // - adjust the cluster's width and height.
      // - adjust the coordinates of modules from the right cluster.
      // - x coordinate doesn't change.
      if(expression[i].cutline == H) {
        for(j=cluster_r.beg; j<=cluster_r.end; ++j) {
          if(expression[j].module == NULL) continue;
          expression[j].module->lly += cluster_l.h;
        }
        cluster.w = cluster_l.w > cluster_r.w ? cluster_l.w : cluster_r.w;
        cluster.h = cluster_l.h + cluster_r.h;
      }
      // Vertical cutline.
      // - adjust the cluster's width and height.
      // - adjust the coordinates of modules from the right cluster.
      // - y coordinate doesn't change.
      else {
        for(j=cluster_r.beg; j<=cluster_r.end; ++j) {
          if(expression[j].module == NULL) continue;
          expression[j].module->llx += cluster_l.w;
        }
        cluster.w = cluster_l.w + cluster_r.w;
        cluster.h = cluster_l.h > cluster_r.h ? cluster_l.h : cluster_r.h;
      }

      // Insert the cluster into the stack.
      stack[stack_top++] = cluster;
    }
  }

  assert(stack_top == 1);

  double area = (double)stack[stack_top - 1].w * (double)stack[stack_top - 1].h;

  free(stack);

  return area;
}

// Function: is_valid_expression
int is_valid_expression(expression_unit_t* expression, int N) {

  // Initialize the stack by setting the variable stack_top as zero. The variable stack_top
  // is also denoting the size of the stack.
  int stack_top = 0;
  cluster_t* stack = (cluster_t*)malloc(N*sizeof(cluster_t));

  // Iterates through the expression
  int i;
  cluster_t cluster = {0, 0, 0, 0}, cluster_l, cluster_r;
  for(i=0; i<N; ++i) {
    // Module
    if(expression[i].module != NULL) {
      if(expression[i].cutline != UNDEFINED_CUTLINE) return 0;
      stack[stack_top++] = cluster;
    }
    // Cutline
    else {
      if(expression[i].cutline == UNDEFINED_CUTLINE) return 0;
      if(stack_top < 2) return 0;
      cluster_r = stack[--stack_top];
      cluster_l = stack[--stack_top];
      stack[stack_top++] = cluster;
    }
  }
  free(stack);
  return stack_top == 1;
}

// Procedure: read_modules
// Read the modules from a given input file and initialize all required data structure.
void read_modules(const char file[]) {

  int i;
  FILE* ifp = fopen(file, "r");

  assert(ifp != NULL);

  // Read the number of modules.
  assert(fscanf(ifp, "%d", &num_modules) == 1);
  assert(num_modules >= 2);

  // Allocate the memory.
  modules = (module_t*)malloc(num_modules*sizeof(module_t));

  // Read the modules one by one.
  for(i=0; i<num_modules; ++i) {
    assert(fscanf(ifp, "%d %d %d", &modules[i].idx, &modules[i].w, &modules[i].h) == 3);
    modules[i].llx = 0;
    modules[i].lly = 0;
  }

  fclose(ifp);
}

// Procedure: copy_expression
void copy_expression(expression_unit_t* lhs, expression_unit_t* rhs, int N) {
  memcpy(lhs, rhs, N*sizeof(expression_unit_t));
}

// Procedure: copy_modules
void copy_modules(module_t* lhs, module_t* rhs, int N) {
  memcpy(lhs, rhs, N*sizeof(module_t));
}

// Function: accept_proposal
// Accept the proposed solution.
int accept_proposal(double current, double proposal, double temperature) {
  if(proposal < current) return 1;
  if(temperature <= FROZEN) return 0;
  double prob = exp(-(double)(proposal - current) / temperature);
  return rand()/(double)RAND_MAX < prob;
}

// Function: get_rand_internal
node_t* get_rand_internal(node_t** internals, int num_internals) {
  return internals[rand()%num_internals];
}

// Function: get_rand_leaf
node_t* get_rand_leaf(node_t** leaves, int num_leaves) {
  return leaves[rand()%num_leaves];
}

// Function: get_random_node
node_t* get_rand_node(node_t** internals, int num_internals, node_t** leaves, int num_leaves) {
  if(rand()%2) {
    return get_rand_leaf(leaves, num_leaves);
  }
  return get_rand_internal(internals, num_internals);
}

// Function: optimize
// Optimize the area of the floorplanner.
double optimize(node_t *root, int num_nodes) {

  if(root == NULL) return FLT_MAX;

  // Storage for leaf and internal nodes.
  int head = 0;
  int tail = 0;
  int num_leaves = 0;
  int num_internals = 0;
  node_t** queue = (node_t**)malloc(num_nodes*sizeof(node_t*));
  node_t** leaves = (node_t**)malloc(num_modules*sizeof(node_t*));
  node_t** internals = (node_t**)malloc((num_modules-1)*sizeof(node_t*));
  node_t* u;
  queue[tail++] = root;

  while(tail - head) {
    u = queue[head++];

    if(u->module) {
      assert(u->cutline == UNDEFINED_CUTLINE);
      leaves[num_leaves++] = u;
    }
    else {
      assert(u->cutline != UNDEFINED_CUTLINE);
      internals[num_internals++] = u;
    }

    if(u->left) queue[tail++] = u->left;
    if(u->right) queue[tail++] = u->right;
  }

  assert(num_leaves == num_modules);
  assert(num_internals == num_modules - 1);

  // Simulated annealing.
  srand(time(0));
  expression_unit_t* best_expression = (expression_unit_t*)malloc(num_nodes*sizeof(expression_unit_t));
  expression_unit_t* curr_expression = (expression_unit_t*)malloc(num_nodes*sizeof(expression_unit_t));
  module_t* best_modules = (module_t*)malloc(num_modules*sizeof(module_t));

  int i, key;
  double best_area, curr_area;
  double temperature = 100.0;
  node_t* a;
  node_t* b;

  // Initialization.
  get_expression(root, num_nodes, best_expression);
  best_area = packing(best_expression, num_nodes);
  memcpy(best_modules, modules, num_modules*sizeof(module_t));

  while(temperature > FROZEN) {

    // Generate the neighboring solution.
    for(i=0; i<MAX_NUM_RAND_STEPS; ++i) {

      key = rand()%4;

      switch(key) {

        // Perform recut.
        case 0:
          recut(get_rand_internal(internals, num_internals));
        break;

        // Perform rotate.
        case 1:
          rotate(get_rand_leaf(leaves, num_leaves));
        break;

        // Perform swap_module.
        case 2:
          do {
            a = get_rand_leaf(leaves, num_leaves);
            b = get_rand_leaf(leaves, num_leaves);
          } while(a == b);
          swap_module(a, b);
        break;

        // Perform swap_topology.
        default:
          do {
            a = get_rand_node(internals, num_internals, leaves, num_leaves);
            b = get_rand_node(internals, num_internals, leaves, num_leaves);
          } while(is_in_subtree(a, b) || is_in_subtree(b, a));
          swap_topology(a, b);
        break;
      }

      // Evaluate the area.
      get_expression(root, num_nodes, curr_expression);
      curr_area = packing(curr_expression, num_nodes);
      if(curr_area < best_area) {
        best_area = curr_area;
        copy_expression(best_expression, curr_expression, num_nodes);
        memcpy(best_modules, modules, num_modules*sizeof(module_t));
      }
    }
    temperature *= TEMPERATURE_DECREASING_RATE;
  }

  memcpy(modules, best_modules, num_modules*sizeof(module_t));
  best_area = packing(best_expression, num_nodes);



  free(queue);
  free(leaves);
  free(internals);
  free(best_expression);
  free(curr_expression);
  free(best_modules);

  return best_area;
}
