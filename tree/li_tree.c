#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node {
    int data;
    struct node* lchild;
    struct node* rchild;
} Node;

/* ------------------ 8.1 트리 구성 ------------------ */
Node* make_tree_by_code() {
    Node* n1 = malloc(sizeof(Node));
    Node* n3 = malloc(sizeof(Node));
    Node* n4 = malloc(sizeof(Node));
    Node* n5 = malloc(sizeof(Node));
    Node* n8 = malloc(sizeof(Node));

    n1->data = 1; n1->lchild = n1->rchild = NULL;
    n4->data = 4; n4->lchild = n4->rchild = NULL;
    n3->data = 3; n3->lchild = n1; n3->rchild = n4;
    n8->data = 8; n8->lchild = n8->rchild = NULL;

    n5->data = 5; n5->lchild = n3; n5->rchild = n8;

    return n5;
}

/* ------------------ 순회 함수 ------------------ */
void inorder(Node* root) {
    if (root == NULL) return;
    inorder(root->lchild);
    printf("%d ", root->data);
    inorder(root->rchild);
}

void preorder(Node* root) {
    if (root == NULL) return;
    printf("%d ", root->data);
    preorder(root->lchild);
    preorder(root->rchild);
}

void postorder(Node* root) {
    if (root == NULL) return;
    postorder(root->lchild);
    postorder(root->rchild);
    printf("%d ", root->data);
}

/* ------------------ 8.2 트리 복사 ------------------ */
Node* copy(Node* original) {
    if (original == NULL) return NULL;

    Node* temp = malloc(sizeof(Node));
    temp->data = original->data;
    temp->lchild = copy(original->lchild);
    temp->rchild = copy(original->rchild);
    return temp;
}

/* ------------------ 8.2 트리 동일성 검사 ------------------ */
int equal(Node* A, Node* B) {
    if (A == NULL && B == NULL) return 1;
    if (A == NULL || B == NULL) return 0;

    return (A->data == B->data) &&
        equal(A->lchild, B->lchild) &&
        equal(A->rchild, B->rchild);
}

/* ------------------ 8.2 swap 트리 복사 ------------------ */
Node* swap(Node* original) {
    if (original == NULL) return NULL;

    Node* temp = malloc(sizeof(Node));
    temp->data = original->data;

    // 오른쪽 subtree -> 왼쪽
    temp->lchild = swap(original->rchild);
    // 왼쪽 subtree -> 오른쪽
    temp->rchild = swap(original->lchild);
    return temp;
}

/* ------------------ 8.3 랜덤 트리 삽입 ------------------ */
Node* insert_random(Node* root, int data) {
    if (root == NULL) {
        Node* n = malloc(sizeof(Node));
        n->data = data;
        n->lchild = n->rchild = NULL;
        return n;
    }

    int dir = rand() % 2; // 0:left, 1:right

    if (dir == 0) {
        if (root->lchild == NULL) {
            Node* n = malloc(sizeof(Node));
            n->data = data;
            n->lchild = n->rchild = NULL;
            root->lchild = n;
        }
        else {
            insert_random(root->lchild, data);
        }
    }
    else {
        if (root->rchild == NULL) {
            Node* n = malloc(sizeof(Node));
            n->data = data;
            n->lchild = n->rchild = NULL;
            root->rchild = n;
        }
        else {
            insert_random(root->rchild, data);
        }
    }
    return root;
}

/* ------------------ main ------------------ */
int main() {
    srand(time(NULL));

    printf("8.1.1. 트리 구성 (A = make_tree_by_code())\n");
    Node* A = make_tree_by_code();

    printf("8.1.2. 트리 순회 (A)\n");
    printf("inorder(A) : "); inorder(A); printf("\n");
    printf("preorder(A) : "); preorder(A); printf("\n");
    printf("postorder(A) : "); postorder(A); printf("\n\n");

    printf("8.2.1. 트리 복사 (B = copy(A))\n");
    Node* B = copy(A);

    printf("8.2.2. 트리 순회 (B)\n");
    printf("inorder(B) : "); inorder(B); printf("\n");
    printf("preorder(B) : "); preorder(B); printf("\n");
    printf("postorder(B) : "); postorder(B); printf("\n\n");

    printf("8.2.3. 트리 동질성 검사 (equal(A, B))\n");
    printf("equal(A, B) : %s\n\n", equal(A, B) ? "TRUE" : "FALSE");

    printf("8.2.4. 트리 swap (C = swap(A))\n");
    Node* C = swap(A);

    printf("8.2.5. 트리 순회 (C)\n");
    printf("inorder(C) : "); inorder(C); printf("\n");
    printf("preorder(C) : "); preorder(C); printf("\n");
    printf("postorder(C) : "); postorder(C); printf("\n\n");

    printf("equal(A, C) : %s\n\n", equal(A, C) ? "TRUE" : "FALSE");

    printf("8.3.1. 랜덤 트리 자동 생성 (D)\n");
    int n;
    printf("Input n : ");
    scanf_s("%d", &n);

    Node* D = NULL;
    for (int i = 1; i <= n; i++) {
        D = insert_random(D, i);
    }

    printf("\n8.3.2. 트리 순회 (D)\n");
    printf("inorder(D) : "); inorder(D); printf("\n");
    printf("preorder(D) : "); preorder(D); printf("\n");
    printf("postorder(D) : "); postorder(D); printf("\n");

    return 0;
}
