#include <stdio.h>
#include <string.h>

#define MAX_LINE 100
#define MAX_ACTION 10
#define MAX_ID_SIZE 10

typedef struct Carta
{
  char valor;
  char naipe[MAX_LINE];

} carta;

typedef struct Players
{
  char jogadores[99];

} Players;

void debug(char *message)
{
  fprintf(stderr, "%s\n", message);
}

int main()
{

  int njogadores = 0, vez, cardsInHand = 0, i;
  carta mao[99];
  carta mesa;
  char *token;
  Players jogs[99];

  char temp[MAX_LINE];
  char my_id[MAX_ID_SIZE];

  setbuf(stdin, NULL);
  setbuf(stdout, NULL);
  setbuf(stderr, NULL);

  scanf("PLAYERS %[^\n]\n", temp);
  token = strtok(temp, " ");
  while (token != NULL)
  {
    strcpy(jogs[njogadores].jogadores, token);
    njogadores++;
    token = strtok(NULL, " ");
  }

  debug(temp);

  scanf("YOU %s\n", my_id);

  scanf("HAND [ %[^\n]\n", temp);
  token = strtok(temp, " ");
  while (strcmp(token, "]") != 0)
  {
    mao[cardsInHand].valor = token[0];
    for (i = 0; i < strlen(token); i++)
    {
      token[i] = token[i + 1];
    }
    strcpy(mao[cardsInHand].naipe, token);
    cardsInHand++;
    token = strtok(NULL, " ");
  }

  scanf("TABLE %s\n", temp);
  mesa.valor = temp[0];
  for (i = 0; i < strlen(temp); i++)
  {
    temp[i] = temp[i + 1];
  }
  strcpy(mesa.naipe, temp);

  char id[MAX_ID_SIZE];
  char action[MAX_ACTION];
  char complement[MAX_LINE];
  char prior[MAX_LINE];
  int qnt = 0;
  carta comp;
  int cardsToBuy = 0;
  int hasPlayed = 0;
  int j = 0;

  while (1)
  {

    do
    {
      strcpy(complement, "");

      scanf("%s ", action);
      if (strcmp(action, "TURN") != 0)
      {
        cardsToBuy = 0;
      }
      if (strcmp(action, "DISCARD") == 0)
      {
        scanf("%c%s", &mesa.valor, mesa.naipe);
        if (mesa.valor == 'V')
        {
          cardsToBuy = 2;
        }
        else if (mesa.valor == 'C')
        {
          cardsToBuy = 4;
        }
        else if (mesa.valor == 'A')
        {
          scanf(" %s", mesa.naipe);
        }
      }
      else
      {
        scanf("%s", complement);
      }

    } while (strcmp(action, "TURN") || strcmp(complement, my_id));

    debug("----- MINHA VEZ -----");

    hasPlayed = 0;
    // trata acao
    if (cardsToBuy == 2 || cardsToBuy == 4)
    {
      printf("BUY %d\n", cardsToBuy);
      for (i = 0; i < cardsToBuy; i++)
      {
        scanf("%s", temp);
        mao[cardsInHand].valor = temp[0];
        for (j = 0; j < strlen(temp); j++)
        {
          temp[j] = temp[j + 1];
        }
        strcpy(mao[cardsInHand].naipe, temp);

        cardsInHand++;
      }
      hasPlayed = 1;
      cardsToBuy = 0;
    }
    else
    {

      for (i = 0; i < cardsInHand; i++)
      {

        if ((mao[i].valor == 'V') || (mao[i].valor == 'C') || (mao[i].valor == 'R') || (mao[i].valor == 'A'))
        {

          if ((mao[i].valor == mesa.valor) || (strcmp(mao[i].naipe, mesa.naipe) == 0))
          {

            if (mao[i].valor == 'A')
            {
              printf("DISCARD %c%s %s\n", mao[i].valor, mao[i].naipe, mao[0].naipe);
            }
            else
            {
              printf("DISCARD %c%s\n", mao[i].valor, mao[i].naipe);
            }

            cardsInHand--;
            mesa.valor = mao[i].valor;
            strcpy(mesa.naipe, mao[i].naipe);
            mao[i].valor = mao[cardsInHand].valor;
            strcpy(mao[i].naipe, mao[cardsInHand].naipe);

            hasPlayed = 1;
          }
        }
        if (hasPlayed == 1)
        {
          break;
        }
      }

      // verificar valor
      if (hasPlayed == 0)
      {

        for (i = 0; i < cardsInHand; i++)
        {
          if (mao[i].valor == mesa.valor)
          {
            printf("DISCARD %c%s\n", mao[i].valor, mao[i].naipe);
            cardsInHand--;
            mesa.valor = mao[i].valor;
            strcpy(mesa.naipe, mao[i].naipe);
            mao[i].valor = mao[cardsInHand].valor;
            strcpy(mao[i].naipe, mao[cardsInHand].naipe);
            hasPlayed = 1;
          }

          if (hasPlayed == 1)
          {
            break;
          }
        }
      }

      // verificar naipe
      if (hasPlayed == 0)
      {
        for (i = 0; i < cardsInHand; i++)
        {
          if (strcmp(mao[i].naipe, mesa.naipe) == 0)
          {
            printf("DISCARD %c%s\n", mao[i].valor, mao[i].naipe);
            cardsInHand--;
            mesa.valor = mao[i].valor;
            strcpy(mesa.naipe, mao[i].naipe);
            mao[i].valor = mao[cardsInHand].valor;
            strcpy(mao[i].naipe, mao[cardsInHand].naipe);
            hasPlayed = 1;
          }

          if (hasPlayed == 1)
          {
            break;
          }
        }
      }

      // se não tiver feito nada, compra
      if (hasPlayed == 0)
      {

        printf("BUY 1\n");
        scanf("%s", temp);
        mao[cardsInHand].valor = temp[0];
        for (i = 0; i < strlen(temp); i++)
        {
          temp[i] = temp[i + 1];
        }
        strcpy(mao[cardsInHand].naipe, temp);

        cardsInHand++;
        cardsToBuy = 0;
      }
    }
  }
  return 0;
}
