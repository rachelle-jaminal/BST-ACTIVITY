#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *left, *right;
} Node;



void InOrder(Node *root){
    if(root== NULL) return;
    InOrder(root->left);
    printf("%d ", root->data);
    InOrder(root->right);
}

void PreOrder(Node *root){
    if(root== NULL) return;
    PreOrder(root->left);
    PreOrder(root->right);
    printf("%d ", root->data);
}

void PostOrder(Node *root){
    if(root== NULL) return;
    printf("%d ", root->data);
    PostOrder(root->left);
    PostOrder(root->right);
}

Node *minimum(Node *root){
    if(root== NULL) return NULL;
    while(root->left != NULL){
        root= root->left;
    }
    return root;
}

int minimums(Node *root){
    if(root== NULL) return NULL;
    while(root->left != NULL){
        root= root->left;
    }
    return root->data;
}

Node *maximum(Node *root){
    if(root== NULL) return NULL;
    while(root->right != NULL){
        root= root->right;
    }
    return root;
}

int maximums(Node *root){
    if(root== NULL) return NULL;
    while(root->right != NULL){
        root= root->right;
    }
    return root->data;
}

Node *searching(Node *root, int key){
    if(root==NULL || root->data == key) return root;
    if(key > root->data) return searching(root->left, key);
    return searching(root->right, key);
}

int countNode(Node *root){
    if(root == NULL) return 0;
    return 1 + countNode(root->left) + countNode(root->right);
}

int height(Node *root){
    if(root==NULL){
        return 0;
    }
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

int countLeaf(Node *root){
    if(root == NULL){
        return 0;
    }
    if(root->left == NULL && root->right == NULL) return 1;
    return countLeaf(root->left) + countLeaf(root->right);
}

Node *insertion_No_Duplicate(Node **root, int value){
    Node *current = *root, *parent = NULL;
    while(current != NULL){
        parent = current;
        if(value < current->data){   
            current = current->left;
        } else if(value > current ->data){
            current = current->right;
        } else {
            return NULL;
        }
    }

    Node *temp = malloc(sizeof(*temp));
    if(temp == NULL){return NULL;}
    temp -> data = value;
    temp->left = NULL;
    temp->right = NULL;

        if(parent == NULL){
            *root = temp;
        } else if(value < parent ->data){
            parent->left = temp;
        } else {
            parent ->right = temp;
        }

        return *root;
}

Node *deletion(Node *root, int key){
    if(root == NULL){
        return NULL;
    }

    if(key < root->data){
        root->left = deletion(root->left, key);
    }
    else if(key > root->data){
        root->right = deletion(root->right, key);
    }
    else{
        Node *temp;
        if(root->left == NULL){
            temp = root->right;
            free(root);
            return temp;
        } else if(root->right == NULL){
            temp = root-> left;
            free(root);
            return temp;
        }

        temp = minimum(root->right);
        root->data = temp->data;
        root->right = deletion(root->right, temp->data);
    }
}
int main(){

    Node *root = NULL;
    int choice;

    do{ 
        printf("========================================");
        printf("       BINARY SEARCH TREE SYSTEM        ");
        printf("========================================");
        printf("[1] Insert Node\n");
        printf("[2] Search Node\n");
        printf("[3] Delete Node\n");
        printf("[4] Inorder Traversal\n");
        printf("[5] Preorder Traversal\n");
        printf("[6] Postorder Traversal\n");
        printf("[7] Find Minimum Value\n");
        printf("[8] Find Maximum Value\n");
        printf("[9] Count Total Nodes\n");
        printf("[10] Count Leaf Nodes\n");
        printf("[11] Find Tree Height\n");
        printf("[12] Exit\n\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice){
            case 1: 
            int values, pick;
            while(pick!=1){
                printf("Enter number to insert: ");
                scanf("%d", &values);
                if(searching(root, values) != NULL){
                    printf("%d already exists.\n" , values);
                }
                else{
                    insertion_No_Duplicate(&root, values);
                     printf("%d successfully input.\n" , values);
                }
                printf("insert another number [1] yes [2] no: ");
                scanf("%d", &pick);
            }
            break;

            case 2:
            int search;
            printf("Enter number in the tree to search: ");
            scanf("%d", &search);
            if(searching(root, search)){
                printf("%d is found!", search);
            } else {
                printf("%d is not found!");
            }
            break;

            case 3:
            int delete;
            printf("Enter node to delete: ");
            scanf("%d", &delete);
            root=deletion(root, delete);
            printf("Inorder: "); InOrder(root); printf("\n");
            break;

            case 4:
            printf("Inorder: "); InOrder(root); printf("\n");
            break;

            case 5:
            printf("Preorder: "); PreOrder(root); printf("\n");
            break;

            case 6: 
            printf("Postorder: "); PostOrder(root); printf("\n");
            break;

            case 7:
            printf("Minimum Value: %d", minimums(root)); 
            break;

            case 8: 
            printf("Maximum Value: %d",  maximums(root));
            break;

            case 9:
            printf("Total Nodes: %d", countNode(root)); 
            break;

            case 10: 
            printf("Total leaf nodes: %d", countLeaf(root)); 
            break;

            case 11: 
            printf("Tree Height: %d", height(root));
            break;

            default:
            printf("Thank you!");
            break;
        }


    }while(choice != 12);

    return 0;
}