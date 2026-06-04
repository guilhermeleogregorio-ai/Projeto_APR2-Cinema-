#include <stdio.h>
#include <string.h>    
#include <stdlib.h> 
// #include <data.h>


// STRUCTS


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


// Variávies globais
Sala *salas= NULL;
int qtdSalas = 0;

Filme *filmes = NULL;
int qtdFilmes = 0;

Sessao *sessoes = NULL;
int qtdSessoes = 0;

//Protótipos

void menu();
void submenuSalas();
void submenuFilmes();
void submenuSessoes();
void submenuRelatorios();

void carregarDados();
void salvarDados();

void listar_salas();
int buscar_salas(int codigo);
void incluir_salas();
void alterar_salas();
void excluir_salas();

void listar_filmes();
int buscar_filmes(int codigo);
void incluir_filmes();
void alterar_filmes();
void excluir_filmes();

void listar_sessoes();
int buscar_sessoes(int codFilme, int codSala, char*data, char *horario);
void incluir_sessoes();
void alterar_sessoes();
void excluir_sessoes();

void relatorio_salas();
void relatorio_filmes();
void relatorio_sessoes();

//Persistencia

void carregarDados(){
    FILE *arq;
    Sala salaTemp;
    Filme filmeTemp;
    Sessao sessaoTemp;

    arq = fopen("salas.dat" , "rb");
    if(arq != NULL){
        while(fread(&salaTemp, sizeof(Sala), 1 , arq)== 1){
            salas = realloc(salas , (qtdSalas + 1) * sizeof(Sala));
            salas[qtdSalas] = salaTemp;
            qtdSalas++;
        }
        fclose(arq);
    }
    arq = fopen("filmes.dat", "rb");
    if(arq != NULL) {
        while(fread(&filmeTemp, sizeof(Filme), 1, arq) == 1) {
            filmes = realloc(filmes, (qtdFilmes + 1) * sizeof(Filme));
            filmes[qtdFilmes] = filmeTemp;
            qtdFilmes++;
        }
        fclose(arq);
    }
    arq = fopen("sessoes.dat", "rb");
    if(arq != NULL){
        while(fread(&sessaoTemp, sizeof(Sessao), 1 ,arq)== 1){
            sessoes = realloc(sessoes , (qtdSessoes + 1) * sizeof(Sessao));
            sessoes[qtdSessoes] = sessaoTemp;
            qtdSessoes++;
        }
        fclose(arq);
    }
}

void salvarDados(){
    FILE *arq;

    arq = fopen("salas.dat" , "wb");
    if(arq != NULL){
        fwrite(salas, sizeof(Sala), qtdSalas, arq);
        fclose(arq);
    }

    arq = fopen("filmes.dat" , "wb");
    if(arq != NULL){
        fwrite(filmes, sizeof(Filme), qtdFilmes, arq);
        fclose(arq);
    }

    arq = fopen("sessoes.dat", "wb");
    if(arq != NULL){
        fwrite(sessoes, sizeof(Sessao), qtdSessoes, arq);
        fclose(arq);
    }
}

// SALAS


void listar_salas(){
int i;
    if(qtdSalas == 0){
        printf("Nenhuma sala cadastrada\n");
        return;
    }
    
    for(i = 0; i < qtdSalas; i++){
        printf("\nCodigo: %d", salas[i].codigo);
        printf("\nNome: %s", salas[i].nome);
        printf("\nCapacidade: %d", salas[i].capacidade);
        printf("\nTipo: %s", salas[i].tipo);
        printf("\nAcessivel: %d\n", salas[i].acessivel);
    }
}

int buscar_salas(int codigo){
int i;
    for(i = 0 ; i <  qtdSalas; i++){
        if(salas[i].codigo == codigo){
            return i;
        }
    }
    return -1;
}

void incluir_salas(){
    Sala nova;

    printf("Codigo: ");
    scanf("%d", &nova.codigo);

    if(buscar_salas(nova.codigo) != -1){
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

    salas = realloc(salas, (qtdSalas + 1) * sizeof(Sala));
    (salas)[qtdSalas] = nova;
    qtdSalas++;

    printf("Sala cadastrada!\n");
}

void alterar_salas(){
    int codigo, pos;

    printf("Codigo da sala: ");
    scanf("%d", &codigo);

    pos = buscar_salas(codigo);
    if(pos == -1){
        printf("Sala não encontrada!\n");
        return;
    }

    printf("Novo nome (%s): ", salas[pos].nome);
    scanf("%[^\n]", salas[pos].nome);

    printf("Nova capacidade (%d): ", salas[pos].capacidade);
    scanf("%d", &salas[pos].capacidade);

    printf("Novo tipo (%s): ", salas[pos].tipo);
    scanf("%s", salas[pos].tipo);

    printf("Novo acessivel (%d): ", salas[pos].acessivel);
    scanf("%d", &salas[pos].acessivel);

    printf("Sala alterada!\n");

}

void excluir_salas(){
    int codigo, pos , i;
    char confirm;

    printf("Digite o codigo da sala que deseja excluir\n");
    scanf("%d", &codigo);

    pos = buscar_salas(codigo);
    if(pos == -1){
        printf("Sala não encontrada");
        return;
    }

    // Mostrar dados
    printf("\nSala encontrada:");
    printf("\nCodigo: %d", salas[pos].codigo);
    printf("\nNome: %s\n" , salas[pos].nome);

    //confirmação
    printf("\n Deseja excluir? (s/n)\n");
    scanf(" %c", &confirm);

    if(confirm !='s' && confirm !='S'){
        printf("Cancelado.\n");
        return;
    }

    for(i = pos; i < qtdSalas -1; i++){
        salas[i] = salas[i + 1];
    }

    qtdSalas--;

    //realocar
    if(qtdSalas == 0){
        free(salas);
        salas = NULL;
    } else {
        salas = realloc(salas, qtdSalas *sizeof(Sala));
    }

    printf("Sala excluida com sucesso!\n");

}


// FILMES



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


// SESSOES


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


// RELATORIO

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

// MENU


void menu(Sistema *sistema){
    int opc;
    
    do {
        printf("\n=== Sistema cinema ===");
        printf("\n1. Salas");
        printf("\n2. Filmes");
        printf("\n3. Sessões");
        printf("\n4. Relatórios");
        printf("\n5. Sair");
        printf("\nOpção\n");

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
        printf("\nOpcao:\n ");

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
                excluir_salas(sistema);
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