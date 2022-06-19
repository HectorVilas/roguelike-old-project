#include <iostream>
#include <fstream>
#include <conio.h>
#include <windows.h>
using namespace std;

void cargar(char m[][75], fstream& nivel){
	for(int i=0; i<20; i++){
		string s;
		getline(nivel, s);
		for(int j=0; j<75; j++){
			m[i][j]=s[j];
		}
	}
}

void mostrar(char m[][75], int hp, int v, int h){
	cout << "HP: " << hp << endl << endl;
	cout << "ubicacion : h=" << h+1 << " v=" << v+1 << endl;
	for(int i=0; i<20; i++){
		for(int j=0; j<75; j++){
			cout << m[i][j];
		}
		cout << endl;
	}
}

void buscar_pj(char m[][75], int& v, int& h){
	for(int i=0; i<20; i++){
		for(int j=0; j<75; j++){
			if(m[i][j]=='@'){
				v=i;
				h=j;
			}
		}
	}
}

void input(char m[][75], int& v, int& h, int& hp, bool& refresh, fstream& save){
	int n;
	n=getch();
	switch(n){
		case(49)://suroeste
			if(m[v+1][h-1]==' '){
				swap(m[v][h], m[v+1][h-1]);
				h-=1;
				v+=1;
				refresh=true;
			}else{
				refresh=false;
			}
			break;
		case(50)://sur
			if(m[v+1][h]==' '){
				swap(m[v][h], m[v+1][h]);
				v+=1;
				refresh=true;
			}else{
				refresh=false;
			}
			break;
		case(51)://sureste
			if(m[v+1][h+1]==' '){
				swap(m[v][h], m[v+1][h+1]);
				h+=1;
				v+=1;
				refresh=true;
			}else{
				refresh=false;
			}
			break;
		case(52)://oeste
			if(m[v][h-1]==' '){
				swap(m[v][h], m[v][h-1]);
				h-=1;
				refresh=true;
			}else{
				refresh=false;
			}
			break;
//		case(53)://pasar turno
//			break;
		case(54)://este
			if(m[v][h+1]==' '){
				swap(m[v][h], m[v][h+1]);
				h+=1;
				refresh=true;
			}else{
				refresh=false;
			}
			break;
		case(55)://noroeste
			if(m[v-1][h-1]==' '){
				swap(m[v][h], m[v-1][h-1]);
				h-=1;
				v-=1;
				refresh=true;
			}else{
				refresh=false;
			}
			break;
		case(56)://norte
			if(m[v-1][h]==' '){
				swap(m[v][h], m[v-1][h]);
				v-=1;
				refresh=true;
			}else{
				refresh=false;
			}
			break;
		case(57)://noreste
			if(m[v-1][h+1]==' '){
				swap(m[v][h], m[v-1][h+1]);
				h+=1;
				v-=1;
				refresh=true;
			}else{
				refresh=false;
			}
			break;
		case(27)://escape, salir
			hp=0;
			break;
		case(115)://tecla "s", save
			for(int i=0; i<20; i++){
				string s;
				for(int j=0; j<75; j++){
					s+=m[i][j];
				}
				save << s << endl;
			}
			cout << "Partida guardada." << endl;
			refresh=false;
			break;
		default:
			refresh=false;
			break;
	}
}


int main(){
	//variables iniciales
	int v=0, h=0; //ubicación pj
	int nuevo=0;
	bool refresh=true;
	fstream nivel;
	fstream save;
	save.open("save.txt");
	int hp=50;
	char mapa[20][75];
		
	//menú ppal
	cout << endl << endl << endl << endl << endl << endl << endl << endl;
	cout << "                             R O";system("color 1");Beep(200, 1000);
	cout << " G U E ";system("color 19");Beep(300, 1000);cout << "L I K E";
	system("color 9f");Beep(400, 1000); 
	Beep(0, 1200);system("color 16");Beep(480, 350);system("color 7");
	Beep(450, 1000);Beep(0, 700);cout << endl << endl << endl << endl;
	cout << "                         [N]ue";system("color 1f");Beep(110, 300);
	cout << "vo  [C]";system("color 7");Beep(80, 300);
	cout << "argar  ";system("color 1f");Beep(110, 300);
	cout << "[S]alir" << endl;system("color 7");Beep(80, 300);
	while(nuevo!=110 && nuevo!=78 && nuevo!=99 //N:110 78   C:99 67   S:115 83
		&& nuevo!=67 && nuevo!=115 && nuevo!=83){
		nuevo=getch();
		}
	if(nuevo==110 || nuevo==78){ //N
		nivel.open("01.txt");
		Beep(700, 100);
	}else if(nuevo==99 || nuevo==67){ //C
		nivel.open("save.txt");
		Beep(300, 100);
	}else{
		hp=0;
	}
	system("CLS");
	
	//preparando mapa
	cargar(mapa, nivel);
	nivel.close();
	buscar_pj(mapa, v, h);
	
	//iniciando partida
	while(hp>0){
		if(refresh==true){
			mostrar(mapa, hp, v, h);
		}
		input(mapa, v, h, hp, refresh, save);
		if(refresh==true){
			system("CLS");
		}
	}
	system("CLS");
	save.close();

	do{ //pantalla game over
		cout << "       ______________" << endl;
		system("color 1f");Beep(200, 400);
		cout << "       \\_   _____/|__| ____" << endl;
		system("color 1f");Beep(200, 400);
		cout << "        |    __)  |  |/    \\" << endl;
		system("color 9f");Beep(210, 400);
		cout << "        |     \\   |  |   |  \\" << endl;
		system("color bf");Beep(225, 400);
		cout << "        \\___  /   |__|___|  /" << endl;
		system("color ff");Beep(225, 400);
		cout << "            \\/            \\/" << endl;
		system("color bf");Beep(210, 400);
		cout << "            ____     ___" << endl;
		system("color 9f");Beep(200, 400);
		cout << "          __| _/____ |  |" << endl;
		system("color 1f");Beep(185, 400);
		cout << "         / __ |/ __ \\|  |" << endl;
		system("color 0f");Beep(160, 400);
		cout << "        / /_/ \\  ___/|  |__" << endl;
		system("color 0f");Beep(160, 400);
		cout << "        \\____ |\\___  >____/" << endl;
		system("color 1f");Beep(170, 400);
		cout << "             \\/    \\/" << endl;
		system("color 9f");Beep(200, 400);
		cout << "     __"<< endl;
		cout << "    |__|__ __   ____   ____   ____" << endl;
		system("color 9f");Beep(200, 700);
		cout << "    |  |  |  \\_/ __ \\ / ___\\ /  _ \\" << endl;
		cout << "    |  |  |  /\\  ___// /_/  >  <_> )" << endl;
		system("color 1f");Beep(175, 200);
		cout << "/\\__|  |____/  \\___  >___  / \\____/" << endl;
		cout << "\\______|           \\/_____/" << endl;
		system("color 0f");Beep(175, 300);
		Sleep(500);
		system("color 0f");Sleep(50);system("color 0b");Sleep(50);
		system("color 09");Sleep(50);system("color 01");Sleep(50);
		system("color 00");Sleep(500);
	}while(false);
}
