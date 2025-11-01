#include <stdio.h>

/* Estrutura para armazenar cada carta */
typedef struct {
    char estado;                  
    char codigo[4];               
    char nomeCidade[100];
    unsigned long int populacao;  
    float area;                   
    float pib;                    
    int pontosTuristicos;
    float densidade;              
    float pibPerCapita;           
    float superPoder;             
} Carta;

/* Calcula derivados */
void calcularDerivados(Carta *c) {
    c->densidade = (float)c->populacao / c->area;
    c->pibPerCapita = (c->pib * 1000000000.0f) / (float)c->populacao;

    double soma = 0.0;
    soma += (double)c->populacao;
    soma += (double)c->area;
    soma += (double)(c->pib * 1000000000.0f);
    soma += (double)c->pontosTuristicos;
    soma += (double)c->pibPerCapita;
    soma += (double)(1.0 / c->densidade);
    c->superPoder = (float)soma;
}

/* Retorna valor do atributo escolhido */
float valorAtributo(const Carta *c, int escolha) {
    switch (escolha) {
        case 1: return (float)c->populacao;
        case 2: return c->area;
        case 3: return c->pib;
        case 4: return (float)c->pontosTuristicos;
        case 5: return c->densidade;
        case 6: return c->pibPerCapita;
        case 7: return c->superPoder;
        default: return 0.0f;
    }
}

/* Retorna o nome do atributo */
const char* nomeAtributo(int escolha) {
    switch (escolha) {
        case 1: return "População";
        case 2: return "Área (km²)";
        case 3: return "PIB (bilhões)";
        case 4: return "Pontos Turísticos";
        case 5: return "Densidade Demográfica (hab/km²)";
        case 6: return "PIB per Capita (reais)";
        case 7: return "Super Poder";
        default: return "Atributo Desconhecido";
    }
}

int main() {
    Carta c1 = {'A', "A01", "São Paulo", 12325000, 1521.11f, 699.28f, 50};
    Carta c2 = {'B', "B02", "Rio de Janeiro", 6748000, 1200.25f, 300.50f, 30};

    /* Cálculos */
    calcularDerivados(&c1);
    calcularDerivados(&c2);

    /* Exibição inicial */
    printf("=== CARTAS CADASTRADAS ===\n\n");

    printf("Carta 1:\n");
    printf("Estado: %c\nCódigo: %s\nCidade: %s\n", c1.estado, c1.codigo, c1.nomeCidade);
    printf("População: %lu\nÁrea: %.2f km²\nPIB: %.2f bilhões\n", c1.populacao, c1.area, c1.pib);
    printf("Pontos Turísticos: %d\nDensidade: %.2f hab/km²\nPIB per Capita: %.2f reais\nSuper Poder: %.2f\n\n",
           c1.pontosTuristicos, c1.densidade, c1.pibPerCapita, c1.superPoder);

    printf("Carta 2:\n");
    printf("Estado: %c\nCódigo: %s\nCidade: %s\n", c2.estado, c2.codigo, c2.nomeCidade);
    printf("População: %lu\nÁrea: %.2f km²\nPIB: %.2f bilhões\n", c2.populacao, c2.area, c2.pib);
    printf("Pontos Turísticos: %d\nDensidade: %.2f hab/km²\nPIB per Capita: %.2f reais\nSuper Poder: %.2f\n\n",
           c2.pontosTuristicos, c2.densidade, c2.pibPerCapita, c2.superPoder);

    /* Menu */
    printf("=== Escolha de Atributos ===\n");
    printf("1 - População\n2 - Área (km²)\n3 - PIB (bilhões)\n4 - Pontos Turísticos\n");
    printf("5 - Densidade Demográfica (menor vence)\n6 - PIB per Capita (reais)\n7 - Super Poder\n\n");

    int escolha1 = 0, escolha2 = 0;

    printf("Escolha o PRIMEIRO atributo (1 a 7): ");
    scanf("%d", &escolha1);

    if (escolha1 < 1 || escolha1 > 7) {
        printf("Opção inválida. Encerrando.\n");
        return 1;
    }

    printf("\nAgora escolha o SEGUNDO atributo (diferente do primeiro):\n");

    for (int i = 1; i <= 7; i++) {
        if (i != escolha1)
            printf("%d - %s\n", i, nomeAtributo(i));
    }

    printf("\nEscolha: ");
    scanf("%d", &escolha2);

    if (escolha2 == escolha1 || escolha2 < 1 || escolha2 > 7) {
        printf("Opção inválida. Encerrando.\n");
        return 1;
    }

    /* Valores */
    float c1_attr1 = valorAtributo(&c1, escolha1);
    float c2_attr1 = valorAtributo(&c2, escolha1);
    float c1_attr2 = valorAtributo(&c1, escolha2);
    float c2_attr2 = valorAtributo(&c2, escolha2);

    /* Comparações */
    int vencedor1 = (escolha1 == 5) ? ((c1_attr1 < c2_attr1) ? 1 : 0) : ((c1_attr1 > c2_attr1) ? 1 : 0);
    int vencedor2 = (escolha2 == 5) ? ((c1_attr2 < c2_attr2) ? 1 : 0) : ((c1_attr2 > c2_attr2) ? 1 : 0);

    float somaC1 = c1_attr1 + c1_attr2;
    float somaC2 = c2_attr1 + c2_attr2;
    int vencedorSoma = (somaC1 > somaC2) ? 1 : (somaC1 < somaC2 ? 0 : -1);

    /* Resultado */
    printf("\n=== RESULTADO ===\n\n");
    printf("Atributo 1: %s\n", nomeAtributo(escolha1));
    printf("  %s: %.2f | %s: %.2f → Carta %d venceu\n\n",
           c1.nomeCidade, c1_attr1, c2.nomeCidade, c2_attr1, vencedor1 ? 1 : 2);

    printf("Atributo 2: %s\n", nomeAtributo(escolha2));
    printf("  %s: %.2f | %s: %.2f → Carta %d venceu\n\n",
           c1.nomeCidade, c1_attr2, c2.nomeCidade, c2_attr2, vencedor2 ? 1 : 2);

    printf("Soma dos atributos:\n");
    printf("  %s: %.2f\n  %s: %.2f\n", c1.nomeCidade, somaC1, c2.nomeCidade, somaC2);

    (vencedorSoma == -1)
        ? printf("\nResultado final: Empate!\n")
        : printf("\nResultado final: %s venceu!\n",
                 vencedorSoma ? c1.nomeCidade : c2.nomeCidade);

    return 0;
}

