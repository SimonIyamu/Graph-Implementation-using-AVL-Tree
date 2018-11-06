#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BankInterface.h"

/* The following are only used by functions in this file, hence they are not part of BankInterface.h */
void TreeNodecpy(TreeNode*, TreeNode*);
TreeNode *newTreeNode(char *);
TreeNode *leftRotation(TreeNode*);
TreeNode *rightRotation(TreeNode*);
TreeNode *freeTreeNode(TreeNode*, TreeNode *);
ListNode *newListNode(int, TreeNode*);
int balanceFactor(TreeNode *); 
int height(TreeNode*);
int max(int, int);
void print_stack(StackNode*);
StackNode *push(StackNode*,TreeNode *,int w);
StackNode *pop(StackNode*,TreeNode **);




TreeNode *insert_edge(TreeNode *r, char *acc1, char *acc2, int w){
    TreeNode *sender = search(r, acc1);
    if ( sender == NULL ){ /* If node doesnt exist then we insert it */
        r = insert(r,acc1);
        sender = search(r,acc1);
    }

    TreeNode *receiver = search(r,acc2); /* Same process for the receiver */
    if ( receiver == NULL ){
        r = insert(r,acc2);
        receiver = search(r,acc2);
    }
    
    if (sender->out_transactions == NULL) /* if there are no other edges on the node*/
        sender->out_transactions = newListNode(w,receiver);
    else{ /* else push listnode at the end of the list */
        ListNode *temp = sender->out_transactions;
        while(temp->next!=NULL)
            temp=temp->next;
        temp->next = newListNode(w,receiver);
    }

    if (receiver->in_transactions == NULL)
        receiver->in_transactions = newListNode(w,sender);
    else{
        ListNode *temp = receiver->in_transactions;
        while(temp->next!=NULL)
            temp=temp->next;
        temp->next = newListNode(w,sender);
    }
    printf("Inserted |%s|->%d->|%s|.\n",acc1,w,acc2);
    return r;
}

void modify_edge(TreeNode *r,char *acc1, char *acc2, int w, int nw){
    TreeNode *sender = search(r, acc1);
    if ( sender == NULL ){ /* If node doesnt exist */
        printf("|%s| does not exist\n",acc1);
        return;
    }

    TreeNode *receiver = search(r,acc2); /* If node doesnt exist */
    if ( receiver == NULL ){
        printf("|%s| does not exist\n",acc2);
        return;
    }

    /* Modify it in sender's out_transactions. */
    bool found = false;
    ListNode *current = sender->out_transactions;
    while(current != NULL){
        if( current->link == receiver && current->ammount==w){
            current->ammount = nw;
            found = true;
            break;
        }
        current = current->next;
    }

    if(found){
        /* Modify it in receiver's in_transactions. */
        current = receiver->in_transactions;
        /* Keep in mind that current->link is actually the sender as mentioned in BankTypes.h */
        while(current != NULL){
            if( current->link == sender && current->ammount==w){
                current->ammount = nw;
                break;
            }
            current = current->next;
        }
        printf("Modified edge |%s|->%d->|%s| to |%s|->%d->|%s|",acc1,w,acc2,acc1,nw,acc2);
    }
    else
        printf("Edge |%s| --%d--> |%s| does not exist.\n",acc1,w,acc2);
}


void delete_edge(TreeNode *r,char *acc1, char *acc2, int w){
    TreeNode *sender = search(r, acc1);
    if ( sender == NULL ){ /* If node doesnt exist */
        printf("|%s| does not exist\n",acc1);
        return;
    }

    TreeNode *receiver = search(r,acc2); /* If node doesnt exist */
    if ( receiver == NULL ){
        printf("|%s| does not exist\n",acc2);
        return;
    }

    /* Delete it from sender's out_transactions. */

    bool found = false;
    ListNode *current = sender->out_transactions;
    if ( current != NULL)
        if ( current->link == receiver && current->ammount==w){
            /* in that case its the first node of the list */
            sender->out_transactions=current->next;
            free(current);
            found = true;
        }
        else{
            /* its not the first one*/
            ListNode *previous = current; 
            current = current->next;
            while(current != NULL){
                if( current->link == receiver && current->ammount==w){
                    previous->next = current->next;
                    free(current);
                    found = true;
                    break;
                }
                previous = current;
                current = current->next;
            }
        }

    if(found){
        /* Delete it from receiver's in_transactions. */

        current = receiver->in_transactions;
        /* Keep in mind that current->link is actually the sender as mentioned in BankTypes.h */
        if(current->link == sender && current->ammount==w){ 
            /* In that case its the first node of the list */
            receiver->in_transactions=current->next;
            free(current);
        }
        else{
            /* its not the first one*/
            ListNode *previous = current; 
            current = current->next;
            while(current != NULL){
                if( current->link == sender && current->ammount==w){
                    previous->next = current->next;
                    free(current);
                    break;
                }
                previous = current;
                current = current->next;
            }
        }
        printf("Deleted edge |%s| --%d--> |%s|.\n",acc1,w,acc2);
    }
    else
        printf("Edge |%s| --%d--> |%s| does not exist.\n",acc1,w,acc2);
}

