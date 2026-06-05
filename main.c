#include <stdio.h>
#include <string.h>    
#include <stdlib.h> 



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

    int qtdAtores;
    char atores[10][50]; // vetor de strings
} Filme;

typedef struct {
    int codFilme;    // Chave composta (Filme + Sala + Data + Hora)
    int codSala;
    int data;  
    int horario; 
    float preco;
} Sessao;

// Funções auxiliares
int stringDataParaInt(char *dataStr) {
    int dia, mes, ano;
    sscanf(dataStr, "%d/%d/%d", &dia, &mes, &ano);
    return ano * 10000 + mes * 100 + dia;
}
// Converte int para "DD/MM/AAAA" (para exibir)
void intParaStringData(int dataInt, char *saida) {
    int ano = dataInt / 10000;
    int mes = (dataInt % 10000) / 100;
    int dia = dataInt % 100;
    sprintf(saida, "%02d/%02d/%04d", dia, mes, ano);
}

// Converte "HH:MM" para int (ex: 20:00 -> 2000)
int stringHorarioParaInt(char *horarioStr) {
    int hora, minuto;
    sscanf(horarioStr, "%d:%d", &hora, &minuto);
    return hora * 100 + minuto;
}

// Converte int para "HH:MM" (para exibir)
void intParaStringHorario(int horarioInt, char *saida) {
    int hora = horarioInt / 100;
    int minuto = horarioInt % 100;
    sprintf(saida, "%02d:%02d", hora, minuto);
}


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
int buscar_filmes(int codigo) ;
void incluir_filmes();
void alterar_filmes();
void excluir_filmes();

