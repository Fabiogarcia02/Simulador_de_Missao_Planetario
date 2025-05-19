#include <stdio.h>
#include <string.h>

// Definindo o número máximo de missões
#define MAX_MISSOES 10

// Vetores paralelos para armazenar informações sobre missões
float distancias[MAX_MISSOES];
float angulos[MAX_MISSOES];
int planetas[MAX_MISSOES];
int sucesso[MAX_MISSOES];
int totalMissoes = 0;

// Função para autenticação do usuário
int autenticar_usuario() {
    const char senha_correta[] = "orbita2025";
    char senha_digitada[50];
    int tentativas = 3;

    while (tentativas > 0) {
        printf("Digite a senha de acesso: ");
        scanf("%49s", senha_digitada);

        if (strcmp(senha_digitada, senha_correta) == 0) {
            printf("✅ Acesso permitido. Bem-vindo(a) ao sistema!\n");
            return 1;
        } else {
            tentativas--;
            printf("❌ Senha incorreta. Tentativas restantes: %d\n", tentativas);
        }
    }

    printf("🚫 Número máximo de tentativas excedido. Encerrando o programa.\n");
    return 0;
}

// Função para simular a queima de combustível
void simular_queima_combustivel() {
    int combustivel = 1000;
    printf("🚀 Iniciando simulação de queima de combustível...\n");

    while (combustivel > 0) {
        combustivel -= 50;
        printf("🔥 Combustível restante: %d litros\n", combustivel);

        if (combustivel == 500) {
            printf("🛸 Atingindo atmosfera superior...\n");
        } else if (combustivel == 100) {
            printf("🛰️ Quase em órbita...\n");
        }
    }

    printf("💥 Combustível esgotado. Nave em órbita.\n");
}

float calcular_angulo(float distancia) {
    return distancia * 0.42 + 18;
}

void exibir_angulo(float distancia) {
    float angulo = calcular_angulo(distancia);
    printf("🚀 Distância até o destino: %.2f mil km\n", distancia);
    printf("🛰️ Ângulo ideal de lançamento: %.2f graus\n", angulo);
}

void calcular_angulo_trajetoria() {
    float distancia;
    printf("Digite a distância até o destino (em mil km): ");
    scanf("%f", &distancia);
    exibir_angulo(distancia);
}

float obter_gravidade(int opcao) {
    switch(opcao) {
        case 1: return 3.7;
        case 2: return 24.8;
        case 3: return 10.4;
        default: return 0.0;
    }
}

void exibir_recomendacao(float gravidade) {
    printf("🌍 Gravidade: %.2f m/s²\n", gravidade);
    if (gravidade > 15) {
        printf("⚠️ Gravidade forte. Aumente o empuxo.\n");
    } else {
        printf("⚖️ Gravidade moderada.\n");
    }
}

void calcular_gravidade_planeta() {
    int opcao;
    printf("Escolha o planeta:\n");
    printf("1. Marte\n2. Júpiter\n3. Saturno\nEscolha uma opção (1, 2, 3): ");
    scanf("%d", &opcao);

    float gravidade = obter_gravidade(opcao);
    if (gravidade == 0.0) {
        printf("❌ Opção inválida.\n");
    } else {
        exibir_recomendacao(gravidade);
    }
}

void registrar_missao() {
    if (totalMissoes >= MAX_MISSOES) {
        printf("⚠️ Limite de missões atingido.\n");
        return;
    }

    float distancia;
    int planeta;
    printf("🚀 Registro de nova missão:\n");
    printf("Distância (km): ");
    scanf("%f", &distancia);
    printf("Escolha o planeta de destino:\n1. Marte\n2. Júpiter\n3. Saturno\nOpção: ");
    scanf("%d", &planeta);

    distancias[totalMissoes] = distancia;
    planetas[totalMissoes] = planeta;
    angulos[totalMissoes] = calcular_angulo(distancia);
    sucesso[totalMissoes] = (distancia > 500) ? 1 : 0;

    totalMissoes++;
    printf("✅ Missão registrada com sucesso.\n");
}

void ver_historico_missoes() {
    printf("📜 Histórico de Missões:\n");
    for (int i = 0; i < totalMissoes; i++) {
        printf("Missão %d - Distância: %.2f km, Ângulo: %.2f, Planeta: %d, Status: %s\n",
               i + 1,
               distancias[i],
               angulos[i],
               planetas[i],
               sucesso[i] == 1 ? "Sucesso" : "Fracasso");
    }
}

