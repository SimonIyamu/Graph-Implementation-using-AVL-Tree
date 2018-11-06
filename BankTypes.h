/*
The graph's purpose is the representation of bank transactions.
Each bank account is a node in the Graph and each transaction is an edge.
The graph is implemented using an AVL Tree.
There is a TreeNode for each bank account.
For the edges of each node in the Graph, a
connected list is used. This list is a member of each TreeNode.
Each ListNode should contain information about the ammount of the transaction
and who is the receiver. For this purpose an integer and a pointer to
a TreeNode are used.
*/

typedef struct ListTag ListNode;
typedef enum { false, true } bool;

typedef struct NodeTag{ 
    /* The following data members are the main items of the node */
    char account_name[50]; /* The account name string is the key of each node */
    ListNode *out_transactions; /* A list of sent transactions */
    ListNode *in_transactions; /* A list of received transactions */
    
    bool visited; /* Used in DFS */
 
    /* The following data members are for the AVL properties */
    struct NodeTag *left;
    struct NodeTag *right;
    int height; /* Height of the tree */
}TreeNode;

struct ListTag{
    int ammount; /* Transaction ammount/Edge weight */
    TreeNode *link; /* This points to the receiver or the sender. Instead of saving the receivers name, a pointer to his TreeNode is used, for fast access. */

    bool visited; /* Used in a dfs manner */

    struct ListTag *next; /* This way we can access him faster than searching his name in the whole tree*/
};

typedef struct StackNodeTag {
    TreeNode *acc;
    int ammount; /* This is the ammount of the transaction that led to this account */

    struct StackNodeTag *next;
} StackNode;

