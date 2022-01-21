#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <windows.h>
#include <locale.h>
#include "lista.h"


#define V 21
#define H 75
#define N 100
#define MAX_JUEGOS 5
#define MAX_USERS 5

typedef int tArray[N];


//tipo serpiente para Snake
typedef struct {
	int x, y;
	int modX, modY;
	char imagen;
}t_snk;

//tipo fruta para Snake
typedef struct {
	int x,  y;
}t_frt;


typedef char tMatrix3IL[3][3];//tipo matriz para 3 en línea
typedef char tMatrixP[V][H];//tipo matriz para pong
typedef char tMatrixS[V][H];//tipo matriz para snake

void portada();
void menuPrincipal();
bool continuar();
void gotoxy (int, int);

//prototipo de manipulacion de archivos
void archivoUsuarios(); //selecciona lo que se hara con el archivo
void abrirArchivo(int); //abre el archivo segun las necesidades del usuario
void modoLectura();
void modoEscritura();
void modoAdicion();

void nuevoUsuario(); // llama a las funciones correspondientes a la creación de un nuevo usuario y grabación de los datos
	t_data ingresarDatosUsuario(t_string,int,int,int,int,int); //se ingresa los datos del usuario
	void grabarUsuario();//se graba los datos del usuario al archivo

void seleccionarUsuario(); //llama a las funciones de le seleccion de usuario
	void cargarPuntuacion(); //graba la puntuacion de cada juego en la lista
	void grabarArchivo(); //graba la lista con los puntajes en el archivo
	void reescribir();
void verUsuarios(); //llamar a las funciones correspondientes a la lectura de datos, obtiene los usuarios y los muestra en pantalla
	void obtenerUsuario(); //obtiene los registros del archivo y los guarda en la lista
	void seleccionUsuario();
void cerrarArchivo();


//prototipos 3 en linea

void loopUnJugador(tMatrix3IL);
void loopDosJugadores(tMatrix3IL);
void introPrimero(tMatrix3IL);
void tablero(tMatrix3IL);
void introPlayer(tMatrix3IL);
void introPlayer2(tMatrix3IL);
void introIA(tMatrix3IL);
int ganado(tMatrix3IL);
void ganadorrr();
void menuTresEnLinea();

//prototipos Pong

void inicio(tMatrixP, int, int, int, int, int, int);
void inicio2(tMatrixP, int, int, int, int, int, int);
void borde(tMatrixP);
void raqJug(tMatrixP, int, int);
void raqJug2(tMatrixP, int, int);
void raqIA(tMatrixP, int, int);
void ball(tMatrixP, int, int);
void leerCampo(tMatrixP);
void gameloop(tMatrixP, int, int, int, int, int, int, int, int, int);
void draw(tMatrixP);
void input(tMatrixP, int *, int *, int *, int *, int *, int *, int *, int *, int *, int *);
void update(tMatrixP, int, int, int, int, int, int);
void gameloop2(tMatrixP, int, int, int, int, int, int, int, int);
void input2(tMatrixP, int *, int *, int *, int *, int *, int *, int *, int *, int *);
void update2(tMatrixP, int, int, int, int, int, int);
void menuPong();

//prototipos Snake

void inicioS(int *, tMatrixS);
void introCampo(tMatrixS);
void introDatos(tMatrixS, int);
void drawS(tMatrixS);
void loop(tMatrixS, int);
void inputS(tMatrixS, int *, int *);
void updateS(tMatrixS, int);
void introDatos2(tMatrixS, int);
void menuSnake();

//prototipos adivina un nro
void menuAdivinaNro();

//prototipos laberinto
void menuLaberinto();

//declaracion de variables globales
t_list *v_lista;

bool newUser;
int seleccion;
t_string userTemp, passTemp;

//tUsuario v_auxUser;
FILE *vf_usuarios;
FILE *extra;
//snake
t_snk snake[N];
t_frt fruta;

//contadores de scores
int contador3IL, contadorP, contadorS, contadorA, contadorL,IL,A,S,L,P;


//prototipado de corte de control
void corteDeControl();

void inicializacion();
void procesoCorte();
void finalizacion();

void inicioCorte();
void procesarUsuario();
void finCorte();

t_data usuario;

t_string userAnt;

int totalPuntaje;

int main() {
	setlocale(LC_ALL, "spanish");

	newUser = false;
	
	portada();
	archivoUsuarios();
	menuPrincipal();	

	
	return 0;
}

void gotoxy(int x, int y)  { 
     COORD coord; 
     coord.X=x; 
     coord.Y=y; 
     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord); 
}

//muestra en pantalla la portada del juego
void portada() {
	system("color 03");
		                                                                                                                                                                                                        
	printf("\n\n");
	printf("     ___ __   __ _______ _______ _______ _______ _______ \n");
	printf("    |   |  | |  |       |   _   |       |       |       |\n");
	printf("    |   |  | |  |    ___|  |_|  |_     _|    ___|       |\n");
	printf("    |   |  |_|  |   | __|       | |   | |   |___|      _|\n");
	printf(" ___|   |       |   ||  |       | |   | |    ___|     |  \n");
	printf("|       |       |   |_| |   _   | |   | |   |___|     |_ \n");
	printf("|_______|_______|_______|__| |__| |___| |_______|_______|\n"); 

	printf("\n\n");
	system("pause");
}

//menu de selección de los juegos
void menuPrincipal() {
	int opcion;
	
	do {
	system("cls");
	printf("Seleccione su juego:\n");
	printf("1-Tres en Línea\n");
	printf("2-Pong\n");
	printf("3-Snake\n");
	printf("4-Adivina el número\n");
	printf("5-Laberinto\n");
	printf("0-Salir\n");
	printf("\n\n");
	scanf("%d", &opcion);
	}while(opcion < 0 || opcion > 5);
	
	switch(opcion) {
		case 1:
			menuTresEnLinea();
			menuPrincipal();
			break;
		case 2:
			menuPong();
			menuPrincipal();
			break;
		case 3:
			menuSnake();
			menuPrincipal();
			break;
		case 4:
			do {
				menuAdivinaNro();
			}while (continuar());
			menuPrincipal();
			break;
		case 5:
			do {
				menuLaberinto();
			}while(continuar());
			menuPrincipal();
			break;
		case 0:
			cargarPuntuacion();
			archivoUsuarios();
			menuPrincipal();
			break;
	}
	
}

bool continuar() {
	char continuar;
	
	do {
		printf("\n¿Quiere volver a intentarlo?(S/N)\n\n");
		fflush(stdin);
		scanf("%c", &continuar);
	}while(continuar != 'S' && continuar != 's' && continuar != 'N' && continuar != 'n');
	
	if(continuar == 'S' || continuar == 's' ) {
		return true;
	}else {
		return false;
	}
	system("cls");
}

//definicion de las funciones de manipulacion de archivos
void archivoUsuarios() {
	int opcion;
	contador3IL = 0;
	contadorP = 0;
	contadorS = 0;
	contadorA = 0; 
	contadorL = 0;
	IL=0;
	P=0;
	S=0;
	A=0;
	L=0;
	
	
	do {
		system("cls");
		printf("1- Nuevo Usuario.\n\n");
		printf("2- Seleccionar Usuario Existente.\n\n");
		printf("3- Ver Registro de Usuarios\n\n");
		printf("0- Salir\n\n");
		scanf("%d", &opcion);
	} while(opcion < 0 || opcion > 3);
	
	if(opcion == 0) {
		exit(-1);
	} else {
		abrirArchivo(opcion);
	}
}

