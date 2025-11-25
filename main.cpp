//Pablo de la Iglesia y Lucia Parreño
#include <iostream>
#include <windows.h>
#include <fstream>
using namespace std;
//Un enumerado para saber que hay en cada casilla
enum Casilla{VACIO,JUGADOR1,JUGADOR2};
//Estructura del tablero
typedef struct{
	//Matriz de que hay en cada casilla
	Casilla matriz[6][8];
	//Contador de cuantos espacios quedan
	int contEsp;
}Tablero;
//Estructura de jugador
typedef struct{
	//Su nombre
	string nick;
	//Numero de partidas ganadas
	int nGanadas;
	//Numero de partias perdidas
	int nPerdidas;
}Jugador;
//Estructura de datos de todos los jugadores
typedef struct{
	//Numero de jugadores registrados
	int nRegistrados;
	//Jugadores
	Jugador jugadores[100];
}DatosPartida;



//función que devuelve true si hay espacios libres en el tabrero y false en caso contrario
bool quedanHuecos(const Tablero t);
//procedimiento que, dada una casilla, muestra el caracter correspondiente al jugador 1, jugador 2 (o máquina) o casilla vacía en el color correspondiente
void muestraCharColor(Casilla c);
//procedimiento que, dado un Tablero lo muestra en la consola en forma de tablero gráfico
void muestraTablero(const Tablero t);
/*función que, dados un tablero y un número de columna, busca el hueco adecuado para
inertar la ficha y devuelve el valor de la fila de dicho hueco (EN ESTA FUNCIÓN NO SE
GUARDA LA FICHA EN EL TABLERO (!!))
*/
int ponerFicha(const Tablero t, int columna);
//función que devuelve true si una columna ya está llena y no caben más fichas; false en caso contrario
bool columnaLlena(const Tablero t, int columna);
//función que comprueba si un jugador es ganador
bool ganador(const Tablero t, int fila, int columna, int jugador);
//procedimiento encargado de poner todas las casillas del tablero a "VACIO"
void inicializaTablero(Tablero &t);
//procedimiento encargado de la ejecución principal del juego
void juegoConecta4(Tablero t, Jugador &j, DatosPartida &d);

// Versión 2:
// devuelve los datos del jugador con el nick especificado. Si no existe, se crea un nuevo jugador
Jugador iniciarSesion(DatosPartida &d, string nick);
// busca al jugador con el nick especificado y devuelve un entero indicando su posición en la lista. Si no lo encuentra, devuelve -1
int buscaJugador(DatosPartida d, string nick);
// carga los datos de los jugadores del archivo "jugadores.txt"
void cargaDatos(DatosPartida &d);
// muestra la información del jugador con el nick especificado
void muestraInfo(DatosPartida d, string nick);
// muestra la información de todos los jugadores registrados
void infoJugadores(DatosPartida d);
// actualiza la lista de jugadores con los nuevos datos del jugador j
void actualizaJugador(DatosPartida &d, Jugador j);
// añade un nuevo jugador a la lista. Si no cabe, muestra un mensaje de error
void guardaJugadorNuevo(DatosPartida &d, Jugador j);
// guarda los datos de todos los jugadores registrados en el archivo "jugadores.txt"
void guardaDatos(DatosPartida d);


