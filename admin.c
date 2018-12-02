#include "fileIO.h"

int maxBookId(){
  int savedat1, savedat2;
  BookNode *head = bookMemAlloc(), *curr = NULL;
  curr = head->nextNode;
  savedat1 = curr->book.bookId;
  while(curr->nextNode != NULL){
	curr = curr->nextNode;
	savedat2 = curr->book.bookId;
	if(savedat1 < savedat2){
	  savedat1 = savedat2;
	}
  }
  curr = NULL;
  return savedat1;
}/*파일에 있는 도서의 번호중 가장 큰 번호를 찾아 리턴해준다.*/

void addNewBook();
void delBook();
void borrBook();
void ReturnBook();
char *NumToDay(struct tm *);
bool SearchBook(char *);

int main(void){
  printf(">>관리자 메뉴<<\n");
  printf("1. 도서 등록\t 2. 도서 삭제\n");
  printf("3. 도서 대여\t 4. 도서 반납\n");
  printf("5. 도서 검색\t 6. 회원 목록\n");
  printf("7. 로그아웃\t 8. 프로그램 종료\n");
  printf("\n");
  printf("번호를 선댁하세요: ");
  int num;
  scanf("%d", &num);

  if(num == 1){
	  addNewBook();
  }

  else if(num == 2){
	  delBook();
  }
  else if(num == 3){
	  borrBook();
  }
  else if(num == 4){
	  ReturnBook();
  }
  else if(num == 5){
  }
  else if(num == 6){
  }
  else if(num == 7){
  }
  else if(num == 8){
	  printf("프로그램을 종료합니다.");
  }
  else{
	  printf("잘못된 입력입니다.");
  }
  return 0;
}

  
void addNewBook(){
	int c;
	char YN;
	bool check;
	BookNode *head = NULL;
	Book newbook;
	char newbName[100];
	char newbPublisher[100];
	char newbAuthor[100];
	char newbLocation[100];
	int bookId = maxBookId()+1;
	
	printf(">>도서 등록<<\n");
	printf("\n");
	printf("도서명: ");
	while(c = getchar() != '\n' && c != EOF);
	scanf("%[^\n]", newbName);
	while(c = getchar() != '\n' && c != EOF);
	printf("출판사: ");
	scanf("%[^\n]", newbPublisher);
	while(c = getchar() != '\n' && c != EOF);
	printf("저자명: ");
	scanf("%[^\n]", newbAuthor);
	while(c = getchar() != '\n' && c != EOF);
	printf("ISBN: ");
	scanf("%lld", &newbook.bookISBN);
	while(c = getchar() != '\n' && c != EOF);
	printf("소장처: ");
	scanf("%[^\n]", newbLocation);
	while(c = getchar() != '\n' && c != EOF);
	printf("\n");
	printf("자동입력사항\n");
	printf("\n");
	printf("대여가능 여부: Y\n");
	printf("도서번호: %d\n", bookId);
	printf("\n");
	printf("등록하시겠습니까? ");
	YN = getchar();
	if(YN == 'Y'){

	newbook.bookName = malloc(sizeof(Book)*(strlen(newbName)+1));
	newbook.bookPublisher = malloc(sizeof(Book)*(strlen(newbPublisher)+1));
	newbook.bookAuthor = malloc(sizeof(Book)*(strlen(newbAuthor)+1));
	newbook.bookLocation = malloc(sizeof(Book)*(strlen(newbLocation)+1));
	
	strcpy(newbook.bookName, newbName);
	strcpy(newbook.bookPublisher, newbPublisher);
	strcpy(newbook.bookAuthor, newbAuthor);
	strcpy(newbook.bookLocation, newbLocation);

	newbook.bookId = bookId;
	newbook.isBookAvailable = 'Y';
	
	head = bookMemAlloc();
	check = addBook(head, newbook);
		if(check == true){
			printf("도서가 등록되었습니다.\n");
		}
		else{
			printf("도서 등록에 실패했습니다.\n");
		}
	head = NULL;
   }
}/* 새 책의 정보를 입력받는다.  
	bookMemAlloc함수를 통해 파일에 저장된 도서 목록을 연결리스트로 만들고 head에 연결리스트의 시작주소를 저장한다.
	addBook함수를 통해 새 책의 정보를 담은 노드를 연결리스트에 추가하고 파일에 수정된 정보를 저장한다.*/