void abrirArchivo(int opcion) {
	
	if(opcion == 1) { // abre el archivo en modo escritura, y si no esta vacío lo abre en modo de adición
		if(vf_usuarios == NULL) {
			modoEscritura();
		} else {
			modoAdicion();
		}
		initialize_list(&v_lista);
		nuevoUsuario();
		cerrarArchivo();
		system("pause");
	} else if(opcion == 2) { //abre en modo adicion, si el archivo está vacío, avisa que lo está, de lo contrario selecciona un usuario
			seleccionUsuario();
			system("pause");
			
	} else {
		modoLectura();
		if(vf_usuarios == NULL) { //si el archivo está vacío, avisa que lo está, de lo contrario muestra los usuarios
			printf("No se ha ingresado usuarios aún.\n\n");
			system("pause");
			archivoUsuarios();
		} else {
			corteDeControl();
			system("pause");
			archivoUsuarios();
		}	
	}
		
}

void modoLectura() {
	vf_usuarios = fopen("Usuarios.dat", "rb");
}

void modoEscritura() {
	vf_usuarios = fopen("Usuarios.dat", "wb");
}

void modoAdicion() {
	vf_usuarios = fopen("Usuarios.dat", "ab");
}

void nuevoUsuario() {
	t_string nusuario;
	system("cls");
		printf("\nIngrese nombre de Usuario: ");
	fflush(stdin);
	scanf("%[^\n]s", &nusuario);
	push_start_list(&v_lista,ingresarDatosUsuario(nusuario,0, 0, 0, 0, 0));
	grabarUsuario();
	printf("\tUsuario creado.\n");
	newUser = true;
}

t_data ingresarDatosUsuario(t_string p_nombre,int pcont3IL,int pcontP,int pcontS,int pcontA,int pcontL) {
	t_data v_auxUser;
	IL=pcont3IL;
	P=pcontP;
	S=pcontS;
	A=pcontA;
	L=pcontL;
	strcpy(v_auxUser.user, p_nombre);
	printf("\n");
	v_auxUser.contador3IL=0;
	v_auxUser.contadorA=0;
	v_auxUser.contadorL=0;
	v_auxUser.contadorP=0;
	v_auxUser.contadorS=0;
	
	strcpy(userTemp,v_auxUser.user);
	
	
return v_auxUser; }
	
	

void grabarUsuario() {
	t_data v_auxUser;
	
	v_auxUser = v_lista->dato;
	fwrite(&v_auxUser, sizeof(t_data), 1, vf_usuarios);
}


void verUsuarios() {
	system("cls");
	printf("Lista de Usuarios:\n\n");
	printf("Nombre de Usuario\t|\tContraseña\n");
	obtenerUsuario();
	show_list(v_lista);
	
}

void obtenerUsuario() {
	t_data v_auxUser;
	
	fread(&v_auxUser, sizeof(t_data), 1, vf_usuarios);
	while (!feof(vf_usuarios)) {
		push_start_list(&v_lista, v_auxUser);
		fread(&v_auxUser, sizeof(t_data), 1, vf_usuarios);
	};
}


void cargarPuntuacion() {
	t_data v_auxUser;
	
	strcpy(v_auxUser.user,userTemp);
	v_auxUser.contador3IL = contador3IL+IL;
	v_auxUser.contadorA= contadorA+A;
	v_auxUser.contadorL = contadorL+L;
	v_auxUser.contadorP = contadorP+P;
	v_auxUser.contadorS = contadorS+S;
	
	if (newUser) {
		modoAdicion();
		fwrite(&v_auxUser, sizeof(t_data), 1, vf_usuarios);
		cerrarArchivo();
	} else {
		push_k_list(&v_lista, seleccion, v_auxUser);
		modoEscritura();
		grabarArchivo();
		cerrarArchivo();
	}
	
	
	
}

void grabarArchivo() {
	t_list *aux;
	aux = v_lista;
	
	while (aux != NULL) {
		fwrite(&aux->dato, sizeof(t_data), 1, vf_usuarios);
		aux = aux->siguiente;
	}
	
}


void cerrarArchivo() {
	fclose(vf_usuarios);
}

//definicion de funciones para 3 en linea
void loopUnJugador (tMatrix3IL c) {
	int i, j;
	i = 0;
	
	introPrimero(c);
	
	do {
		system("cls");
		tablero(c);
		
		if(i % 2 == 0) {
			introPlayer(c);
		}else {
			introIA(c);
		}
		j = ganador(c);
		i++;
		
	}while (i <= 9 && j == 2);
	
	system("cls");
	tablero(c);
	
	if(j == 0) {
		contador3IL += 1;
		printf("Felicidades!! Has ganado!!\n\n");
		system("cls");
		ganadorrr();
	}else if(j == 1) {
		printf("D'oh no!! Has perdido!\n\n");
	} else {
		printf("Has empatado!! Intentalo de nuevo!!\n\n");
	}
	
}

void loopDosJugadores(tMatrix3IL c) {
	int i, j;
	i = 0;
	
	introPrimero(c);
	
	do {
		system("cls");
		tablero(c);
		
		if(i % 2 == 0) {
			introPlayer(c);
		}else {
			introPlayer2(c);
		}
		j = ganador(c);
		i++;
		
	}while (i <= 9 && j == 2);
	
	system("cls");
	tablero(c);
	
	if(j == 0) {
		printf("Felicidades!! Jugador 1 ha ganado!!\n\n");
	}else if(j == 1) {
		printf("Felicidades!! Jugador 2 ha ganado\n\n");
	} else {
		printf("Han empatado!! Intentelo de nuevo!!\n\n");
	}
	system("pause");
}

void introPrimero(tMatrix3IL c){
	int i, j;
	char aux;
	aux = '1';
	
	for(i=0; i<3; i++) {
		for(j=0; j<3; j++) {
			c[i][j] = aux++;
		}
	}
}

void tablero(tMatrix3IL c) {
	int i, j;
	
	for(i=0; i<3; i++) {
	printf("\n\t\t\t\t| ");
		for(j=0; j<3; j++) {
			if(j<2) {
				printf(" %c  |", c[i][j]);
			}else {
				printf(" %c  |", c[i][j]);
			}
		}
		if (i<2) {
			printf("\n\n\t\t\t\t----------------\n");
		}
	}
	printf("\n\n");
}