int main(){
	//Declaramos variables
	int i=0, fila, columna, eleccion;
	bool ganador1=false,d1=false,d2=false,d3=false,d4=false;
	bool quedanhuecos=true;
	string nick;
	//Declaramos estructura tipo tablero
	Tablero T;
	//Declaramos estructura de datos de partida
	DatosPartida D;
	//Declaramos el jugador que va a jugar
	Jugador J;
	//Cargamos los datos del fichero
	cargaDatos(D);
	//Pedimos el nick del jugador que va a jugar
	cout<<"BIENVENIDO A CONECTA 4"<<endl;
	cout<<"INTRODUCE TU NICK: ";
	cin>>nick;
	//Pedimos los datos del jugador iniciando sesion
	J=iniciarSesion(D,nick);
	//Menu
	cout<<"MENU"<<endl;
	cout<<"0.Salir"<<endl<<"1.Jugar"<<endl<<"2.Ver mi informacion"<<endl<<"3.Ver informacion de los jugadores registrados"<<endl<<"4.Buscar informacion de un jugador"<<endl;
	cin>>eleccion;
	//Si es un numero menor a 0 o mayor a 4 se pide de nuevo
	while(eleccion<0||eleccion>4){
		cout<<"Introduce un numero del 0-4: ";
		cin>>eleccion;
	}
	//Switch con lo que hayan elegido
	switch(eleccion){
		case 0:
			break;
		case 1:
			//Empieza el juego
			juegoConecta4(T,J,D);
			break;
		case 2:
			//Muestra la informacion del jugador
			muestraInfo(D,J.nick);
			break;
		case 3:
			//Se muestra la info de todos los jugadores registrados
			infoJugadores(D);
			break;
		case 4:
			//Se pide el nick a buscar
			cout<<"Nick de jugador a buscar: ";
			cin>>nick;
			//Se muestra la info del jugador con el nick aportado
			muestraInfo(D,nick);
			break;
	}
	//Se actualiza la info del jugador
	actualizaJugador(D,J);
	//Se guardan de nuevo los datos de todos los jugadores en el fichero
	guardaDatos(D);
	return 0;
}
void guardaDatos(DatosPartida d){
	//Abrimos fichero de jugadores para escribir
	ofstream fichero1("jugadores.txt");
	//Si se abre
	if(fichero1.is_open()){
		//Guardamos todos los datos 
		fichero1<<d.nRegistrados<<endl;
		for(int i=0;i<d.nRegistrados;i++){
			fichero1<<d.jugadores[i].nick<<" "<<d.jugadores[i].nGanadas<<" "<<d.jugadores[i].nPerdidas<<endl;
		}
	}
	//Si no se abre muestra ERROR
	else{
		cout<<"NO SE PUDO ABRIR EL FICHERO PARA GUARDAR LOS DATOS"<<endl;
	}
	//Cerramos fichero
	fichero1.close();
}
void actualizaJugador(DatosPartida &d, Jugador j){
	int pos;
	//Buscamos la posicion en la lista del jugador a actualizar
	pos=buscaJugador(d,j.nick);
	//Pasamos el numero de ganadas nuevo a la lista
	d.jugadores[pos].nGanadas=j.nGanadas;
	//Pasamos el numero de perdidas nuevo a la lista
	d.jugadores[pos].nPerdidas=j.nPerdidas;
}
void infoJugadores(DatosPartida d){
	//Bucle de todos los jugadores de la lista mostrando su info
	for(int i=0;i<d.nRegistrados;i++){
		cout<<endl<<"Nick: "<<d.jugadores[i].nick<<endl;
		cout<<"Partidas ganadas: "<<d.jugadores[i].nGanadas<<endl;
		cout<<"Partidas perdidas: "<<d.jugadores[i].nPerdidas<<endl;
	}
}
void muestraInfo(DatosPartida d, string nick){
	int pos;
	//Buscamos la posicion del Jugador a buscar
	pos=buscaJugador(d,nick);
	//Si no se encuentra se muestra ERROR
	if(pos==-1){
		cout<<"ESTE JUGADOR NO ESTA EN LA LISTA"<<endl;
	}
	//Si se encuentra se muestra su informacion
	else {	
		cout<<"INFORMACION DE "<<nick<<":"<<endl;
		cout<<"Partidas ganadas: "<<d.jugadores[pos].nGanadas<<endl;
		cout<<"Partidas perdidas: "<<d.jugadores[pos].nPerdidas<<endl;
	}
}
void cargaDatos(DatosPartida &d){
	//Abrimos ficheros para leer
	ifstream fichero("jugadores.txt");
	//Si se puede abrir
	if(fichero.is_open()){
		//Se guarda el numero de registrados
		fichero>>d.nRegistrados;
		//Bucle para guardar toda la informacion de cada unp
		for(int i=0;i<d.nRegistrados;i++){
			fichero>>d.jugadores[i].nick;
			fichero>>d.jugadores[i].nGanadas;
			fichero>>d.jugadores[i].nPerdidas;
		}
	}
	else{
		cout<<"El fichero de jugadores no se pudo abrir :("<<endl;
	}
	fichero.close();
}
int buscaJugador(DatosPartida d, string nick){
	//Bucle de la lista de jugadores
	for(int i=0;i<d.nRegistrados;i++){
		//Si alguno tiene el mismo nick al que se pide buscar se devuelve la posicion
		if(nick==d.jugadores[i].nick){
			return i;
		}
	}
	//Sino se pasa -1
	return -1;
}
void guardaJugadorNuevo(DatosPartida &d, Jugador j){
	//Si se alcanza el numero maximo de registrados se muestra un error
	if(d.nRegistrados==100){
		cout<<"ERROR, numero maximo de jugadores en el fichero alcanzado"<<endl;
	}
	else{
		//Se suma el numero de registrados
		d.nRegistrados++;
		//Se guarda su nick y se le pone a 0 sus estadisticas 
		d.jugadores[d.nRegistrados-1].nGanadas=0;
		d.jugadores[d.nRegistrados-1].nPerdidas=0;
		d.jugadores[d.nRegistrados-1].nick=j.nick;
	}
}
Jugador iniciarSesion(DatosPartida &d, string nick){
	//Declaramos un jugador
	Jugador J;
	int pos;
	//Guardamos la posicion del jugador que inicia sesion
	pos=buscaJugador(d,nick);
	//Si no existe
	if(pos==-1){
		//Guardamos su info en el jugador y lo pasamos a crear un nuevo jugador
		J.nick=nick;
		J.nGanadas=0;
		J.nPerdidas=0;
		guardaJugadorNuevo(d,J);
	}
	//Si ya existe
	else{
		//Guardamos la info de este jugador en J
		J.nick=d.jugadores[pos].nick;
		J.nGanadas=d.jugadores[pos].nGanadas;
		J.nPerdidas=d.jugadores[pos].nPerdidas;
	}
	//Devolvemos el jugador
	return J;

}
int ponerFicha(const Tablero t, int columna){
	//Bucle de toda la columna
	for(int i=0;i<6;i++){
		//Si esta vacio el espacio, empezando por el mas abajo
		if(t.matriz[5-i][columna]==VACIO){
			//Devolvemos ese espacio
			return 5-i;
		}
	}
}
bool quedanHuecos(const Tablero t){
	//Si no quedan huecos devolvemos false
	if(t.contEsp==0){
		return false;
	}
	//Si si quedan devolvemos true
	else{
		return true;
	}
}
bool ganador(const Tablero t, int fila, int columna, int jugador){
	bool d1=false,d2=false;
	int contador=0;
	//Declaramos una casilla
	Casilla c;
	//Si pasamos 1 la casilla es de jugador1 y si no de jugador 2
	if(jugador==1){
		c=JUGADOR1;
	}
	else{
		c=JUGADOR2;
	}
	//Bucle para comprobar si en la columna hay 4 fichas seguidas del jugador
	for(int i=0;i<6;i++){
		//si la ficha es del jugador sumamos 1 al contador
		if(t.matriz[i][columna]==c){
			contador++;
		}
		//Si no volvemos el contador a 0
		else{
			contador=0;
		}
		//Si el contador llega a 4 mostramos el ganador y devolvemos true
		if(contador==4){
			return true;
		}
	}
	//Ponemos contador a 0
	contador=0;
	//Bucle para comprobar si en la fila hay 4 fichas seguidas del jugador
	for(int i=0;i<8;i++){
		if(t.matriz[fila][i]==c){
			contador++;
		}
		else{
			contador=0;
		}
		if(contador==4){
			return true;
		}
	}
	contador=1;
	int i=0;
	//Bucle para la primera diagonal con maximo de 6 y con contador de 1 en inicio
	while(i<6){
		//Si se llega al final de la matriz no se sigue comprobando mas
		if(fila+1+i>5||columna+1+i>7){
			d1=true;
		}
		//Si la casilla siguiente es del jugador se suma 1 al contador
		if(t.matriz[fila+1+i][columna+1+i]==c && d1==false){
			contador++;
		}
		//Si no lo es se para de contar
		else{
			d1=true;
		}
		//Si se llega al final de la matriz se para de comprobar
		if(fila-1-i<0||columna-1-i<0){
			d2=false;
		}
		//Si la casilla anterior es del jugador se suma 1 al contador
		if(t.matriz[fila-1-i][columna-1-i]==c && d2==false){
			contador++;
		}
		//Sino se para de contar
		else{
			d2=true;
		}
		//Se pasa a la siguiente
		i++;
	}
	//Si se ha llegado a las 4 fichas se declara ganador
	if(contador>=4){
		return true;
	}
	i=0;
	d1=false;
	d2=false;
	contador=1;
	//Bucle segunda diagonal
	while(i<6){
		if(fila+1+i>5||columna-1-i<0){
			d1=true;
		}
		if(t.matriz[fila+1+i][columna-1-i]==c && d1==false){
			contador++;
		}
		else{
			d1=true;
		}
		if(fila-1-i<0||columna+1+i>7){
			d2=true;
		}
		if(t.matriz[fila-1-i][columna+1+i]==c && d2==false){
			contador++;
		}
		else{
			d2=true;
		}
		if(d1==true && d2==true){
			break;
		}
		i++;
	}
	if(contador>=4){
		return true;
	}
	//Si no cumple nada de esto se devuelve que no hay ningún ganador
	return false;
}
bool columnaLlena(const Tablero t, int columna){
	//Comprobar si el espacio de mas arriba de la columna esta libre
	if(t.matriz[0][columna]==VACIO){
		return false;
	}
}
void juegoConecta4(Tablero T, Jugador &j, DatosPartida &d){
	int i=0, fila, columna;
	bool ganador1=false,d1=false,d2=false,d3=false,d4=false, columnallena;
	bool quedanhuecos=true;
	//Declaramos que hay 48 espacios en toal
	T.contEsp=48;
	//Inicializamos tablero
	inicializaTablero(T);
	//Mostramos el tablero
	muestraTablero(T);
	//Bucle continuo si no hay un ganador o si aun quedan huecos
	while(ganador1==false && quedanhuecos==true){
		//Guardamos columna
		//Pedimos en que columna quieren poner la ficha
		int n;
		cout<<"INTRODUCE COLUMNA PARA PONER FICHA: ";
		cin>>n;
		//comprobamos si esta libre la columna
		columnallena=columnaLlena(T,n-1);
		//Si la columna esta llena o el numero no es valido se le muestra
		while(n<1||n>8||columnallena==true){
			cout<<"COLUMNA NO VALIDA"<<endl;
			cin>>n;
			columnallena=columnaLlena(T,n-1);
		}
		columna=n-1;
		//Encontramos la fila
		fila=ponerFicha(T,columna);
		//Si es par juega el jugador 1
		if(i%2==0){
			//Ponemos la ficha del jugador en la matriz
			T.matriz[fila][columna]=JUGADOR1;
			//Limpiamos pantalla
			system("cls");
			//Mostramos tablero
			muestraTablero(T);
			//Comprobamos si gana
			ganador1=ganador(T,fila,columna,1);
			//Si gana
			if(ganador1==true){
				//Se muestra como ganador y se le suma 1 a su numero de partidas ganadas
				cout<<j.nick<<" GANADOR"<<endl;
				j.nGanadas++;
			}
		}
		//Si es impar juega el jugador 2
		else{
			//Ponemos la ficha del jugador en la matriz
			T.matriz[fila][columna]=JUGADOR2;
			//Limpiamos pantalla
			system("cls");
			//mostramos tablero
			muestraTablero(T);
			//Comprobamos si gana
			ganador1=ganador(T,fila,columna,2);
			if(ganador1==true){
				//Si el jugador 2 gana se muestra el usuario como perdedor
				cout<<j.nick<<" PERDEDOR"<<endl;
				//Se le suma una partida perdida al usuario
				j.nPerdidas++;
			}
		}
		//Restamos un espacio libre
		T.contEsp--;
		//Comprobamos si quedan huecos
		quedanhuecos=quedanHuecos(T);
		//Sumamos 1 a i para saber si es par o no
		i++;
	}
	//Si no quedan huecos marcar empate
	if(quedanhuecos==false){
		cout<<"EMPATE"<<endl;
	}
}
void muestraCharColor(Casilla c){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if (c == JUGADOR1) {
		SetConsoleTextAttribute(hConsole, 6);
		cout << char(4);
		SetConsoleTextAttribute(hConsole, 15);
	}
	else if (c == JUGADOR2){
		SetConsoleTextAttribute(hConsole, 4);
		cout << char(4);
		SetConsoleTextAttribute(hConsole, 15);
	}
	else{
		cout << " ";
	}
}

