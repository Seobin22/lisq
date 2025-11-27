#include <stdio.h>
#include <stdlib.h>

typedef struct polyNode {
    float coef;
    int expon;
    struct polyNode* link;
} polyNode;

typedef polyNode* polyPointer;

/* 가용 공간 리스트의 헤드 포인터 */
polyPointer avail = NULL;

/* 함수 원형 (PDF 기준) */
polyPointer getNode(void);
void retNode(polyPointer node);
void cerase(polyPointer* ptr);

void attach(float coefficient, int exponent, polyPointer* ptr);
polyPointer create_polynomial(void);
void print_polynomial(polyPointer C);
polyPointer cpadd(polyPointer A, polyPointer B);
polyPointer single_cpmul(polyNode Ai, polyPointer B);
polyPointer cpmul(polyPointer A, polyPointer B);

/* 가용 공간 리스트에서 노드 하나 가져오기 */
polyPointer getNode(void) {
    polyPointer node;
    if (avail != NULL) {
        node = avail;
        avail = avail->link;
    }
    else {
        node = (polyPointer)malloc(sizeof(polyNode));
        if (node == NULL) {
            printf("메모리 할당 실패\n");
            exit(1);
        }
    }
    return node;
}

/* 사용이 끝난 노드를 가용 공간 리스트로 반환 */
void retNode(polyPointer node) {
    node->link = avail;
    avail = node;
}

/* 원형 연결 리스트 전체를 가용 공간 리스트로 반환 */
void cerase(polyPointer* ptr) {
    if (*ptr == NULL) return;

    polyPointer head = *ptr;
    polyPointer p = head->link;
    polyPointer temp;

    while (p != head) {
        temp = p;
        p = p->link;
        retNode(temp);
    }
    /* 헤더 노드도 반환 */
    retNode(head);
    *ptr = NULL;
}

/* 마지막 노드(*ptr)가 가리키는 곳 뒤에 새 노드 붙이기 */
void attach(float coefficient, int exponent, polyPointer* ptr) {
    polyPointer temp = getNode();
    temp->coef = coefficient;
    temp->expon = exponent;
    temp->link = NULL;

    (*ptr)->link = temp;
    *ptr = temp;  // ptr가 새로운 마지막 노드를 가리키도록
}

/* 다항식 출력 (헤더 노드는 출력 X) */
void print_polynomial(polyPointer C) {
    polyPointer p;

    if (C == NULL) {
        printf("(빈 다항식)\n");
        return;
    }

    printf("    coef    expon\n");
    p = C->link;          // 헤더 다음 노드부터
    while (p != C) {      // 다시 헤더로 돌아올 때까지
        printf("%8.2f%10d\n", p->coef, p->expon);
        p = p->link;
    }
}

/* (7.1) 다항식 생성: 입력 → 원형 연결 리스트로 구성
   A = create_polynomial();
   B = create_polynomial();
   이런 식으로 쓴다는 PDF 내용을 반영해서 인수 없음(void) */
polyPointer create_polynomial(void) {
    float c;
    int e;

    polyPointer head, rear;

    /* 몇 번째 다항식인지에 따라 A, B, C... 이름을 출력용으로만 결정 */
    static int polyCount = 0;
    char name = 'A' + polyCount;
    polyCount++;

    printf("7.1. 다항식 생성\n");
    printf("다항식 %c(x)\n", name);

    /* 헤더 노드 생성 */
    head = getNode();
    head->coef = 0.0f;
    head->expon = -1;   // 헤더 표시용
    head->link = head;  // 일단 자기 자신을 가리키게

    rear = head;

    while (1) {
        printf("다항식의 항을 입력하세요. (coef expon) : ");
        if (scanf_s("%f %d", &c, &e) != 2) {
            printf("입력 오류\n");
            exit(1);
        }

        if (e == -1) {  // 입력 종료
            break;
        }

        attach(c, e, &rear);
    }

    /* 마지막 노드의 link를 헤더로 이어서 원형 완성 */
    rear->link = head;

    printf("다항식 %c(x) :\n", name);
    print_polynomial(head);

    return head;
}

