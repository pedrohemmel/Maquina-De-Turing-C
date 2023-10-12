#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


int verifyTape(char qAccept, char transactions[][16], int numberOfTransactions, char word[64]) {
  int i = 0;
  int state = 1;
  int wordIndex = 0;
  char D = 'D';
  char E = 'E';
  int totalCount = 0;
  bool didFindWay = false;
  while(true) {
    while(i < numberOfTransactions) {
      if (word[wordIndex] == transactions[i][2] && state == (transactions[i][0] - '0')) {
        word[wordIndex] = transactions[i][4];
        char direction = transactions[i][6];

        if (direction == D) {
          if (word[wordIndex + 1] != NULL) {
            // printf("state: %d", (transactions[i][8] - '0'));
            // printf("\nMoveu para direita, estado atual %c, próximo estado %c", word[wordIndex], word[wordIndex + 1]);
            wordIndex++;
          } else {
            printf("Não consigo mais incrementar!");
            return 0;
          }
        } else if (direction == E) {
          if (word[wordIndex - 1] != NULL) {
            // printf("\nMoveu para esquerda, estado atual %c, próximo estado %c", word[wordIndex], word[wordIndex - 1]);
            wordIndex--;
          } else {
            printf("Não consigo mais decrementar!");
            return 0;
          }
        }

        if (state > (transactions[i][8] - '0')) {
          state = (transactions[i][8] - '0');
          i = -1;
        } else if (state != (transactions[i][8] - '0')) {
          state = (transactions[i][8] - '0');
          i++;
        } 
        if (state == 5) {
          return 1;
        }
        didFindWay = true;
      } else {
        i++;
      }
    }
    if (didFindWay == true) {
      didFindWay = false;
    } else {
      return 0;
    }
    
    i = 0;
  }
  return 0;
}

int main() {
  FILE *file;
  char t[4];
  char simbles[16];
  char qAccept;
  int numberOfTransactions;
  int tapes;

  printf("Open file file.txt\n");
  file = fopen("file.txt", "r");
  if (!file) {
    printf("Error: No file found.");
    return 0;
  }

  fgets(simbles, 16, file);
  printf("Simbles: %s",simbles);
  
  qAccept = getc(file);
  printf("Accept on %c\n",qAccept);

  fscanf(file, "%2d", &numberOfTransactions);
  printf("%d Transactions\n",numberOfTransactions);

  char transactions[numberOfTransactions][16];

  fgets(t, 16, file);
  for (int i=0; i < numberOfTransactions; i++) {
    fgets(transactions[i], 16, file);
  }

  fscanf(file, "%1d", &tapes);
  printf("%d tapes to test\n",tapes);
  fgets(t, 16, file);

  for(int i=0; i < tapes; i++) {
    
    char word[64];
    fgets(word, 64, file);
    printf("\n\nWord: ");
    if (word[strlen(word)-1] == '\n') word[strlen(word)-1] = 0x0;
    for (int j = 0; j < 64; j++) {
      if (word[j] == '\0') {
        word[j] = '-';
      }
      printf("%c", word[j]);
    }
    if (verifyTape(qAccept, transactions, numberOfTransactions, word) == 0) {
      printf("\nResult: Not Ok");
    } else {
      printf("\nResult: Ok");
    }
    printf("\n\n");
  }
  return 0;
}
