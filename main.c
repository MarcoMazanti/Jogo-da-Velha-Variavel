#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

struct local {
    int linha;
    int coluna;
    char jogador;
};

struct local resp[999];
int tamanho;

char mapa(int z) {
    char bloco[z][z];
    
    printf("\n");
    
    for(int i = 1; i <= z; i++) {
        printf(" ");
        
        //cria o jogo da velha
        for(int j = 1; j <= z; j++) {
            if(i % 2 == 0 && j % 2 == 0) {
                bloco[i][j] = '+';
            } else if(i % 2 == 0 && j % 2 == 1) {
                bloco[i][j] = '-';
            } else if(i % 2 ==1 && j % 2 == 0) {
                bloco[i][j] = '|';
            } else {
                for(int k = 0; k <= 999; k++) {
                    // relaciona a pocisão escolhida e armazenada no resp[] com a real posição na matriz bloco e se os dados forem o mesmo o valor jogador é armazenado na matriz
                    if(1 + (2 * (resp[k].linha - 1)) == i && 1 + (2 * (resp[k].coluna - 1)) == j) {
                        bloco[i][j] = resp[k].jogador;
                        break;
                    } else {
                        bloco[i][j] = ' ';
                    }
                }
            }
            
            printf("%c ", bloco[i][j]);
        }
        
        printf("\n");
    }
    
    printf("\n");
}

char resultado(int linha, int coluna, char jogador) {
    int verificacao = 0;
    
    // verificação se a linha é igual
    for(int i = 0; i <= 999 && resp[i].linha != 0 && resp[i].coluna != 0; i++) {
        if(resp[i].linha == linha && resp[i].jogador == jogador) {
            verificacao++;
        }
    }
    
    // verifica se preencheu todos os espaços desejados
    if(verificacao == tamanho) {
        return 1;
        exit(0);
    }
    verificacao = 0;
    
    // verificação se a coluna é igual
    for(int i = 0; i <= 999 && resp[i].linha != 0 && resp[i].coluna != 0; i++) {
        if(resp[i].coluna == coluna && resp[i].jogador == jogador) {
            verificacao++;
        }
    }
    
    // verifica se preencheu todos os espaços desejados
    if(verificacao == tamanho) {
        return 1;
        exit(0);
    }
    verificacao = 0;
    
    // verificação se a diagonal principal é igual
    if(linha == coluna) {
        for(int i = 0; i <= 999 && resp[i].linha != 0 && resp[i].coluna != 0; i++) {
            if(resp[i].linha == resp[i].coluna && resp[i].jogador == jogador) {
                verificacao++;
            }
        }
    }
    
    // verifica se preencheu todos os espaços desejados
    if(verificacao == tamanho) {
        return 1;
        exit(0);
    }
    verificacao = 0;
    
    // verificação se a diagonal secundária é igual
    if(linha + coluna == tamanho + 1) {
        for(int i = 0; i <= 999 && resp[i].linha != 0 && resp[i].coluna != 0; i++) {
            if(resp[i].linha + resp[i].coluna == tamanho + 1 && resp[i].jogador == jogador) {
                verificacao++;
            }
        }
    }
    
    // verifica se preencheu todos os espaços desejados
    if(verificacao == tamanho) {
        return 1;
        exit(0);
    }
    verificacao = 0;
    
    //sistema para determinar empate devido a ocupação de todas as casas
    for(int i = 0; i <= 999; i++) {
        if(i + 1 > tamanho * tamanho) {
            return 2;
            exit(0);
        }
        
        if(resp[i].linha == 0 && resp[i].coluna == 0) {
            break;
        }
    }
}

int main() {
    setlocale(LC_ALL, "Portuguese");
    
    int resposta,
        z,
        linha = 0,
        coluna = 0,
        jogador,
        vitoria = 0,
        repetir = 0,
        limite = 0;
    
    for(int i = 0; i <= 999; i++) {
        resp[i].linha = 0;
        resp[i].coluna = 0;
        resp[i].jogador = '0';
    }
    
    printf("Digite um número para as casas: ");
    scanf("%d", &resposta);
    
    limite = resposta * resposta;
    tamanho = resposta;
    
    z = 1 + (2 * (resposta - 1));
    
    do {
        // limpa o terminal
        system("clear");
        
        do {
            mapa(z);
            
            repetir = 0;
            
            printf("----------------------Jogador 1----------------------\n");
            printf("Digite a linha e a coluna da onde deseja ocupar: ");
            scanf("%d %d", &linha, &coluna);
            jogador = 'X';
            
            // verifica se a resposta condiz com a quantidade de linhas e colunas existentes
            if(linha <= resposta && coluna <= resposta  && linha >= 1 && coluna >= 1) {
                //verifica todas as casas para ver se existe uma com os 2 valores iguais e para quando chega em uma com valores 0 0, assim atribuindo o valor nela e saindo do ciclo
                for(int i = 0; i <= 999; i++) {
                    if(linha == resp[i].linha && coluna == resp[i].coluna) {
                        printf("\nVocê digitou uma casa já ocupada!\n");
                        repetir = 1;
                        break;
                    }
                    
                    if(resp[i].linha == 0 && resp[i].coluna == 0) {
                        resp[i].linha = linha;
                        resp[i].coluna = coluna;
                        resp[i].jogador = jogador;
                        break;
                    }
                }
            } else {
                printf("\nVocê digitiu uma casa não existente!\n");
                repetir = 1;
            }
        } while(repetir == 1);
        
        vitoria = resultado(linha, coluna, jogador);
        
        if(vitoria == 1) {
            printf("\n🎆 🎆 🎆     O jogador 1 ganhou o jogo!!!     🎆 🎆 🎆");
            exit(0);
        } else if(vitoria == 2) {
            printf("\nO jogo deu empate!");
            exit(0);
        }
        
        // limpa o terminal
        system("clear");
        
        do {
            mapa(z);
            
            repetir = 0;
            
            printf("----------------------Jogador 2----------------------\n");
            printf("Digite a linha e a coluna da onde deseja ocupar: ");
            scanf("%d %d", &linha, &coluna);
            jogador = 'O';
            
            // verifica se a resposta condiz com a quantidade de linhas e colunas existentes
            if(linha <= resposta && coluna <= resposta  && linha >= 1 && coluna >= 1) {
                //verifica todas as casas para ver se existe uma com os 2 valores iguais e para quando chega em uma com valores 0 0, assim atribuindo o valor nela e saindo do ciclo
                for(int i = 0; i <= 999; i++) {
                    if(linha == resp[i].linha && coluna == resp[i].coluna) {
                        printf("\nVocê digitou uma casa já ocupada!\n");
                        repetir = 1;
                        break;
                    }
                    
                    if(resp[i].linha == 0 && resp[i].coluna == 0) {
                        resp[i].linha = linha;
                        resp[i].coluna = coluna;
                        resp[i].jogador = jogador;
                        break;
                    }
                }
            } else {
                printf("\nVocê digitiu uma casa não existente!\n");
                repetir = 1;
            }
        } while(repetir == 1);
        
        vitoria = resultado(linha, coluna, jogador);
        
        if(vitoria == 1) {
            printf("\n🎆 🎆 🎆     O jogador 2 ganhou o jogo!!!     🎆 🎆 🎆");
        } else if(vitoria == 2) {
            printf("\nO jogo deu empate!");
        }
    } while(vitoria == 0);
    
    return 0;
}