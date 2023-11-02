#include <stdio.h>
#include <stdlib.h>

// Definição do tipo de estrutura para cadastro de produtos
typedef struct
{
  char nome[40];
  int quantidade;
  float valorUnitario;
  char tipo;
} Produto;

// Protótipos das funções
int cadastrarQuantidade();
void cadastrarTipo(char *tipo);
void cadastrarValorUnitario(Produto *listaProd);
void cadastrarNome(char *nome);
void cadastrarProduto(Produto *listaProd, int quantidade);
void exibirProdutos(Produto *listaProd, int quantidade);
void exibirProdutosPorTipo(Produto *listaProd, int quantidade, char tipo, float *valorTotal, int *quantidadeProdutos);

int main()
{
  int quantidadeProdutos = 0;
  Produto *listaProd = NULL;
  char opcao;

  do
  {
    printf("Menu:\n");
    printf("A - Preencher dados\n");
    printf("B - Exibir dados dos produtos\n");
    printf("C - Exibir dados dos produtos por tipo\n");
    printf("D - Finalizar\n");
    printf("Escolha uma opção: ");
    scanf(" %c", &opcao);

    switch (opcao)
    {
    case 'A':
      if (listaProd != NULL)
      {
        free(listaProd); // Liberar a memória se já existir
      }
      quantidadeProdutos = cadastrarQuantidade();
      listaProd = (Produto *)malloc(quantidadeProdutos * sizeof(Produto));
      cadastrarProduto(listaProd, quantidadeProdutos);
      break;
    case 'B':
      exibirProdutos(listaProd, quantidadeProdutos);
      break;
    case 'C':
      printf("Informe o tipo (P para Perecível, N para Não perecível): ");
      char tipo;
      scanf(" %c", &tipo);
      float valorTotal = 0;
      int qtdProdutos = 0;
      exibirProdutosPorTipo(listaProd, quantidadeProdutos, tipo, &valorTotal, &qtdProdutos);
      if (qtdProdutos > 0)
      {
        printf("Média de preço dos produtos do tipo %c: %.2f\n", tipo, valorTotal / qtdProdutos);
      }
      else
      {
        printf("Nenhum produto do tipo %c encontrado.\n", tipo);
      }
      break;
    case 'D':
      free(listaProd); // Liberar a memória antes de sair
      break;
    default:
      printf("Opção inválida!\n");
    }
  } while (opcao != 'D');

  return 0;
}

int cadastrarQuantidade()
{
  int quantidade;
  do
  {
    printf("Informe a quantidade de produtos a serem cadastrados: ");
    scanf("%d", &quantidade);
    if (quantidade <= 0)
    {
      printf("A quantidade deve ser um valor positivo.\n");
    }
  } while (quantidade <= 0);
  return quantidade;
}

void cadastrarTipo(char *tipo)
{
  do
  {
    printf("Informe o tipo (P para Perecível, N para Não perecível): ");
    scanf(" %c", tipo);
    if (*tipo != 'P' && *tipo != 'N')
    {
      printf("Tipo inválido! Use P para Perecível ou N para Não perecível.\n");
    }
  } while (*tipo != 'P' && *tipo != 'N');
}

void cadastrarValorUnitario(Produto *listaProd)
{
  do
  {
    printf("Informe o valor unitário do produto: ");
    scanf("%f", &listaProd->valorUnitario);
    if (listaProd->valorUnitario < 0)
    {
      printf("O valor unitário deve ser um valor positivo.\n");
    }
  } while (listaProd->valorUnitario < 0);
}

void cadastrarNome(char *nome)
{
  printf("Informe o nome do produto: ");
  scanf(" %39s", nome); // Limita o tamanho do nome a 39 caracteres
}

void cadastrarProduto(Produto *listaProd, int quantidade)
{
  for (int i = 0; i < quantidade; i++)
  {
    printf("Produto %d:\n", i + 1);
    cadastrarNome(listaProd[i].nome);
    listaProd[i].quantidade = cadastrarQuantidade();
    cadastrarTipo(&listaProd[i].tipo);
    cadastrarValorUnitario(&listaProd[i]);
  }
}

void exibirProdutos(Produto *listaProd, int quantidade)
{
  for (int i = 0; i < quantidade; i++)
  {
    printf("Produto %d:\n", i + 1);
    printf("Nome: %s\n", listaProd[i].nome);
    printf("Quantidade: %d\n", listaProd[i].quantidade);
    printf("Valor Unitário: %.2f\n", listaProd[i].valorUnitario);
    printf("Tipo: %c\n", listaProd[i].tipo);
  }
}

void exibirProdutosPorTipo(Produto *listaProd, int quantidade, char tipo, float *valorTotal, int *quantidadeProdutos)
{
  for (int i = 0; i < quantidade; i++)
  {
    if (listaProd[i].tipo == tipo)
    {
      printf("Produto %d:\n", i + 1);
      printf("Nome: %s\n", listaProd[i].nome);
      printf("Quantidade: %d\n", listaProd[i].quantidade);
      printf("Valor Unitário: %.2f\n", listaProd[i].valorUnitario);
      printf("Tipo: %c\n", listaProd[i].tipo);

      *valorTotal += listaProd[i].valorUnitario * listaProd[i].quantidade;
      (*quantidadeProdutos)++;
    }
  }
}