void delete_all_edges(TreeNode *r, char *acc1, char *acc2){
    TreeNode *sender = search(r, acc1);
    if ( sender == NULL ){ /* If node doesnt exist */
        printf("|%s| does not exist\n",acc1);
        return;
    }

    TreeNode *receiver = search(r,acc2); /* If node doesnt exist */
    if ( receiver == NULL ){
        printf("|%s| does not exist\n",acc2);
        return;
    }

    /* Delete it from sender's out_transactions. */

    bool found = false;
    ListNode *current = sender->out_transactions;
    if ( current != NULL){
        ListNode *previous=NULL;
        if ( current->link == receiver){ /* if current points at an edge to the receiver/acc2 */
            /* The first node is an edge we want to delete */
            printf("Deleted edge |%s| --%d--> |%s|.\n",acc1,current->ammount,acc2);
            sender->out_transactions=current->next;
            ListNode *temp = current;
            current = current->next;
            free(temp);
            found = true;
        }
        else{
            previous = current; 
            current = current->next;
        }
        /* Delete the rest edges */
        while(current != NULL){
            if( current->link == receiver){ /* If current points at an edge to the receiver/acc2 */
                printf("Deleted edge |%s| --%d--> |%s|.\n",acc1,current->ammount,acc2);
                if (previous == NULL) /* Then there is no previous node */
                    sender->out_transactions=current->next;
                else
                    previous->next = current->next;
                ListNode *temp = current;
                current = current->next; /* Notice that I dont set previous = current */
                free(temp);  /* and that's because when temp is deleted, the previous node remains */
                found = true;   /* the same as before deletion. */
            }
            else{
                previous = current;
                current = current->next;
            }
        }
    }

    if(found){
        /* Delete it from receiver's in_transactions. */
        current = receiver->in_transactions;
        /* Keep in mind that current->link is actually the sender as mentioned in BankTypes.h */
        if( current!=NULL){
            ListNode *previous;
            if(current->link == sender){ 
                /* The first node is an edge we want to delete */
                receiver->in_transactions=current->next;
                ListNode *temp = current;
                previous = current;
                current = current->next;
                free(temp);
            }
            /* Delete the rest edges */
            while(current != NULL){
                if( current->link == sender){
                    previous->next = current->next;
                    previous = current;
                    ListNode *temp = current;
                    current = current->next;
                    free(temp);
                }
                else{
                    previous = current;
                    current = current->next;
                }
            }
        }
    }
    else
        printf("No edges exist from |%s| to |%s|.\n",acc1,acc2);
}

TreeNode *search(TreeNode *n,char *acc1){
    if(n == NULL)
        return NULL; /* It doesn't exists in tree */

    if(strcmp(n->account_name,acc1) < 0)
        return search(n->right,acc1);   
    else if(strcmp(n->account_name,acc1) > 0)
        return search(n->left,acc1);   
    return n; /* Found it */
}

