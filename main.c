#include <stdio.h>
#include <string.h>
#include "BankInterface.h"
#include "menu.h"

int main(int argc,char *argv[]){
    /* Handling command line arguments */
    char *input_file=NULL, *output_file=NULL;
    if(argc>1){
        int i;
        for(i=1 ; i<argc ; i++){
            if(!strcmp(argv[i],"-i"))
                input_file = argv[i+1];
            if(!strcmp(argv[i],"-o"))
                output_file = argv[i+1];
        }
    }

    /* Create an empty tree */
    TreeNode *root = NULL;

    if(input_file){ /* (!=NULL) then there is a given input_file */
        root=menu_insert_from_file(root, input_file);
    }    

    /* User Interface loop*/
    char choice = 'h'; /* choice = 'h' to get into the while loop, and also print the help menu */
    while (choice != 'e'){  /* the loop stops when user enters 'e' */
        if (choice == 'h')
            menu();
        printf(">");
        scanf("%c", &choice);
        switch(choice){
            case 'i':
                /* insert a new node */
                root = menu_insert(root);
                break;
 
            case 'n':
                /* insert a new edge */
                root = menu_insert_edge(root);
                break;
 
            case 'd':
                /* delete a node from the graph (and edges that are connected to it) */
                root = menu_delete(root);
                break;
 
            case 'l':
                /* delete an edge from the graph */
                menu_delete_edge(root);
                break;
 
            case 'm':
                /* modify the weight of an edge */
                menu_modify_edge(root);
                break;
 
            case 'r':
                /* print all the receiving transactions of the node (all the weights of the receiving edges) */
                menu_receiving_edges(root);
                break;
 
            case 'c':
                /* find the simple cycles that the node is involved in */
                menu_cycles_find(root);
                break;
 
            case 'f':
                /* find the cycles whose edges have weight bigger than a given value */
                menu_find_cycles(root);
                break;
            
            case 't':
                /* finds paths between two nodes */
                menu_traceflow(root);
                break;
            case 'h':
                /* prints help menu */
                break;
            case 'q':
                /* q and p are secret commands for debbugging :P */
                print_all_edges(root);
                break;
            case 'p':
                preorder(root);
                printf("\n");
                break;
           case 'e':
                printf("\nBye.\n");
                /* exits the program */
                break;
            default:
                printf("This is not a valid option. Enter 'h' to view the help menu.\n");
                break;
        }
    getchar(); /*To ignore the Enter*/
    }

    if((output_file) && (choice == 'e'))
        menu_write_in_file(root, output_file); 

    return 0;
}
