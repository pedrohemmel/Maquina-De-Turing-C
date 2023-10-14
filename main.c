#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*
  A função imprime os simbolos até 64 vezes que seria o limite, 
  em todos indices vazios são alocados "-"s para representar o vazio.
*/
void printWord(char word[64]) {
  printf("\n\nWord: ");
  if (word[strlen(word)-1] == '\n') word[strlen(word)-1] = 0x0;
  for (int j = 0; j < 64; j++) {
    if (word[j] == '\0') {
      word[j] = '-';
    }
    printf("%c", word[j]);
  }
}

/*
  Verifica qual seria a direção a ser seguida 
  e retorna o char da mesma. 
  Caso não seja possível ir para nenhum lado 
  após a tratativa, retorna 'N'.
*/
char verifyDirection(char direction, char word[64], int wordIndex) {
  if (direction == 'D') {
    if (word[wordIndex + 1] != NULL) {
      return 'D';
    } 
  } else if (direction == 'E') {
    if (word[wordIndex - 1] != NULL) {
      return 'E';
    } 
  }
  printf("Não consigo mais decrementar ou incrementar!");
  return 'N';
}


int verifyTape(char qAccept, char transactions[][16], int numberOfTransactions, char word[64]) {
  int i = 0;
  int state = 1;
  int wordIndex = 0;
  bool didFindWay = false;

  /*
    While true quebra quando o didFindWay continua 
    false mesmo após iterar todas as possíveis transações e 
    nenhuma se encaixar.
  
    While true também quebra quando o 
    estado atual da fita chega ao qAccept (5).
  */
  while(true) {
    while(i < numberOfTransactions) {
      if (word[wordIndex] == transactions[i][2] && state == (transactions[i][0] - '0')) {

        /*
          Escreve símbolo na fita.
        */
        word[wordIndex] = transactions[i][4];

        /*
          Se a direção for para direita, avança um indice na palavra.
          Se for para esquerda, retrocede um indice na palavra.
          Se for qualquer outro caminho, retorna 0 e a fita foi declinada.
        */
        if (verifyDirection(transactions[i][6], word, wordIndex) == 'D') {
          wordIndex++;
        } else if (verifyDirection(transactions[i][6], word, wordIndex) == 'E') {
          wordIndex--;
        } else {
          return 0;
        }
        /*
          Se o estado anterior não mudar da transação atual, 
          então mantém a mesma em loop. 
          Se mudar, atribui o estado da transação atual 
          para o estado anterior e vai para próxima transação.
        */
        if (state != (transactions[i][8] - '0')) {
          state = (transactions[i][8] - '0');
          i++;
        } 

        /*
          Verifica se o estado chegou no qAccept
        */
        if (state == (qAccept - '0')) {
          return 1;
        }

        /*
          Símbolo e estado atual se encaixou com a 
          transação atual, então didFindWay agora é true.
        */
        didFindWay = true;
      } else {
        i++;
      }
    }
    /*
      Indice volta o ponto inicial para iterar novamente todas 
      transações e verificar se alguma se encaixa no símbolo e estado atual.
    */
    i = 0;

    /*
      Se didFindWay se tornou true, 
      atribui false novamente para iterar todas as transações 
      e ver se alguma vai encaixar a atribuir true para ele.
    */
    if (didFindWay == true) {
      didFindWay = false;
    } else {
      return 0;
    }
  }
  return 0;
}

int main() {
  FILE *file;
  char simbles[16];
  char qAccept;
  int numberOfTransactions;
  int tapes;
  char aux[16];

  printf("Open file\n");
  file = fopen("file.txt", "r");
  if (!file) {
    printf("Error: Could not find file.");
    return 0;
  }

  /*
    Pegando informações do arquivo necessárias para verificar a fita.
  */
  fgets(simbles, 16, file);
  printf("Simbles: %s",simbles);
  
  qAccept = getc(file);
  printf("Accept case: %c\n",qAccept);

  fscanf(file, "%2d", &numberOfTransactions);
  printf("Transactions: %d\n", numberOfTransactions);
  fgets(aux, 16, file);

  char transactions[numberOfTransactions][16];
  for (int i=0; i < numberOfTransactions; i++) {
    fgets(transactions[i], 16, file);
  }

  fscanf(file, "%1d", &tapes);
  printf("Number of tapes: %d\n",tapes);
  fgets(aux, 16, file);

  /*
    Para cada indice da fita, pega a fita e verifica a mesma.
  */
  for(int i=0; i < tapes; i++) {
    char word[64];
    fgets(word, 64, file);
    printWord(word);

    if (verifyTape(qAccept, transactions, numberOfTransactions, word) == 0) {
      printf("\nResult: Not Ok");
    } else {
      printf("\nResult: Ok");
    }
    printf("\n\n");
  }
  return 0;
}
