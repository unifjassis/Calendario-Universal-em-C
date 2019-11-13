#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

/*

   O usuario devera fornecer o ano e seu programa devera informar as datas
   e os dias da semana em que cada data comemorativa acontece.

   1.  Domingo de Pascoa.
   2.  Paixao de Cristo: Sexta-feira antes da Pascoa.
   3.  Quarta-Feira de cinzas: calculado 46 dias antes da pascoa.
   4.  Natal.
   5.  Confraternizacao Universal.
   6.  Aniversario de Sao Bernardo do Campo.
   7.  Dias de Lua Cheia.
   8.  Entrada das estacoes: verao, inverno, outono, primavera.
   9.  Equinocio de primavera.
   10. Equinocio de outono.
   ** BONUS 11. Sexta-feira 13.


   Criterios de Avaliacao do Trabalho:

   1.  Modelo de representacao para datas:  1 ponto
   2.  Interacao  com  o  usuario:  3  pontos
   (seja  criativo  para  exibir  os  dias comemorativos,
    como uma forma de calendario, etc...)
   3.  Utilizacao do biblioteca IUP: 3 pontos.
    (Voce podera optar por fazer tudo pelo terminal, porem serao descontados 2 pontos)
   4.  Uso correto da linguagem C: 3 pontos

   https://pt.wikipedia.org/wiki/C%C3%A1lculo_da_P%C3%A1scoa#R

   LEIA:

   Desenvolvido por João Gabriel;

   */


//___________________ FUNCAO QUE CALCULA O DIA SEMANAL _______________________
char *diaSemana(int dia, int mes, int ano){
  int teste;
  do{
    teste = 0;

    if((dia < 1 || dia > 31) || (mes < 1 || mes > 12))
    teste = 1;
    if((mes == 2) && (dia + mes) > 31){
      if((mes == 2) && (dia == 29)){
        if(bissexto(ano) == 0)
        teste = 1;
      }
    }
    if(teste){
      printf("\n!!!ERRO!!! A data (%i/%i/%i) nao existe!!!\n",dia,mes,ano);
    }
  }while(teste);

  //depois do teste de erro

  switch (mes){
    case 1: break;
    case 2: dia += 31; break;
    case 3: dia += 59; break;
    case 4: dia += 90; break;
    case 5: dia += 120; break;
    case 6: dia += 151; break;
    case 7: dia += 181; break;
    case 8: dia += 212; break;
    case 9: dia += 243; break;
    case 10: dia += 273; break;
    case 11: dia += 304; break;
    case 12: dia += 334; break;
  }

  if (((ano%4)==0) && (((ano%100)!=0) || ((ano%400)==0)) && (mes > 2)){
    dia += 1;
  }

  dia += -1 + (ano-1)*365 + (ano-1)/4 -(ano-1)/100 +(ano-1)/400;

  switch (dia % 7){
    case 0: return "Segunda-feira"; break;
    case 1: return "Terca-feira"; break;
    case 2: return "Quarta-feira"; break;
    case 3: return "Quinta-feira"; break;
    case 4: return "Sexta-feira"; break;
    case 5: return "Sabado"; break;
    case 6: return "Domingo"; break;
  }
}

//_____________________ FUNCAO QUE VERIFICA ANO BISSEXTO _____________________

int bissexto(int ano){                              // verificacao de ano bissexto
    if((ano % 4 == 0) && (ano % 100 != 0) || (ano % 400 == 0)){
        return 0;                                   // caso seja bissexto
    }

    else{
        return 1;                                   // caso nao seja
    }
}

//_________________________ FUNCAO QUE CALCULA PASCOA ___________________________