void delBook(){
	BookNode *bookHead = bookMemAlloc(), *head = NULL;
	BorrowNode *borrowHead = borrowMemAlloc();
	int targetBookId, c;
	char *kind = "삭제";
	bool check;

	head = bookHead;

	printf(">>도서 삭제<<\n");
	check = SearchBook(kind);
	printf("\n");
	if(check == true){
		printf("삭제할 도서의 번호를 입력하세요: ");
		scanf("%d", &targetBookId);
		while(c = getchar() != '\n' && c != EOF);
		while(head != NULL){
		  head = head->nextNode;
		  if(head->book.bookId == targetBookId){
			check = removeBook(bookHead, borrowHead, targetBookId);	
			if(check == true){
			  printf("도서가 삭제되었습니다.\n");
			}
			else{
			  printf("이 도서는 삭제할 수 없습니다.\n");
			}
		  }
		}
	}
}/* 삭제할 도서의 번호를 입력받는다.
	removeBook함수를 통해 해당 도서를 삭제한다.*/

void borrBook(){
  int targetStuId, targetBookId, c;
  char *kind = "대여";
  char YN;
  bool check;
  Borrow newBorrow;
  ClientNode *clientHead = clientMemAlloc(), *c_head = NULL;
  BookNode *bookHead = bookMemAlloc(), *b_head = NULL;
  BorrowNode *borrowHead = borrowMemAlloc();
  c_head = clientHead;
  b_head = bookHead;

  printf(">>도서 대여<<\n");
  check = SearchBook(kind);
  printf("\n");
  if(check == true){
	printf("학번을 입력하세요: ");
	scanf("%d",&targetStuId);
	while(c = getchar() != '\n' && c != EOF);
	while(c_head->nextNode != NULL){
	  c_head = c_head->nextNode;
	  if(c_head->client.clientStuId == targetStuId){
		break;
	  }
	}

	if(c_head->nextNode == NULL && c_head->client.clientStuId != targetStuId){
	  printf("일치하는 학번이 없습니다.\n");
	}

	else{
	  printf("도서번호를 입력하세요: ");
	  scanf("%d", &targetBookId);		
	  while(c = getchar() != '\n' && c != EOF);
	  while(b_head->nextNode != NULL){
		b_head = b_head->nextNode;
		if(b_head->book.bookId == targetBookId){
		  break;
		}
	  }
	}

	if(b_head->nextNode == NULL && b_head->book.bookId != targetBookId){
	  printf("일치하는 도서번호가 업습니다.\n");
	}
	
	else{
	  if(b_head->book.isBookAvailable == 'Y'){
		printf("\n");
		printf("이 도서를 대여합니까? ");
		scanf("%c", &YN);
		while(c = getchar() != '\n' && c != EOF);		
		if(YN == 'Y'){
		  struct tm* now;
		  time_t now_t = time(NULL);
		  now = localtime(&now_t);;

		  newBorrow.clientStuId = targetStuId;
		  newBorrow.bookId = targetBookId;
		  newBorrow.checkoutDay = now_t;
		  if(now->tm_wday == 5){ 
			newBorrow.returnDay = now_t+31*24*3600;
		  }
		  else{
			newBorrow.returnDay = now_t+30*24*3600;
		  }

		  check = addBorrow(bookHead, borrowHead, newBorrow);
		  printf("도서가 대여되었습니다.\n");
		}
		else{
		  printf("도서 대여가 취소되었습니다.\n");
		}
	  }

	  else if(b_head->book.isBookAvailable == 'N'){ 
		printf("이 도서는 대여할 수 없습니다.\n");
	  }
	}
  }
}/*학번과 빌릴 도서의 번호를 입력받는다.
  addBorrow함수를 통해 변경된 정보를 book.txt와 borrow.txt.에 저장한다.*/
	
