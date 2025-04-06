#include <stdio.h>
#include <string.h>

#define DATA_FILE "bookdata.dat"

void store_bkdata(char *bookname, int last) {
  FILE *f = fopen(DATA_FILE, "a+");
  if (!f) return;

  fprintf(f, "%.64s %d\n", bookname, last);

  fclose(f);
}
int read_last(const char *bookname) {
  FILE *f = fopen(DATA_FILE, "r");
  if (!f) return -1;
  
  char booktmp[256], lbuf[256];
  int out = -1, t;
  
  while (fgets(lbuf, sizeof(lbuf), f)) {
    if (sscanf(lbuf, "%255s %d", booktmp, &t) == 2 && !strcmp(booktmp, bookname)) {
      out = t;
    }
  }
  
  fclose(f);
  return out;
}

void clear_file() {
  FILE *f = fopen(DATA_FILE, "w");
  if (f) fclose(f);
}

int main() { 
  int in;
  printf("BOOK LOGGER:\n");
  printf("(1) APPEND BOOK & PAGE\n");
  printf("(2) RETREIVE LAST PAGE\n");
  printf("(9) CLEAR ALL DATA (NUCLEAR)\n");
  printf("$ ");
  scanf("%d", &in);

  if (in == 9) {
    clear_file();
    goto exit;
  }

  char book[64];
  printf("BOOK: ");
  scanf("%s", book);

  if (in == 1) {
    int pag;
    printf("PAGE: ");
    scanf("%d", &pag);
    store_bkdata(book, pag);
  }
  else if (in == 2) {
    printf("LAST PAGE: %d\n", read_last(book));
  }
  else {
    printf("INVALID OPTION\n");
  }

exit:

  return 0;
}