void muestraTablero(const Tablero t){
	cout<<"CONECTA4"<<endl;
	//Primera linea
	cout<<char(218);
	for(int i=0;i<15;i++){
		if(i%2==0){
			cout<<char(196)<<char(196)<<char(196);
		}
		else{
			cout<<char(194);
		}
	}
	cout<<char(191);
	cout<<endl;
	//Lineas de en medio
	for(int i=0;i<11;i++){
		if(i%2==0){
			for(int j=0;j<17;j++){
				if(j%2==0){
					cout<<char(179);
				}
				else{
					cout<<" ";
					muestraCharColor(t.matriz[(i+1)/2][j/2]);
					cout<<" ";
				}
			}
			cout<<endl;
		}
		else{
			cout<<char(195);
			for(int j=0;j<15;j++){
				if(j%2==0){
					cout<<char(196)<<char(196)<<char(196);
				}
				else{
					cout<<char(197);
				}
			}
			cout<<char(180);
			cout<<endl;
		}
	}
	//Ultima linea
	cout<<char(192);
	for(int i=0;i<15;i++){
		if(i%2==0){
			cout<<char(196)<<char(196)<<char(196);
		}
		else{
			cout<<char(193);
		}
	}
	cout<<char(217)<<endl;
	cout<<"  1   2   3   4   5   6   7   8"<<endl;
}
void inicializaTablero(Tablero &t){
	//Para cada casilla se la pone en VACIO
	for(int i=0;i<6;i++){
		for(int j=0;j<8;j++){
			t.matriz[i][j]=VACIO;
		}
	}
}
