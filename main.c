#include <stdio.h>
#include <stdlib.h>
#include <string.h>

float calcularMedia(float *notas, int numNotas) {
    float soma = 0.0;
    for (int i = 0; i < numNotas; i++) {
        soma += notas[i];
    }
    return soma / numNotas;
}

int main() {
    FILE *entrada = fopen("DadosEntrada.csv", "r");
    FILE *saida = fopen("SituacaoFinal.csv", "w");

    if (entrada == NULL || saida == NULL) {
        printf("Arquivos n encontrados.\n");
        return 1;
    }

    printf("Dados do arquivo de entrada:\n");
    printf("Nome do Aluno | Telefone | Curso | Notas\n");

    char linha[100];
    while (fgets(linha, sizeof(linha), entrada) != NULL) {
        char *nome, *telefone, *curso, *nota_str; 
        float notas[10]; 

        nome = strtok(linha, ",");		//strtok é usada para dividir a linha em campos usando a vírgula como delimitador.
        telefone = strtok(NULL, ",");
        curso = strtok(NULL, ",");
        
        int numNotas = 0;
        float nota;
        nota_str = strtok(NULL, ",");
        while (nota_str != NULL) {
            nota = atof(nota_str);
            notas[numNotas++] = nota;
            nota_str = strtok(NULL, ",");
        }

        printf("%s | %s | %s |", nome, telefone, curso);         //Aqui resultado incial
        for (int i = 0; i < numNotas; i++) {
            printf(" %.1f", notas[i]);
        }
        printf("\n");

        
        float media = calcularMedia(notas, numNotas);			// Calcular a média das notas

        
        const char *situacao = (media >= 7.0) ? "APROVADO" : "REPROVADO"; 		// Determinar a situação do aluno

        
        fprintf(saida, "%s, %.2f, %s\n", nome, media, situacao);	// Mostra o resultado na saida
    }

    fclose(entrada);
    fclose(saida);

    printf("\nResultados finais em 'SituacaoFinal.csv':\n");  // Aqui resultado final
    printf("Nome do Aluno | Média | Situação\n");

    saida = fopen("SituacaoFinal.csv", "r");
    if (saida == NULL) {
        printf("Erro ao abrir o arquivo 'SituacaoFinal.csv'.\n");
        return 1;
    }

    while (fgets(linha, sizeof(linha), saida) != NULL) {
        printf("%s\n", linha);
    }

    fclose(saida);

    return 0;
}
