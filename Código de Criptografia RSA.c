#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


/*Variáveis globais*/
int p, q, n, t, i, flag;
/*p e q, são os dois números primos inseridos pelo usuário*/
/*n é o produto de p e q*/
/*t: totiente de n, dado por (p-1)(q-1)*/
/*i, flag: auxiliares*/
long int lista_expo_publica[50], lista_expo_Privada[50];
/*listas com possíveis valores de chave pública e privada*/
long int cripto_Numerica[50], j;
long int mensagem_original[50], cripto_caracter[50];
/*mensagem original e criptografada como caracteres*/
char mensagem[100];/*mensagem lida do usuário como string*/

/*Protótipos*/
int primo(long int); /*verifica se o número é primo*/
int chave_criptografada(); /*gera pares de chaves públicas e privadas*/
long int cd(long int); /*calcula chave privada*/
int criptografar(); /*função de criptografar a mensagem*/
int descriptografar(); /*função de descriptografar a mensagem*/

int main() {
    /*entrada dos dois números primos*/
    printf("\nDigite o primeiro numero primo (p):\n");
    scanf("%d", &p);
    if (!primo(p)) { /*verifica se o número inserido é primo*/
        printf("\nNumero invalido\n");
        return 1;
    }
   
    printf("\nDigite o segundo numero primo (q):\n");
    scanf("%d", &q);
    if (!primo(q) || p == q) { /*verifica se o número é primo igualando com o já confirmado (p)*/
        printf("\nNumero invalido\n");
        return 1;
    }

    /*entrada da mensagem a ser criptografada*/
    printf("\nDigite a mensagem para criptografar:\n");
    scanf(" %[^\n]s", mensagem); /*lê a linha inteira, incluindo espaços*/

    /*converte cada caractere da mensagem original para inteiro (base ASCII)*/
    for (i = 0; mensagem[i] != '\0'; i++)
        mensagem_original[i] = mensagem[i];

    /*calcula n e t (totiente de n)*/
    n = p * q;
    t = (p - 1) * (q - 1);

    /*gera a chaves criptografadas*/
    if (!chave_criptografada()) {
        printf("Erro ao gerar chaves.\n");
        return 1;
    }
    /*mostra os pares possíveis de chaves públcas e privadas*/
    printf("\nPossiveis valores de 'e' e 'd' sao:\n");
    for (i = 0; i < j - 1; i++)
        printf("\n%ld\t%ld", lista_expo_publica[i], lista_expo_Privada[i]);


    criptografar();
    descriptografar();


    return 0;
}

/*verifica se o número recebido é primo*/
int primo(long int pr) {
    int i;
    long int raiz = sqrt(pr);
    for (i = 2; i <= raiz; i++) {
        if (pr % i == 0)
            return 0;
    }
    return 1;
}

/*gera os pares de chaves públicas e privadas*/
int chave_criptografada() {
    int k = 0;
    j = 0;
    for (i = 2; i < t; i++) {
        if (t % i == 0)
            continue;
        if (primo(i) && i != p && i != q) {
            lista_expo_publica[k] = i;
            long int d = cd(i); /*calcula o d correspondente ao e*/
            if (d > 0) {
                lista_expo_Privada[k] = d;
                k++;
            }
            if (k == 50) break; /*máximo de 50 pares*/
        }
    }
    j = k;
    return k > 0;
}


long int cd(long int a) {
    long int k = 1;
    while (1) {
        k = k + t;
        if (k % a == 0)
            return (k / a);
    }
}

/*criptografa a mensagem*/
int criptografar() {
    long int pt, ct, key = lista_expo_publica[0], k;
    i = 0;
    long int lendo = strlen(mensagem);/*tamanho da mensagem*/


    while (i != lendo) {
        pt = mensagem_original[i]; /*pega caractere original*/
        pt = pt - 96; /*transforma em valor numérico a = 1, b = 2...*/


        k = 1;
        for (j = 0; j < key; j++) {
            k = k * pt;
            k = k % n;
        }


        cripto_Numerica[i] = k; /*armazena o valor criptografado*/
        ct = k + 96; /*converte de volta para caractere*/
        cripto_caracter[i] = ct;
        i++;
    }


    cripto_caracter[i] = -1; /*fim da string*/

    /*exibe a mensagem criptografada*/
    printf("\n\nMensagem criptografada:\n");
    for (i = 0; cripto_caracter[i] != -1; i++)
        printf("%c", cripto_caracter[i]);


    return 1;
}

/*descriptografa a mensagem*/
int descriptografar() {
    long int pt, ct, key = lista_expo_Privada[0], k;
    i = 0;


    while (cripto_caracter[i] != -1) {
        ct = cripto_Numerica[i]; /*pega valor criptografado*/
        k = 1;
        for (j = 0; j < key; j++) {
            k = k * ct;
            k = k % n;
        }


        pt = k + 96; /*converte para caractere*/
        mensagem_original[i] = pt;
        i++;
    }


    mensagem_original[i] = -1;

    /*exibe mensagem descriptografada*/
    printf("\n\nMensagem descriptografada:\n");
    for (i = 0; mensagem_original[i] != -1; i++)
        printf("%c", mensagem_original[i]);

    printf("\n");
        return 1;
}
