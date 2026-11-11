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
    printf("%d ", root->data);
    PreOrder(root->left);
    PreOrder(root->right);
}

void PostOrder(Node *root){
    if(root== NULL) return;
    PostOrder(root->left);
    PostOrder(root->right);
    printf("%d ", root->data);
}


Node *minimum(Node *root){
    if(root== NULL) return NULL;
    while(root->left != NULL){
        root= root->left;
    }
    return root;
}

int minimums(Node *root){
    if(root== NULL) return 0;
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
    if(root== NULL) return 0;
    while(root->right != NULL){
        root= root->right;
    }
    return root->data;
}

Node *searching(Node *root, int key){
    if(root==NULL || root->data == key) return root;
    if(key < root->data) return searching(root->left, key);
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
    Node *temp = (Node *)malloc(sizeof(*temp));
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
        return temp;
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
    return root;
}

int countLevel(Node *root){
    if(root == NULL) return 0;
    int leftLevel = countLevel(root->left);
    int rightLevel = countLevel(root->right);
    if(leftLevel > rightLevel){
        return 1 + leftLevel;
    }
    else{
        return 1 + rightLevel;
    }
}

int Empty(Node *root){
    if(root == NULL){
        return 1;
    }
    return 0;
}

Node *findParentNode(Node *root, int key){
    if(root == NULL || root->data == key) return NULL;
    if(root->left != NULL && root->left->data == key || root->right != NULL && root->right->data == key){
        return root;
    }
    if(key < root->data){
        return findParentNode(root->left, key);
    }
    return findParentNode(root->right, key);
}

int countOneChild(Node *root){
    if(root == NULL) return 0;
    int count = 0;
    if(root->left == NULL && root->right != NULL || root->left != NULL && root->right == NULL){
        count = 1;
    }
    return count + countOneChild(root->left) + countOneChild(root->right);
}

int main(){

    Node *root = NULL, *root2 = NULL, *p;
    int choice;

    do{ 
        printf("========================================\n");
        printf("       BINARY SEARCH TREE SYSTEM        \n");
        printf("========================================\n");
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
        printf("[12] Count One Child Nodes\n");
        printf("[13] Find Parent of a Node\n");
        printf("[14] Exit\n\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);   

        switch(choice){
            case 1: 
                int values, pick = 1;
                while(pick == 1){
                    printf("Enter number to insert: ");
                    scanf("%d", &values);
                    if(searching(root, values) != NULL){
                        printf("%d already exists.\n" , values);
                    }
                    else{
                        insertion_No_Duplicate(&root, values);
                        printf("%d successfully input.\n" , values);
                    }
                    do{
                        printf("insert another number [1] yes [2] no: ");
                        scanf("%d", &pick);
                            if(pick < 1 || pick > 2){
                                printf("Invalid choice!\n");
                            }
                        }
                    while(pick < 1 || pick > 2);
                }
            break;

            case 2:
                int search;
                printf("Enter number to search: ");
                scanf("%d", &search);
                if(Empty(root)){
                    printf("Tree is Empty.\n\n");
                } else{
                    if(searching(root, search)){
                        printf("%d is FOUND in the Binary Search Tree.\n", search);
                    } else {
                        printf("%d is not found!\n", search);
                    }
                }
            break;

            case 3:
                int delete_number;
                if(Empty(root)){
                    printf("Tree is Empty.\n\n");
                } else{
                    printf("Enter node to delete: ");
                    scanf("%d", &delete_number);
                    root=deletion(root, delete_number);
                    printf("Inorder: "); InOrder(root); printf("\n\n");
                }
                
            break;

            case 4:
                if(Empty(root)){
                    printf("Tree is Empty.\n\n");
                } else{
                    printf("Inorder: "); InOrder(root); printf("\n\n");
                }
            break;

            case 5:
                if(Empty(root)){
                    printf("Tree is Empty.\n\n");
                } else{
                    printf("Preorder: "); PreOrder(root); printf("\n\n");
                }
            break;

            case 6: 
                if(Empty(root)){
                    printf("Tree is Empty.\n\n");
                } else{
                    printf("Postorder: "); PostOrder(root); printf("\n\n");
                }         
            break;

            case 7:
                if(Empty(root)){
                    printf("Tree is Empty.\n\n");
                } else{
                    printf("Minimum Value: %d\n\n", minimums(root));
                }     
            break;

            case 8: 
                if(Empty(root)){
                    printf("Tree is Empty.\n\n");
                } else{
                    printf("Maximum Value: %d\n\n",  maximums(root));
                }
            break;

            case 9:
                if(Empty(root)){
                    printf("Tree is Empty.\n\n");
                } else{
                    printf("Total Nodes: %d\n\n", countNode(root)); 
                }
            break;

            case 10: 
                if(Empty(root)){
                    printf("Tree is Empty.\n\n");
                } else{
                    printf("Total leaf nodes: %d\n\n", countLeaf(root)); 
                }  
            break;

            case 11: 
                if(Empty(root)){
                    printf("Tree is Empty.\n\n");
                } else{
                    printf("Tree Height: %d\n", height(root));
                    printf("Level of Tree: %d\n\n", countLevel(root));
                }
            break;

            case 12:
                printf("Number of Nodes with exactly one child: %d\n\n", countOneChild(root));
            break;

            case 13:
                int parent;
                printf("Enter Node to find its parent: ");
                scanf("%d", &parent);
                if(searching(root, parent) == NULL){
                    printf("%d is not in the tree.\n\n", parent);
                } else{
                    p = findParentNode(root, parent);
                    if(p == NULL){
                        printf("%d is the root and has no parent.\n\n", parent);
                    } else{
                        printf("The parent of %d is %d\n\n", parent, p->data);
                    }
                }
            break;

            case 14:
                printf("Thank you");
            break; 

            default:
                printf("Invalid choice\n\n");
            break;
        }
    }
    
    while(choice != 13);
    
    return 0;
}