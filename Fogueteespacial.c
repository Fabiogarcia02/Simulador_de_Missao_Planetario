#include <stdio.h>
#include <string.h>

#define MAX_MISSOES 10

float distancias[MAX_MISSOES];
float angulos[MAX_MISSOES];
int planetas[MAX_MISSOES];
int sucesso[MAX_MISSOES];
int totalMissoes = 0;

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

void calcular_angulo_trajetoria() {
    float distancia;
    printf("Digite a distância até o destino (em mil km): ");
    scanf("%f", &distancia);
    float angulo = calcular_angulo(distancia);
    printf("🚀 Distância até o destino: %.2f mil km\n", distancia);
    printf("🛰️ Ângulo ideal de lançamento: %.2f graus\n", angulo);
}

float obter_gravidade(int opcao) {
    switch(opcao) {
        case 1: return 3.7;
        case 2: return 24.8;
        case 3: return 10.4;
        default: return 0.0;
    }
}

void calcular_gravidade_planeta() {
    int opcao;
    printf("Escolha o planeta:\n1. Marte\n2. Júpiter\n3. Saturno\nOpção: ");
    scanf("%d", &opcao);

    float gravidade = obter_gravidade(opcao);
    if (gravidade == 0.0) {
        printf("❌ Opção inválida.\n");
    } else {
        printf("🌍 Gravidade: %.2f m/s²\n", gravidade);
        if (gravidade > 15) {
            printf("⚠️ Gravidade forte. Aumente o empuxo.\n");
        } else {
            printf("⚖️ Gravidade moderada.\n");
        }
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
    printf("Escolha o planeta:\n1. Marte\n2. Júpiter\n3. Saturno\nOpção: ");
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
               i + 1, distancias[i], angulos[i], planetas[i],
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
    for (int i = 0; i < totalMissoes - 1; i++) {
        for (int j = 0; j < totalMissoes - i - 1; j++) {
            if (distancias[j] > distancias[j + 1]) {
                float tempDist = distancias[j];
                distancias[j] = distancias[j + 1];
                distancias[j + 1] = tempDist;

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

    printf("✅ Missões ordenadas por distância.\n");
}

void simulacao_decisao() {
    int matriz[3][2] = {
        {10, 500},
        {-5, 800},
        {5, 200}
    };

    int escolha;
    printf("🛑 Situação crítica! Escolha uma ação:\n");
    printf("1. Ativar escudos\n2. Lançar propulsores\n3. Enviar sinal\nOpção: ");
    scanf("%d", &escolha);

    if (escolha >= 1 && escolha <= 3) {
        int i = escolha - 1;
        printf("🎯 Impacto: %+d%%\n🔋 Energia: %d\n", matriz[i][0], matriz[i][1]);

        if (matriz[i][0] >= 10)
            printf("✅ Decisão excelente!\n");
        else if (matriz[i][0] > 0)
            printf("☑️ Decisão razoável.\n");
        else
            printf("⚠️ Complicações na missão.\n");
    } else {
        printf("❌ Opção inválida.\n");
    }
}


float calcularMediaPonderadaSucesso(int vetorSucesso[], float vetorDistancia[], int total) {
    float somaPesos = 0, somaPonderada = 0;
    for (int i = 0; i < total; i++) {
        somaPesos += vetorDistancia[i];
        somaPonderada += vetorSucesso[i] * vetorDistancia[i];
    }
    if (somaPesos == 0) return 0;
    return (somaPonderada / somaPesos) * 100;
}

void media_ponderada_sucesso() {
    if (totalMissoes == 0) {
        printf("⚠️ Nenhuma missão registrada.\n");
        return;
    }
    float media = calcularMediaPonderadaSucesso(sucesso, distancias, totalMissoes);
    printf("📊 Média ponderada de sucesso: %.2f%%\n", media);

    if (media >= 80)
        printf("✅ Ótima eficiência em missões longas.\n");
    else if (media >= 50)
        printf("⚠️ Desempenho regular, há margem para melhorias.\n");
    else
        printf("🚨 Preocupante: muitas falhas em missões críticas.\n");
}


int energiaExponencial(int n) {
    if (n == 1) return 100;
    return (1 << (n - 1)) * 100 + energiaExponencial(n - 1);
}

void energia_em_cadeia() {
    int n;
    printf("🔌 Quantos sistemas na cadeia? ");
    scanf("%d", &n);
    int energia = energiaExponencial(n);
    printf("⚡ Energia total necessária: %d unidades\n", energia);

    if (energia <= 100000)
        printf("✅ Energia dentro do limite, missão segura.\n");
    else
        printf("🚨 Alerta: sobrecarga energética! Missão comprometida.\n");
}

// ====================== MENU PRINCIPAL ==========================
int main() {
    if (!autenticar_usuario()) return 0;

    int opcao;
    do {
        printf("\n=== MENU PRINCIPAL ===\n");
        printf("1. Simular Queima de Combustível\n");
        printf("2. Calcular Ângulo de Trajetória\n");
        printf("3. Calcular Gravidade em Planeta\n");
        printf("4. Registrar Missão\n");
        printf("5. Ver Histórico de Missões\n");
        printf("6. Calcular Energia para Emergência (Recursivo)\n");
        printf("7. Ordenar Missões por Distância\n");
        printf("8. Missão Final - Simulação de Decisão\n");
        printf("9. Calcular Média Ponderada de Sucesso\n");
        printf("10. Calcular Energia em Cadeia (Recursivo)\n");
        printf("11. Sair\n");
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
            case 9: media_ponderada_sucesso(); break;
            case 10: energia_em_cadeia(); break;
            case 11: printf("👋 Encerrando o programa.\n"); break;
            default: printf("❌ Opção inválida.\n");
        }

    } while (opcao != 11);

    return 0;
}
