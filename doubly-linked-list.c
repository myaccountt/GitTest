/*
 *  doubly-linked-list.c
 *
 *  Doubly Linked List
 *
 *  Data Structures
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
 /* 필요한 헤더파일 추가 if necessary */


typedef struct Node {
   int key;
   struct Node* llink;
   struct Node* rlink;
} listNode;


typedef struct Head {
   struct Node* first;
}headNode;

/* 함수 리스트 */

/* note: initialize는 이중포인터를 매개변수로 받음
       singly-linked-list의 initialize와 차이점을 이해 할것 */
int initialize(headNode** h);

/* note: freeList는 싱글포인터를 매개변수로 받음
      - initialize와 왜 다른지 이해 할것
       - 이중포인터를 매개변수로 받아도 해제할 수 있을 것 */
int freeList(headNode* h);

int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);
int insertFirst(headNode* h, int key);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int deleteFirst(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);


int main()
{
   char command;
   int key;
   headNode* headnode = NULL;

   do {
      printf("---2017016033 statstic songseunghyun----\n");
      printf("----------------------------------------------------------------\n");
      printf("                     Doubly Linked  List                        \n");
      printf("----------------------------------------------------------------\n");
      printf(" Initialize    = z           Print         = p \n");
      printf(" Insert Node   = i           Delete Node   = d \n");
      printf(" Insert Last   = n           Delete Last   = e\n");
      printf(" Insert First  = f           Delete First  = t\n");
      printf(" Invert List   = r           Quit          = q\n");
      printf("----------------------------------------------------------------\n");

      printf("Command = ");
      scanf(" %c", &command);

      switch (command) {
      case 'z': case 'Z':
         initialize(&headnode);
         break;
      case 'p': case 'P':
         printList(headnode);
         break;
      case 'i': case 'I':
         printf("Your Key = ");
         scanf("%d", &key);
         insertNode(headnode, key);
         break;
      case 'd': case 'D':
         printf("Your Key = ");
         scanf("%d", &key);
         deleteNode(headnode, key);
         break;
      case 'n': case 'N':
         printf("Your Key = ");
         scanf("%d", &key);
         insertLast(headnode, key);
         break;
      case 'e': case 'E':
         deleteLast(headnode);
         break;
      case 'f': case 'F':
         printf("Your Key = ");
         scanf("%d", &key);
         insertFirst(headnode, key);
         break;
      case 't': case 'T':
         deleteFirst(headnode);
         break;
      case 'r': case 'R':
         invertList(headnode);
         break;
      case 'q': case 'Q':
         freeList(headnode);
         break;
      default:
         printf("\n       >>>>>   Concentration!!   <<<<<     \n");
         break;
      }

   } while (command != 'q' && command != 'Q');

   return 1;
}