int pascoa(int ano){

     printf("\nFeriados de %d!\n", ano);

     if(ano < 1583){

            // mes = mes do ano
            // dia = dia do ano
            // variaveis para calculo
            int a, b, c, d, e, mes, dia;

            a = (ano%4);
            b = (ano%7);
            c = (ano%19);
            d = ((19*c + 15) % 30);
            e = (2*a + 4*b - d + 34) % 7;
            mes = (d  + e + 114) / 31;
            dia = ((d  + e + 114) % 31) + 1;

            char meses[13][10] = {"NULL", "Janeiro", "Fevereiro", "Marco", "Abril", "Maio",
                            "Junho", "Julho", "Agosto", "Setembro", "Outubro", "Novembro", "Dezembro"};

            char* mes1 = meses[mes];

            printf("1. Pascoa: %d de %s - %s.\n", dia, mes1, diaSemana(dia, mes, ano));

            int diaNovo;                    // variavel para calcular paixao de cristo
            int quant = bissexto(ano);      // variavel para saber se e bissexto

             if((dia - 2) <= 0){            // caso o dia da pascoa -2 seja <= 0, subtrai um ou 2 meses
                if(mes == 4){
                    diaNovo = (31 + dia) - 2;
                }
                else if(mes == 3){
                        if(quant == 0){
                            diaNovo = (dia + 29) - 2;
                        }
                        else{
                            diaNovo = (dia + 28) - 2;
                        }
                }
                char* mes2 = meses[mes-1];
                printf("2. Paixao de Cristo: %d de %s - %s.\n", diaNovo, mes2, diaSemana(diaNovo, mes-1, ano));
             }
             else{                          // senao, sutrai -2 do dia da pascoa e 1 mes
                 printf("2. Paixao de Cristo: %d de %s - %s.\n", dia-2, mes1, diaSemana(dia-2, mes, ano));
             }

             // ___________________________ CALCULO DA QUARTA FEIRA DE CINZAS ___________________________

             if(dia <= 15){                     // verifica se o dia esta no limite de subtrair 2 meses
                if(quant == 0){                 // caso o ano seja bissexto
                    if(mes == 4){               // soma-se ao dia os 2 meses anteriores e subtrai 46
                        diaNovo = (dia + 31 + 29) - 46;
                    }
                    else if(mes == 3){
                        diaNovo = (dia + 29 + 31) - 46;
                    }
                }
                else {
                    if(mes == 4){
                        diaNovo = (dia + 31 + 28) - 46;
                    }
                    else if(mes == 3){
                        diaNovo = (dia + 28 + 31) - 46;
                    }
                }
                char* mes2 = meses[mes-2];
                printf("3. Quarta-feira de Cinzas: %d de %s - %s.\n", diaNovo, mes2, diaSemana(diaNovo, mes-2, ano));
             }
             else if(dia > 15){                 // caso esteja no limite, subtrai apenas 1 mes
                if(quant == 0){                 // caso o ano seja bissexto
                    if(mes == 4){               // somo ao dia o mes anterior e subtraio 46
                        diaNovo = (dia + 31) - 46;
                    }
                    else if(mes == 3){
                        diaNovo = (dia + 29) - 46;
                    }
                }
                else {
                    if(mes == 4){
                        diaNovo = (dia + 31) - 46;
                    }
                    else if(mes == 3){
                        diaNovo = (dia + 28) - 46;
                    }
                }
                char* mes2 = meses[mes-1];
                printf("3. Quarta-feira de Cinzas: %d de %s - %s.\n", diaNovo, mes2, diaSemana(diaNovo, mes-1, ano));
             }
     }

     else{                                                  // anos acima de 1582 pois o calendario não era o mesmo
         // a = variavel seculo
         // mes = variavel mes
         // dia = variavel dia
         // b, c, d, e, f, g, h, i, j, k, L, m = variaveis de calculo

         int a, b, c, d, e, f, g, h, i, j, k, L, m, mes, dia;

         a = ano%19;
         b = (ano/100);
         c = ano%100;
         d = (b/4);
         e = b%4;
         f = ((b+8)/25);
         g = ((b-f+1)/3);
         h = ((19*a+b-d-g+15)%30);
         i = (c/4);
         k = c%4;
         L = ((32+2*e+2*i-h-k)%7);
         m = (a+11*h+22*L)/451;
         mes = ((h+L-7*m+114)/31);
         dia=((h+L-7*m+114)%31)+1;

         char meses[13][10] = {"NULL", "Janeiro", "Fevereiro", "Marco", "Abril", "Maio",
                            "Junho", "Julho", "Agosto", "Setembro", "Outubro", "Novembro", "Dezembro"};

         char* mes1 = meses[mes];               // o mes por estenso eh o vetor meses na posicao mes
         printf("1. Pascoa: %d de %s - %s.\n", dia, mes1, diaSemana(dia, mes, ano));


         //_______________________________ CALCULO DA PAIXAO DE CRISTO ____________________________
         int diaNovo;
         int quant = bissexto(ano);

         if((dia - 2) <= 0){
            if(mes == 4){
                diaNovo = (31 + dia) - 2;
            }
            else if(mes == 3){
                    if(quant == 0){
                        diaNovo = (dia + 29) - 2;
                    }
                    else{
                        diaNovo = (dia + 28) - 2;
                    }
            }
            char* mes2 = meses[mes-1];
            printf("2. Paixao de Cristo: %d de %s - %s.\n", diaNovo, mes2, diaSemana(diaNovo, mes-1, ano));
         }
         else{
             printf("2. Paixao de Cristo: %d de %s - %s.\n", dia-2, mes1, diaSemana(dia-2, mes, ano));
         }

         // ___________________________ CALCULO DA QUARTA FEIRA DE CINZAS ___________________________

         if(dia <= 15){
            if(quant == 0){                 // caso o ano seja bissexto
                if(mes == 4){
                    diaNovo = (dia + 31 + 29) - 46;
                }
                else if(mes == 3){
                    diaNovo = (dia + 29 + 31) - 46;
                }
            }
            else {
                if(mes == 4){
                    diaNovo = (dia + 31 + 28) - 46;
                }
                else if(mes == 3){
                    diaNovo = (dia + 28 + 31) - 46;
                }
            }
            char* mes2 = meses[mes-2];
            printf("3. Quarta-feira de Cinzas: %d de %s - %s.\n", diaNovo, mes2, diaSemana(diaNovo, mes-2, ano));
         }
         else if(dia > 15){
            if(quant == 0){                 // caso o ano seja bissexto
                if(mes == 4){
                    diaNovo = (dia + 31) - 46;
                }
                else if(mes == 3){
                    diaNovo = (dia + 29) - 46;
                }
            }
            else {
                if(mes == 4){
                    diaNovo = (dia + 31) - 46;
                }
                else if(mes == 3){
                    diaNovo = (dia + 28) - 46;
                }
            }
            char* mes2 = meses[mes-1];
            printf("3. Quarta-feira de Cinzas: %d de %s - %s.\n", diaNovo, mes2, diaSemana(diaNovo, mes-1, ano));
         }
     }
}

