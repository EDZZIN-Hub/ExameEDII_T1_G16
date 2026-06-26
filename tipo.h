/* Define um produto do mercado agrícola digital. */
typedef struct {
    int codigo;
    char nome[50];
    char categoria[30];
    float preco;
    int quantidade;
} Produto;
/* Nó da AVL que armazena um produto e mantém altura para balanceamento. */
typedef struct no {
    Produto produto;
    int altura;
    struct no *esq;
    struct no *dir;
} No;
/* Registo de utilizador, com credenciais e inventário próprio. */
typedef struct {
    char nome[50];
    char email[50];
    char senha[30];
    char tipo[20];
    No *inventario;
} Usuario;
/* Nó de lista ligada para itens do carrinho de compras. */
typedef struct ItemCarrinho {
    Produto produto;
    int quantidade;
    char vendedorEmail[50];
    struct ItemCarrinho *prox;
} ItemCarrinho;
/* Estrutura de bucket encadeado para indexação rápida de produtos. */
typedef struct HashNo HashNo;
/* Cria um produto a partir da entrada do utilizador. */
Produto criarProduto(void);
/* Estruturas globais partilhadas pelos menus do sistema. */
extern No *listaProdutos;          /* Raiz da AVL de produtos. */
extern ItemCarrinho *carrinho;     /* Lista ligada do carrinho atual. */
extern HashNo **tabelaHash;        /* Tabela hash para pesquisa rÃ¡pida. */
extern int hashTamanho;            /* NÃºmero de posiÃ§Ãµes da tabela hash. */
extern int hashQuantidade;         /* Quantidade de elementos atualmente indexados. */
extern Usuario *usuarios;          /* Lista dinamica de utilizadores registados. */
extern int totalUsuarios;          /* Número de utilizadores atualmente guardados. */
extern int capacidadeUsuarios;     /* Capacidade atual da lista de utilizadores. */
extern int indiceUsuarioAtual;     /* Índice do utilizador autenticado na sessão actual. */
void limparBufferEntrada(void);   /* Limpa o buffer de entrada para leituras futuras. */
void mostrarTitulo(const char *titulo); /* Mostra um título formatado no ecrã. */
void mostrarProdutoFormatado(const Produto *produto); /* Mostra os detalhes de um produto. */
int inicializarHash(int tamanho); /* Inicializa a tabela hash com o tamanho informado. */
int garantirHashInicializada(void); /* Garante que a tabela hash está pronta para uso. */
int maximo(int a, int b); /* Retorna o maior de dois inteiros. */
int indiceHashComTamanho(int codigo, int tamanho); /* Calcula o índice hash para um código e tamanho específicos. */
int alturaNo(No *no); /* Retorna a altura de um nÃ³ AVL. */
int fatorBalanceamento(No *no); /* Retorna o fator de balanceamento de um nó AVL. */
No *criarNoAVL(Produto p); /* Cria um novo nó AVL com o produto informado. */
No *rotacaoDireita(No *y); /* Executa rotação direita em um nó AVL. */
No *rotacaoEsquerda(No *x); /* Executa rotação esquerda em um nó AVL. */
int indiceHash(int codigo); /* Calcula o Ã­ndice hash para o código usando o tamanho atual. */
int redimensionarHash(int novoTamanho); /* Redimensiona a tabela hash para um tamanho maior. */
void hashAtualizar(No *no); /* Insere ou atualiza a entrada na tabela hash. */
void hashRemover(int codigo); /* Remove a entrada da tabela hash pelo cÃ³digo. */
No *hashBuscar(int codigo); /* Pesquisa um produto na tabela hash pelo cÃ³digo. */
void limparHash(void); /* Limpa as entradas da tabela hash sem liberar sua estrutura. */
void libertarHash(void); /* Libera completamente a estrutura da tabela hash. */
No *menorNo(No *raiz); /* Retorna o menor nÃ³ em uma subÃ¡rvore AVL. */
No *balancearNo(No *raiz); /* Rebalanceia um nÃ³ AVL apÃ³s inserÃ§Ã£o ou remocao. */
No *inserirNoAVL(No *raiz, Produto p, No **noAlterado, int *novoProduto); /* Insere ou atualiza um produto na AVL. */
No *removerNoAVL(No *raiz, int codigo, int controlarHash); /* Remove um produto da AVL e atualiza a hash se necessÃ¡rio. */
void listarEmOrdem(No *raiz); /* Percorre a AVL em ordem crescente e mostra os produtos. */
void guardarEmOrdem(FILE *fp, No *raiz); /* Grava a AVL em ficheiro em ordem crescente. */
void libertarAVL(No *raiz); /* Libera a memória alocada pela AVL. */
void limparCarrinho(ItemCarrinho **carrinhoAtual); /* Remove todos os itens do carrinho. */
int quantidadeNoCarrinho(ItemCarrinho *carrinhoAtual, int codigo, const char *vendedorEmail); /* Retorna quantas unidades de um produto de um vendedor estao no carrinho. */
void inserirProduto(No **lista, Produto p); /* Insere ou atualiza um produto no catalogo global. */
void listarProdutos(No *lista); /* Lista produtos disponíveis no mercado. */
void listarCatalogoMercado(void); /* Lista os produtos do mercado agrupados por banca/vendedor. */
void listarBancas(void); /* Lista as bancas/vendedores cadastrados para selecção do cliente. */
int selecionarBanca(void); /* Permite ao cliente escolher uma banca antes de comprar. */
No *buscarProduto(No *lista, int codigo); /* Procura um produto na AVL por código. */
No *buscarProdutoNoMercado(int codigo, int *indiceVendedor); /* Procura um produto em todos os vendedores do mercado. */
void removerProduto(No **lista, int codigo); /* Remove um produto do catálogo global. */
void adicionarCarrinho(ItemCarrinho **carrinhoAtual, Produto produto, int quantidade, const char *vendedorEmail); /* Adiciona ou atualiza um item no carrinho. */
void mostrarCarrinho(ItemCarrinho *carrinhoAtual); /* Exibe o conteudo do carrinho e o total. */
void finalizarCompra(ItemCarrinho **carrinhoAtual); /* Finaliza a compra, regista a venda e atualiza o stock. */
void guardarProdutos(No *lista);			 /* Guarda os produtos do catÃ¡logo para ficheiro. */
void carregarProdutos(No **lista);			 /* Carrega produtos guardados do ficheiro*/	
void carregarUsuarios(void);                 /* Carrega os utilizadores do ficheiro para a memria. */
void guardarUsuarios(void);                  /* Guarda os utilizadores atuais para ficheiro. */
void guardarStocks(void);                    /* Guarda o stock de cada utilizador para ficheiro. */
void carregarStocks(void);                   /* Reconstroi os stocks a partir do ficheiro. */
void registrarUsuario(void);                 /* Regista um novo utilizador no sistema. */
void listarUsuarios(void);                   /* Mostra os utilizadores registados. */
void eliminarConta(void);                    /* Remove a conta do utilizador autenticado. */
void inserirProdutoNoInventarioAtual(Produto p); /* Regista um produto no stock do vendedor autenticado. */
void removerProdutoDoInventarioAtual(int codigo); /* Remove um produto do stock do vendedor autenticado. */
void listarInventarioAtual(void);           /* Mostra o stock do utilizador autenticado. */
No *buscarProdutoNoInventarioAtual(int codigo); /* Procura um produto no stock do utilizador autenticado. */
int existeUsuario(const char *email);        /* Verifica se um email ja existe. */
int autenticarUsuario(const char *email, const char *senha, Usuario *usuario); /* Valida credenciais de acesso. */
void menuCliente(void); 					 /*Menu cliente*/
void menuVendedor(void);				 	 /*Menu vendedor*/
