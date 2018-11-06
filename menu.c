#include <stdio.h>
#include <string.h>
#include "BankInterface.h"
#include "menu.h"

TreeNode* menu_insert_from_file(TreeNode *r,char *input_file){
    char acc1[50],acc2[50];
    int ammount;
  
    FILE *fp = fopen(input_file,"r");
    if( fp == NULL){
        printf("Could not open file %s.\n",input_file);
        return r;
    }
    printf("Reading from file %s...\n",input_file);
    while(!feof(fp)){
        fscanf(fp,"%s %s %d ",acc1,acc2,&ammount);
        r=insert_edge(r, acc1, acc2, ammount);
    }
    fclose(fp);
    printf("\033[2J\033[1;1H");
    printf("Reading from file %s was complete.\n",input_file);
    return r;    
}

/* This functions is called from menu_write_in_file which is implemented right after this one */
void write_file(TreeNode *r,FILE *fp){
    if( r==NULL )
        return;
    ListNode *it = r->out_transactions;
    fprintf(fp,"|%s|\n",r->account_name);
        while(it != NULL){
            fprintf(fp,"\t-%d->|%s|\n",it->ammount,it->link->account_name);
            it = it->next;
        }
        if(r->left)
            write_file(r->left,fp);
        if(r->right)
            write_file(r->right,fp);
}

void menu_write_in_file(TreeNode *r,char *output_file){
    char acc1[50],acc2[50];
    int ammount;
  
    FILE *fp = fopen(output_file,"w");
    if( fp == NULL){
        printf("Could not open file %s.\n",output_file);
        return;
    }
    printf("Writing in file %s...\n",output_file);

    write_file(r,fp);

    fclose(fp);
    printf("Writing in file %s was complete.\n",output_file);
}

TreeNode *menu_insert_edge(TreeNode *r){
    char Ni[50],Nj[50];
    int weight;
    scanf("%s %s %d",Ni,Nj,&weight);
    r=insert_edge(r,Ni, Nj, weight);
    return r;
}

void menu_modify_edge(TreeNode *r){
    char Ni[50],Nj[50];
    int weight,nweight;
    scanf("%s %s %d %d",Ni,Nj,&weight,&nweight);
    modify_edge(r,Ni, Nj, weight,nweight);
}

void menu_delete_edge(TreeNode *r){
    char Ni[50],Nj[50],ch;
    int weight;
    scanf("%s %s",Ni,Nj);
    ch = getchar();
    if ( ch=='\n'){ /* user did not enter a weight so all edges are deleted */
        printf("Are you sure you want to delete all transactions between |%s| and |%s|? [Y/n]",Ni,Nj);
        ch =getchar();
        if (ch == 'y' || ch == 'Y'){
            delete_all_edges(r,Ni,Nj);
            delete_all_edges(r,Nj,Ni);
        }
    }else{
        scanf("%d",&weight);
        delete_edge(r,Ni, Nj, weight);
    }
}


TreeNode *menu_insert(TreeNode *r){
    char Ni[50],Nj[50];
    scanf("%s",Ni);
    r = insert(r,Ni);
    return r;
}
 
TreeNode *menu_delete(TreeNode *r){
    char Ni[50],Nj[50];
    scanf("%s",Ni);
    TreeNode *node = search(r,Ni);
    if (node)
        node = del(r,node);
    else
        printf("|%s| does not exist.\n",Ni);
    return r;
}

void menu_cycles_find(TreeNode *r){
    char Ni[50];
    scanf("%s",Ni);
    TreeNode *node = search(r,Ni);
    if (node)
        cycles_find(r,node);
    else
        printf("|%s| does not exist.\n",Ni);
}

void menu_find_cycles(TreeNode *r){
    char Ni[50];
    int k;
    scanf("%s %d",Ni,&k);
    TreeNode *node = search(r,Ni);
    if (node)
        find_cycles(r,node,k);
    else
        printf("|%s| does not exist.\n",Ni);
}

void menu_traceflow(TreeNode *r){
    char Ni[50],Nj[50];
    int l;
    scanf("%s %s %d",Ni,Nj,&l);
    TreeNode *start = search(r,Ni);
    TreeNode *goal = search(r,Nj);
    if (start)
        if (goal)
            traceflow(r,start,goal,l);
        else
            printf("|%s| does not exist.\n",Nj);
    else
        printf("|%s| does not exist.\n",Ni);
}

void menu_receiving_edges(TreeNode *r){
    char Ni[50];
    scanf("%s",Ni);
    TreeNode *node = search(r,Ni);
    if (node)
        receiving_edges(node);
    else
        printf("|%s| does not exist.\n",Ni);
}

void menu(){
    printf("\n\t\t\t--------------- Bank Graph Menu ---------------\n"); 
    printf("\033[1;34m i Ni \033[0m: Inserts Ni as a new node.\n");
    printf("\033[1;34m n Ni Nj weight \033[0m: Insert a new edge between Ni and Nj.\n");
    printf("\033[1;34m d Ni \033[0m: Deletes a node from the graph (and edges that are connected to it).\n");
    printf("\033[1;34m l Ni Nj weight \033[0m: Deletes an edge from the graph.\n");
    printf("\033[1;34m m Ni Nj weight nweight \033[0m: Modifies the weight of the edge, from weight to nweight.\n");
    printf("\033[1;34m r Ni \033[0m: Prints all the receiving transactions of the node (all the weights of the receiving edges).\n");
    printf("\033[1;34m c Ni \033[0m: Finds the simple cycles that the node is involved in.\n");
    printf("\033[1;34m f Ni k \033[0m: Finds the cycles whose edges have weight bigger than a given value.\n");
    printf("\033[1;34m t Ni Nj l \033[0m: Finds paths between two nodes. l is the maximum ammount of edges that are traversed.\n");
    printf("\033[1;34m h \033[0m: Prints this menu.\n");
    printf("\033[1;34m e \033[0m: Exits the program.\n");
}
