#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


typedef struct poltrona
{
    int num;
    char fileira;
    int flag_livre; // 1 = Livre, 0 = Ocupada
} Poltrona;

typedef struct sala
{
    Poltrona poltronas[15];
    int num_sala;
} Sala;

typedef struct data
{
    int dia, mes, ano;
} Data;

typedef struct sessao
{
    char nomeFilme[30];
    Data dataFilme;
    int horaFilme;
    Sala salaReservada;
} Sessao;


void cadastrarPoltrona(Poltrona *p, int num, char fileira);
void inicializarSala(Sala *s, int numSala);
void cadastrarData(Data *d, int dia, int mes, int ano);
void cadastrarSessao(Sessao *s, char *filme, Data d, int hora, Sala sala);
void comprarPoltrona(Sessao *s, int posPoltrona);
void cancelarCompra(Sessao *s, int posPoltrona);


void mostrarPoltrona(Poltrona p);
void mostrarMapaSala(Sala s);
void mostrarData(Data d);
void mostrarSessao(Sessao s);


int mostrarMenu();
int escolherSessao(Sessao sessoes[], int totalSessoes);
void listarSessoes(Sessao sessoes[], int totalSessoes);
void fluxoComprarPoltrona(Sessao sessoes[], int totalSessoes);
void fluxoCancelarPoltrona(Sessao sessoes[], int totalSessoes);



void cadastrarPoltrona(Poltrona *p, int num, char fileira)
{
    p->num = num;
    p->fileira = fileira;
    p->flag_livre = 1; // 1 = Livre
}


void inicializarSala(Sala *s, int numSala)
{
    s->num_sala = numSala;

    char fileiras[3] = {'A', 'B', 'C'};
    int indice = 0;

    for (int f = 0; f < 3; f++)
    {
        for (int n = 1; n <= 5; n++)
        {
            
            cadastrarPoltrona(&s->poltronas[indice], n, fileiras[f]);
            indice++;
        }
    }
}


void cadastrarData(Data *d, int dia, int mes, int ano)
{
    d->dia = dia;
    d->mes = mes;
    d->ano = ano;
}


void cadastrarSessao(Sessao *s, char *filme, Data d, int hora, Sala sala)
{
    strncpy(s->nomeFilme, filme, sizeof(s->nomeFilme) - 1);
    s->nomeFilme[sizeof(s->nomeFilme) - 1] = '\0';

    s->dataFilme = d;
    s->horaFilme = hora;
    s->salaReservada = sala;
}


void comprarPoltrona(Sessao *s, int posPoltrona)
{
    if (posPoltrona < 0 || posPoltrona >= 15)
    {
        printf("\n[ERRO] Poltrona invalida!\n");
        return;
    }

    if (s->salaReservada.poltronas[posPoltrona].flag_livre == 0)
    {
        printf("\n[ERRO] Essa poltrona ja esta OCUPADA. Escolha outra.\n");
        return;
    }

    s->salaReservada.poltronas[posPoltrona].flag_livre = 0; // 0 = Ocupada
    printf("\nPoltrona %c%d comprada com sucesso para o filme \"%s\"!\n",
           s->salaReservada.poltronas[posPoltrona].fileira,
           s->salaReservada.poltronas[posPoltrona].num,
           s->nomeFilme);
}


void cancelarCompra(Sessao *s, int posPoltrona)
{
    if (posPoltrona < 0 || posPoltrona >= 15)
    {
        printf("\n[ERRO] Poltrona invalida!\n");
        return;
    }

    if (s->salaReservada.poltronas[posPoltrona].flag_livre == 1)
    {
        printf("\n[ERRO] Essa poltrona ja esta LIVRE. Nao ha compra para cancelar.\n");
        return;
    }

    s->salaReservada.poltronas[posPoltrona].flag_livre = 1; // 1 = Livre
    printf("\nCompra da poltrona %c%d cancelada. Poltrona liberada!\n",
           s->salaReservada.poltronas[posPoltrona].fileira,
           s->salaReservada.poltronas[posPoltrona].num);
}



void mostrarPoltrona(Poltrona p)
{
    printf("Poltrona %c%d [%s]", p.fileira, p.num, p.flag_livre ? "LIVRE" : "OCUPADA");
}

void mostrarMapaSala(Sala s)
{
    printf("\n----- MAPA DA SALA %d -----\n", s.num_sala);
    char fileiraAtual = s.poltronas[0].fileira;
    printf("Fileira %c: ", fileiraAtual);

    for (int i = 0; i < 15; i++)
    {
        if (s.poltronas[i].fileira != fileiraAtual)
        {
            fileiraAtual = s.poltronas[i].fileira;
            printf("\nFileira %c: ", fileiraAtual);
        }
        
        if (s.poltronas[i].flag_livre)
            printf("[%d] ", s.poltronas[i].num);
        else
            printf("[X%d] ", s.poltronas[i].num);
    }
    printf("\n(Legenda: [n] = Livre   [Xn] = Ocupada)\n");
    printf("---------------------------\n");
}