void ReturnBook(){
  int targetStuId, targetBookId, c;
  BorrowNode *borrowHead = borrowMemAlloc(), *br_head = NULL;
  BookNode *bookHead = bookMemAlloc(), *b_head = NULL;
  bool check = false;
  char *tempBookName, *thatDay;
  struct tm *day;
  time_t day_t;
  
  br_head = borrowHead;
  b_head = bookHead;

  printf("학번을 입력하세요: ");
  scanf("%d",&targetStuId);
  while(c = getchar() != '\n' && c != EOF);

  printf("\n");
  printf(">>회원의 대여 목록<<\n");
  
  while(br_head->nextNode != NULL){
	br_head = br_head->nextNode;
	if(br_head->borrow.clientStuId == targetStuId){
	  while(b_head->nextNode != NULL){
		b_head = b_head->nextNode;
		if(br_head->borrow.bookId == b_head->book.bookId){
		  tempBookName = b_head->book.bookName;
		  break;
		}
	  }
	  printf("\n");
	  printf("도서번호: %d\n",br_head->borrow.bookId);
	  printf("도서명: %s\n", tempBookName);
	  day_t = br_head->borrow.checkoutDay;
	  day = localtime(&day_t);
	  thatDay = NumToDay(day);
	  printf("대여일자: %d년 %d월 %d일 %s\n", day->tm_year+1900, day->tm_mon+1, day->tm_mday, thatDay);
	  day_t = br_head->borrow.returnDay;
	  day = localtime(&day_t);
	  thatDay = NumToDay(day);
	  printf("반납일자: %d년 %d월 %d일 %s\n", day->tm_year+1900, day->tm_mon+1, day->tm_mday, thatDay);
	  check = true;
	} 
  }
  if(check == true){
	printf("\n");
	printf("반납할 도서번호를 입력하세요: ");
	scanf("%d",&targetBookId);
	while(c = getchar() != '\n' && c != EOF);
	check = removeBorrow(bookHead, borrowHead, targetBookId);
	if(check == true){
	  printf("\n");
	  printf("도서가 반납되었습니다.\n");
	}
	else{
	  printf("도서 반납이 취소되었습니다.\n");
	}
  }
  else{
	printf("도서 대여 정보가 없습니다.\n");
  }
}/*학번을 입력받으면 회원이 대여한 도서의 목록을 보여준다.
   도서번호를 입력받아 도서를 반납한다.*/


char *NumToDay(struct tm* day){
  char *thatDay;
  switch(day->tm_wday){
	case 0: thatDay = "일요일"; break;
	case 1: thatDay = "월요일"; break;
	case 2: thatDay = "화요일"; break;
	case 3: thatDay = "수요일"; break;
	case 4: thatDay = "목요일"; break;
	case 5: thatDay = "금요일"; break;
	case 6: thatDay = "토요일"; break;
  }	
  return thatDay;
}/*월화수목금토일*/

