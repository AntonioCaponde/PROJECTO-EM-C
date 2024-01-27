#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>
#include<locale.h>
#include<math.h>
#include<time.h>
#include <string.h>
#include <ctype.h>


typedef struct conta{
	int numero_conta,codigo_cliente;
	float saldo;
	char estado[10];
}conta;

typedef struct pessoa{
	int codigo,telefone;
	char nome[40],BI[15],NIF[15];
	conta conta_do_cliente;

} Pessoa;

typedef struct no{
	Pessoa pessoa;
	struct no *proximo;
}No;

Pessoa cliente,cliente1;
No *encontrado,*minha_lista=NULL;
int tipo_de_cliente,codigo;
int codigo_do_cliente;

void inserir_no_inicio(No **lista, Pessoa p){
	No *novo=malloc(sizeof(No));
	if(novo){
		novo->pessoa=p;
		novo->proximo=*lista;
		*lista=novo;
	}
	else{
		printf("erro ao alocar memoria!\n");
	}
}
void inserir_no_fim(No **lista,Pessoa p){
	No *aux,*novo=malloc(sizeof(No));
	if(novo){
		novo->pessoa=p;
		novo->proximo=NULL;
		if(*lista==NULL){
			*lista=novo;
		}
		else{
			aux=*lista;
			while(aux->proximo)
				aux=aux->proximo;
				aux->proximo=novo;
			
		}
	}else{
			printf("Erro ao alocar memoria!\n");
		}
}

No* buscar(No **lista, int codigo){
	No *aux,*no=NULL;
	aux=*lista;
	while(aux && aux->pessoa.codigo!=codigo){
		aux=aux->proximo;
	}
	if(aux){
		no=aux;
	}
	return no;
}

No* buscar_numero_da_conta(No **lista, int codigo){
	No *aux,*no=NULL;
	aux=*lista;
	while(aux && aux->pessoa.conta_do_cliente.numero_conta!=codigo){
		aux=aux->proximo;
	}
	if(aux){
		no=aux;
	}
	return no;
}

void imprimir(No *no){
	printf("\n\tLista:");
	while(no){
		printf("____________________________________");
		printf("telefone:%d\n",no->pessoa.telefone);
        printf("nome:%s\n",no->pessoa.nome);
        printf("BI:%s\n",no->pessoa.BI);
        printf("codigo:%d\n",no->pessoa.codigo);
        printf("numero_conta:%d\n",no->pessoa.conta_do_cliente.numero_conta);
        printf("saldo:%.2f\n",no->pessoa.conta_do_cliente.saldo);
        printf("estado:%s\n",no->pessoa.conta_do_cliente.estado);
        printf("%s\n",no->pessoa.NIF);
        printf("____________________________________");
		no=no->proximo;
		
	}
	printf("\n\n");
}
void menu(){
	setlocale(LC_ALL,"Portuguese");
	printf("\t\tSISTEMA DE GESTAO E CONTROLO DE CLIENTES BAI-SGCB\n\n");
    printf("1-Cadastrar cliente\t\t 2-Listar cliente\t 3-Abertura de conta\n\n4-Depositar dinheiro\t\t 5-Levantar dinheiro\t 6-Consultar saldo\t\n7-Transferir dinheiro\t\t 8-Actualizar dados\t 9-terminar\nOpcao:");
    
}
   void liberar_lista(No *lista) {
    while (lista) {
        No *temp = lista;
        lista = lista->proximo;
        free(temp);
    }
}
int gerar_codigo(int codigo){
	int x=1;
	codigo=codigo+x;
	return codigo;
}
int gerar_numero_da_conta(){
	int numero;
	srand(time(NULL));
	int numero_fixo=2200;
	int numero_aleatorio=(rand()%100);
	numero=numero_fixo*100+numero_aleatorio;
    return numero;
}
bool validar_bilhete(char *numero_bilhete){
	int tamanho=strlen(numero_bilhete);
	if(tamanho!=15)
	return 0;
	int i;
	for(i=0;i<9;i++){
		if(!isdigit(numero_bilhete[i]))
		return false;
	}
	for( i=9;i<11;i++){
		if(!isalpha(numero_bilhete[i]))
		return false;
	}
	for( i=11;i<14;i++){
		if(!isdigit(numero_bilhete[i]))
		return false;
	}
	return true;
}
bool validar_telefone(char *numero_bilhete){
	int numero,tamanho=strlen(numero_bilhete);
	if(tamanho!=9)
	return false;
	if(numero_bilhete[0]!=9)
	return false;
	int i;
	for(i=0;i<9;i++){
		if(!isdigit(numero_bilhete[i]))
		return false;
	}
	return true;
}

