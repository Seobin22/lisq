#include <stdio.h>
#include <stdlib.h>
//리스트:순서를 가지고 있는 데이터들의 모임. 중복된 데이터들이 들어가도 된다.
//리스트의 구분-배열과 동적할당. 보통 동적할당.
//배열: 배열에 그냥 값을 집어넣으면 인덱스에 따라 들어가 있기 떄문에 리스트이다.[항목추가]:모두 한 칸 뒤로 민다.[항목삭제]:모두 한 칸 당긴다.
//배열의 장점은 구현이 간단하고 참조가 쉽다. 단점은 크기가 고정되어 있어 크기 변경이 어렵고, 삽입 및 삭제 시 성능이 저하될 수 있다.
//동적할당(연결리스트): [항목추가]:새로운 노드를 만들고, 이전 노드의 포인터를 새로운 노드를 가리키게 한다.[항목삭제]:이전 노드의 포인터를 삭제할 노드의 다음 노드를 가리키게 한다.
//[장]:크기변동 용이, 크기 ㄴ[단]:구현이 어려움.
//[단순연결리스트]:헤드>A>B>C>null,[단순 연결 원형 리스트]:head>A>B>C>A..[이중연결리스트]:양 옆으로 linkfild. head>A왼필드 C>null,c왼필드>B우필드 
void insert_front(int **A,int data);//더블
void insert_last(int A[],int data);//더블
void print_list(int A[]);
int search(int A[],int data);
int delete_front(int A[]);//더블
int delete(int A[],int data);//더블

struct node{
    int data; 
    struct node *next;
};

struct node *A, *temp, *ptr;  // 포인터 변수 선언
A = NULL;                     // A를 NULL로 초기화
int main(void){

    printf("Hello, World!\n");
    
    return 0;
}
void insert_front(int A[],int data){
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    new_node->data = data;
    new_node->next = A;
    A = new_node;
}