void introPlayer(tMatrix3IL c) {
	int i, j, k;
	char aux;
	
	do {
		do {
			printf("Jugador 1:\n");
			printf("Coloca una ficha: ");
			fflush(stdin);
			scanf("%s", &aux);
		}while(aux!='1'&&aux!='2' &&aux!='3'&&aux!='4'&&aux!='5'&&aux!='6'&&aux!='7'&&aux!='8'&&aux!='9');
		
		switch (aux) {
			case '1': {
				i = 0;
				j = 0;
				if(c[i][j] == 'X' || c[i][j] == 'O') {
					k = 1;
					printf("La casilla esta ocupada! Intenta con otro número!! \n\n");
				}
				break;
			}
			case '2': {
				i = 0;
				j = 1;
				if(c[i][j] == 'X' || c[i][j] == 'O') {
					k = 1;
					printf("La casilla esta ocupada! Intenta con otro número!! \n\n");
				}
				break;
			}
			case '3': {
				i = 0;
				j = 2;
				if(c[i][j] == 'X' || c[i][j] == 'O') {
					k = 1;
					printf("La casilla esta ocupada! Intenta con otro número!! \n\n");
				}
				break;
			}
			case '4': {
				i = 1;
				j = 0;
				if(c[i][j] == 'X' || c[i][j] == 'O') {
					k = 1;
					printf("La casilla esta ocupada! Intenta con otro número!! \n\n");
				}
				break;
			}
			case '5': {
				i = 1;
				j = 1;
				if(c[i][j] == 'X' || c[i][j] == 'O') {
					k = 1;
					printf("La casilla esta ocupada!\n Intenta con otro número!! \n\n");
				}
				break;
			}
			case '6': {
				i = 1;
				j = 2;
				if(c[i][j] == 'X' || c[i][j] == 'O') {
					k = 1;
					printf("La casilla esta ocupada! Intenta con otro número!! \n\n");
				}
				break;
			}
			case '7': {
				i = 2;
				j = 0;
				if(c[i][j] == 'X' || c[i][j] == 'O') {
					k = 1;
					printf("La casilla esta ocupada! Intenta con otro número!! \n\n");
				}
				break;
			}
			case '8': {
				i = 2;
				j = 1;
				if(c[i][j] == 'X' || c[i][j] == 'O') {
					k = 1;
					printf("La casilla esta ocupada! Intenta con otro número!! \n\n");
				}
				break;
			}
			case '9': {
				i = 2;
				j = 2;
				if(c[i][j] == 'X' || c[i][j] == 'O') {
					k = 1;
					printf("La casilla esta ocupada! Intenta con otro número!! \n\n");
				}
				break;
			}
		}
	}while(k == 1);
	
	c[i][j] = 'X';
}

void introPlayer2(tMatrix3IL c) {
	int i, j, k;
	char aux;
	
	do {
		do {
			printf("Jugador 2:\n");
			printf("Coloca una ficha: ");
			fflush(stdin);
			scanf("%s", &aux);
		}while(aux!='1'&&aux!='2' &&aux!='3'&&aux!='4'&&aux!='5'&&aux!='6'&&aux!='7'&&aux!='8'&&aux!='9');
		
		switch (aux) {
			case '1': {
				i = 0;
				j = 0;
				if(c[i][j] == 'X' || c[i][j] == 'O') {
					k = 1;
					printf("La casilla esta ocupada! Intenta con otro número!! \n\n");
				}
				break;
			}
			case '2': {
				i = 0;
				j = 1;
				if(c[i][j] == 'X' || c[i][j] == 'O') {
					k = 1;
					printf("La casilla esta ocupada! Intenta con otro número!! \n\n");
				}
				break;
			}
			case '3': {
				i = 0;
				j = 2;
				if(c[i][j] == 'X' || c[i][j] == 'O') {
					k = 1;
					printf("La casilla esta ocupada! Intenta con otro número!! \n\n");
				}
				break;
			}
			case '4': {
				i = 1;
				j = 0;
				if(c[i][j] == 'X' || c[i][j] == 'O') {
					k = 1;
					printf("La casilla esta ocupada! Intenta con otro número!! \n\n");
				}
				break;
			}
			case '5': {
				i = 1;
				j = 1;
				if(c[i][j] == 'X' || c[i][j] == 'O') {
					k = 1;
					printf("La casilla esta ocupada!\n Intenta con otro número!! \n\n");
				}
				break;
			}
			case '6': {
				i = 1;
				j = 2;
				if(c[i][j] == 'X' || c[i][j] == 'O') {
					k = 1;
					printf("La casilla esta ocupada! Intenta con otro número!! \n\n");
				}
				break;
			}
			case '7': {
				i = 2;
				j = 0;
				if(c[i][j] == 'X' || c[i][j] == 'O') {
					k = 1;
					printf("La casilla esta ocupada! Intenta con otro número!! \n\n");
				}
				break;
			}
			case '8': {
				i = 2;
				j = 1;
				if(c[i][j] == 'X' || c[i][j] == 'O') {
					k = 1;
					printf("La casilla esta ocupada! Intenta con otro número!! \n\n");
				}
				break;
			}
			case '9': {
				i = 2;
				j = 2;
				if(c[i][j] == 'X' || c[i][j] == 'O') {
					k = 1;
					printf("La casilla esta ocupada! Intenta con otro número!! \n\n");
				}
				break;
			}
		}
	}while(k == 1);
	
	c[i][j] = 'O';
}

void introIA(tMatrix3IL c) {
	int i, j, k;
	
	srand(time(NULL));
	
	
	
	do {
		i = rand() % 3;
		j = rand() % 3;
		k = 0;
		
		if(c[i][j] == 'X' || c[i][j] == 'O') {
			k = 1;
		}
	}while(k == 1);
	
	c[i][j] = 'O';
}

int ganador(tMatrix3IL c) {
	
	if (c[0][0] == 'X' || c[0][0] == 'O') {
		if (c[0][0] == c[0][1] && c[0][0] == c[0][2]) {
			if(c[0][0] == 'X') {
				return 0; //he ganado
			}else {
				return 1; //he perdido
			}
		}
		if(c[0][0] == c[1][0] && c[0][0] == c[2][0]) {
			if(c[0][0] == 'X') {
				return 0; //he ganado
			}else {
				return 1; //he perdido
			}
		}
	}
	
	if(c[1][1] == 'X' || c[1][1] == 'O') {
		if(c[1][1] == c[0][0] && c[1][1] == c[2][2]) {
			if(c[1][1] == 'X') {
				return 0; //he ganado
			}else {
				return 1; //he perdido
			}
		}
		if(c[1][1] == c[1][0] && c[1][1] == c[1][2]) {
			if(c[1][1] == 'X') {
				return 0; //he ganado
			}else {
				return 1; //he perdido
			}
		}
		if(c[1][1] == c[2][0] && c[1][1] == c[0][2]) {
			if(c[1][1] == 'X') {
				return 0; //he ganado
			}else {
				return 1; //he perdido
			}
		}
		if(c[1][1] == c[0][1] && c[1][1] == c[2][1]) {
			if(c[1][1] == 'X') {
				return 0; //he ganado
			}else {
				return 1; //he perdido
			}
		}
	}
	
	if(c[2][2] == 'X' || c[2][2] == 'O') {
		if (c[2][2] == c[2][0] && c[2][2] == c[2][1]) {
			if(c[2][2] == 'X') {
				return 0; //he ganado
			}else {
				return 1; //he perdido
			}
		}
		if (c[2][2] == c[0][2] && c[2][2] == c[1][2]) {
			if(c[2][2] == 'X') {
				return 0; //he ganado
			}else {
				return 1; //he perdido
			}
		}
	}
	
 return 2;	
}


