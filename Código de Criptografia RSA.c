#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

int p, q, n, t, i, flag;
/*p e q, s�o os dois n�meros primos inseridos pelo usu�rio*/
/*n � o produto de p e q*/
/*t: totiente de n, dado por (p-1)*(q-1)*/
long int e[50], d[50], temp[50], j, m[50], en[50];
/*e[50] � a chave p�blica gerada e d[50] � a chave privada gerada*/
/*m[]: mensagem convertida em inteiros*/
/*temp[]: valores criptografados intermedi�rios*/
/*en[]: mensagem criptografada final (como caracteres)*/
char msg[100];
/*msg[]: a mensagem original (string)*/
int primo(long int);
/*primo ser� usado para identificar o se o n�mero digitado � primo*/
void chave_criptografada();
long int cd(long int);
void criptografar();
void descriptografar();

/*nesta parte o usu�rio ir� inserir o primeiro n�mero primo (p)*/
int main()
{
  printf("\ndigite o primeiro numero primo\n");
  scanf("%d", &p);
  flag = primo(p); /*verifica se o n�mero p � primo*/
  if(flag == 0) /* Se o n�mero n�o for primo (ou seja, tiver outros divisores al�m de 1 e ele mesmo), encerra o programa */
  {
    printf("\nnumero invalido\n");
    exit(0); /*encerra o programa caso n�o seja primo*/
  }
/*nesta parte o usu�rio ir� inserir o segundo n�mero primo (q)*/
  printf("\ndigite o segundo numero primo\n");
  scanf("%d", &q);
  flag = primo(q); /*verifica se o n�mero q � primo*/
  if(flag == 0 || p == q)
  {
    printf("\nnumero invalido\n");
    exit(0); /*encerra o programa caso n�o seja primo*/
  }
  printf("\ndigite a mensagem para criptografar\n");

  scanf(" %[^\n]s",msg); /*%[^\n]s ser� usada para contar espa�o no vetor de string*/
  for(i = 0; msg[i] != '\0'; i++) /*Percorre a string 'msg' at� encontrar o caractere '\0'(NULL)*/
    m[i] = msg[i];
  n = p * q; /*produto de p e q para criar o n�mero n, que ser� usada na cria��o da chave p�blica e privada e dificultar a descoberta de p e q*/
  t = (p-1) * (q-1); /*esse � o Totiente de Euler e ser� usada para calcular as chaves "e" e "d"*/
  chave_criptografada(); /*Gera as chaves poss�veis com chave_criptografada()*/
  printf("\npossiveis valores de 'e' e 'd' sao\n");
  for(i = 0; i < j-1; i++)
    printf("\n%ld\t%ld", e[i], d[i]);
  criptografar();
  descriptografar();
  return 0;
}
int primo(long int pr)
{
  int i;
  j = sqrt(pr);
  for(i = 2; i <= j; i++)
  {
   if(pr % i == 0)
     return 0;
  }
  return 1;
 }

/*fun��o para gerar chave de criptografia*/
void chave_criptografada()
{
  int k;
  k = 0;
  for(i = 2; i < t; i++)
  {
    if(t % i == 0)
     continue;
    flag = primo(i);
    if(flag == 1 && i != p && i != q)
    {
     e[k] = i;
     flag = cd(e[k]);
    if(flag > 0)
    {
     d[k] = flag;
     k++;
    }
   if(k == 99)
    break;
   }
 }
}
long int cd(long int a)
{
  long int k = 1;
  while(1)
  {
    k = k + t;
    if(k % a == 0)
     return(k / a);
  }
}

/*fun��o para criptografar a mensagem*/
void criptografar()
{
  /*a vari�vel pt � o texto claro (plain text), ou seja, o valor num�rico do caractere original da mensagem*/
  /*a vari�vel ct � o texto cifrado (cipher text), ou seja, � o valor ap�s a criptografia*/

  long int pt, ct, key = e[0], k, len;
  i = 0;
  len = strlen(msg);
  while(i != len)
  {
    pt = m[i];
    pt = pt - 96;
    k = 1;
    for(j = 0; j < key; j++)
    {
     k = k * pt;
     k = k % n;
    }
   temp[i] = k;
   ct = k + 96;
   en[i] = ct;
   i++;
  }
  en[i] = -1;
  printf("\n\nmensagem criptografada: \n");
  for(i = 0; en[i] != -1; i++)
    printf("%c", en[i]);
}

/*fun��o para descriptografar a mensagem*/
void descriptografar()
{
  long int pt, ct, key = d[0], k;
  i = 0;
  while(en[i] != -1)
  {
    ct = temp[i];
    k = 1;
    for(j = 0; j < key; j++)
    {
      k = k * ct;
      k = k % n;
    }
   pt = k + 96;
   m[i] = pt;
   i++;
  }
  m[i] = -1;
  printf("\n\nmensagem descriptografada: \n");
  for(i = 0; m[i] != -1; i++)
   printf("%c", m[i]);
  printf("\n");
}

