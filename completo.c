#include <stdio.h>
#include <string.h>

#define MAX_PACIENTES 50
#define MAX_CONSULTAS 200
#define NOME_TAM 80
#define DATA_TAM 11
#define HORA_TAM 6

// Representa um paciente do sistema
typedef struct {
    char nome[NOME_TAM];
    int idade;
} Paciente;

// Representa uma consulta médica
typedef struct {
    int paciente_id;        // ID (1..N) do paciente
    char data[DATA_TAM];    // YYYY-MM-DD
    char hora[HORA_TAM];    // HH:MM
} Consulta;

Paciente pacientes[MAX_PACIENTES];
Consulta consultas[MAX_CONSULTAS];
int qtd_pacientes = 0;
int qtd_consultas = 0;


void remover_quebra_linha(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '\n') {
            str[i] = '\0';
            return;
        }
    }
}


int ler_inteiro_da_linha(int *out) {
    if (scanf("%d", out) != 1)
        return 0;
    getchar(); 
    return 1;
}


int idade_valida(int idade) {
    return idade >= 0 && idade <= 130;
}

void ler_dados_paciente(Paciente *p) {
    printf("Nome: ");
    fgets(p->nome, NOME_TAM, stdin);
    remover_quebra_linha(p->nome);

    printf("Idade: ");
    ler_inteiro_da_linha(&p->idade);
}

void ler_data_hora(Consulta *c) {
    printf("Data (YYYY-MM-DD): ");
    fgets(c->data, DATA_TAM, stdin);
    remover_quebra_linha(c->data);

    printf("Hora (HH:MM): ");
    fgets(c->hora, HORA_TAM, stdin);
    remover_quebra_linha(c->hora);
}

int consulta_duplicada(const Consulta *c) {
    for (int i = 0; i < qtd_consultas; i++) {
        if (consultas[i].paciente_id == c->paciente_id &&
            strcmp(consultas[i].data, c->data) == 0 &&
            strcmp(consultas[i].hora, c->hora) == 0)
            return 1;
    }
    return 0;
}

void cadastrar_paciente(void) {
    if (qtd_pacientes >= MAX_PACIENTES) {
        printf("Limite de pacientes atingido.\n");
        return;
    }

    Paciente p;
    ler_dados_paciente(&p);

    if (!idade_valida(p.idade)) {
        printf("Idade inválida.\n");
        return;
    }

    pacientes[qtd_pacientes++] = p;
    printf("Paciente cadastrado com sucesso.\n");
}

void agendar_consulta(void) {
    if (qtd_consultas >= MAX_CONSULTAS) {
        printf("Limite de consultas atingido.\n");
        return;
    }

    int id;
    printf("ID do paciente: ");
    if (!ler_inteiro_da_linha(&id) || id < 1 || id > qtd_pacientes) {
        printf("Paciente inexistente.\n");
        return;
    }

    Consulta c;
    c.paciente_id = id;

    ler_data_hora(&c);

    if (consulta_duplicada(&c)) {
        printf("Consulta já existe.\n");
        return;
    }

    consultas[qtd_consultas++] = c;
    printf("Consulta agendada com sucesso.\n");
}

void listar_pacientes(void) {
    if (qtd_pacientes == 0) {
        printf("Nenhum paciente cadastrado.\n");
        return;
    }

    for (int i = 0; i < qtd_pacientes; i++) {
        printf("%d) %s - %d anos\n",
               i + 1,
               pacientes[i].nome,
               pacientes[i].idade);
    }
}

void listar_consultas(void) {
    if (qtd_consultas == 0) {
        printf("Nenhuma consulta agendada.\n");
        return;
    }

    for (int i = 0; i < qtd_consultas; i++) {
        printf("%d) %s | %s | %s\n",
               i + 1,
               pacientes[consultas[i].paciente_id - 1].nome,
               consultas[i].data,
               consultas[i].hora);
    }
}

void exibir_menu(void) {
    printf("\n===== AGENDA DE CONSULTAS =====\n");
    printf("1 - Cadastrar paciente\n");
    printf("2 - Listar pacientes\n");
    printf("3 - Agendar consulta\n");
    printf("4 - Listar consultas\n");
    printf("0 - Sair\n");
}

int main(void) {
    int opcao;

    do {
        exibir_menu();
        printf("Escolha: ");
        ler_inteiro_da_linha(&opcao);

        switch (opcao) {
            case 1: cadastrar_paciente(); break;
            case 2: listar_pacientes(); break;
            case 3: agendar_consulta(); break;
            case 4: listar_consultas(); break;
            case 0: printf("Encerrando...\n"); break;
            default: printf("Opção inválida.\n");
        }
    } while (opcao != 0);

    return 0;
}