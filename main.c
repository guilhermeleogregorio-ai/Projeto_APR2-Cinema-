#include <stdio.h>
#include <string.h>    
#include <stdlib.h> 
#include <data.h>


// ===========================
// SALAS
// =======================
typedef struct {
    int codigo;      // Chave
    char nome[50];
    int capacidade;
    char tipo[20];   // Ex: "3D", "IMAX"
    int acessivel;   // 1 para Sim, 0 para Não
} Sala;

Sala *vSalas = NULL;
int qtdSalas = 0;


void listar_salas(){

}

int buscar_salas(){

}

void incluir_salas(){

}

void alterar_salas(){

}

void excluir_salas(){

}

// ===========================
// SESSOES
// =======================
typedef struct {
    int codFilme;    // Chave composta (Filme + Sala + Data + Hora)
    int codSala;
    char data[11];   // "DD/MM/AAAA"
    char horario[6]; // "HH:MM"
    float preco;
} Sessao;

Sessao *vSessoes = NULL;
int qtdSessoes = 0;

void listar_sessoes(){

}

int buscar_sessoes(){

}

void incluir_sessoes(){

}

void alterar_sessoes(){

}

void excluir_sessoes(){
    
}
// ===========================
// FILMES
// =======================
typedef struct {
    int codigo;      // Chave
    char nome[100];
    int ano;
    char diretor[50];
    char atores[200]; // Armazena vários nomes como uma string longa
} Filme;

Filme *vFilmes = NULL;
int qtdFilmes = 0;

void listar_Filmes(){

}

int buscar_Filmes(){

}

void incluir_Filmes(){

}

void alterar_Filmes(){

}

void excluir_filmes(){
    
}
// ===========================
// RELATORIO
// ===========================

void listar_relatorio(){

}

int buscar_relatorios(){

}

void incluir_relatorios(){

}

void alterar_relatorios(){

}

void excluir_relatorios(){
    
}
// ===========================
// MENU
// ===========================

void menu(){
    int opc;
    
    do {
        printf("\n=== Sistema cinema ===");
        printf("\n1. Salas\n2. Filmes\n3. Sessões\n4. Relatórios\n5. Sair");
        printf("\nOpção");

        if(scanf("%d", &opc) != 1){
            printf("Entrada invalida! Digite um numero");
            while(getchar() != '\n'); //// Limpa o buffer se o usuário digitar letras
            continue;
        }

        switch (opc){
            case 1:
                submenuSalas()
                break:
            case 2:
                submenuFilmes()
                break:
            case 3:
                submenuSessoes()
                break:
            case 4:
                submenuRelatorios()
                break:
            case 5:
                printf("Saindo...\n");
                break:
            default:
                printf("Opcao invalida!\n");
                        
        }
   } while (opc != 5);
   
   return 0;     
    
}

void submenuSalas(){
    int opc;


    do{
        printf("\n--- Salar ---");
        printf("\n1. Listar todas as salas\n2. Buscar sala\n3. Incluir sala\n4. Alterar sala\n5. Excluir sala\n6. Sair");
        printf("\nOpcao");
        getchar();

        switch(opc) {
            case 1:
                // listar_salas(salas);
                break;
            case 2:
                // buscar_salas(salas);
                break;
            case 3:
                //salas = incluir_salas(salas);
                break;
            case 4:
                // salas = alterar_salas(salas);
                break;
            case 5:
               // salas = excluir_salas(salas);
                break;
            case 6:
                printf("Saindo...\n");
                break:
        }
    } while (opc != 6);

    return 0;
}

void submenuFilmes(){
    int opc;


    do{
        printf("\n--- Filmes ---");
        printf("\n1. Listar todas as salas\n2. Buscar sala\n3. Incluir sala\n4. Alterar sala\n5. Excluir sala\n6. Sair");
        printf("\nOpcao");
        getchar();

        switch(opc) {
            case 1:
                //listar_Filmes(filmes);
                printf("Listando...\n")
                break;
            case 2:
                //buscar_Filmes(filmes);
                break;
            case 3:
                //filmes = incluir_Filmes(filmes);
                break;
            case 4:
                //filmes = alterar_Filmes(filmes);
                break;
            case 5:
                //filmes = excluir_filmes(filmes);
                break;
            case 6:
                printf("Saindo...\n");
                break;
        }
    } while (opc != 6);

    return;

}

void submenuSessoes(){
    int opc;


    do{
        printf("\n--- Sessoes ---");
        printf("\n1. Listar todas as sessoes\n2. Buscar sessao\n3. Incluir sessao\n4. Alterar sessao\n5. Excluir sessao\n6. Sair");
        printf("\nOpcao");
        getchar();

        switch(opc) {
            case 1:
                // listar_sessoes(sessoes);
                printf("Listando...\n")
                break;
            case 2:
                // buscar_sessoes(sessoes);
                break;
            case 3:
                // sessoes = incluir_sessoes(sessoes);
                break;
            case 4:
                // sessoes = alterar_sessoes(sessoes);
                break;
            case 5:
                // sessoes = excluir_sessoes(sessoes);
                break;
            case 6:
                printf("Saindo...\n");
                break;
        }
    } while (opc != 6);

    return;
}

void submenuRelatorios(){
    int opc;


    do{
        printf("\n--- Relatorios ---");
        printf("\n1. Listar todos os relatorios\n2. Buscar relatorio\n3. Incluir relatorio\n4. Alterar relatorio\n5. Excluir relatorio\n6. Sair");
        printf("\nOpcao");
        getchar();

        switch(opc) {
            case 1:
                
                printf("Listando...\n")
                break;
            case 2:
                            
                break;
            case 3:
                
                break;
            case 4:
                printf("Saindo...\n");
                break;
        }
    } while (opc != 6);

    return ;
}

int main(){
    
    menu(); 
    // Aqui free() nos mallocs antes de fechar
    return 0;



}