int initialize(headNode** h) {
   
   (*h) = (listNode*)malloc(sizeof(listNode));

   /* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
   if (*(h) != NULL)
      freeList(h);

   (*h)->first = NULL;

   return 1;
}

int freeList(headNode* h) {
   return 0;
}


void printList(headNode* h) {
   int i = 0;
   listNode* p;

   printf("\n---PRINT\n");

   if (h == NULL) {
      printf("Nothing to print....\n");
      return;
   }

   p = h->first;

   while (p != NULL) {
      printf("[ [%d]=%d ] ", i, p->key);
      p = p->rlink;
      i++;
   }

   printf("  items = %d\n", i);
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {

   //삽입될 노드 동적할당
   listNode* node = (listNode*)malloc(sizeof(listNode));
   listNode* p = h->first; //연결리스트 h가 공백 리스트가 아니면 리스트 h의 첫 노드의 주소를 p에 저장

   node->key = key;
   node->rlink = NULL;

   if (h->first == NULL) {      //현재 공백 리스트이면
      h->first = node;      //첫 노드
      node->llink = NULL;      //왼쪽링크는 NULL을 가리킴
      return;               //종료
   }

   while (p->rlink != NULL)  //리스트의 첫 노드부터 마지막 노드가 누구인지 계속 찾기
      p = p->rlink;
   
   p->rlink = node;    //리스트 p의 rlink 필드에 node추가 
   node->llink = p;   //node의 llink 필드에 p추가

   return 0;
}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {
   listNode* previous;
   listNode* current;
   
   if (h->first == NULL) return;      //공백 리스트이면 삭제 연산 수행 불가능
   
   //리스트 h에 삭제할 노드가 남아 있으면
   if (h->first->rlink == NULL) {  //리스트 h에 노드가 한 개만 존재하면
      free(h->first);             //첫 번째 노드의 메모리 해제
      h = NULL;          //리스트 h를 공백 리스트로 설정
   
      return;
   }
   else {       //리스트 h에 여러 개 노드가 남아 있으면
      previous = h->first;     // 직전 노드는 헤드 노드의 next 노드
      current = h->first->rlink;  //헤드 노드의 next 노드의 link 필드 주소를 current에 저장,  
                //즉, 헤드의 다음- 다음 노드가 current 노드
   
      while (current->rlink != NULL) {  //n개로 구성된 리스트 h의 n -1번째 노드에 도착할 
           //때까지 모든 노드의 link 필드에 자신의 후속 노드의 주소 저장되도록 변경함
         previous = current;
         current = current->rlink;
         }
   
         //current에는 마지막 노드의 주소가 저장된 상태이므로 마지막 노드를 삭제
         free(current);
         previous->rlink = NULL;           //n번째인 마지막 노드가 삭제되었으므로 n-1번째 노드의 link 
                                        //필드를 NULL로 지정해서 마지막 노드로 만든다
   }

   return 0;
}

/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

   listNode* node = (listNode*)malloc(sizeof(listNode));
   listNode* p = h->first;
   
   node->key = key;

   if (h->first == NULL) {      //현재 공백 리스트이면
      h->first = node;      //첫 노드
      node->llink = NULL;      //왼쪽링크는 NULL을 가리킴
      return;               //종료
   }
   else {                  //공백리스트가 아니면
      node->rlink = p;      //노드의 오른쪽링크는 처음 노드를 가리키고
      node->llink = NULL;      //노드의 왼쪽링크는 NULL을 가리킨다.
      p->llink = node;      //p의 왼쪽링크는 노드를 가리키고
      h->first = node;      //첫 부분을 노드로 바꾼다.
   }

   return 0;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {
   listNode* previous;
   listNode* current;

   if (h->first == NULL) return;      //공백 리스트이면 삭제 연산 수행 불가능

   //리스트 h에 삭제할 노드가 남아 있으면
   if (h->first->rlink == NULL) {  //리스트 h에 노드가 한 개만 존재하면
      free(h->first);             //첫 번째 노드의 메모리 해제
      h =  NULL;          //리스트 h를 공백 리스트로 설정

      return;
   }
   else {       //리스트 h에 여러 개 노드가 남아 있으면
      previous = h->first;     // 직전 노드는 헤드 노드
      current = h->first->rlink;  //헤드 노드의 next 노드의 link 필드 주소를 current에 저장,  
                         //즉, 헤드의 다음 노드가 current 노드

      //current에는 첫 노드의 다음노드
      current->llink = NULL;
      free(previous);
      h->first = current;      
   }

   return 0;
}

/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {
   listNode* current = h->first;      //처음으로 시작할노드
   listNode* last = h->first;         //맨뒤로 갈노드
   int cnt=0;
   int temp;

   while (last->rlink != NULL) {      //맨뒤로 갈 노드를 맨뒤로 보낸다
      last = last->rlink;
      cnt++;                     //노드의개수를 카운팅한다
   }

   cnt = cnt / 2;                  //노드를 반으로 나눈다

   while (cnt != 0)               //반으로 나눈 노드가 0이 안될때까지
   {
      temp = last->key;            //temp에 맨 마지막 노드 key를 넣어주고
      last->key = current->key;      //맨 마지막 노드의 키값에 맨 처음 노드의 키값을 넣어준다.
      current->key = temp;         //현재 키에 맨 마지막 노드값을 넣어준다.

      last = last->llink;
      current = current->llink;

      cnt--;
   }

   return 0;
}

/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {
   //삽입될 노드 동적할당
   listNode* node = (listNode*)malloc(sizeof(listNode));
   listNode* current = h->first; //연결리스트 h가 공백 리스트가 아니면 리스트 h의 첫 노드의 주소를 p에 저장
   listNode* previous;
   node->key = key;

   if (h->first == NULL) {      //현재 공백 리스트이면
      h->first = node;      //첫 노드
      node->llink = NULL;      //왼쪽링크는 NULL을 가리킴
      return;               //종료
   }

   while (current->rlink != NULL)  //리스트의 첫 노드부터 마지막 노드가 누구인지 계속 찾기
   {
      current = current->rlink;
      if (current->key > key)
         break;
   }
   previous = current->llink;   //previous는 현재 노드의 이전노드

   previous->rlink = node;      //previous 다음 노드는 삽입 될 노드
   previous = node->llink;      //삽입 될 노드의 전노드는 previous

   node->rlink = current;      //노드의 오른쪽노드는 큰값이 나오는 노드 바로 앞
   current->llink = node;      //current의 왼쪽은 삽입될 노드를 가리킴

   return 0;
}

/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {

   listNode* current = h->first; //연결리스트 h가 공백 리스트가 아니면 리스트 h의 첫 노드의 주소를 p에 저장
   listNode* previous;
   listNode* after;

   while (current->rlink != NULL)      //키값이 걸릴때까지 링크함
   {
      current = current->rlink;

      if (current->key == key)      //키값이 걸리면 탈출
         break;
   }

   previous = current->llink;         //previous는 이전노드
   after = current->rlink;            //after는 이후노드
   
   free(current);                  //동적할당해제

   previous->rlink = after;         //previous의 오른쪽에 after연결
   after->llink = previous;         //after의 왼쪽에 previous연결

   return 0;
}