void ganadorrr(){
		int i=0,j=0;
		 srand(time(NULL));
		while(j<6){
		switch(7+rand()%(15+1-7)){
		case 7: system("color 03");break;
		case 8: system("color 06");break;
		case 9: system("color A");break;
		case 10: system("color B");break;
		case 11: system("color C");break;
		case 12: system("color D");break;
		case 13: system("color E");break;
		case 14: system("color 8");break;
	}
		char t[30][80]={

	"                                          +                000     *        " ,
	"     +              *       00000                  *         000            " ,
	"                           00O0O00    +                      0000  +        " ,                    
    "           +        +       00000            +               000    *       " ,
	"                             000                       +   000              " ,
	"                         000000010000000                       +            " ,
	"      +                0000 0 00000000000      +                            " ,
	"            *        00000   00000 0000                *                    " ,
	"      +            0000    00000 000            +                            " ,
	"            *    0000    0000 000000                     *                    " ,
	"      +        0000     000 0000000            +                            " ,
	"            * 0000     000  00000000                   *                    " ,
	"                            00000000         *               +              " ,
	"                   *       000    000                               *       " ,                    
    "        +                 000      000                                      " ,
	"                 +       000        000        +      +                      " ,
	"        +                000         0000                                     " ,
	"                 +       000         0000       +      +                      " ,
	"                          000    +    000                                     " ,
	"                 +        000         000        +      +                      " ,
	"                          000    +   000                                     " ,
	"                         00000       00000                                   " ,
    "============================================================================",   };
	for(i=0;i<=30;i++)
            puts(t[i]);
            Sleep(200);
            system("cls");
	char r[30][80]={

	"                                       *                   000              " ,
	"        +        +       *   00000               +     *     000 +      *    " ,
	"                            00O0O00                          00000           " ,                    
    "  *            *             00000      *                    000             " ,
	"         +                0000000000000           +        000              " ,
	"                      00000000000000 0000                           +       " ,
	"            *       00000  000000000   000             +                    " ,
	"                   000      00000000     000                                " ,
	"            *     000       00000000      00             +                    " ,
	"                  000       00000000     000                                " ,
	"            *      00000    00000000    00             +                    " ,
	"                    00000 * 00000000  0000                                 " ,
	"     *        +             00000000              *                         " ,
	"                           0000   000    *                       *          " ,                    
    "                           000*    000                                 +    " ,
	"    +               *      000      000          +                          " ,
	"               +          000     *  000                    *               " ,
	"    +              *      000        000          +                          " ,
	"               +          000     *  000                    *               " ,
	"    +               *     000       000                                     " ,
	"               +         000      * 000        +            *               " ,
	"                         0000       0000                                     " ,
    "============================================================================",   };
    switch(7+rand()%(15+1-7)){
		case 7: system("color 03");break;
		case 8: system("color 06");break;
		case 9: system("color A");break;
		case 10: system("color B");break;
		case 11: system("color C");break;
		case 12: system("color D");break;
		case 13: system("color E");break;
		case 14: system("color 8");break;
	}
	for(i=0;i<=30;i++)
            puts(r[i]);
            Sleep(200);
            system("cls"); 
            	char e[30][80]={
	"                                                           000     *        " ,
	"               +                         *             *     000            " ,
	"     *                  *   00000            +               00000     *    " ,
	"             +             00O0O00                           000            " ,                    
    "                            00000                          000              " ,
	"     *          *         0000000000000 *                   *      *        " ,
	"                          0000000 00 000                                    " ,
	"                       *   00 00000 0  000         +     +            +    " ,
	"                             00 0000    000                    *            " ,
	"       +  +                  0000 000     000                              " ,
	"                   *         000000 0000  0000                             " ,
	"                             00000000  0000   0000*            +     +      " ,
	"       *                +   0000   000   000            *                    " ,                    
    "                +           000*    000                                      " ,
	"                           000       0000                             *      " ,
	"     *         *          000          000                  *                 " ,
	"                          000     *    000         +                           " ,
	"                          000          000                               +    " ,
	"         +             *  000         0000                       *            " ,
	"                          000        000000        *       *    +            " ,
	"                          000                                                " ,
	"                         0¿00                                                " ,
    "============================================================================",   };
    switch(7+rand()%(15+1-7)){
		case 7: system("color 03");break;
		case 8: system("color 06");break;
		case 9: system("color A");break;
		case 10: system("color B");break;
		case 11: system("color C");break;
		case 12: system("color D");break;
		case 13: system("color E");break;
		case 14: system("color 8");break;
	}
	for(i=0;i<=30;i++)
            puts(e[i]);
            Sleep(200);
            system("cls");
            
             j=j+1;         
	}
}

void menuTresEnLinea() {
	tMatrix3IL c;
	int opcion;
	
	do {
		system("cls");
		printf("Seleccione el modo de juego:\n\n");
		printf("1 Jugador\n\n");
		printf("2 Jugadores\n\n");
		printf("Presione 0 para salir al menu principal.");
		printf("\n\n");
			
		scanf("%d", &opcion);
	}while(opcion < 0 || opcion >2);
	system("cls");
		
	switch(opcion) {
		case 1:
			do {
				loopUnJugador(c);
			}while(continuar());
			menuPrincipal();
		case 2:
			do {
				loopDosJugadores(c);
			}while(continuar());
			menuPrincipal();
		case 0:
			break;
	}	
	system("pause");
}

//definicion de funciones para Pong
void menuPong() {
	int ballX, ballY, iniJug, finJug, iniIA, finIA, iniJug2, finJug2; // variables de posicion 
	int modX, modY, modIA; // variables de modificacion
	int opcion;
	tMatrixP campo;
	
	
	// inicialiacion de posicion 
	ballX = 37;
	ballY = 10;
	iniJug = 8;
	finJug = 12;
	iniJug2 = 8;
	finJug2 = 12;
	iniIA = 2;
	finIA = 18;
	
	//inicialización de modificacion
	srand(time(NULL));
	int pelota = rand() % 4;
	switch(pelota) {
		case 1:
			modX = -1; 
			modY = 1 ;
			break;
		case 2:
			modX = 1; 
			modY = 1;
			break;
		case 3:
			modX = 1; 
			modY = -1;
			break;
		case 4:
			modX = -1; 
			modY = -1;
			break;
	}
	
	modIA = -1;
		
	do {
		system("cls");
		printf("Seleccione el modo de juego:\n\n");
		printf("1 Jugador\n\n");
		printf("2 Jugadores\n\n");
		printf("Presione 0 para salir al menu principal.");
		printf("\n\n");
		
		scanf("%d", &opcion);
	}while(opcion < 0 || opcion >2);
	system("cls");
	
	switch(opcion) {
		case 1:
			do {
				inicio(campo, ballX, ballY, iniJug, finJug, iniIA, finIA);
				gameloop(campo, ballX, ballY, iniJug, finJug, iniIA, finIA, modX, modY, modIA);
			} while (continuar());
			break;
		case 2:
			do {
				inicio2(campo, ballX, ballY, iniJug, finJug, iniJug2, finJug2);
				gameloop2(campo, ballX, ballY, iniJug, finJug, iniJug2, finJug2, modX, modY);
			} while (continuar());
			break;
		case 0:
			break;
	}
}

void inicio(tMatrixP campo, int ballX, int ballY, int iniJug, int finJug, int iniIA, int finIA) {
	borde(campo);
	raqJug(campo, iniJug, finJug);
	raqIA(campo, iniIA, finIA);
	ball(campo, ballX, ballY);
}

void inicio2(tMatrixP campo, int ballX, int ballY, int iniJug, int finJug, int iniJug2, int finJug2) {
	borde(campo);
	raqJug(campo, iniJug, finJug);
	raqJug2(campo, iniJug2, finJug2);
	ball(campo, ballX, ballY);
}

