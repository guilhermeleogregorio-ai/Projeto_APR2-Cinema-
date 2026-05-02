#include <stdio.h>
#include <string.h>    
#include <stdlib.h> 
// #include <data.h>

// ===========================
// STRUCTS
// ===========================

typedef struct {
    int codigo;  // Chave
    char nome[50];
    int capacidade;
    char tipo[20]; // Ex: "3D", "IMAX"
    int acessivel;  // 1 para Sim, 0 para Não
} Sala;

typedef struct {
    int codigo;   // Chave
    char nome[100];   
    int ano;
    char diretor[50];
    char atores[200]; // Armazena vários nomes como uma string longa
} Filme;

typedef struct {
    int codFilme;    // Chave composta (Filme + Sala + Data + Hora)
    int codSala;
    char data[11];  // "DD/MM/AAAA"
    char horario[6]; // "HH:MM"
    float preco;
} Sessao;

typedef struct {
    Sala *salas;
    int qtdSalas;

    Filme *filmes;
    int qtdFilmes;

    Sessao *sessoes;
    int qtdSessoes;
} Sistema;

void menu(Sistema *sistema);
void submenuSalas(Sistema *sistema);


// ===========================
// SALAS
// =======================

void listar_salas(Sala *vSalas, int qtdSalas){
    

}

int buscar_salas(Sala *vSalas, int qtdSalas, int codigo){
int i;
    for(i = 0 ; i <  qtdSalas; i++){
        if(vSalas[i].codigo == codigo){
            return i;
        }
    }
    return -1;
}

void incluir_salas(Sala **vSalas, int *qtdSalas){
    Sala nova;

    printf("Codigo: ");
    scanf("%d", &nova.codigo);

    if(buscar_salas(*vSalas, *qtdSalas, nova.codigo) != -1){
        printf("Sala já existe!\n");
        return;
    }

    printf("Nome: ");
    scanf(" %[^\n]", nova.nome);

    printf("Capacidade: ");
    scanf("%d", &nova.capacidade);

    printf("Tipo: ");
    scanf("%s", nova.tipo);

    printf("Acessivel (1/0): ");
    scanf("%d", &nova.acessivel);

    *vSalas = realloc(*vSalas, (*qtdSalas + 1) * sizeof(Sala));

    (*vSalas)[*qtdSalas] = nova;
    (*qtdSalas)++;

    printf("Sala cadastrada!\n");
}

void alterar_salas(){

}

void excluir_salas(){

}

// ===========================
// FILMES
// =======================


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
// SESSOES
// =======================

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

void menu(Sistema *sistema){
    int opc;
    
    do {
        printf("\n=== Sistema cinema ===");
        printf("\n1. Salas");
        printf("\n2. Filmes");
        printf("\n3. Sessões");
        printf("\n4. Relatórios");
        printf("\n5. Sair");
        printf("\nOpção");

        if(scanf("%d", &opc) != 1){
            printf("Entrada invalida! Digite um numero");
            while(getchar() != '\n'); //// Limpa o buffer se o usuário digitar letras
            continue;
        }

        switch (opc){
            case 1:
                submenuSalas(sistema);
                break;
            case 2:
                //submenuFilmes()
                break;
            case 3:
                //submenuSessoes()
                break;
            case 4:
                //submenuRelatorios()
                break;
            case 5:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
                        
        }
   } while (opc != 5);
   
   return;
    
}

void submenuSalas(Sistema *sistema){
    int opc;

    do{
        printf("\n--- Salas ---");
        printf("\n1. Listar todas as salas");
        printf("\n2. Incluir sala");
        printf("\n3. Alterar sala");
        printf("\n4. Excluir sala");
        printf("\n5. Sair");
        printf("\nOpcao: ");

        scanf("%d", &opc);
        while(getchar() != '\n');

        switch(opc) {
            case 1:
                listar_salas(sistema->salas, sistema->qtdSalas);
                break;
            case 2:
                incluir_salas(&sistema->salas, &sistema->qtdSalas);
                break;

            case 3:
                alterar_salas();
                break;

            case 4:
                excluir_salas();
                break;

            case 5:
                printf("Saindo...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }

    } while (opc != 5);

    return;
}

void submenuFilmes(){
    int opc;


    do{
        printf("\n--- Filmes ---");
        printf("\n1. Listar todos os filmes");
        printf("\n2. Buscar filme");
        printf("\n3. Incluir filme");
        printf("\n4. Alterar filme");
        printf("\n5. Excluir filme");
        printf("\n6. Sair");
        scanf("%d", &opc);
        while(getchar() != '\n');   

        switch(opc) {
            case 1:
                //listar_Filmes(filmes);
                printf("Listando...\n");
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
        printf("\n1. Listar todas as sessoes");
        printf("\n2. Buscar sessao");
        printf("\n3. Incluir sessao");
        printf("\n4. Alterar sessao");
        printf("\n5. Excluir sessao");
        printf("\n6. Sair");
        scanf("%d", &opc);
        while(getchar() != '\n');

        switch(opc) {
            case 1:
                // listar_sessoes(sessoes);
                printf("Listando...\n");
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
        printf("\n1. Listar todos os relatorios");
        printf("\n2. Buscar relatorio");
        printf("\n3. Incluir relatorio");
        printf("\n4. Alterar relatorio");
        printf("\n5. Excluir relatorio");
        printf("\n6. Sair");
        scanf("%d", &opc);
        while(getchar() != '\n');

        switch(opc) {
            case 1:
                printf("Listando...\n");
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
    Sistema sistema;

    sistema.salas = NULL;
    sistema.qtdSalas = 0;

    sistema.filmes = NULL;
    sistema.qtdFilmes = 0;

    sistema.sessoes = NULL;
    sistema.qtdSessoes = 0;

    menu(&sistema);

    free(sistema.salas);
    free(sistema.filmes);
    free(sistema.sessoes);

    return 0;
}