TreeNode *insert(TreeNode *node, char *key){
    if (node == NULL){ /*then the tree is emtpy and a one-node tree is returned*/
        printf("Inserted |%s|.\n",key);
        return newTreeNode(key);
    }

    if (strcmp(key,node->account_name) < 0)  /*if key < node->account_name */
        node->left = insert(node->left, key);
    else if (strcmp(key,node->account_name) > 0)
        node->right = insert(node->right,key);
    else{ /*The account name already exists in the tree*/
        printf("|%s| exists already.\n",key);
        return node; /* Nothing changes */
    }

    node->height = max(height(node->left),height(node->right)) +1; /* New height of node after key was inserted */
    
    int balance = balanceFactor(node);
    if (balance == 2)
        if (strcmp(key,node->left->account_name) < 0)
            /* node->left is left higher so a single right rotation is performed. */
            return rightRotation(node);
        else{
            /* node->left is right higher so a double left-right rotation is performed. */
            node->left = leftRotation(node->left);
            return rightRotation(node);
        }

    if (balance == -2)
        if (strcmp(key,node->right->account_name) > 0)
            /* node->right is right higher so a single left rotation is performed. */
            return leftRotation(node);
        else{
            /* node->right is left higher so a double right-left rotation is performed. */
            node->right = rightRotation(node->right);
            return leftRotation(node);
        }
    
    return node; /* if the node is balanced nothing changed */
}

TreeNode *del(TreeNode *r,TreeNode *n){
    /* This function has to do with the avl operations that must be executed on deletion. */
        
    if ( n->left == NULL || n->right == NULL){
        TreeNode *temp;
        printf("Deleted |%s|.\n",n->account_name);
        if ( n->left == NULL && n->right == NULL){
            /*If n has no child */
            temp = n;
            n = NULL;
            freeTreeNode(r,temp);
            return n; /*there was only one node ,so empty tree is returned */
        }
        else{  
            /* If n has one child */
            if (n->left == NULL) /* temp point at it */
                temp = n->right;
            else
                temp = n->left;

            /* Now copy the child to this node and then delete the child */
            /* I use temp2 because the copying must be done after freeTreeNode() */
            /* or else the edges will be messed up.*/
            TreeNode *temp2 = (TreeNode*)malloc(sizeof(TreeNode));
            *temp2 = *temp; 
            freeTreeNode(r,n);
            *n = *temp2;
        }
    }
    else{
        /* n has two children */
        /* Let's find its successor */
        TreeNode *successor = n->right;
        while(successor->left != NULL)
            successor = successor->left;
        
        /* swap n and successor */
        TreeNodecpy(n,successor);
        
        /* Now the old n is a leaf. Delete it */
        n->right = del(r,n->right);
    }
    /* Now that the node is deleted, we check if the tree became unbalanced and if so we should rebalance it. */

    /* Find the new height */
    n->height = max(height(n->left), height(n->right)) + 1;
    
    int balance = balanceFactor(n);
    
    if (balance == 2)
        /* n is left higher*/
        if( balanceFactor(n->left) >= 0)
            /*  The left child of n is balanced or left higher. A single right rotation is performed */
            return rightRotation(n);
        else{
            /* The left child of n is right higher. A double left-right rotation is performed */
            n->left = leftRotation(n->left);
            return rightRotation(n);
        }        
    if (balance == -2)
        /* n is right higher */
        if( balanceFactor(n->right) <= 0)
            /* The right child of n is balanced or right higher. A single right iotation is performed */
            return leftRotation(n);
        else{
            /* The right child of n is left higher. A double right-left rotation is performed */
            n->right = rightRotation(n->right); 
            return leftRotation(n);
        }

    return n; /* If we get here it means that the new tree was balanced and no rotation were required. */
}

bool cycles_find_util(TreeNode *start,TreeNode *n, int w,StackNode *S){
    /* Works similar to DFS with the diffrence that */
    /* nodes that are part of cycle can be visited multiple times. */
    S = push(S, n, w);
    bool flag=false;
    n->visited = true;
    ListNode *it = n->out_transactions;
    while(it != NULL){
        if(it->link == start){
            flag = true;
            printf("Cycle found : ");
            print_stack(push(S,start,it->ammount)); /* pushing start so that its printed in the end */
            printf("\n");
        }
        else if(!it->link->visited){
            if(cycles_find_util(start,it->link,it->ammount,S)){
                it->link->visited = false;
                flag=true;
            }
        }
        it = it->next;
    }
    if(flag) /* This way i unvisit only the nodes that are part of cucle */
        n->visited = false; /* so that it can be traversed again from other cycles */
    S = pop(S, &n);
    return flag;
}

void initialize_nodes(TreeNode *n){
    /* This function sets the desired values, to all nodes of the tree recursively */
    if(n != NULL){
        n->visited = false;
        initialize_nodes(n->left);
        initialize_nodes(n->right);
    }
}