void borde(tMatrixP campo) {
	int i, j;
	
	for(i = 0; i < V; i++) {
		for(j = 0; j < H; j++) {
			if(i == 0 || i == V-1) {
				campo[i][j] = '-';	
			} 
			else if(j == 0 || j == H-1) {
				campo[i][j] = '|';
				
			} 
			else {
				campo[i][j] = ' ';
			}
		}
	}
	printf("Puntaje: %d\n", contadorP);
}

void raqJug(tMatrixP campo, int iniJug, int finJug) {
	int i, j;
	
	for(i = iniJug; i < finJug; i++) {
		for(j = 2; j <= 3 ; j++) {
			campo[i][j] = '#';
		}
	}	
}

void raqJug2(tMatrixP campo, int iniJug, int finJug) {
	int i, j;
	
	for(i = iniJug; i < finJug; i++) {
		for(j = H - 4; j <= H-3 ; j++) {
			campo[i][j] = '#';
		}
	}	
}

void raqIA(tMatrixP campo, int iniIA, int finIA) {
	int i, j;
	
	for(i = iniIA; i < finIA; i++) {
		for(j = H-4; j <= H-3; j++) {
			campo[i][j] = '#';
		}
	}	
}

void ball(tMatrixP campo, int ballX, int ballY) {
	campo[ballY][ballX] = 'O';
}

void leerCampo(tMatrixP campo) {
	int i, j;
	
	for(i = 0; i < V; i++) {
		for(j = 0; j < H; j++){
			printf("%c", campo[i][j]);
		}
		printf("\n");
	}
}

void gameloop(tMatrixP campo, int ballX, int ballY, int iniJug, int finJug, int iniIA, int finIA, int modX, int modY, int modIA) {
	int gol;
	gol = 0;
	
	do {
		draw(campo); //dibujar en pantalla
		input(campo, &ballX, &ballY, &iniJug, &finJug, &iniIA, &finIA, &modX, &modY, &modIA, &gol); //verificar y modificar las posiciones
		update(campo, ballX, ballY, iniJug, finJug, iniIA, finIA); //actualizar la matriz campo
		
		Sleep(1);
		
	} while(gol == 0);
}

void draw(tMatrixP campo) {
	gotoxy(0, 0);
	leerCampo(campo);
}

void input(tMatrixP campo, int *ballX, int *ballY, int *iniJug, int *finJug, int *iniIA, int *finIA, int *modX, int *modY, int *modIA, int *gol) {
	int i;
	char key;
	
	//verificacion
	if(*ballY == 1 || *ballY == V-2) {
		*modY *= -1;
	}
	if(*ballX == 1 || *ballX == H-2) {
		*gol = 1;
		if(*ballX == H-2) {
			contadorP+=1;
		}
	}
	
	if(*ballX == 4) {
		for(i = (*iniJug); i < (*finJug); i++) {
			if(i == (*ballY)) {
				*modX *= -1; 
			}
		}
	}
	if(*ballX == H - 5) {
		for(i = (*iniIA); i < (*finIA); i++) {
			if(i == (*ballY)) {
				*modX *= -1; 
			}
		}
	}
	
	if(*iniIA == 1 || *finIA == V -1) {
		*modIA *= -1;
	}
	
	//modificacion
	if(*gol == 0) {
		//movimiento pelota
		*ballX += (*modX);
		*ballY += (*modY);
		
		//movimiento raqueta ia
		*iniIA += (*modIA);
		*finIA += (*modIA);
		
		if(kbhit() == 1) {
			key = getch();
			
			if(key == 'w' || key == 'W') {
				if(*iniJug != 1) {
					*iniJug -= 1;
					*finJug -= 1;
				}
			}
			if(key == 's' || key == 'S') {
				if(*finJug != V-1) {
					*iniJug += 1;
					*finJug +=1;
				}
			}
		}
	}
	
}

void update(tMatrixP campo, int ballX, int ballY, int iniJug, int finJug, int iniIA, int finIA) {
	borde(campo);
	raqJug(campo, iniJug, finJug);
	raqIA(campo, iniIA, finIA);
	ball(campo, ballX, ballY);
}

void gameloop2(tMatrixP campo, int ballX, int ballY, int iniJug, int finJug, int iniJug2, int finJug2, int modX, int modY) {
	int gol;
	gol = 0;
	
	do {
		draw(campo); //dibujar en pantalla
		input2(campo, &ballX, &ballY, &iniJug, &finJug, &iniJug2, &finJug2, &modX, &modY, &gol); //verificar y modificar las posiciones
		update2(campo, ballX, ballY, iniJug, finJug, iniJug2, finJug2); //actualizar la matriz campo
		
		Sleep(1);
		
	} while(gol == 0);
}

void input2(tMatrixP campo, int *ballX, int *ballY, int *iniJug, int *finJug, int *iniJug2, int *finJug2, int *modX, int *modY, int *gol) {
	int i;
	char key;
	
	//verificacion
	if(*ballY == 1 || *ballY == V-2) {
		*modY *= -1;
	}
	if(*ballX == 1 || *ballX == H-2) {
		*gol = 1;
	}
	
	if(*ballX == 4) {
		for(i = (*iniJug); i < (*finJug); i++) {
			if(i == (*ballY)) {
				*modX *= -1; 
			}
		}
	}
	if(*ballX == H - 5) {
		for(i = (*iniJug2); i < (*finJug2); i++) {
			if(i == (*ballY)) {
				*modX *= -1; 
			}
		}
	}

	
	//modificacion
	if(*gol == 0) {
		//movimiento pelota
		*ballX += (*modX);
		*ballY += (*modY);
		
		
		//movimiento raqueta jug1
		if(kbhit() == 1) {
			key = getch();
			
			if(key == 'w' || key == 'W') {
				if(*iniJug != 1) {
					*iniJug -= 1;
					*finJug -= 1;
				}
			}
			if(key == 's' || key == 'S') {
				if(*finJug != V-1) {
					*iniJug += 1;
					*finJug +=1;
				}
			}	
			if(key == '8') {
				if(*iniJug2 != 1) {
					*iniJug2 -= 1;
					*finJug2 -= 1;
				}
			}
			if(key == '2') {
				if(*finJug2 != V-1) {
					*iniJug2 += 1;
					*finJug2 += 1;
				}
			}
		}
	}
	
}

void update2(tMatrixP campo, int ballX, int ballY, int iniJug, int finJug, int iniJug2, int finJug2) {
	borde(campo);
	raqJug(campo, iniJug, finJug);
	raqJug2(campo, iniJug2, finJug2);
	ball(campo, ballX, ballY);
}

//definicion de variables de Snake
void menuSnake() {
	int tam;
	tMatrixS campo;
	
	do {
	inicioS(&tam, campo); //iniciar todos nuestros elementos
	loop(campo, tam);
	}while(continuar());
	
	system("pause");
}

void inicioS(int *tam, tMatrixS campo) {
	int i;
	//la cabeza de la serpiente
	snake[0].x = 32;
	snake[0].y = 10;
	
	//tamaño de la serpiente
	*tam = 4;
	
	//coordenadas de fruta
	srand(time(NULL));
	
	fruta.x = rand() % (H-2) + 1;
	fruta.y = rand() % (V-2) + 1;


	for(i = 0; i < *tam; i++){
		snake[i].modX = 1;
		snake[i].modY = 0;
	}	
	
	introCampo(campo);
	introDatos(campo, *tam);
}

