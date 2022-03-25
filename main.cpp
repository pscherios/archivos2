#include <iostream>
#include <string.h>
#include <stdio.h>

using namespace std;
const char *nombre_archivo="archivo2.dat";

struct Alumno{
	int codigo;
	char nombre[30];
	char apellido[30];
	char direccion[50];
	int telefono;
};

void agregar_alumno();
void ver_alumno();
void modificar_alumno();
void buscar_alumno();
void eliminar_alumno();

int main(){
	ver_alumno();
	agregar_alumno();
	modificar_alumno();
	buscar_alumno();
	eliminar_alumno();
	return 0;
}

void buscar_alumno(){
	FILE* archivo=fopen(nombre_archivo,"rb");
	int pos=0,ind=0,cod=0;
	cout<<"Que codigo desea ver: ";
	cin>>cod;
	
	Alumno alumno;
	fread(&alumno,sizeof(Alumno),1,archivo);
	do{
		if(alumno.codigo==cod){
			cout<<"Codigo: "<<alumno.codigo<<endl;
			cout<<"Nombre: "<<alumno.nombre<<endl;
			cout<<"Apellido: "<<alumno.apellido<<endl;
			cout<<"Direccion: "<<alumno.direccion<<endl;
			cout<<"Telefono: "<<alumno.telefono<<endl;
		}
		fread(&alumno,sizeof(Alumno),1,archivo);
	}while(feof(archivo)==0);
	fclose(archivo);
}

void ver_alumno(){
	system("cls");
	FILE* archivo=fopen(nombre_archivo,"rb");
	if(!archivo){
		archivo=fopen(nombre_archivo,"w+b");
	}
	Alumno alumno;
	int registro=0;
	fread(&alumno,sizeof(Alumno),1,archivo);
	cout<<"--------------------------------"<<endl;
	cout<<"Id"<<"|"<<"Codigo"<<"|"<<"Nombre"<<" "<<"Apellido"<<" "<<"Direccion"<<" "<<"Telefono"<<" "<<endl;
	do{
		cout<<"------------------------------------"<<endl;
		cout<<registro<<"|"<<alumno.codigo<<"|"<<alumno.nombre<<" "<<alumno.apellido<<" "<<alumno.direccion<<" "<<alumno.telefono<<endl;
		fread(&alumno,sizeof(Alumno),1,archivo);
		registro+=1;
	}while(feof(archivo)==0);
	cout<<endl;
	fclose(archivo);
}

void agregar_alumno(){
	char continuar;
	FILE* archivo=fopen(nombre_archivo,"ab");
	Alumno alumno;
	string nombre,apellido,direccion;
	do{
		fflush(stdin);
		
		cout<<"Ingrese el Codigo: ";
		cin>>alumno.codigo;
		cin.ignore();
		
		cout<<"Ingrese el Nombre: ";
		getline(cin,nombre);
		strcpy(alumno.nombre,nombre.c_str());
		
		cout<<"Ingrese el Apellido: ";
		getline(cin,apellido);
		strcpy(alumno.apellido,apellido.c_str());
		
		cout<<"Ingrese la Direccion: ";
		getline(cin,direccion);
		strcpy(alumno.direccion,direccion.c_str());
		
		cout<<"Ingrese el Telefono: ";
		cin>>alumno.telefono;
		cin.ignore();
		
		fwrite(&alumno,sizeof(Alumno),1,archivo);
		
		cout<<"Desea Agregar otro nombre? s/n: ";
		cin>>continuar;	
	}while((continuar=='s')||(continuar=='S'));
	fclose(archivo);
	ver_alumno();
	buscar_alumno();
}

void modificar_alumno(){
	FILE* archivo=fopen(nombre_archivo,"r+b");
	int id;
	string nombre,apellido,direccion;
	Alumno alumno;
	
	cout<<"Ingrese el ID que quiere modificar: ";
	cin>>id;
	fseek(archivo,id*sizeof(Alumno),SEEK_SET);
	
	cout<<"Ingrese el Codigo: ";
	cin>>alumno.codigo;
	cin.ignore();
		
	cout<<"Ingrese el Nombre: ";
	getline(cin,nombre);
	strcpy(alumno.nombre,nombre.c_str());
		
	cout<<"Ingrese el Apellido: ";
	getline(cin,apellido);
	strcpy(alumno.apellido,apellido.c_str());
	
	cout<<"Ingrese la Direccion: ";
	getline(cin,direccion);
	strcpy(alumno.direccion,direccion.c_str());
	
	cout<<"Ingrese el Telefono: ";
	cin>>alumno.telefono;
	cin.ignore();
	
	fwrite(&alumno,sizeof(Alumno),1,archivo);
	fclose(archivo);
	ver_alumno();
	system("PAUSE");
}

void eliminar_alumno(){
	FILE* archivo=fopen(nombre_archivo,"rb");
	int cod=0,pos=0;
	cout<<"Que registro desea eliminar, ingresar el codigo: ";
	cin>>cod;
	fseek(archivo,pos*sizeof(Alumno),SEEK_SET);
	
	Alumno alumno;
	
	fread(&alumno,sizeof(Alumno),1,archivo);
	
	cout<<"Codigo: "<<alumno.codigo<<endl;
	cout<<"Nombre: "<<alumno.nombre<<endl;
	cout<<"Apellido: "<<alumno.apellido<<endl;
	cout<<"Direccion: "<<alumno.direccion<<endl;
	cout<<"Telefono: "<<alumno.telefono<<endl;
	cout<<endl;
	
	while(!feof(archivo)){
		if(alumno.codigo==cod){
			fwrite(&alumno,sizeof(Alumno),1,archivo);
		}
	}
	
	fclose(archivo);	
}
