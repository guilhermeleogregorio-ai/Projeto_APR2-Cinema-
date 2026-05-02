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

int buscar_salas(int codigo){
int i;
    for(i = 0 ; i <  qtdSalas; i++){
        if(vSalas[i].codigo == codigo){
            return i;
        }
    }
    return -1;
}

void incluir_salas(Sala){


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
   
   return;
    
}

void submenuSalas(){
    int opc;

    do{
        printf("\n--- Salas ---");
        printf("\n1. Listar todas as salas");
        printf("\n2. Buscar sala");
        printf("\n3. Incluir sala");
        printf("\n4. Alterar sala");
        printf("\n5. Excluir sala");
        printf("\n6. Sair");
        printf("\nOpcao: ");

        scanf("%d", &opc);
        while(getchar() != '\n');

        switch(opc) {
            case 1:
                listar_salas();
                break;

            case 2: {
                int codigo;
                printf("Codigo: ");
                scanf("%d", &codigo);

                int pos = buscar_sala(codigo);

                if(pos == -1)
                    printf("Nao encontrada\n");
                else
                    printf("Encontrada: %s\n", vSalas[pos].nome);

                break;
            }

            case 3:
                incluir_sala();
                break;

            case 4:
                alterar_sala();
                break;

            case 5:
                excluir_sala();
                break;

            case 6:
                printf("Saindo...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }

    } while (opc != 6);

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