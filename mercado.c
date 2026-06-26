#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "tipo.h"

/* Menu principal do Mercado Agrícola Digital. */
void mostrarPortalMercado(void) {
    printf("\n==========================================================");
    printf("\n|              MERCADO AGRICOLA DIGITAL 2026             |");
    printf("\n==========================================================");
    printf("\n|  [1] Entrar na minha conta                             |");
    printf("\n|      Acesso rápido para cliente ou vendedor            |");
    printf("\n|  [2] Criar nova conta                                  |");
    printf("\n|      Registe-se como cliente ou vendedor               |");
    printf("\n|  [3] Explorar catálogo sem entrar                      |");
    printf("\n|      Consulte produtos disponíveis no mercado          |");
    printf("\n|  [0] Encerrar!				         |");
    printf("\n==========================================================");
}
/* Realiza o login do utilizador, autentica as credenciais e abre o menu adequado. */
int entrarNoSistema(void) {
    char email[50];
    char senha[30];
    Usuario usuario;
    printf("\n=== ACESSO AO SISTEMA ===");
    printf("\nEmail: ");
    limparBufferEntrada();
    scanf(" %49[^\n]", email);
    printf("Senha: ");
    limparBufferEntrada();
    scanf(" %29[^\n]", senha);
    if (autenticarUsuario(email, senha, &usuario)) {
        printf("\n[Acesso] Bem-vindo(a), %s!\n", usuario.nome);

        if (strcmp(usuario.tipo, "vendedor") == 0) {
            menuVendedor();
        } else {
            menuCliente();
        }
        return 1;
    }
    printf("\n[FALHA] Email ou senha inválidos.\n");
    return 0;
}
/* Ponto de entrada do programa, exibe o portal e controla o ciclo principal. */
int main() {
    setlocale(LC_ALL, "Portuguese");
    int opcao;
    carregarUsuarios(); /* Carrega os utilizadores do ficheiro para a memória. */
    carregarProdutos(&listaProdutos); /* Carrega os produtos do ficheiro para a memória. */
    carregarStocks(); /* Carrega os stocks do ficheiro para a memória. */

    do {
        mostrarPortalMercado();
        printf("\n\nEscolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                entrarNoSistema();
                break;
            case 2:
                registrarUsuario();
                break;
            case 3:
                listarCatalogoMercado();
                break;
            case 0:
                printf("\nMercado encerrado.\n");
                break;
            default:
                printf("\n[FALHA] Entrada inválida. Escolha 1, 2, 3 ou 0.\n");
        }
    } while (opcao != 0);

    /* Persiste o estado atual dos produtos e utilizadores ao encerrar o programa. */
    guardarProdutos(listaProdutos); /* Guarda os produtos no ficheiro. */
    guardarUsuarios(); /* Guarda os utilizadores no ficheiro. */
    guardarStocks(); /* Guarda os stocks no ficheiro. */

    return 0;
}
