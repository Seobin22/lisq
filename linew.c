#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node* next;
};

struct node* A = NULL, * temp, * ptr;

void insert_front(int data) {
    temp = (struct node*)malloc(sizeof(struct node));
    temp->data = data;
    temp->next = A;
    A = temp;
}

void insert_last(int data) {
    temp = (struct node*)malloc(sizeof(struct node));
    temp->data = data;
    temp->next = NULL;
    if (A == NULL) {
        A = temp;
        return;
    }
    ptr = A;
    while (ptr->next != NULL) ptr = ptr->next;
    ptr->next = temp;
}

int delete_front() {
    if (A == NULL) return -999;
    temp = A;
    int v = temp->data;
    A = A->next;
    free(temp);
    return v;
}

int delete_data(int data) {
    ptr = A;
    temp = NULL;
    while (ptr != NULL) {
        if (ptr->data == data) {
            if (temp == NULL) A = ptr->next;
            else temp->next = ptr->next;
            free(ptr);
            return data;
        }
        temp = ptr;
        ptr = ptr->next;
    }
    return -999;
}
/*int delete(node** A,int item){
node*ptr=NULL,*ptrb=NULL;
int value;
for(ptr=(*A);ptr;ptrb=ptr.ptr=ptr->next){
if(ptr->data==item){value=ptr->data;
if(ptrb==NULL)(*A)=ptr->next;
else ptrb->next=ptr->next;
free(ptr);
return value;
}

}

}*/


int search(int data) {
    int index = 0;
    ptr = A;
    while (ptr != NULL) {
        if (ptr->data == data) return index;
        ptr = ptr->next;
        index++;
    }
    return -1;
}

void print_list() {
    ptr = A;
    printf("리스트 : Head->");
    while (ptr != NULL) {
        printf("%d->", ptr->data);
        ptr = ptr->next;
    }
    printf("Null\n");
}

void stack_menu() {
    int sel, x;
    while (1) {
        printf("\n 리스트로 구현한 스택\n 1. push\n 2. pop\n-1. exit\n어떤 기능을 수행할까요? : ");
        scanf_s("%d", &sel);
        if (sel == -1) { printf("Bye-bye ~\n"); return; }
        if (sel == 1) {
            printf("push item :");
            scanf_s("%d", &x);
            insert_front(x);
            printf("Stack : ");
            print_list();
        }
        else if (sel == 2) {
            x = delete_front();
            printf("pop item : %d\n", x);
            printf("Stack : ");
            print_list();
        }
    }
}

void queue_menu() {
    int sel, x;
    while (1) {
        printf("\n 리스트로 구현한 큐\n 1. addq\n 2. deleteq\n-1. exit\n어떤 기능을 수행할까요? : ");
        scanf_s("%d", &sel);
        if (sel == -1) { printf("Bye-bye ~\n"); return; }
        if (sel == 1) {
            printf("addq item :");
            scanf_s("%d", &x);
            insert_last(x);
            printf("Queue : ");
            print_list();
        }
        else if (sel == 2) {
            x = delete_front();
            printf("deleteq item : %d\n", x);
            printf("Queue : ");
            print_list();
        }
    }
}

int main() {
    int sel, x, result;
    while (1) {
        printf("\n 리스트 기본연산 \n 0. print list\n 1. insert_front\n 2. insert_last\n 3. delete_front\n 4. delete_\n 5. search\n-1. exit\n어떤 기능을 수행할까요? : ");
        scanf_s("%d", &sel);
        if (sel == -1) break;
        if (sel == 0) print_list();
        else if (sel == 1) {
            printf("데이터 :");
            scanf_s("%d", &x);
            insert_front(x);
            print_list();
        }
        else if (sel == 2) {
            printf("데이터 :");
            scanf_s("%d", &x);
            insert_last(x);
            print_list();
        }
        else if (sel == 3) {
            result = delete_front();
            printf("삭제 데이터 : %d\n", result);
            print_list();
        }
        else if (sel == 4) {
            printf("데이터 :");
            scanf_s("%d", &x);
            result = delete_data(x);
            printf("삭제 데이터 : %d\n", result);
            print_list();
        }
        else if (sel == 5) {
            printf("데이터 :");
            scanf_s("%d", &x);
            result = search(x);
            printf("노드번호 : %d\n", result);
            print_list();
        }
    }
    printf("Bye-bye ~\n");

    A = NULL;
    stack_menu();

    A = NULL;
    queue_menu();

    return 0;
}