bool SearchBook(char *kind){
	int num, c;
	BookNode *head = bookMemAlloc();
	BookNode *Search = NULL, *SearchNext = NULL, *SearchFollow = NULL;
	Book value;
	char valueBookName[100];
	int criteria;
	char delAvailable;
	printf("1.도서명 검색\t 2.ISBN 검색\n");
	printf("\n");
	printf("검색 번호를 입력하세요: ");
	scanf("%d",&num);
	while(c = getchar() != '\n' && c != EOF);

	if(num == 1){
		criteria = BOOK_NAME;
		printf("도서명을 입력하세요: ");
		scanf("%[^\n]", valueBookName);
		while(c = getchar() != '\n' && c != EOF);

		value.bookName = malloc(sizeof(Book)*(strlen(valueBookName)+1));
		strcpy(value.bookName, valueBookName);
		
		Search = searchBy(head, criteria, value);
		Search = Search->nextNode;
		
		if(Search != NULL){
		  printf("\n");
		  printf(">>검색 결과<<");
		  if(Search-> nextNode == NULL){
			printf("\n");
			printf("도서번호: %d(%s 가능 여부: %c)", Search->book.bookId, kind, Search->book.isBookAvailable);
			printf("도서명: %s\n", Search->book.bookName);
			printf("출판사: %s\n", Search->book.bookPublisher);
			printf("저자명: %s\n", Search->book.bookAuthor);
			printf("ISBN: %lld\n", Search->book.bookISBN);
			printf("소장처: %s\n", Search->book.bookLocation);
			printf("\n");
			return true;
		  }
		  else{
			while(Search != NULL){
			  if(Search->nextNode != NULL){
				SearchNext = Search->nextNode;
			  }
			  if(SearchFollow != NULL && SearchFollow->book.bookISBN == Search->book.bookISBN){
				return true;
			  }

			  if((Search->book.bookISBN == SearchNext->book.bookISBN) && (Search->nextNode != NULL)){
				printf("\n");
				printf("도서번호: %d(%s 가능 여부: %c)", Search->book.bookId, kind, Search->book.isBookAvailable);
				while(SearchNext->book.bookISBN == Search->book.bookISBN){
				  printf(", %d(%s 가능 여부: %c)", SearchNext->book.bookId, kind, SearchNext->book.isBookAvailable);
				  if(SearchNext->nextNode != NULL){
				  SearchNext = SearchNext->nextNode;
				  }
				  else{
					break;
				  }
				}
			  }
			  else {
				printf("\n");
				printf("도서번호: %d(%s 가능 여부: %c)", Search->book.bookId, kind, Search->book.isBookAvailable);
			  }
			  printf("\n");
			  printf("도서명: %s\n", Search->book.bookName);
			  printf("출판사: %s\n", Search->book.bookPublisher);
			  printf("저자명: %s\n", Search->book.bookAuthor);
			  printf("ISBN: %lld\n", Search->book.bookISBN);
			  printf("소장처: %s\n", Search->book.bookLocation);

			  if(Search-> nextNode == NULL){
				return true;
			  }
			  SearchFollow = Search;
			  Search = SearchNext;
			  
			}
		  }
		}

		else{
		  printf("검색 결과가 없습니다.");
		  return false;
		}
	}

	else if(num == 2){
		criteria = ISBN;
		printf("ISBN을 입력하세요: ");
		scanf("%lld", &value.bookISBN);
		while(c = getchar() != '\n' && c != EOF);
		Search = searchBy(head, criteria, value);
		Search = Search->nextNode;

		if(Search != NULL){
			printf(">>검색 결과<<\n");
			printf("\n");

			if(Search->nextNode == NULL){
			printf("도서번호: %d(%s 가능 여부: %c)", Search->book.bookId, kind, Search->book.isBookAvailable);
			}
			else{
				printf("도서번호: %d(%s 가능 여부: %c)", Search->book.bookId, kind, Search->book.isBookAvailable);
				while(Search->nextNode != NULL){
					Search = Search->nextNode;
					printf(", %d(%s 가능 여부: %c)", Search->book.bookId, kind, Search->book.isBookAvailable);
				}
			}
			printf("\n");
			printf("도서명: %s\n", Search->book.bookName);
			printf("출판사: %s\n", Search->book.bookPublisher);
			printf("저자명: %s\n", Search->book.bookAuthor);
			printf("ISBN: %lld\n", Search->book.bookISBN);
			printf("소장처: %s\n", Search->book.bookLocation);
			return true;
		}
		else{
			printf("검색 결과가 없습니다.");
			return false;
		}
	}	
	else{
		printf("잘못된 입력입니다.");
		return false;
	}
}/* 번호를 입력받아 검색을 하는 방법을 선택한다.
	1. 도서명 검색
		도서명을 입력받고 searchBy함수를 통해 검색결과를 연결리스트로 가져온다.
		출력할 때, 같은 ISBN을 가진 책들의 도서번호들은 한 줄에 모두 출력된다.
		꼭 도서명이 일치할 필요는 없다. 입력된 단어나 문장이 들어간 도서는 모두 출력된다.
	2. ISBN 검색
		도서의 ISBN을 입력받고 searchBy함수를 통해 검색결과를 연결리스트로 가져온다.
		출력할 때, 같은 ISBN을 가진 책들의 도서번호들은 한 줄에 모두 출력된다.
		ISBN 검색은 도서명 검색과 달리 ISBN이 도서의 것과  정확히 일치해야 원하는 도서가 검색된다.*/


		