//_______________________ FUNCAO DOS FERIADOS FIXOS _________________________________________
int feriadosFixos(int ano){     // bastou o dia e o mes exato do ano para saber o dia semanal
    printf("4. Natal: 25 de Dezembro - %s.\n", diaSemana(25, 12, ano));
    printf("5. Confraternizacao Universal: 01 de Janeiro - %s.\n", diaSemana(01, 1, ano));
    printf("6. Aniversario de Sao Bernardo: 20 de Agosto - %s.\n", diaSemana(20, 8, ano));
}

//______________________________ FUNCAO SEXTA TREZE ________________________________
int sextaTreze(int ano){
    char meses[13][10] = {"NULL", "Janeiro", "Fevereiro", "Marco", "Abril", "Maio",
                        "Junho", "Julho", "Agosto", "Setembro", "Outubro", "Novembro", "Dezembro"};

    int mes, i = 0, j;

    for(mes = 1; mes <= 12; mes++){         // calculo primeiro quantas sexta treze ha no ano
        if(diaSemana(13, mes, ano) == "Sexta-feira"){
            i++;
        }
    }
    printf("13. Ha %d sexta-feira treze!\n", i);        // exibo a quantidade

    for(mes = 1; mes <= 12; mes++){         // depois calculo o mes exato no ano
            if(diaSemana(13, mes, ano) == "Sexta-feira"){
                printf("***13 de %s - %s.***\n", meses[mes], diaSemana(13, mes, ano));
            }
    }
}

// ______________________ FUNCAO MAIN _______________________________________

int main(){
	setlocale(LC_ALL, "");                      // deixa o terminal no idioma do sistema

    int ano;

    while(1){                                // loop infinito para testes
        puts("\nDigite o ano: ");
        scanf("%d", &ano);

        while(ano < 0){                         // verificaÃ§Ã£o de entrada correta
            puts("\nDigite uma entrada valida!");
            puts("Digite o ano: ");
            scanf("%d", &ano);
        }

        //__________________________ AREA QUE CHAMA FUNCOES ___________________________
        pascoa(ano);                            // chama funcao que calcula pascoa
        feriadosFixos(ano);                     // chama funcao que exibe feriados fixos
        sextaTreze(ano);                        // chama a funcao BONUS que calcula sexta 13

        }
		system("pause");
		return 0;                               // fim do programa!!
}