void mostrarData(Data d)
{
    printf("%02d/%02d/%04d", d.dia, d.mes, d.ano);
}

void mostrarSessao(Sessao s)
{
    printf("Filme: %-20s | Data: ", s.nomeFilme);
    mostrarData(s.dataFilme);
    printf(" | Hora: %02dh | Sala: %d\n", s.horaFilme, s.salaReservada.num_sala);
}



int mostrarMenu()
{
    int opcao;
    printf("\n========================================\n");
    printf("     SISTEMA DE CONTROLE DE CINEMA      \n");
    printf("========================================\n");
    printf("1. Listar todas as sessoes\n");
    printf("2. Comprar poltrona (Opcao 7.a)\n");
    printf("3. Cancelar compra de poltrona (Opcao 7.b)\n");
    printf("4. Sair\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &opcao);
    return opcao;
}

void listarSessoes(Sessao sessoes[], int totalSessoes)
{
    printf("\n===== SESSOES DISPONIVEIS =====\n");
    for (int i = 0; i < totalSessoes; i++)
    {
        printf("%d) ", i + 1);
        mostrarSessao(sessoes[i]);
    }
}


int escolherSessao(Sessao sessoes[], int totalSessoes)
{
    int escolha;
    listarSessoes(sessoes, totalSessoes);

    do
    {
        printf("Escolha a sessao (1 a %d): ", totalSessoes);
        scanf("%d", &escolha);
    } while (escolha < 1 || escolha > totalSessoes);

    return escolha - 1;
}

int calcularIndicePoltrona(char fileira, int num)
{
    int base;
    switch (fileira)
    {
        case 'A': base = 0; break;
        case 'B': base = 5; break;
        case 'C': base = 10; break;
        default: return -1;
    }
    if (num < 1 || num > 5) return -1;
    return base + (num - 1);
}

void fluxoComprarPoltrona(Sessao sessoes[], int totalSessoes)
{
    int idxSessao = escolherSessao(sessoes, totalSessoes);

    mostrarMapaSala(sessoes[idxSessao].salaReservada);

    char fileira;
    int num, indice;

    printf("Escolha a poltrona - Fileira (A, B ou C): ");
    scanf(" %c", &fileira);
    fileira = (char)toupper((unsigned char)fileira);
    printf("Numero da poltrona (1 a 5): ");
    scanf("%d", &num);

    indice = calcularIndicePoltrona(fileira, num);
    if (indice == -1)
    {
        printf("\n[ERRO] Poltrona invalida!\n");
        return;
    }

    comprarPoltrona(&sessoes[idxSessao], indice);

    printf("\nMapa atualizado:\n");
    mostrarMapaSala(sessoes[idxSessao].salaReservada);
}

void fluxoCancelarPoltrona(Sessao sessoes[], int totalSessoes)
{
    int idxSessao = escolherSessao(sessoes, totalSessoes);

    mostrarMapaSala(sessoes[idxSessao].salaReservada);

    char fileira;
    int num, indice;

    printf("Poltrona a cancelar - Fileira (A, B ou C): ");
    scanf(" %c", &fileira);
    fileira = (char)toupper((unsigned char)fileira);
    printf("Numero da poltrona (1 a 5): ");
    scanf("%d", &num);

    indice = calcularIndicePoltrona(fileira, num);
    if (indice == -1)
    {
        printf("\n[ERRO] Poltrona invalida!\n");
        return;
    }

    cancelarCompra(&sessoes[idxSessao], indice);

    printf("\nMapa atualizado:\n");
    mostrarMapaSala(sessoes[idxSessao].salaReservada);
}



int main()
{
    int opcao;
    
    Sessao sessoes[4];

    
    Sala sala1, sala2, sala3, sala4;
    Data data1, data2, data3, data4;

    inicializarSala(&sala1, 1);
    inicializarSala(&sala2, 2);
    inicializarSala(&sala3, 3);
    inicializarSala(&sala4, 4);

    cadastrarData(&data1, 10, 9, 2026);
    cadastrarData(&data2, 12, 9, 2026);
    cadastrarData(&data3, 15, 9, 2026);
    cadastrarData(&data4, 20, 9, 2026);

    cadastrarSessao(&sessoes[0], "Vingadores", data1, 20, sala1);
    cadastrarSessao(&sessoes[1], "Duna", data2, 18, sala2);
    cadastrarSessao(&sessoes[2], "Divertida Mente 2", data3, 16, sala3);
    cadastrarSessao(&sessoes[3], "Coringa", data4, 22, sala4);

    int totalSessoes = 4;

    do
    {
        opcao = mostrarMenu();

        switch (opcao)
        {
            case 1:
                listarSessoes(sessoes, totalSessoes);
                break;

            case 2:
                fluxoComprarPoltrona(sessoes, totalSessoes);
                break;

            case 3:
                fluxoCancelarPoltrona(sessoes, totalSessoes);
                break;

            case 4:
                printf("\nEncerrando o sistema. Ate logo!\n");
                break;

            default:
                printf("\n[ERRO] Opcao invalida! Tente novamente.\n");
                break;
        }

    } while (opcao != 4);

    return 0;
}