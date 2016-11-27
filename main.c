#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// -- Structs
typedef struct {
    int estadoAssento;
    long int infoPassageiro;
} infoAssento ;

typedef struct {
    int capacidade;
    infoAssento poltrona[10];
    int numeroVoo;
} infoVoo;

// -- Funções para controle de fluxo principal
char getOpcaoPrincipal() {
	char ch;

	printf("\n-- Menu de opcoes --\n");
	printf("\na. Inicializar dados");
	printf("\nb. Incluir reserva");
	printf("\nc. Excluir reserva");
	printf("\nd. Imprimir reserva");
	printf("\n\ns. Sair");

	printf("\n\nEscolha a opcao desejada: ");
	ch = getchar();
	return ch;
}

int getOpcaoImprimir() {
    int opcaoImprimir;

    printf("\n-- Opcoes de impressao --\n");
    printf("\n1. Imprimir dados de um voo");
    printf("\n2. Imprimir ocupacao dos voos");
    printf("\n3. Imprimir todos os dados");

    printf("\n\nEscolha a opcao desejada: ");
    scanf("%d", &opcaoImprimir);
    return opcaoImprimir;
}

void clearBuffer(char c) {
	while(c != '\n') {
		scanf("%c", &c);
	}
}

int getNumeroVoo() {
    int numeroVoo;

    printf("\nNumero do voo: ");
    scanf("%d", &numeroVoo);

    return numeroVoo;
}

void iniciar() {
    // Variáveis de sistema
    infoVoo airBus[50];
    long int idCliente;
    int nVoo;

    // Variáveis de menu
    char opcaoPrincipal;
    int opcaoImprimir, resultadoIncluir;

	while (opcaoPrincipal != 's') {
		opcaoPrincipal = getOpcaoPrincipal();
		clearBuffer(opcaoPrincipal);

		switch (opcaoPrincipal) {
			case 'a':
				printf("Inicializando dados...");
                inicializarDados(airBus);
				break;
			case 'b':
			    printf("Digite somente os numeros da sua identidade: ");
			    scanf("%li", &idCliente);
			    nVoo = getNumeroVoo();
				printf("Incluindo reserva...");

				resultadoIncluir = incluirReserva(airBus, idCliente, nVoo);
                switch (resultadoIncluir) {
                    case 0:
                        printf("Voo nao existe");
                        break;
                    case 1:
                        printf("Voo lotado");
                        break;
                    case 2: 
                        printf("Inclusao realizada com sucesso");
                        break;
                }
				clearBuffer(opcaoPrincipal);
				break;
			case 'c':
				printf("Excluindo reserva...");
				break;
			case 'd':
                opcaoImprimir = getOpcaoImprimir();
                nVoo = getNumeroVoo();
				printf("Imprimindo reserva...");
                imprimirReserva(airBus, opcaoImprimir, nVoo);
                clearBuffer(opcaoPrincipal);
				break;
            case 's':
				printf("Encerrando...");
				break;
			default:
			    printf("\n-- Digitado: %c\n", opcaoPrincipal);
				printf("A opcao selecionada e invalida, digite novamente");
				break;
		}
	}
}

//-- Inicializar dados
int inicializarDados(infoVoo airBus[50]){
    int i, j , n = 1000;

    for(i = 0; i < 50; i++) {
        airBus[i].capacidade = 0;
        airBus[i].numeroVoo = n;
        n++;
    }

    printf("\nDados inicializados com sucesso!\n");
}

//-- Incluir reserva
int incluirReserva(infoVoo airBus[50], int idCliente, int nVoo) {
    int i, j;

    for (i = 0; i < 50; i++) {
        if (nVoo == airBus[i].numeroVoo) {
            if (airBus[i].capacidade == 10) {
                return 1;
            } else {
                for (j = 0; j < 10; j++) {
                    if (airBus[i].poltrona[j].estadoAssento == 0) {
                        airBus[i].capacidade++;
                        airBus[i].poltrona[j].estadoAssento = 1;
                        airBus[i].poltrona[j].infoPassageiro = idCliente;
                        return 2;
                    }
                }
            }
        }
    }

    return 0;
}

//-- Excluir reserva
int excluirReserva(infoVoo airBus[50],int idCliente,int numeroVoo) {
    int i, j;
    for(i=0;i<50; i++) {
        if(numeroVoo==airBus[i].numeroVoo) {
            for(j=0; j<10; j++) {
                if (idCliente==airBus[i].poltrona[i].infoPassageiro) {
                    airBus[i].poltrona[j].infoPassageiro=0;
                    airBus[i].capacidade--;
                    airBus[i].poltrona[j].estadoAssento=0;
                    return 2;
                }
            }
            return 1;
            printf("Reserva excluida com sucesso!");
        }

        else{
            printf("Numero do voo nao encontrado, digite novamente.");
        }
    }
    return 0;
}

//-- Imprimir reserva
void imprimirReserva(infoVoo airBus[50], int opcao, int numeroVoo) {
    int i,j;
    int vooInexistente = 1;
    switch (opcao) {
    case 1:
        printf("\nNumero do voo: %d\n",numeroVoo);
        for ( i=0; i<50; i++) {
            if (numeroVoo==airBus[i].numeroVoo) {
                vooInexistente=0;
                printf("\nNumero de reservas do voo: %d\n",airBus[i].capacidade);
                for ( j=0; j<10; j++) {
                    if (airBus[i].poltrona[j].estadoAssento==1) {
                        printf("%li\n",airBus[i].poltrona[j].infoPassageiro);
                    }
                }
            }
        }
        if (vooInexistente==1) {
            printf("Numero de voo inexistente\n");
        }
        break;

    case 2:
        for ( i=0; i<50; i++) {
            if (numeroVoo==airBus[i].numeroVoo) {
                vooInexistente=0;
                printf("Numero do voo: %d Reservas: %d\n",airBus[i].numeroVoo,airBus[i].capacidade);
            }
        }
        if (vooInexistente==1) {
            printf("Numero de voo inexistente\n");
        }
        break;

    case 3:
        for ( i=0; i<50; i++) {
            if (numeroVoo==airBus[i].numeroVoo) {
                vooInexistente=0;
                printf("Numero do voo: %d\n",airBus[i].numeroVoo);
                printf("Numero de reservas no voo: %d\n",airBus[i].capacidade);
                for ( j=0; j<10; j++) {
                    if (airBus[i].poltrona[j].estadoAssento==1) {
                        printf("%li\n",airBus[i].poltrona[j].infoPassageiro);
                    }
                }
            }
        }
        if (vooInexistente==1) {
            printf("Numero de voo inexistente\n");
        }
        break;
    }
}

int main() {
    iniciar();
}
