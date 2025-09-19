#include <stdio.h>
#include <string.h>
#include <time.h>

#define N 10

// Struct do ônibus
typedef struct {
    int numero;
    char nome[30];
    float tempo; // tempo de chegada em minutos
} Onibus;

// Função para exibir horário previsto de chegada
void exibirOnibusComHorario(Onibus v[], int tamanho) {
    // Pega o horário atual
    time_t agora = time(NULL);
    struct tm *horaAtual = localtime(&agora);

    printf("---------------------------------------------------------------------------------------------\n");
    printf("| Nº  | Nome da Linha                | Chegara em:| Horario Previsto de Chegada|\n");
    printf("---------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < tamanho; i++) {
        // Cópia do horário atual para calcular a chegada
        struct tm chegada = *horaAtual;

        // Adiciona os minutos simulados ao horário atual
        chegada.tm_min += (int)v[i].tempo;
        mktime(&chegada); // Ajusta possíveis estouros (tipo 12:60 → 13:00)

        // Exibe linha da tabela
        printf("| %3d | %-28s | %6.1f min |     %02d:%02d                  |\n",
               v[i].numero, v[i].nome, v[i].tempo,
               chegada.tm_hour, chegada.tm_min);
    }

    printf("---------------------------------------------------------------------------------------------\n");
}

// Bubble Sort crescente
void bubbleSortCrescente(Onibus v[], int tamanho) {
    for (int i = 0; i < tamanho - 1; i++) {
        for (int j = 0; j < tamanho - i - 1; j++) {
            if (v[j].tempo > v[j + 1].tempo) {
                Onibus temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;
            }
        }
    }
}

// Bubble Sort decrescente
void bubbleSortDecrescente(Onibus v[], int tamanho) {
    for (int i = 0; i < tamanho - 1; i++) {
        for (int j = 0; j < tamanho - i - 1; j++) {
            if (v[j].tempo < v[j + 1].tempo) {
                Onibus temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;
            }
        }
    }
}

int main() {
    printf("===============================================\n");
    printf("     SIMULADOR DE CHEGADA DE ÔNIBUS EM TEMPO REAL\n");
    printf("        (Com Horário Previsto de Chegada)\n");
    printf("===============================================\n\n");

    // Lista dos ônibus com tempo de chegada simulado
    Onibus lista[N] = {
        {101, "Jardim das Flores", 12.5},
        {102, "Centro - Estacao", 9.0},
        {103, "Bairro Novo", 15.2},
        {104, "Universidade", 7.8},
        {105, "Shopping Central", 10.3},
        {106, "Terminal Norte", 5.6},
        {107, "Hospital Municipal", 13.1},
        {108, "Parque Industrial", 11.0},
        {109, "Rodoviaria", 8.7},
        {110, "Praca das Arvores", 6.4}
    };
    
    Onibus original[N];
    memcpy(original, lista, sizeof(lista)); // Cópia segura da lista original
    
    // Mostra o horário atual
    time_t agora = time(NULL);
    struct tm *horaAtual = localtime(&agora);
    printf("Hora atual do sistema: %02d:%02d\n\n", horaAtual->tm_hour, horaAtual->tm_min);
    // -------- ORDEM ORIGINAL --------
    printf(">>> Lista ORIGINAL dos ônibus (sem ordenação) <<<\n");
    exibirOnibusComHorario(original, N);
    printf("\n");
    // -------- ORDEM CRESCENTE --------
    bubbleSortCrescente(lista, N);
    printf(">>> Previsão de chegada dos ônibus (ordem CRESCENTE - mais rápidos primeiro): <<<\n");
    exibirOnibusComHorario(lista, N);
    printf("\n");

    // -------- ORDEM DECRESCENTE --------
    bubbleSortDecrescente(lista, N);
    printf(">>> Previsão de chegada dos ônibus (ordem DECRESCENTE - mais lentos primeiro): <<<\n");
    exibirOnibusComHorario(lista, N);

    return 0;
}