/* (7.2) 두 다항식의 덧셈: C = cpadd(A, B) */
polyPointer cpadd(polyPointer A, polyPointer B) {
    polyPointer C, lastC;
    polyPointer a, b;
    float sum;

    /* 결과 다항식의 헤더 노드 생성 */
    C = getNode();
    C->coef = 0.0f;
    C->expon = -1;
    C->link = C;
    lastC = C;

    a = A->link;  // A의 첫 항
    b = B->link;  // B의 첫 항

    /* 두 리스트 모두 헤더로 돌아오기 전까지 병합 */
    while (a != A && b != B) {
        if (a->expon > b->expon) {          // A의 지수가 더 큼
            attach(a->coef, a->expon, &lastC);
            a = a->link;
        }
        else if (a->expon < b->expon) {   // B의 지수가 더 큼
            attach(b->coef, b->expon, &lastC);
            b = b->link;
        }
        else {                            // 지수가 같음
            sum = a->coef + b->coef;
            if (sum != 0.0f) {
                attach(sum, a->expon, &lastC);
            }
            a = a->link;
            b = b->link;
        }
    }

    /* 남은 항들 처리 */
    while (a != A) {
        attach(a->coef, a->expon, &lastC);
        a = a->link;
    }

    while (b != B) {
        attach(b->coef, b->expon, &lastC);
        b = b->link;
    }

    /* 원형 리스트로 마무리 */
    lastC->link = C;
    return C;
}

/* (7.3) 단일 항 Ai 와 다항식 B의 곱: X(x) = Ai * B(x)
   PDF 함수원형: polyPointer single_cpmul(polyNode Ai, polyPointer B) */
polyPointer single_cpmul(polyNode Ai, polyPointer B) {
    polyPointer C, lastC;
    polyPointer p;

    C = getNode();
    C->coef = 0.0f;
    C->expon = -1;
    C->link = C;
    lastC = C;

    p = B->link;
    while (p != B) {
        float c = Ai.coef * p->coef;
        int e = Ai.expon + p->expon;
        attach(c, e, &lastC);
        p = p->link;
    }

    lastC->link = C;
    return C;
}

/* (7.3) 두 다항식의 곱셈: D(x) = cpmul(A(x), B(x)) */
//polyPointer cpmul(polyPointer A, polyPointer B) {
//    polyPointer D;          // 결과 다항식
//    polyPointer p;          // A의 각 항을 순회
//    polyPointer X;          // single_cpmul 결과
//    int count = 1;
//
//    /* D를 0 다항식(헤더만 있는)으로 초기화 */
//    D = getNode();
//    D->coef = 0.0f;
//    D->expon = -1;
//    D->link = D;
//
//    p = A->link;
//    while (p != A) {
//        /* A의 한 항과 B 전체의 곱 */
//        X = single_cpmul(*p, B);  // p는 polyPointer, *p는 polyNode
//
//        /* 예시 출력: 중간 결과 다항식 */
//        printf("singul_mul - C%d(x)\n", count++);
//        print_polynomial(X);
//
//        /* 누적 결과 D = cpadd(D, X) */
//        D = cpadd(D, X);
//
//        /* X 리스트는 가용 공간 리스트로 반환 */
//        cerase(&X);
//
//        p = p->link;
//    }
//
//    return D;
//}
polyPointer cpmul(polyPointer A, polyPointer B) {
    polyPointer D;
    polyPointer p;
    polyPointer X;
    int count = 1;

    D = getNode();
    D->coef = 0.0f;
    D->expon = -1;
    D->link = D;

    /* 🔵 이제는 B의 항을 기준으로 돈다! */
    p = B->link;
    while (p != B) {
        /* B의 항 하나(*p)와 A 전체(A)를 곱한다 */
        X = single_cpmul(*p, A);   // ✅ 이 줄이 핵심

        printf("singul_mul - C%d(x)\n", count++);
        print_polynomial(X);

        D = cpadd(D, X);
        cerase(&X);

        p = p->link;
    }

    return D;
}

/* main 함수: PDF 예시 흐름에 맞게 구성 */
int main(void) {
    polyPointer A = NULL, B = NULL;
    polyPointer D_add = NULL, D_mul = NULL;

    /* 7.1 다항식 생성 : A(x), B(x) */
    A = create_polynomial();   // 첫 번째 호출 → A(x)
    B = create_polynomial();   // 두 번째 호출 → B(x)

    /* 7.2 다항식 덧셈 */
    printf("7.2 다항식 덧셈\n");
    printf("다항식 덧셈 결과 : D(x)\n");
    D_add = cpadd(A, B);
    print_polynomial(D_add);

    /* 7.3 다항식 곱셈 */
    printf("7.3 다항식 곱셈\n");
    D_mul = cpmul(A, B);
    printf("다항식 곱셈 결과 : D(x)\n");
    print_polynomial(D_mul);

    /* 사용한 리스트들 정리 */
    cerase(&A);
    cerase(&B);
    cerase(&D_add);
    cerase(&D_mul);

    return 0;
}
