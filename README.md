# Multi-graph-Implementation-using-AVL-Tree
Implementing a Graph using an adjacency AVL Tree. Each TreeNode represents a vertex of the graph, and each TreeNode has a linked list in order to represent the edges of the graph.

The graph's purpose is to represent money transactions between the accounts of a bank. 
There are no restrictions regarding the size of the graph, since it was implemented in such way that it's size can change dynamicaly. (Use command "make" in order to compile the program. The executable is called ./mygraph).There are multiple operations that can be applied on the graph, such as finding simple or non-simple cycles, and computing the money traceflow between two accounts. More specifically:

Insert Ni as a new node:
>i Ni

Insert a new edge between ni and Nj of weight w:
>n Ni Nj w

Delete a node from the graph (and edges that are connected to it)Q
>d Ni

Delete an edge from the graph:
>l Ni Nj weight

Modifie the weight of an edge:
>m Ni Nj weight nweight

Print all the receiving transactions of a Node:
>r Ni

Find all simple cycles that a node is involved in:
>c Ni

Find all cycles(simple or non) whose edges have weight bigger than k:
>f Ni k

Find all paths(simple or non) between two nodes. l is the maximum ammount of the edges traversed.
>t Ni Nj l

The application can be called from command line with the following arguments:

>./mygraph -i inputfile -o outputfile

There are some example files for testing are included in the repository.

Example execution:
>./mygraph -i small_trs.txt -o output.txt