void introCampo(tMatrixS campo) {
	int i, j;
	
	for(i = 0; i < V; i++) {
		for(j = 0; j < H; j++) {
			if(i == 0 || i == (V-1)) {
				campo[i][j] = '-';
			} else if(j == 0 || j == (H-1)) {
				campo[i][j] = '|';
			} else {
				campo[i][j] = ' ';
			}
		}
	}
	printf("Puntaje: %d", contadorS);
}

void introDatos(tMatrixS campo, int tam) {
	int i;
	
	for(i = 1; i < tam; i++) {
		snake[i].x = snake[i-1].x - 1;
		snake[i].y = snake[i-1].y;
		
		snake[i].imagen = 'X';
	}
	snake[0].imagen = 'O';
	
	for(i = 0; i < tam; i++){
		campo[snake[i].y][snake[i].x] = snake[i].imagen;
	}
	campo[fruta.y][fruta.x] = '%';
}

void drawS(tMatrixS campo) {
	int i, j;
	
	for(i = 0; i < V; i++){
		for(j = 0; j < H; j++) {
			printf("%c", campo[i][j]);
		}
		printf("\n");
	}
}

void loop(tMatrixS campo, int tam) {
	int muerto;
	muerto = 0;
	
	do {
		gotoxy(0, 0);
		drawS(campo);
		inputS(campo, &tam, &muerto);
		updateS(campo, tam);
	}while (muerto == 0);
}

void inputS(tMatrixS campo, int *tam, int *muerto) {
	int i;
	char key;
	
	//verificacion de muerte
	if(snake[0].x == 0 || snake[0].x == H-1 || snake[0].y == 0 || snake[0].y  == V-1){
		*muerto = 1;
	}
	
	for (i = 1; i < *tam && *muerto == 0; i++) {
		if(snake[0].x == snake[i].x && snake[0].y == snake[i].y) {
			*muerto = 1;
		}
	}
	
	//comprobacion de haber comido la fruta
	
	if(snake[0].x == fruta.x && snake[0].y == fruta.y) {
		*tam += 1;
		snake[*tam - 1].imagen = 'X'; //dibuja el crecimiento
		contadorS += 1;
		
		//reubica la fruta
		fruta.x = rand() % (H-2) + 1;
		fruta.y = rand() % (V-2) + 1;
	}
	
	if(*muerto == 0) {
		if (kbhit() == 1) {
			key = getch();
			
			if((key == 's' || key == 'S') && snake[0].modY != -1) {
				snake[0].modX = 0;
				snake[0].modY = 1;
			}
			if((key == 'w' || key == 'W') && snake[0].modY != 1) {
				snake[0].modX = 0;
				snake[0].modY = -1;
			}
			if((key == 'a' || key == 'A') && snake[0].modX != 1) {
				snake[0].modX = -1;
				snake[0].modY = 0;
			}
			if((key == 'd' || key == 'D') && snake[0].modX != -1) {
				snake[0].modX = 1;
				snake[0].modY = 0;
			}
		}
	}
}

void updateS(tMatrixS campo, int tam) {
	//borrar todos los datos de la matriz
	introCampo(campo);
	
	//introducir los nuevos datos
	introDatos2(campo, tam);
}

void introDatos2(tMatrixS campo, int tam) {
	int i;
	
	//crear el seguimiento de cada parte del cuerpo
	for(i= tam - 1; i > 0; i--) {
		snake[i].x = snake[i-1].x;
		snake[i].y = snake[i-1].y;
	}
	
	snake[0].x += snake[0].modX;
	snake[0].y += snake[0].modY;
	
	for(i = 0; i < tam; i++) {
		campo[snake[i].y][snake[i].x] = snake[i].imagen;
	}
	
	campo[fruta.y][fruta.x] = '%';
}

//declaracion de funciones de adivina el nro
void menuAdivinaNro() {
     system("cls");
	 int x;         //numero ingresado x el usuario
     int y = 0;
     int contador = 0;         //numero aleatorio
     y = (rand() % 100) + 1;
     printf("\t\t#####   JUEGO DE ADIVINANZAS Juga Tec   #####\n\n");
     printf("\tEl programa te pedira un numero entre 0 y 100 y lo compara\n");
     printf("\tcon uno aleatorio creado por el. El programa le dira si el\n");
     printf("\tnumero es mayor o menor que el aleatorio asta que aciertes\n");

     do{
         contador ++;
         printf("\nIntroduce un numero entre 0 y 100: ");
         scanf("%d", &x);
         if( x > y){
             printf("\n Error, el numero que buscas es menor\n");
         }
         if (x < y){
              printf("\n Error el numero que buscas es mayor\n");
         }
         if ( x == y){
             printf("\n\tAcertaste, has ganado!!!!. Lo has logrado en %d intentos\n", contador);
         }

    }       // fin de do
         while (x != y);

	system("pause");
	system("cls");
}

//definicion de funciones de Laberinto