void listar_sessoes();
int buscar_sessoes(int codFilme, int codSala, int data, int horario);
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
        Sala *temp;

        while(fread(&salaTemp, sizeof(Sala), 1 , arq)== 1){

        temp = realloc(salas, (qtdSalas + 1) * sizeof(Sala));

        if(temp == NULL){
            printf("Erro ao carregar salas!\n");
            fclose(arq);
            return;
        }

        salas = temp;
        salas[qtdSalas] = salaTemp;
        qtdSalas++;
        }
        fclose(arq);
    }

    arq = fopen("filmes.dat", "rb");
    if(arq != NULL) {
        Filme *temp;

        while(fread(&filmeTemp, sizeof(Filme), 1, arq) == 1) {

            temp = realloc(filmes, (qtdFilmes + 1) * sizeof(Filme));

            if(temp == NULL){
                printf("Erro ao carregar filmes!\n");
                fclose(arq);
                return;
            }

            filmes = temp;
            filmes[qtdFilmes] = filmeTemp;
            qtdFilmes++;
        }
        fclose(arq);
    }
    arq = fopen("sessoes.dat", "rb");
    if(arq != NULL){
        Sessao *temp;

        while(fread(&sessaoTemp, sizeof(Sessao), 1 ,arq)== 1){

            temp = realloc(sessoes , (qtdSessoes + 1) * sizeof(Sessao));

            if(temp == NULL){
                printf("Erro ao carregar sessoes!\n");
                fclose(arq);
                return;
            }    
            
            sessoes = temp;
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

    do {
        printf("Capacidade: ");
        scanf("%d", &nova.capacidade);
    } while(nova.capacidade <= 0);

    printf("Tipo: ");
    scanf("%s", nova.tipo);

    printf("Acessivel (1/0): ");
    scanf("%d", &nova.acessivel);

    Sala *temp;
    temp = realloc(salas, (qtdSalas + 1) * sizeof(Sala));

    if(temp == NULL){
    printf("Erro ao alocar!\n");
    return;
    }

    salas = temp;
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
    scanf(" %[^\n]", salas[pos].nome);

    do {
        printf("Nova capacidade (%d): ", salas[pos].capacidade);
        scanf("%d", &salas[pos].capacidade);
    } while(salas[pos].capacidade <= 0);

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



void listar_filmes(){
    int i, j;
    if(qtdFilmes == 0){
        printf("Nenhum filme cadastrado\n");
        return;
    }

    for(i = 0 ; i < qtdFilmes; i++){
        printf("\nCodigo: %d", filmes[i].codigo);
        printf("\nNome: %s", filmes[i].nome);
        printf("\nAno: %d", filmes[i].ano);
        printf("\nDiretor: %s", filmes[i].diretor);

        printf("\nAtores:\n");
        for(j = 0; j < filmes[i].qtdAtores; j++)
        printf("\n %s\n", filmes[i].atores[j]);
    }
}

int buscar_filmes(int codigo){
    int i;
    for(i = 0 ; i < qtdFilmes; i++){
        if(filmes[i].codigo == codigo){
            return i ;
        }
    }
    return -1;
}

void incluir_filmes(){
    Filme novo;
    int i;

    printf("Codigo: ");
    scanf("%d", &novo.codigo);

    if(buscar_filmes(novo.codigo) != -1){
        printf("Filme já existe!\n");
        return;
    }

    printf("Nome: ");
    scanf(" %[^\n]", novo.nome);

    printf("Ano: ");
    scanf("%d", &novo.ano);

    printf("Diretor: ");
    scanf(" %[^\n]", novo.diretor);

    printf("Quantidade de atores: ");
    scanf("%d", &novo.qtdAtores);

    for(i = 0; i < novo.qtdAtores; i++){
        printf("Ator %d: ", i + 1);
        scanf(" %[^\n]", novo.atores[i]);
    }

    printf("Atores: ");
    scanf(" %[^\n]", novo.atores);

    Filme *temp;
    
    temp = realloc(filmes, (qtdFilmes + 1) * sizeof(Filme));

    if(temp == NULL){
        printf("Erro ao alocar:\n");
        return;
    }

    filmes = temp;
    filmes[qtdFilmes] = novo;
    qtdFilmes++;

    printf("Filme cadastrado!\n");

}

void alterar_filmes(){
    int codigo, pos, i;

    printf("Codigo do filme: ");
    scanf("%d", &codigo);

    pos = buscar_filmes(codigo);
    if(pos == -1){
        printf("Filme não encontrado!\n");
        return;
    }

        printf("Novo nome (%s): ", filmes[pos].nome);
        scanf(" %[^\n]", filmes[pos].nome);

        printf("Novo ano (%d): ", filmes[pos].ano);
        scanf("%d", &filmes[pos].ano);

        printf("Novo diretor (%s): ", filmes[pos].diretor);
        scanf(" %[^\n]", filmes[pos].diretor);

        printf("Quantidade de atores: ");
        scanf("%d", &filmes[pos].qtdAtores);

        for(i = 0; i < filmes[pos].qtdAtores; i++){
            printf("Ator %d: ", i + 1);
            scanf(" %[^\n]", filmes[pos].atores[i]);
        }

        printf("Filme alterado!\n");

}

void excluir_filmes(){
    int codigo, pos , i;
    char confirm;

    printf("Digite o codigo do filme que deseja excluir:");
    scanf("%d", &codigo);

    pos = buscar_filmes(codigo);
    if(pos == -1){
        printf("Filme não encontrado!\n");
        return;
    }

    printf("\nFilme encontrado:");
    printf("\nCodigo: %d", filmes[pos].codigo);
    printf("\nNome: %s", filmes[pos].nome);


    printf("\nDeseja excluir? (s/n): ");
    scanf(" %c", &confirm);

    if(confirm != 's' && confirm != 'S'){
        printf("Cancelado.\n");
        return;
    }

    for(i = pos; i < qtdFilmes - 1; i++){
        filmes[i] = filmes[i + 1];
    }

    qtdFilmes--;

    if(qtdFilmes == 0){
        free(filmes);
        filmes = NULL;
    }else {
        filmes = realloc(filmes, qtdFilmes * sizeof(Filme));
    }
    
    printf("Filme excluido com sucesso!\n");
}


// SESSOES


void listar_sessoes(){
    int i;
    char dataSrt[11], horarioStr[6];

    if(qtdSessoes == 0){
        printf("Nenhuma sessao cadastrada\n");
        return;
    }

    for(i = 0 ; i < qtdSessoes ; i++){
        intParaStringData(sessoes[i].data, dataSrt);
        intParaStringHorario(sessoes[i].horario, horarioStr);
        printf("\nFilme: %d | Sala: %d", sessoes[i].codFilme, sessoes[i].codSala);
        printf("\nData: %s | horario: %s", dataSrt, horarioStr);
        printf("\nPreco: R$ %.2f\n", sessoes[i].preco);
    }

}

int buscar_sessoes(int codFilme, int codSala, int data, int horario){
    int i;
    for(i = 0; i < qtdSessoes; i++){
        if(sessoes[i].codFilme ==  codFilme && sessoes[i].codSala == codSala && sessoes[i].data == data && sessoes[i].horario == horario){
            return i;
        }
    }
    return -1;
}

void incluir_sessoes(){
    Sessao nova;
    char dataStr[11], horarioStr[6];

    printf("Codigo do filme: ");
    scanf("%d", &nova.codFilme);

    if(buscar_filmes(nova.codFilme)== -1){
        printf("Filme não existe!\n");
        return;
    }

    printf("Codigo da Sala: ");
    scanf("%d", &nova.codSala);

    if(buscar_salas(nova.codSala)== -1){
        printf("Sala não existe!\n");
        return;
    }

    printf("Data (DD/MM/AAAA):");
    scanf(" %[^\n]", dataStr);

    printf("Horario (HH:MM): ");
    scanf(" %[^\n]",horarioStr);

    nova.data = stringDataParaInt(dataStr);
    nova.horario = stringHorarioParaInt(horarioStr);

    if(buscar_sessoes(nova.codFilme, nova.codSala, nova.data , nova.horario) != -1){
        printf("Sessão ja existe!\n");
        return;
    }

    printf("Preco: ");
    scanf("%f", &nova.preco);

    Sessao *temp;
    
    temp = realloc(sessoes, (qtdSessoes + 1) * sizeof(Sessao));
    
    if(temp == NULL){
        printf("Erro ao alocar:\n");
        return;
    }

    sessoes = temp;
    sessoes[qtdSessoes] = nova;
    qtdSessoes++;

    printf("Sessao cadastrada!\n");

}

void alterar_sessoes(){
    int codFilme, codSala, pos;
    char dataStr[11], horarioStr[6];
    int dataInt, horarioInt;

    printf("Codigo do filme: ");
    scanf("%d", &codFilme);
    printf("Codigo da Sala: ");
    scanf("%d", &codSala);
    printf("Data: ");
    scanf(" %[^\n]", dataStr);
    printf("Horario: ");
    scanf(" %[^\n]", horarioStr);

// CONVERTE PARA INTEIRO ANTES DE BUSCAR
    dataInt = stringDataParaInt(dataStr);
    horarioInt = stringHorarioParaInt(horarioStr);

    pos = buscar_sessoes(codFilme, codSala, dataInt, horarioInt);
    if(pos == -1){
        printf("Sessao não encontrada!\n");
        return;
    }

    printf("Novo preco (R$ %.2f): ", sessoes[pos].preco);
    scanf("%f", &sessoes[pos].preco);

    printf("Sessao alterada!\n");

}

void excluir_sessoes(){
    int codFilme, codSala, pos , i;
    char dataStr[11], horarioStr[6], confirm;
    int dataInt, horarioInt;

    printf("Codigo do Filme: ");
    scanf("%d", &codFilme);
    printf("Codigo da Sala: ");
    scanf("%d", &codSala);
    printf("Data: ");
    scanf(" %[^\n]", dataStr);
    printf("Horario: ");
    scanf(" %[^\n]", horarioStr);

    //CONVERTE PARA INTEIRO ANTE DE BUSCAR
    dataInt = stringDataParaInt(dataStr);
    horarioInt = stringHorarioParaInt(horarioStr);


    pos = buscar_sessoes(codFilme, codSala, dataInt, horarioInt);
    if(pos == -1){
        printf("Sessao não encontrada!\n");
        return;
    }

    //CONVERTE DE VOLTA PARA STRING PARA EXIBIÇÃO
    intParaStringData(sessoes[pos].data, dataStr);
    intParaStringHorario(sessoes[pos].horario, horarioStr);

    printf("\nSessao encontrada:");
    printf("\nFilme: %d | Sala: %d", sessoes[pos].codFilme, sessoes[pos].codSala);
    printf("\nData: %s | Horario: %s", dataStr, horarioStr);

    printf("\nDeseja excluir? (s/n): ");
    scanf(" %c", &confirm);

    if(confirm != 's' && confirm != 'S'){
        printf("Cancelado.\n");
        return;
    }

    for(i = pos; i < qtdSessoes - 1; i++){
        sessoes[i] = sessoes[i + 1];
    }
    
    qtdSessoes--;

    if(qtdSessoes == 0){
        free(sessoes);
        sessoes = NULL;
    }else {
        sessoes = realloc(sessoes, qtdSessoes * sizeof(Sessao));
    }

    printf("Sessao excluida com sucesso!\n");
}


// RELATORIOS

void relatorio_salas(){
    FILE *arq;
    char tipo[20];
    int capacidade, i , encontrados = 0 ;

    printf("Tipo de exibicao: ");
    scanf(" %[^\n]", tipo);
    printf("Capacidade minima: ");
    scanf("%d", &capacidade);

    arq = fopen("relatorio_salas.txt", "w");
    fprintf(arq, "RELATORIO DE SALAS\n");
    fprintf(arq, "Tipo: %s | Capacidade > %d\n\n", tipo, capacidade);

    for(i = 0; i < qtdSalas; i++){
        if(strcmp(salas[i].tipo, tipo) == 0 && salas[i].capacidade > capacidade){
            fprintf(arq, "Codigo: %d\n", salas[i].codigo);
            fprintf(arq, "Nome: %s\n", salas[i].nome);
            fprintf(arq, "Capacidade: %d\n", salas[i].capacidade);
            fprintf(arq, "Tipo: %s\n", salas[i].tipo);
            fprintf(arq, "Acessivel: %d\n", salas[i].acessivel);
            fprintf(arq, "-------------------\n");
            encontrados++;
        }
    }

    if(encontrados == 0){
        fprintf(arq, "Nenhuma sala encontrada.\n");
    }

    fclose(arq);
    printf("Relatorio salvo em relatorio_salas.txt\n");

}

void relatorio_filmes(){
    FILE *arq;
    int ano, i , encontrados = 0;

    printf("A parti do ano:");
    scanf("%d", &ano);

    arq = fopen("relatorio_filmes.txt", "w");
    fprintf(arq, "RELATORIO DE FILMES\n");
    fprintf(arq, "Ano >= %d\n\n", ano);

    for(i = 0; i < qtdFilmes; i++){
        if(filmes[i].ano >= ano){
            fprintf(arq, "Codigo: %d\n", filmes[i].codigo);
            fprintf(arq, "Nome: %s\n", filmes[i].nome);
            fprintf(arq, "Ano: %d\n", filmes[i].ano);
            fprintf(arq, "Diretor: %s\n", filmes[i].diretor);
            fprintf(arq, "Atores:\n");

            for(int j = 0; j < filmes[i].qtdAtores; j++){
                fprintf(arq, "- %s\n", filmes[i].atores[j]);
            }
            fprintf(arq, "-------------------\n");
            encontrados++;
        }
    }
    
    if (encontrados == 0){
        fprintf(arq, "Nenhum filme encontrado.\n");
    }
    
    fclose(arq);
    printf("Relatorio salvo em relatorio_filmes.txt");
}



void relatorio_sessoes() {
    FILE *arq;
    char dataIni[11], dataFim[11];
    int i, encontrados = 0, posFilme, posSala;
    int dataIniInt, dataFimInt, dataSessaoInt;
    char dataStr[11], horarioStr[6];
    
    printf("Data inicial (DD/MM/AAAA): ");
    scanf(" %[^\n]", dataIni);
    printf("Data final (DD/MM/AAAA): ");
    scanf(" %[^\n]", dataFim);

    //CONVERTE AS DATA DIGITADAS PARA INTEIRO
    dataIniInt = stringDataParaInt(dataIni);
    dataFimInt = stringDataParaInt(dataFim);
    
    arq = fopen("relatorio_sessoes.txt", "w");
    fprintf(arq, "RELATORIO DE SESSOES\n");
    fprintf(arq, "Periodo: %s a %s\n\n", dataIni, dataFim);
    
    for(i = 0; i < qtdSessoes; i++) {
        dataSessaoInt = sessoes[i].data;
        if(dataSessaoInt >= dataIniInt && dataSessaoInt <= dataFimInt) {
            posFilme = buscar_filmes(sessoes[i].codFilme);
            posSala = buscar_salas(sessoes[i].codSala);
            
            if(posFilme != -1 && posSala != -1) {
                fprintf(arq, "Codigo Filme: %d\n", sessoes[i].codFilme);
                fprintf(arq, "Nome Filme: %s\n", filmes[posFilme].nome);

                fprintf(arq, "Atores:\n");
                for(int j = 0; j < filmes[posFilme].qtdAtores; j++){
                    fprintf(arq, "- %s\n", filmes[posFilme].atores[j]);
                }

                fprintf(arq, "Codigo Sala: %d\n", sessoes[i].codSala);
                fprintf(arq, "Nome Sala: %s\n", salas[posSala].nome);

                intParaStringData(sessoes[i].data, dataStr);
                intParaStringHorario(sessoes[i].horario, horarioStr);
                fprintf(arq, "Data: %s\n", dataStr);
                fprintf(arq, "Horario: %s\n", horarioStr);

                fprintf(arq, "Preco: R$ %.2f\n", sessoes[i].preco);
                fprintf(arq, "-------------------\n");
                encontrados++;
            }
        }
    }
    
    if(encontrados == 0) {
        fprintf(arq, "Nenhuma sessao encontrada.\n");
    }
    
    fclose(arq);
    printf("Relatorio salvo em relatorio_sessoes.txt\n");
}

// MENU

void menu(){
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
                submenuSalas();
                break;
            case 2:
                submenuFilmes();
                break;
            case 3:
                submenuSessoes();
                break;
            case 4:
                submenuRelatorios();
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
        printf("\nOpcao:\n ");

        scanf("%d", &opc);
        while(getchar() != '\n');

        switch(opc) {
            case 1:
                printf("Listando...\n");
                listar_salas();
                break;
            case 2:{
                int cod, pos;
                printf("Codigo: ");
                scanf("%d", &cod);
                pos = buscar_salas(cod);
                if(pos == -1){
                    printf("Sala nao encontrada!\n");
                }else{
                    printf("\nCodigo: %d", salas[pos].codigo);
                    printf("\nNome: %s", salas[pos].nome);
                    printf("\nCapacidade: %d", salas[pos].capacidade);
                    printf("\nTipo: %s", salas[pos].tipo);
                    printf("\nAcessivel: %d\n", salas[pos].acessivel);
                }
                break;
            }
            case 3:
                incluir_salas();
                break;

            case 4:
                alterar_salas();
                break;
            case 5:
                excluir_salas();
                break;
            case 6:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }

    } while (opc != 6);
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
        printf("\n6. Sair\n");
        scanf("%d", &opc);
        while(getchar() != '\n');   

        switch(opc) {
            case 1:
                printf("Listando...\n");
                listar_filmes();
                break;
            case 2:{
                int cod, pos, i;
                printf("Codigo: ");
                scanf("%d", &cod);
                pos = buscar_filmes(cod);
                if(pos == -1){
                    printf("Filme nao encontrado!\n");
                }else {
                    printf("\nCodigo: %d", filmes[pos].codigo);
                    printf("\nNome: %s", filmes[pos].nome);
                    printf("\nAno: %d", filmes[pos].ano);
                    printf("\nDiretor: %s", filmes[pos].diretor);
                    printf("\nAtores:\n");
                    for(int i = 0; i < filmes[pos].qtdAtores; i++){
                        printf("- %s\n", filmes[pos].atores[i]);
                    }
                                    }
                break;
            }
            case 3:
                incluir_filmes();
                break;
            case 4:
                alterar_filmes();
                break;
            case 5:
                excluir_filmes();
                break;
            case 6:
                printf("Saindo...\n");
                break;
            default:
            printf("Opcao invalida!\n");
        }
    } while (opc != 6);
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
        printf("\n6. Sair\n");
        scanf("%d", &opc);
        while(getchar() != '\n');

        switch(opc) {
            case 1:
                printf("Listando...\n");
                listar_sessoes();
                break;
            case 2:{
                int cf, cs, pos;
                char d[11], h[6];
                int dataInt, horarioInt;
                char dataStr[11], horarioStr[6];


                printf("Codigo Filme: ");
                scanf("%d", &cf);
                printf("Codigo Sala: ");
                scanf("%d", &cs);
                printf("Data: ");
                scanf(" %[^\n]", d);
                printf("Horario: ");
                scanf(" %[^\n]", h);

                //CONVERTE APRA INTEIRO
                dataInt = stringDataParaInt(d);
                horarioInt = stringHorarioParaInt(h);

                pos = buscar_sessoes(cf, cs, dataInt, horarioInt);
                if(pos == -1){
                    printf("Sessao nao encontrada\n");
                }else {
                    intParaStringData(sessoes[pos].data, dataStr);
                    intParaStringHorario(sessoes[pos].horario, horarioStr);

                    printf("\nFilme: %d | Sala: %d", sessoes[pos].codFilme, sessoes[pos].codSala);
                    printf("\nData: %s | Horario: %s", dataStr, horarioStr);
                    printf("\nPreco: R$ %.2f\n", sessoes[pos].preco);
                }
                break;
            }
            case 3:
                incluir_sessoes();
                break;
            case 4:
                alterar_sessoes();
                break;
            case 5:
                excluir_sessoes();
                break;
            case 6:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opc != 6);
}

void submenuRelatorios(){
    int opc;
    
    do {
        printf("\n--- Relatorios ---");
        printf("\n1. Relatorio de Salas");
        printf("\n2. Relatorio de Filmes");
        printf("\n3. Relatorio de Sessoes");
        printf("\n4. Voltar\n");
        printf("\nOpcao: ");
        
        scanf("%d", &opc);
        
        switch(opc) {
            case 1:
                relatorio_salas();
                break;
            case 2:
                relatorio_filmes();
                break;
            case 3:
                relatorio_sessoes();
                break;
            case 4:
                printf("Voltando...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while(opc != 4);
}

//Main

int main(){
    carregarDados();
    menu();
    salvarDados();

    free(salas);
    free(filmes);
    free(sessoes);

    return 0;
}