void cycles_find(TreeNode *r, TreeNode *n){
    initialize_nodes(r);
    StackNode *S = NULL;
    if(!cycles_find_util(n,n,0,S))
        printf("No cycles found involving |%s|\n",n->account_name);
}

bool find_cycles_util(TreeNode *start,TreeNode *n, int w, int k,StackNode *S){
    /* Works similar to DFS with the diffrence that */
    /* nodes that are part of cycle can be visited multiple times. */
    /* k is the max allowed edge weight */
    bool flag=false;
    S = push(S, n, w);
    ListNode *it = n->out_transactions;
    while(it != NULL){
        if(it->ammount >= k){
            if(it->link == start){
                it->visited = false;
                flag = true;
                printf("Cycle found : ");
                print_stack(push(S,start,it->ammount)); /* pushing start so that its printed in the end */
                printf("\n");
            }
            else if(!it->visited){
                it->visited = true;
                if(find_cycles_util(start,it->link,it->ammount,k,S)){
                    it->visited = false;
                    flag=true;
                }
            }
        }
        it = it->next;
    }
    S = pop(S, &n);
    return flag;
}

void initialize_edges(TreeNode *n){
    if(n != NULL){
        ListNode *it = n->out_transactions;
        while(it!=NULL){
            it->visited = false;
            it=it->next;
        }
        initialize_edges(n->left);
        initialize_edges(n->right);
    }
}

void find_cycles(TreeNode *r, TreeNode *n, int k){
    initialize_edges(r);
    StackNode *S = NULL;
    if (!find_cycles_util(n,n,0,k,S))
        printf("No cycles found involving |%s| (k=%d)\n",n->account_name,k);
}

bool traceflow_util(TreeNode *n, TreeNode *goal, int w, int l, StackNode *S){
    /* Works similar to DFS. */
    /* l is the max allowed path length */
    if(l <= 0)
        return false;
    bool flag = false;
    S = push(S, n, w);
    ListNode *it = n->out_transactions;
    while(it != NULL){
        if(!it->visited){
            it->visited = true;
            if( it->link == goal){
                flag = true;
                printf("Trace found : ");
                print_stack(push(S,goal,it->ammount));
                printf("\n");
            }
            if(traceflow_util(it->link,goal,it->ammount,l-1,S)) /* decreament l by 1 */
                flag = true;
            it->visited = false;
        }
        it = it->next;
    }
    S = pop(S, &n);
    return flag;
}

void traceflow(TreeNode *r, TreeNode *start, TreeNode *goal, int l){
    initialize_edges(r);
    StackNode *S = NULL;
    if(!traceflow_util(start,goal,0,l,S))
        printf("No trace from |%s| to |%s| of length <= %d\n",start->account_name, goal->account_name,l);
}
    
void receiving_edges(TreeNode *n){
    printf("|%s| has received the following transactions:\n",n->account_name);
    int count = 0,sum=0;
    ListNode *it = n->in_transactions;
    while (it != NULL){
        printf("\t|%s| --%d--> |%s|\n",it->link->account_name,it->ammount,n->account_name);
        count++;
        sum+=it->ammount;
        it=it->next;
    }
    printf("Transactions ammount: %d \nTotal sum: %d $\n",count,sum);
}

void TreeNodecpy(TreeNode *a,TreeNode *b){
    strcpy(a->account_name,b->account_name);

    a->out_transactions = b->out_transactions;

    ListNode *it = b->out_transactions;
    while (it != NULL){
        ListNode *it_receiver = it->link->in_transactions;  /*iterate receivers' incoming edges and make them point to a instead of b*/
        while (it_receiver != NULL){
            if (it_receiver->ammount == it->ammount && it_receiver->link == b){
                it_receiver->link = a;
                break;
            }
            it_receiver = it_receiver->next;
        }
        it=it->next;
    }

    a->in_transactions = b->in_transactions;

    it = b->in_transactions;
    while (it != NULL){
        ListNode *it_sender = it->link->out_transactions;  /*iterate senders' outgoing edges and make them point to a instead of b*/
        while (it_sender != NULL){
            if (it_sender->ammount == it->ammount && it_sender->link == b){
                it_sender->link = a;
                break;
            }
            it_sender = it_sender->next;
        }
        it=it->next;
    }
}