void menuLaberinto() {
	int i,r; 
	system("cls");
printf("\n\n");
char t[30][300]={"               ####",
	"              ######                               =====================",
	"               ####                          ===============================",
	"                                  ============================================" ,
	" __       ____     ______    _____   _____     __   ____   __  ______   ____",
    "|,||     |,,,,||  |,,...||  |,,__|| |,,__ \\\\  |,|| |,,,\\\\ |,|||,,,,,|| |,,,,||",
	"|,||    |,,| ,,|| |,||_|||  |,||    |,|__],|| |,|| |,|,,\\\\|,||  |,||  |,|| |,||",           																	                                                                                                                                                                     																					 
    "|,||    |,,|_|,|| |,,,,,\\\\  |,====  |,,,,,//  |,|| |,|\\,,\\|,||  |,||  |,|| |,||",
    "|,||    |,, _,,|| |,,,_,,|| |,====  |,,,__,\\  |,|| |,||\\,,!,||  |,||  |,|| |,||",                     
    "|,||__  |,|| |,|| |,||_|,|| |,||__  |,|| |,|| |,|| |,|| \\,,,||  |,||  |,||_|,||",
	"|_____|||_|| |_|| |______|| |_____|||_|| |,|| |_|| |_||  \\__||  |_||   |____|| " ,                                           
    "                                                                               ",
    "============================================================================",                                                    
    "       ===================================================================     ",
    "            ================================================"};
	for(i=0;i<=15;i++)
            puts(t[i]);
	printf("Juegue en pantalla completa.\n");
	system("pause");
	system("cls");
	srand(time(NULL));
 r=rand()%1;
 switch(r){
 	case 0:{
	


		char a[42][80]={"##############################################################################",
                    "#o  # ## #### ### ## # # # ## # ## ###### ## ##    # # # ##  ############### ##",
                    "## ###    ###### ###   #### #### ###      ### ## ## # #####  #  #####         #",
                    "## ### ##     ## # # #   # ## ## #  #### ###  ## ###    ### ## ##    ### #   ##",
                    "##     ## ### # ##   # # #     # ##  ### ## # ##  ## ##  # ##     # ## #####  #",
                    "### # ### ##  ## #  ## #   ###  ## ##  #### # ## # # ### ###  ##### # #  # ## #",
                    "## ### ## ## ####  ###  ####### ## ## ### ###  # ##  ###    ####### ###### #  #",
                    "####      ##                  # ## #### # #          # # #               ## # #",
                    "## # ## # # ## #  ### ####### #    # ##  ## ### # ## ## #  ######### ### ## # #",
                    "###  ### ## # ### ### ##    # ### ### ##### #  ## #       #### #  ##   #  # # #",
                    "### ## # #    ##   ## ## ## # ## ### ##     ## ##    ### ##    ####### ## #  ##",
                    "##    ## # # ##### ## #  ## #    ### # # ####     ##  ## #  ##       # ## #   #",
                    "## ## # ### ## # #    # ### ####  # ###  ###  # ### ## #  # ## ## ## # #  # # #",
                    "## ##   ##   # # ###### # #  ### ###    ##   ##   # # ###   # #   ##  # ### # #",
                    "## #### ## # # #        # ##    # ## # ### ## # # #      ## #  #   ## # ### # #",
                    "## ####    # # #  ####### # ## ## #  ##    # #  ## ###   ##   ### # # #     # #",
                    "##  ### # ## ### #      # ## # #### ### # # ## ###   ### ## ###   ### ## ## # #",
                    "###    #  #  # # ## ##   #       ##  ## # # ##     # ###     ## ### #    #    #",
                    "###### #  #         ##  #######         ###  # ### #  ## ###    ### ## ##### ##",
                    "########  ## # #### ##      ###### ### ## ## ### # ##### ##########  # ##### ##",	  
                    "######### # # # #   #######  ### ##### ## ## ## ## ## ###          ###       ##",
                    "#      ##  ## ### ##### ####           ####     ## ### ########## ##### #######",
                    "### ### ####           ## ### ### # ##  ###  ### # ## #                       #",
                    "###  ##  ### # ##  ###        ### ## ## ##  ## # #  # # ## # ### ### ### #### #",
                    "### ####     # ###  ############  ## ##    # # # #### ## # ### ### ##### ## # #",
                    "### ###  ##### ####     ###      #### ##### ## #      # #           #### #  # #",
                    "### ### ############### ### ######### #### # ## ####### # #########      ## # #",
                    "### ### ####         ## ### ## ##  ## ##               ## ###    ## # ##### # #",
                    "### ### #### #### ## ##     ### ## ## ## #####   ######## ### ##  # ## # ## # #",
                    "### ### #### #### ##    ############# ## #######    ####  ##  ##### # ## ## # #",
                    "##      #### ## # # ## ## ###         ##       ####          ##           # # #",
                    "## #### ####  ### ## ##### ## ###   #### #####  ####  ###### ## #### ####     >",
                    "## ####    ##  ### ###        ### #  ### ##   #   ### ### # ## ##  ### ## ## ##",
                    "## ####### ###  ###### ### ## ### ##     ## #  ## ###  ### # # # #      ## # ##",
                    "## #######  ###        ### ## ### ######### ## ## #### ## # ## ### # ##  ### ##",
                    "##          ##########  ## ## ###                 #### ####### # ### # #     ##",
                    "####### ###        #######    #########################        ###   ### ## ###",
                    "############# ############################################ #### # # ### #######",
                    "##########                                                 ### ##  ##  ##   ###",
                    "###############################################################################",
                    
                    };
	
   
                  
int i,x,y,fin;
char ch;
 x=1;
 y=1; 
 fin=0;

 for(i=0;i<=40;i++){
 puts(a[i]);}

 while(fin!=1)
 {
     ch = getch();
     if(ch == 's')
     {
         if(a[x+1][y] != '#')
         {
             a[x][y] = ' ';
             x++;
             a[x][y]='o';
         }
     }
    if(ch == 'w')
    {
         if(a[x-1][y] != '#')
         {
             a[x][y] = ' ';
             x--;
             a[x][y]='o';
         }
    }
    if(ch == 'a')
    {
         if(a[x][y-1] != '#')
         {
             a[x][y] = ' ';
             y--;
             a[x][y]='o';
         }
    }
    if(ch == 'd')
    {
         if(a[x][y+1] != '#')
         {if(a[x][y+1]=='>'){
         	 a[x][y] = ' ';
             y++;
             a[x][y]='o';fin=1;
		 }else{
		 
             a[x][y] = ' ';
             y++;
             a[x][y]='o';
         }}
         
    }
         system("cls");
         for(i=0;i<=40;i++)
      	puts(a[i]);
    }
     system("cls");
         for(i=0;i<=40;i++)
      	puts(a[i]);
    printf("¡Vaya, ganaste!  "); 
    contadorL +=1;
	break;}
    case 1:{
	
    
    char b[42][80]={"##############################################################################",
                    "#o  # ## #### ### ## # # # ## # ## ###### ## ##    # # #     ############### ##",
                    "##     ################################################  ###       ############",
                    "## ###                           ##                     ##########  ###   #####",
                    "## ###    ################# #### #### ################# ### #######    ###    #",
                    "## ### ##                   ####                        ### ###          #   ##",
                    "## ### #### ######## ################### #### ###  ### #### #### ### ###  ## ##",
                    "## ### ####  #######             ####### ### #### ####  ###   ## ### ####    ##",
                    "## ### #### ########  #   ######  ###### ########  # ##  ####    ### #### ## ##",
                    "#  ### ###  ##       ###### #                    # #  ##    #### ###   ## #  ##",
                    "#   ## #### ## ############  ###################   ## ######     ##### ## ## ##",
                    "## ###    # ##                                    ###                # ## ## ##",
               		"## ######   ############### ##### ### ##### # ### #### ##### ####### #  # ## ##",
                	"##  ## ## #    ## ####      ####   ## ### ### # # ### ### ##### # ## #### ## ##",
                	"### #### ### ######    ######## ## ##     #######               #  # ####  # ##",
                	"### ###      #    # #######     ## ######     ################# # ## #####   ##",
                	"### ##  ###### ##   ############## ##########         ######### # ##       # ##",
                	"##  ## ####### #### ###                   ### ####### ####      # ## ##### #  #",
                	"#    #            #    ################## ###         ###  # ## ## # ##### #  #",
                	"# #### ############# #################### ################ ## # ####  ### # # #",
					"# # ## ###                   ##       ###  #               # # ##  ##  ##   ###",
                    "# #  # ######### ###### ######## ######## ############### ## # ##### # ## #####",
                    "# ## # ######### ### #    ### ##      ### ##              ## #    ### ### #####",
                    "# #### ######### ### ####   ## # #### ##  ## ##  ###  ## ### ####   # ### #####",
                    "#    #         # ### ## ###  ### ####    ###  ##   ## ## ### ####  ## ###   ###",
                    "###    ######### ### # #   ##### ########## ## # #### #  ### ######## ##### ###",
                    "###### ######### ###### ##                   # #   ## # #                ## ###",
                    "###### ##               ## ################### ### ## # ## ###   #  #  # ## ###",
                    "###### ## ################ ####       ###   ## #      #### ##  ### #  ## ## ###",
                    "######### ######           #### ##### ### # ###  #### # ## #  #### ## ## ## ###",
                    "##        ###### ###### #######    ## ### # ####  ##### ## ##### # ## ##      >",
                    "## ############# ###### ########## ## ### #    ##  #### ##         ## ## ### ##",
                    "## ############# ######            ## ### #### ###      ########## ## ## ### ##",
                    "#  #             ############# ######   # #### ### ############### ## ## ### ##",
                    "## # ##############        ### ########## #### ###       ##        ##### ### ##",
                    "## # ############## ###### ###                    ######### ########## # ### ##",
                    "## #                ## ### ################## ### ######### #######      ### ##",
                    "## ################### ### ################# #  ##          #       ######## ##",
                    "##                     ###                         #################         ##",
                    "###############################################################################",
                    };
	   
                  
int i,x,y,fin;
char ch;
 x=1;
 y=1; 
 fin=0;

 for(i=0;i<=40;i++){
 puts(b[i]);}

 while(fin!=1)
 {
     ch = getch();
     if(ch == 's')
     {
         if(b[x+1][y] != '#')
         {
             b[x][y] = ' ';
             x++;
             b[x][y]='o';
         }
     }
    if(ch == 'w')
    {
         if(b[x-1][y] != '#')
         {
             b[x][y] = ' ';
             x--;
             b[x][y]='o';
         }
    }
    if(ch == 'a')
    {
         if(b[x][y-1] != '#')
         {
             b[x][y] = ' ';
             y--;
             b[x][y]='o';
         }
    }
    if(ch == 'd')
    {
         if(b[x][y+1] != '#')
         {if(b[x][y+1]=='>'){
         	 b[x][y] = ' ';
             y++;
             b[x][y]='o';fin=1;
		 }else{
		 
             b[x][y] = ' ';
             y++;
             b[x][y]='o';
         }}
         
    }
         system("cls");
         for(i=0;i<=40;i++)
      	puts(b[i]);
    }
     system("cls");
         for(i=0;i<=40;i++)
      	puts(b[i]);
    printf("¡Vaya, ganaste!  ");
    contadorL +=1;
	break;}	
	}
}


