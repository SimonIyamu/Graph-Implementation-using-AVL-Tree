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