TreeNode *newTreeNode(char *acc_name){
    TreeNode* node = (TreeNode *) malloc(sizeof(TreeNode));
    if (node == NULL){
        printf("Memory Error.\n");
        exit(27);
    }
    strcpy(node->account_name,acc_name);
    node->out_transactions = NULL;
    node->in_transactions = NULL;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}


TreeNode *freeTreeNode(TreeNode *r,TreeNode *n){
    /* This function's goal is to free the node's memory correctly. */
    /* CAUTION: In order to delete a node from the tree, del() should be called instead, */
    /* since freeTreeNode() has nothing to do with the AVL operations that are required*/

    ListNode *it = n->out_transactions;
    /*delete outgoing edges*/
    while (it != NULL){
        ListNode *temp=it;
        delete_edge(r,n->account_name,temp->link->account_name,temp->ammount);
        it = it->next;
    }

    it = n->in_transactions;
    /*delete incoming edges*/
    while (it != NULL){
        ListNode *temp=it;
        delete_edge(r,temp->link->account_name,n->account_name,temp->ammount);
        it = it->next;
    }
    free(n);
    
    return n;
}

ListNode *newListNode(int amm, TreeNode *n){
    ListNode *l = (ListNode *) malloc(sizeof(ListNode));
    if (l == NULL){
        printf("Memory Error.\n");
        exit(27);
    }
    l->ammount = amm;
    l->link = n;
    l->next = NULL;
    return l;
}

TreeNode *leftRotation(TreeNode *r){
    TreeNode *x = r->right;  /* x is the right child of the given Treenode */
    TreeNode *w = x->left; /* w is the left child of x */
   
    /* Rotation */ 
    x->left = r; /* x becomes the new root */ 
    r->right = w; /* the old root now has w as right child */
    
    /* Find new heights */
    r->height = max(height(r->left), height(r->right)) + 1; 
    x->height = max(height(x->left), height(x->right)) + 1;
    
    return x;
}

TreeNode *rightRotation(TreeNode *r){
    TreeNode *x = r->left;  /* x is the left child of the given Treenode */
    TreeNode *w = x->right; /* w is the right child of x */
   
    /* Rotation */ 
    x->right = r; /* x becomes the new root */ 
    r->left = w; /* the old root now has w as left child */
    
    /* Find new heights */
    r->height = max(height(r->left), height(r->right)) + 1; 
    x->height = max(height(x->left), height(x->right)) + 1;
    
    return x;
}

int balanceFactor(TreeNode *node){
    if (node==NULL)
        return 0;
    return height(node->left) - height(node->right); /* If it is negative it means the node is right higher */
}

int height(TreeNode *root){
    if (root == NULL)
        return 0;
    return root->height;
}

int max(int a, int b){
    if (a > b) 
        return a;
    return b;
}

int isEmpty(StackNode *S){
    return (S==NULL);
}

StackNode *push(StackNode *s,TreeNode *n, int w){
    //printf("Pushed %s\n",n->account_name);
    StackNode *temp= (StackNode *) malloc(sizeof(StackNode));
    if (temp == NULL){
        printf("Memory Error\n");
        exit(27);
    }
    temp->next = s;
    temp->acc = n;
    temp->ammount = w;
    return temp;
}

StackNode *pop(StackNode *s,TreeNode **n){
    StackNode *temp;
    if (s == NULL){
        printf("Stack is already empty.\n");
    }
    else{
        temp = s;
        //printf("Popped %s\n",temp->acc->account_name);
        *n = temp->acc; /* the popped item is assigned to the given tree node*/
        s = temp->next;
        free(temp);
        return s;
    }
}

void print_stack(StackNode *s){
    if(s==NULL)
        return;
    print_stack(s->next); /* so that they are printed in the correct order */
    if(s->ammount)
        printf("--%d->  |%s|  ",s->ammount,s->acc->account_name);
    else
        printf("|%s|  ",s->acc->account_name);
}

void print_all_edges(TreeNode *r){
    if(r==NULL)
        return;
    ListNode *it = r->out_transactions;
    while(it != NULL){
        printf("|%s| --%d--> |%s|\n",r->account_name,it->ammount,it->link->account_name);
        it = it->next;
    }
    print_all_edges(r->left);
    print_all_edges(r->right);
}

void preorder(TreeNode *r){
    if(r!=NULL){
        printf("%s,%d ", r->account_name, r->height);
        preorder(r->left);
        preorder(r->right);
    }
}
        