void corteDeControl() {

	inicializacion();
	procesoCorte();
	finalizacion();
}

void inicializacion(){

	vf_usuarios = fopen("Usuarios.dat", "rb");
	fread(&usuario, sizeof(t_data), 1, vf_usuarios);
	totalPuntaje = 0;
	
	printf("Lista de Usuarios:\n\n");
	printf("Nombre de Usuario   | 3 en Linea | Pong | Snake | Adivinanza | Laberinto\n");
}

void procesoCorte(){
	while(!feof(vf_usuarios)) {
		inicioCorte();
		
		while(!feof(vf_usuarios) && strcmp(usuario.user, userAnt) == 0) {
			procesarUsuario();
			fread(&usuario, sizeof(t_data), 1, vf_usuarios);
		}
		
		finCorte();
	}
	
}

void inicioCorte() {
	contador3IL = 0;
	contadorP = 0;
	contadorS = 0;
	contadorA = 0; 
	contadorL = 0;
	
	strcpy(userAnt, usuario.user);
	printf("%s", userAnt);
}

void procesarUsuario() {
	contador3IL += usuario.contador3IL;
	contadorP += usuario.contadorP;
	contadorS += usuario.contadorS;
	contadorA += usuario.contadorA;
	contadorL += usuario.contadorL;
}

void finCorte() {
	totalPuntaje = contador3IL + contadorP + contadorS + contadorA + contadorL;
	
	printf("\t\t\t%d\t   %d   \t    %d   \t%d\t%d\n", contador3IL, contadorP, contadorS, contadorA, contadorL);
	
	printf("\nTotal Puntaje del Usuario %s: %d.", userAnt, totalPuntaje);
	printf("\n-------------------------------------------------------------------------------\n");
}

void finalizacion() {
	fclose(vf_usuarios);
}

void seleccionUsuario(){
	int i=1,valorDeUsuario,IL,A,L,P,S;
	t_string pnombre;
	t_data v_auxUser;
	extra = fopen("AuxUsuarios.dat", "wb");
	vf_usuarios = fopen("Usuarios.dat", "rb");
	fread(&usuario, sizeof(t_data), 1, vf_usuarios);
	while(!feof(vf_usuarios)){
		strcpy(pnombre,usuario.user);
	
		IL=0;
		A=0;
		L=0;
		P=0;
		S=0;
		
		while(!feof(vf_usuarios)&&strcmp(pnombre,usuario.user)==0){
			IL=IL+usuario.contador3IL;
		
			A=A+usuario.contadorA;
			L=L+usuario.contadorL;
			P=P+usuario.contadorP;
			S=S+usuario.contadorS;
			
			fread(&usuario, sizeof(t_data), 1, vf_usuarios);	}
		
	
		strcpy(v_auxUser.user,pnombre);
			v_auxUser.contador3IL=IL;
			v_auxUser.contadorA=A;
			v_auxUser.contadorL=L;
			v_auxUser.contadorP=P;
			v_auxUser.contadorS=S;
			
			fwrite(&v_auxUser, sizeof(t_data), 1, extra);
	}
	fclose(vf_usuarios);
	fclose(extra);
	vf_usuarios = fopen("Usuarios.dat", "rb");
	if(vf_usuarios==NULL) {
		printf("No se ha ingresado usuarios aún.\n\n");
		fclose(vf_usuarios);
		} 
	else {
		
	printf("\nSeleccionar usuario:\n\n	");
	extra = fopen("AuxUsuarios.dat", "rb");
	fread(&usuario, sizeof(t_data), 1, extra);
	while(!feof(extra)){
		printf("%d-%s\n	",i,usuario.user);
		fread(&usuario, sizeof(t_data), 1, extra);
		i=i+1;}
		fclose(extra);
		printf("\nNumero : ");
		scanf("%d",&valorDeUsuario);
		reescribir(valorDeUsuario);}
}
		
void reescribir(int pvalorDeUsuario) {
	int i=1,IL=0,A=0,L=0,P=0,S=0;
	t_string pnombre;
	t_data v_auxUser;
	extra = fopen("AuxUsuarios.dat", "rb");
	vf_usuarios = fopen("Usuarios.dat", "wb");
	fread(&usuario, sizeof(t_data), 1, extra);
	while(!feof(extra)){
		if(i==pvalorDeUsuario){
			IL=usuario.contador3IL;
			A=usuario.contadorA;
			L=usuario.contadorL;
			P=usuario.contadorP;
			S=usuario.contadorS;
			strcpy(pnombre,usuario.user);
			fread(&usuario, sizeof(t_data), 1, extra);	}
			else{
		
		strcpy(v_auxUser.user,usuario.user);
			v_auxUser.contador3IL=usuario.contador3IL;
			v_auxUser.contadorA=usuario.contadorA;
			v_auxUser.contadorL=usuario.contadorL;
			v_auxUser.contadorP=usuario.contadorP;
			v_auxUser.contadorS=usuario.contadorS;
			fread(&usuario, sizeof(t_data), 1,extra );	
			fwrite(&v_auxUser, sizeof(t_data), 1, vf_usuarios);}
			i=i+1;
		}
	fclose(vf_usuarios);
	fclose(extra);
	vf_usuarios = fopen("Usuarios.dat", "ab");
	
	strcpy(v_auxUser.user,pnombre);
	v_auxUser.contador3IL = IL;
	v_auxUser.contadorA = A;
	v_auxUser.contadorL = L;
	v_auxUser.contadorP = P;
	v_auxUser.contadorS = S;
	fwrite(&v_auxUser, sizeof(t_data), 1, vf_usuarios);
	fclose(vf_usuarios);
	ingresarDatosUsuario(pnombre,0,0,0,0,0);
	newUser=true;
}
