#include <stdio.h>
#include <string.h>
#include <time.h>
#define MAX 1000

typedef struct{
	int codigo;
	char nome[20];
}registro;

typedef struct{
	registro carro[MAX];
	int tamanho;
}tabela;

void insere(tabela *t);
void ordenar(tabela *t);
void desempenho(tabela *t);
int sequencial(int chave, tabela *t, int *contsequen);
int binaria(int chave, tabela *t, int *contbin);
int repeticao(int cod, tabela *t);
void remover(tabela *t);
int pesquisa (char nome[], tabela *t);
void insercao(tabela *t);

int main (){
	
	srand(time(NULL));
    tabela t;
    int qtd = 0, cod = 0, comp;
	char nome[20];	
	//questao02
    insere(&t);
	ordenar(&t);
	//questao03
	desempenho(&t);
    //questao04
    printf("\nDigite o codigo que deseja buscar: ");
    scanf("%d", &cod);
    qtd = repeticao(cod, &t);
    printf("No codigo %i se repete %i vez(es)\n\n", cod, qtd);
    //questao05
    remover(&t);
    //questao06
    printf("Digite o nome que deseja verificar se existe: \n");
    scanf("%s", nome);
    comp = pesquisa(nome, &t);
    if(comp == 0) {
        printf("Ja existe carro com o nome digitado\n");
    } else {
        printf("Nao existe carro com o nome digitado\n");
    }
	//questao07
    insercao(&t);
    return 0;
	
}

void insere(tabela *t){
	int i;
	for(i=0;i<MAX;i++){
		t->carro[i].codigo = rand() % 1001; 
		strcpy(t->carro[i].nome, "GOL");  
	}
}

void ordenar(tabela *t) {
    int i, j, aux;
	for (i=0; i<MAX-1; i++){
		for (j=1; j<MAX-i; j++){
			if (t->carro[j].codigo < t->carro[j-1].codigo){
				aux = t->carro[j].codigo;
				t->carro[j].codigo = t->carro[j-1].codigo;
				t->carro[j-1].codigo = aux;
			}
		}	
	}
}

void desempenho(tabela *t){
	int chave, seq, bin, contbin = 0, contsequen = 0;
 
    for(int j = 0; j < 100; j++) {
        chave = rand() % 1000 + 1;
        //chamando a pesquisa sequencial
        seq = sequencial(chave, t, &contsequen);
        //chamando a pesquisa binaria
        bin = binaria(chave, t, &contbin);

    }
    printf("Pesquisa sequencial: a media de registros percorridos por pesquisa eh %i\n", contsequen/100);
    printf("Pesquisa binaria: a media de registros percorridos por pesquisa eh %i\n", contbin/100);
	/*Para o algoritmo de pesquisa sequencial a media de registros percorridos é de (n+1)/2, enquanto a
	media de registros percorridos pelo algoritmo de busca binaria é de (Log n). Ambos os algoritmos 
	apresentaram resultados próximos aos valores medios esperados.*/
}

int sequencial(int chave, tabela *t, int *contsequen){
	int j;

    t->carro[0].codigo = chave;
    for( j = MAX; t->carro[j].codigo != chave; j--) {
        *contsequen += 1;
    }
    if(t->carro[0].codigo == chave) {
        t->carro[0].codigo = 0;
    }
    return j;
}

int binaria(int chave, tabela *t, int *contbin) {
    int i, esq, dir;
    t->tamanho = 1000;
    if(t->tamanho == 0) {
        return 0;
    }
    esq = 1;
    t->tamanho = 1000;
    dir = t->tamanho;
    do {
        *contbin += 1;
        i = (esq + dir) / 2;
        if (chave > t->carro[i].codigo) {
            esq = i + 1;

        } else {
            dir = i - 1;
        }

    } while((chave != t->carro[i].codigo) && (esq <= dir));
    if (chave == t->carro[i].codigo) {
        return i;
    }
    else {
        return 0;
    }
}

int repeticao(int cod, tabela *t){
	int qtd = 0, i = 0;

    for(i = 0; i < t->tamanho; i++) {
        if(t->carro[i].codigo == cod) {
            qtd += 1;
        }
    }
    return qtd;
}

void remover(tabela *t){
	int codigo, i, qtd, retirado = 0;
    printf("\nDigite o codigo a ser retirado: ");
    scanf("%d", &codigo);

    for(i = 0; i < t->tamanho; i++) {
        if(t->carro[i].codigo == codigo) {
            t->carro[i].codigo = t->carro[t->tamanho].codigo;
            t->tamanho = t->tamanho - 1;
            retirado += 1;
        }
    }
    printf("%i registros com o codigo %i foram removidos\n", retirado, codigo);
    qtd = repeticao(codigo, t);
    printf("O codigo %i se repete %i vez(es)\n\n", codigo, qtd);
}

int pesquisa (char nomeCarro[], tabela *t){
	int j, comp;

    for( j = MAX; j > 0; j--) {
        comp = strcmp(t->carro[j].nome, nomeCarro);
        if(comp == 0) {
            return comp;
        }
    }

    return comp;
}

void insercao(tabela *t){
	int registro = 0, comp, confirma;
    char nome[20];
    printf("\nDigite o codigo e em seguida o nome do veiculo\n");
    scanf("%d %s", &registro, nome);

    comp = pesquisa(nome, t);
    if(comp == 0) {
        printf("Existem registros desse veiculo. Digite 0 para cancelar e 1 para confirmar a insercao:\n");
        scanf("%d", &confirma);
    } else {
        printf("Nao existem registros desse veiculo. Digite 0 para cancelar e 1 para confirmar a insercao:\n");
        scanf("%d", &confirma);
    }
    switch(confirma) {
    case 0:
        printf("\nNao foi registrado\n");
        break;
    case 1:

        if(t->tamanho == MAX) {
            printf("Erro: tabela cheia\n");
        } else {
            t->tamanho += 1;
            t->carro[t->tamanho].codigo = registro;
            strcpy(t->carro[t->tamanho].nome, nome);
            printf("\nCodigo do carro: %d\nNome do carro: %s\n", registro, t->carro[t->tamanho].nome);
            break;
        }
    }
}