int evitar_erro(char *digitado){
	int i,codigo_ascii,numero, tamanho=strlen(digitado);
	char formar_numero[tamanho];
	if(atoi(digitado)==0){
		return -01;
	}
	for( i=0;i<=tamanho;i++){
		if((int)digitado[i]>=48 && (int)digitado[i]<=57){
			formar_numero[i]=digitado[i];
		}
		
}
numero=atoi(formar_numero);
	return numero;
}

bool cadastro_cliente(Pessoa *p){
	char auxiliar[19];
	printf("Escolha:\t\t1-pessoa individual\t2-Empresa:\n");
	scanf("%s",&auxiliar);
	evitar_erro(auxiliar);
	if(evitar_erro(auxiliar)>0){
		tipo_de_cliente=atoi(auxiliar);
	}
else{
	tipo_de_cliente=3;
	}
		getchar();
		switch(tipo_de_cliente){
		case 1:
        printf("Digite o numero do BI:");
        fgets(auxiliar,sizeof(auxiliar),stdin);
        if(validar_bilhete(auxiliar)){
        	strcpy(p->BI,auxiliar);
			}
			else{
			printf("Bilhete invalido\n");
			return false;
			}
			break;
			case 2:
				printf("Digite o numero do NIF:");
        		fgets(auxiliar,sizeof(auxiliar),stdin);
        	if(validar_bilhete(auxiliar)){
        		strcpy(p->NIF,auxiliar);
				}
				else{
			printf("Bilhete invalido\n");
			return false;
				}
				break;	
				default:
				printf("Escolha entre 1 e 2\n");
				return false;	
		}
			if(tipo_de_cliente==1 || tipo_de_cliente==2){
			
		
		printf("digite o nome:");
        fgets(p->nome,sizeof(p->nome),stdin);
        printf("Digite o numero de telefone:");
        scanf("%s",&auxiliar);
        getchar();
        if(evitar_erro(auxiliar)>0){
        if(validar_telefone(auxiliar)){
        p->telefone=atoi(auxiliar);
        getchar();
        
        }}
        return true;
    
	
	
			}
		
	}
	
	bool abertura_de_conta(Pessoa *p,int tipo_de_conta){
	switch(tipo_de_conta){
		case 1:
			if(strlen(p->BI)==0){
				printf("Nao e uma conta individual\n");
				return false;
			}
			break;
		
		case 2:
			if(strlen(p->NIF)==0){
				printf("Nao e uma conta empresa\n");
				return false;
			}
			break;
		default:
			printf("Erro\n escolha entre 1 e 2\n");
            return false;
				
				
	}
	if(p->conta_do_cliente.numero_conta==0){
	p->conta_do_cliente.numero_conta=gerar_numero_da_conta();
	strcpy(p->conta_do_cliente.estado,"Ativo");
	return true;	
	}else{
		printf("Ja possui uma conta");
	}
	
}
 
 bool depositar(int num_da_conta, int valor){
 	
	 encontrado=buscar_numero_da_conta(&minha_lista,num_da_conta);
	 if(encontrado){
	 	if(valor>0){
	 	cliente=encontrado->pessoa;
	 cliente.conta_do_cliente.saldo=cliente.conta_do_cliente.saldo+valor;
	 return true;	
		 }
	 	
	 }
	 return false;
	 
 }
 bool levantar(int num_da_conta, int valor){
 	
	 encontrado=buscar_numero_da_conta(&minha_lista,num_da_conta);
	 if(encontrado){
	 	if(valor>0){
	 		if(cliente.conta_do_cliente.saldo>valor){
	 			cliente=encontrado->pessoa;
	 			cliente.conta_do_cliente.saldo=cliente.conta_do_cliente.saldo-valor;
	 				return true;	
			 }
	 	
		 }
	 	
	 }
	 return false;
	 
 }
 
 
 float consultar_saldo(int num_da_conta){
 	
	 encontrado=buscar_numero_da_conta(&minha_lista,num_da_conta);
	 if(encontrado){
	 	cliente=encontrado->pessoa;
	 return cliente.conta_do_cliente.saldo; 
	 }
	 
 }
 
 bool transferir(int num_da_conta_de_origem,int num_da_conta_de_destino ,int valor){
 		
	 encontrado=buscar_numero_da_conta(&minha_lista,num_da_conta_de_origem);
	 if(encontrado){
	 	if(valor>0){
	 	cliente=encontrado->pessoa;
	 encontrado=buscar_numero_da_conta(&minha_lista,num_da_conta_de_destino);
	 if(encontrado){
	 	if(valor>0){
	 	cliente1=encontrado->pessoa;
	 cliente1.conta_do_cliente.saldo=cliente.conta_do_cliente.saldo+valor;
	 cliente.conta_do_cliente.saldo=cliente.conta_do_cliente.saldo-valor;
	 return true;	
		 }
	 	
	 }
	 
	 }
	 }
	 return false;
	 
 }
 bool actualizar_dados(Pessoa p,int codigo){
 	int telefone,opcao;
 	char nbn[40];
 	printf("Para actualizar digite:\t 1-Nome\t2-Numero de telefone\t3-BI\t:");
 	
 	scanf("%s",&nbn);
	if(evitar_erro(nbn)>0){
		opcao=atoi(nbn);
	}
else{
	opcao=43;
	}
	switch(opcao){
		case 1:
		fgets(nbn,sizeof(nbn),stdin);
		strcpy(p.nome,nbn);
		return true;
		case 2:
			scanf("%s",&nbn);
		if(evitar_erro(nbn)>0){
		if(validar_telefone(nbn)){
			p.telefone=atoi(nbn);
			return true;
		}
	
	}
	return false;
	case 3:
		fgets(nbn,sizeof(nbn),stdin);
		if(validar_bilhete(nbn)){
		strcpy(p.BI,nbn);
		return true	;
		}
		case 4:
			fgets(nbn,sizeof(nbn),stdin);
		if(validar_bilhete(nbn)){
		strcpy(p.NIF,nbn);
		return true;
	}
	default:
	printf("Erro! opcao errada\n");
	return false;	
			
	}}
 
 void criar_ficheiro(const char *arqivo){
 	FILE *arquivo=fopen(arqivo,"w");
 	if(arquivo!=NULL){
 		fclose(arquivo);
 		printf("arquivo criado com sucesso:%s\n\n",arqivo);
	 }else{
	 	printf("Erro ao criar arquivo\n");
	 }
	 
 }
 void copia_de_seguranca(const char *arqivo, No **lista){
 	No *aux;
 	aux=*lista;
	 FILE *arquivo=fopen(arqivo,"w");
 	if(arquivo!=NULL){
 		while(aux!=NULL){
 			fprintf(arquivo,"%s\n",aux);
 					aux=aux->proximo;
		 }
 		fclose(arquivo);
 		printf("copia feita com sucesso \n");
 }else{
	 	printf("Erro ao abrir  arquivo\n");
	 }
}
void restaurar_copia(const char *arqivo, No **lista){
 	No *aux;
	 FILE *arquivo=fopen(arqivo,"w");
 	if(arquivo!=NULL){
 		while(fscanf(arquivo,"%d",& (aux->pessoa))!=EOF){
		 }
 		fclose(arquivo);
 		printf("copia feita com sucesso \n");
 }else{
	 	printf("Erro ao abrir  arquivo\n");
	 }
}
int main(int argc, char *argv[]) {
	criar_ficheiro("backup_Isaf.txt");
	int opcao,sair=0,tipo_de_conta,valor,valor2,num_da_conta;
	char auxiliar[16];
	do{
		menu();
		scanf("%s",&auxiliar);
	 	if(evitar_erro(auxiliar)>0){
	 		opcao=atoi(auxiliar);
	 		getchar();
	 	}
		 else{
	 		opcao=0;
	 		}
	 		
	 	
        	
		switch(opcao){
			case 1:
				if(cadastro_cliente(&cliente)){
				codigo=gerar_codigo(codigo);
				cliente.codigo=codigo;
				inserir_no_fim(&minha_lista, cliente);
				}
				break;
			case 2:
				imprimir(minha_lista);

				break;
    		case 3:
    			printf("Digite o codigo de Cliente\n:");
				scanf("%s",&auxiliar);
	 	if(evitar_erro(auxiliar)>0){
	 		opcao=atoi(auxiliar);
	 		
	 	}
		 else{
	 		opcao=0;
	 		}

    		encontrado=buscar(&minha_lista,opcao);
    		if(encontrado){
    			cliente=encontrado->pessoa;
    			printf("encontrado\n%d",cliente.codigo);
    			printf("Digite \t\t 1-Conta particular\t\t 2-Conta Empresa\n:");
    			scanf("%s",&auxiliar);
	 			if(evitar_erro(auxiliar)>0){
	 					tipo_de_conta=atoi(auxiliar);
				}
		 		else{
	 				tipo_de_conta=0;
	 			}
    			abertura_de_conta(&cliente,tipo_de_conta);
			}
    			break;
    			case 4:
    				printf("Digite o numero de conta\n:");
				scanf("%s",&auxiliar);
	 	if(evitar_erro(auxiliar)>0){
	 		opcao=atoi(auxiliar);
	 		getchar();
	 	}
		 else{
	 		opcao=0;
	 		}
	 		printf("Digite o valor\n:");
				scanf("%s",&auxiliar);
	 	if(evitar_erro(auxiliar)>0){
	 		valor=atoi(auxiliar);
	 		getchar();
	 	}
		 else{
	 		valor=0;
	 		}
    				if(depositar(opcao,valor)){
    					
					}
    				printf("Deposito efectuado com sucesso\n");
    				break;
    	case 5:
    					
    				printf("Digite o numero de conta\n:");
				scanf("%s",&auxiliar);
	 	if(evitar_erro(auxiliar)>0){
	 		opcao=atoi(auxiliar);
	 		getchar();
	 	}
		 else{
	 		opcao=0;
	 		}
	 		printf("Digite o valor\n:");
				scanf("%s",&auxiliar);
	 	if(evitar_erro(auxiliar)>0){
	 		valor=atoi(auxiliar);
	 		getchar();
	 	}
		 else{
	 		valor=0;
	 		}
    				if(depositar(opcao,valor))
    				printf("Levantamento efectuado com sucesso\n");
    					levantar(opcao,valor);
    					break;
    					
    	case 6:
    		printf("Digite o numero de conta\n:");
				scanf("%s",&auxiliar);
	 	if(evitar_erro(auxiliar)>0){
	 		opcao=atoi(auxiliar);
	 		getchar();
	 	}
		 else{
	 		opcao=0;
	 		}
    				printf("%.2f",consultar_saldo(opcao));
    				break;
    					
    					
    					
    					case 7:
    						
    				printf("Digite o numero de conta\n:");
				scanf("%s",&auxiliar);
	 	if(evitar_erro(auxiliar)>0){
	 		opcao=atoi(auxiliar);
	 		getchar();
	 	}
		 else{
	 		opcao=0;
	 		}
	 		printf("Digite o valor\n:");
				scanf("%s",&auxiliar);
	 	if(evitar_erro(auxiliar)>0){
	 		valor=atoi(auxiliar);
	 		getchar();
	 	}
		 else{
	 		valor=0;
	 		}
    					
    				printf("Digite o numero de conta de destino\n:");
				scanf("%s",&auxiliar);
	 	if(evitar_erro(auxiliar)>0){
	 		num_da_conta=atoi(auxiliar);
	 		getchar();
	 	}
		 else{
	 		num_da_conta=0;
	 		}
				transferir(opcao,num_da_conta,valor);
    					break;
    					
    					case 8:
    			printf("Digite o codigo de Cliente\n:");
				scanf("%s",&auxiliar);
	 	if(evitar_erro(auxiliar)>0){
	 		opcao=atoi(auxiliar);
	 		getchar();
	 	}
		 else{
	 		opcao=0;
	 		}

    		encontrado=buscar(&minha_lista,opcao);
    		if(encontrado){
    			cliente=encontrado->pessoa;
    			printf("encontrado\n%d",cliente.codigo);
    			actualizar_dados(cliente,opcao);
						}
			case 9:
				liberar_lista(minha_lista);
				sair=1;
				break;
			default:
				printf("Erro! Verifique as opcoes\n");
				system("pause");
			
		}
	
	}while(sair!=1);
}
    