int calcular_energia_emergencia(int sistemas) {
    if (sistemas == 1) return 100;
    return 100 + calcular_energia_emergencia(sistemas - 1);
}

void energia_emergencia() {
    int n;
    printf("🔌 Quantos sistemas precisam de energia? ");
    scanf("%d", &n);
    int energia = calcular_energia_emergencia(n);
    printf("⚡ Energia total necessária: %d unidades\n", energia);
}

void ordenar_missoes() {
    printf("📜 Histórico de Missões Antes da Ordenação:\n");
    ver_historico_missoes();

    for (int i = 0; i < totalMissoes - 1; i++) {
        for (int j = 0; j < totalMissoes - i - 1; j++) {
            if (distancias[j] > distancias[j + 1]) {
                float tempDistancia = distancias[j];
                distancias[j] = distancias[j + 1];
                distancias[j + 1] = tempDistancia;

                float tempAngulo = angulos[j];
                angulos[j] = angulos[j + 1];
                angulos[j + 1] = tempAngulo;

                int tempPlaneta = planetas[j];
                planetas[j] = planetas[j + 1];
                planetas[j + 1] = tempPlaneta;

                int tempSucesso = sucesso[j];
                sucesso[j] = sucesso[j + 1];
                sucesso[j + 1] = tempSucesso;
            }
        }
    }

    printf("✅ Missões ordenadas por distância com sucesso.\n");
    printf("📜 Histórico de Missões Após a Ordenação:\n");
    ver_historico_missoes();
}

// 🔁 NOVA função simulacao_decisao com matriz
void simulacao_decisao() {
    // Matriz 3x2: [impacto no sucesso (%), consumo de energia (unidades)]
    int matriz[3][2] = {
        {10, 500},   // Ativar escudos
        {-5, 800},   // Lançar propulsores
        {5, 200}     // Enviar sinal
    };

    int escolha;
    printf("🛑 Alerta! Situação crítica detectada!\n");
    printf("Escolha uma ação de emergência:\n");
    printf("1. Ativar escudos\n");
    printf("2. Lançar propulsores\n");
    printf("3. Enviar sinal\n");
    printf("Opção: ");
    scanf("%d", &escolha);

    if (escolha >= 1 && escolha <= 3) {
        int indice = escolha - 1;
        int impacto = matriz[indice][0];
        int energia = matriz[indice][1];

        printf("\n📊 Resultado da ação:\n");
        printf("🎯 Impacto no sucesso da missão: %+d%%\n", impacto);
        printf("🔋 Consumo de energia: %d unidades\n", energia);

        if (impacto >= 10) {
            printf("✅ Decisão excelente! Probabilidade de sucesso aumentou significativamente.\n");
        } else if (impacto > 0) {
            printf("☑️ Decisão razoável. Sucesso levemente favorecido.\n");
        } else {
            printf("⚠️ A decisão causou complicações. Sucesso da missão comprometido.\n");
        }
    } else {
        printf("❌ Opção inválida.\n");
    }
}

// Função principal
int main() {
    if (!autenticar_usuario()) {
        return 0;
    }

    int opcao;

    do {
        printf("\n===== SISTEMA DE CONTROLE DE MISSÕES ESPACIAIS =====\n");
        printf("--- MENU PRINCIPAL ---\n");
        printf("1. Simular Queima de Combustível\n");
        printf("2. Calcular Ângulo de Trajetória\n");
        printf("3. Calcular Gravidade em Planeta\n");
        printf("4. Registrar Missão\n");
        printf("5. Ver Histórico de Missões\n");
        printf("6. Calcular Energia para Emergência (Recursivo)\n");
        printf("7. Ordenar Missões por Distância\n");
        printf("8. Missão Final - Simulação de Decisão\n");
        printf("9. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: simular_queima_combustivel(); break;
            case 2: calcular_angulo_trajetoria(); break;
            case 3: calcular_gravidade_planeta(); break;
            case 4: registrar_missao(); break;
            case 5: ver_historico_missoes(); break;
            case 6: energia_emergencia(); break;
            case 7: ordenar_missoes(); break;
            case 8: simulacao_decisao(); break;
            case 9: printf("👋 Encerrando o programa. Até logo!\n"); break;
            default: printf("❌ Opção inválida. Tente novamente.\n");
        }

    } while (opcao != 9);

    return 0;
}
