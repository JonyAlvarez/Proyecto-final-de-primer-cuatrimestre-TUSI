#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <stdbool.h>
#include <time.h>
#include <conio.h>
#include "pila.h"
#include "gotoxy.h"
// HANDLE wHnd;
#define COPYRIGHT "| Copyright 2021  JONY |"
#define PEDIDOSHISTORIAL "pedidos/pedidosHistorial.bin"
#define AUXELIMINARPEDIDO "pedidos/copia.bin"
/////////////////////////////////////////////////////////////////////////
#define STOCK_HISTORIAL "stock/stockHistorial.bin"
#define AUX_ELIMINAR_STOCK "stock/copia.bin"
/////////////////////////////////////////////////////////////////////////
#define PROVEEDORES_HISTORIAL "proveedores/proveedoresHistorial.bin"
#define AUX_ELIMINAR_PROVEEDOR "proveedores/copia.bin"
/////////////////////////////////////////////////////////////////////////
#define CLIENTES_HISTORIAL "clientes/clientesHistorial.bin"
#define AUX_ELIMINAR_CLEINTES "clientes/copia.bin"
/////////////////////////////////////////////////////////////////////////
#define USUARIO "admin"
#define CLAVE "1234"

#define LONGITUD 80

struct pais {
    
    char pais[LONGITUD];
    char provincia[LONGITUD];
    char ciudad[LONGITUD];
    char codigoPostal[LONGITUD];
    char calleYnumero[LONGITUD];

};

struct telas{
    char tipoTela[LONGITUD];
    int cantidadRollosTela;
    float precioRollo;
};


typedef struct {
    char nombreYapellidoCliente[LONGITUD];
    
    struct pais paisCliente;
    struct pais ProvinciaCliente;
    struct pais CiudadCliente;
    struct pais codigoPostalCliente;
    struct pais calleYnumeroCliente;
}clientes;

typedef struct {
    char empresa[LONGITUD];

    struct pais paisproveedor;
    struct pais ProvinciaProveedor;
    struct pais CiudadProveedor;
    struct pais codigoPostalProveedor;
    struct pais calleYnumeroProveedor;

}proveedor;

typedef struct {

    char fecha[LONGITUD];
    int CodPedidos;
    int DNI;
    char nombreYapellido[LONGITUD];
    char empresa[LONGITUD];

    struct pais paisPedido;
    struct pais ProvinciaPedido;
    struct pais CiudadPedido;
    struct pais codigoPostalPedido;
    struct pais calleYnumeroPedido;

    struct telas pedidoTipoTela;
    struct telas pedidocantidadRollosTela;
    struct telas pedidoprecioRollo;

}pedidos;
typedef struct{
    char proveedor[LONGITUD];
    struct telas telaStock;
    struct telas cantidadRollosTelaStock;
    struct telas precioRolloStock;
    
}stock;


/////////////////////////////////////////////////////////////////////////////////////////////////
void Usuario();
void dibujarCuadro(int x1,int y1,int x2,int y2);
int CodigoPedido(int dim);
void creaCarpetas();
int cantidaCarga();
void cargando();
void verArchivoCargarArchivoMenu();
void marcoConsola();
void logo();
/////////////////////////////////////////////////////////////////////////////////////////////////MENU
void menu();
int pintarMenu();
void menuPedidos();
void menuStock();
void menuProveedores();
void menuClientes();
/////////////////////////////////////////////////////////////////////////////////////////////////PEDIDOS
void opcionesModificarPedido();
pedidos cargarUnPedido(int cantidad);
void verUnPedido(pedidos aux);
void verMuchosPedidos(pedidos aux, int cont);
void cargarEnArchivoPedido(char nombreArchivo[LONGITUD], pedidos aux[LONGITUD], int validos);
void leerArchivoPedido(char nombreArchivo[LONGITUD]);
int  cargarMuchosPedidos(pedidos arr[], int dim, int cantidad);
void modificarArchivo(char nombreArchivo[LONGITUD], char nombreArchivoTemporal[LONGITUD]); 
void eliminarPedidoArchivo(char nombreArchivo[LONGITUD], char nombreArchivoTemporal[LONGITUD]);
/////////////////////////////////////////////////////////////////////////////////////////////////STOCK
void opcionesModificarStock();
void opcioneCargarStock();
void verTodoStock(stock aux, int cont);
void verUnStock(stock aux);
int cantidaCargaStock();
stock cargarUnStock(int cantidad);
int cargarMuchosstock(stock arr[], int dim, int cantidad);
void cargarEnArchivoStock(char nombreArchivo[LONGITUD], stock aux[LONGITUD], int validos);
void leerArchivoStock(char nombreArchivo[LONGITUD]);
void modificarArchivoStock(char nombreArchivo[LONGITUD], char nombreArchivoTemporal[LONGITUD]);
void eliminarStockArchivo(char nombreArchivo[LONGITUD], char nombreArchivoTemporal[LONGITUD]);
/////////////////////////////////////////////////////////////////////////////////////////////////PROVEEDORES
void verTodoproveedor( proveedor aux, int cont);
void verUnproveedor(proveedor aux);
int cantidaCargaproveedor();
proveedor cargarUnproveedor(int cantidad);
int cargarMuchosproveedor(proveedor arr[], int dim, int cantidad);
void cargarEnArchivoproveedor(char nombreArchivo[LONGITUD], proveedor aux[LONGITUD], int validos);
void leerArchivoproveedor(char nombreArchivo[LONGITUD]);
void modificarArchivoproveedor(char nombreArchivo[LONGITUD], char nombreArchivoTemporal[LONGITUD]);
void eliminarproveedorArchivo(char nombreArchivo[LONGITUD], char nombreArchivoTemporal[LONGITUD]);
void opcioneCargarproveedor();
void opcionesModificarproveedor();
/////////////////////////////////////////////////////////////////////////////////////////////////CLIENTES
void verTodoCliente( clientes aux, int cont);
void verUnCliente(clientes aux);
int cantidaCargaCliente();
clientes cargarUnCliente(int cantidad);
int cargarMuchosCliente(clientes arr[], int dim, int cantidad);
void cargarEnArchivoCliente(char nombreArchivo[LONGITUD], clientes aux[LONGITUD], int validos);
void leerArchivoCliente(char nombreArchivo[LONGITUD]);
void modificarArchivoCliente(char nombreArchivo[LONGITUD], char nombreArchivoTemporal[LONGITUD]);
void eliminarClienteArchivo(char nombreArchivo[LONGITUD], char nombreArchivoTemporal[LONGITUD]);
void opcioneCargarCliente();
void opcionesModificarCliente();


int main()
{  
    system("mode con: cols=152 lines=29");
    system ("color 3F ");
 
    creaCarpetas();
    Usuario();

    return 0;
}

void Usuario(){


       system ("color 3F "); //DF
    

    char usuario[LONGITUD+1];
    char clave[LONGITUD+1];

    bool ingresa = false;
    bool escribio = false;
    int intentos = 0;
    
    char caracter;
    int contCaracter = 0;

    
    do{ //pameñ de ingreso con 3 intentos 
        system("cls");
        marcoConsola();
        logo();
        gotoxy(120,28);printf(COPYRIGHT);
        gotoxy(38,1);printf("=============================================================================");
        gotoxy(71,2);printf("TELAS PUNK");
        gotoxy(60,3);printf("IMPORTADORA Y EXPORTADORA DE TELAS");
        gotoxy(38,4);printf("=============================================================================");
        dibujarCuadro(53,6,98,13);
        gotoxy(68,8);printf("INICIO DE SESION");
        gotoxy(54,9);printf("____________________________________________");
        
        
        gotoxy(62,11);printf("USUARIO: ");
        fflush(stdin);
        gotoxy(80,11);printf("CLAVE: ");
        gotoxy(70,11);gets(usuario);
        
        gotoxy(87,11);while(caracter  = getch() )
        {

            if ( caracter == 13)//cuando apreta enter 
            {
                clave['\0'];
                break;
            }else if( caracter == 8){//para borrar contraseña

                if(contCaracter > 0){// borrara unicamente si el contador es mayor que cero

                    contCaracter--;
                    printf("\b \b");//mueve el cursor hacia atras y agrega un espacio en blanco para dar la sensacion de borrado
            
                }
            }else{

                if( contCaracter < LONGITUD){//solo me va a dejar agregar los caracteres que longitud permite
                    printf("*");
                    clave[contCaracter] = caracter;
                    
                    contCaracter++;
                }
            }
        }
        system("cls");

        if (strcmp(usuario, USUARIO) == 0 && strcmp(clave, CLAVE) == 0){ //valida las claves comparandolas con usuario y cont
            
            ingresa = true;
            }else{
        
            printf("\t\t\t\t USUARIO Y/O CLAVES INCORRECTOS!!\n");
            printf("\t\t\t\t solo tiene 3 intentos\n");
            printf("\t\t\t\t usted uso %d intento de los 3\n", intentos+1);
            intentos++;
            system("pause");
        }

    }while (intentos < 3 && ingresa == false);
    system("cls");


//compara si F o T 
    
        if (ingresa == true) {
            menu();

        }else if(intentos == 3 && ingresa == false){
            printf("Solo tiene 3 intentos, cierre y vuelva a abrir el programa.");
        }



}

////////////////////////////////////////////////////////////////
//////////                                            //////////
//////////              MENUS  LOGICA                 //////////   
//////////                                            //////////
////////////////////////////////////////////////////////////////

void menu(){

    bool repite = true;
    int option = 0;

    do{
        system("cls");
        marcoConsola();
        gotoxy(45,3);logo();
        dibujarCuadro(25,6,127,8);
        option = pintarMenu();
        switch (option){
        case 1:
            system("cls");
            menuPedidos(); 
           
            break;
        case 2:
            system("cls");
            menuStock();
            break;
        case 3:
            system("cls");
            menuProveedores();
            break;
        case 4:      
            system("cls");
            menuClientes();
            break;
        case 5:      
            repite = false;
      
            break;
        default:
            printf("error al elegir opcion");
            break;
        }
    }while(repite);

}
int pintarMenu(){
    int option = 0;

    gotoxy(45,3);printf("==============================================================");
    gotoxy(73,4);printf("MENU");
    gotoxy(45,5);printf("==============================================================");
    gotoxy(120,28);printf(COPYRIGHT);
    gotoxy(28,7);printf("[1]Gestion de pedidos");
    gotoxy(52,7);printf("[2]Gestios de Stock telas");
    gotoxy(82,7);printf("[3]Proveedores");
    gotoxy(101,7);printf("[4]clientes");
    gotoxy(117,7);printf("[5]Salir");
    gotoxy(70,10);printf("Opcion: ");
    scanf("%d", &option);
    
    return option;

}
void menuPedidos(){
    bool repite = true;
    int option = 0;
    int validos = 0;
    int cantidad = 0;

    do{//agregar color de tela, direccion, ciudad etc
        system("cls");
        logo();
        marcoConsola();
        dibujarCuadro(25,6,127,8);
        gotoxy(45,3);printf("==============================================================");
        gotoxy(68,4);printf("GESTION PEDIDOS");
        gotoxy(45,5);printf("==============================================================");
        gotoxy(120,28);printf(COPYRIGHT);
        gotoxy(29,7);printf("[1]crear pedido");
        gotoxy(48,7);printf("[2]Ver pedidos");
        gotoxy(68,7);printf("[3]Modificar pedido");
        gotoxy(92,7);printf("[4]Eliminar pedido");
        gotoxy(116,7);printf("[5]Salir");
        gotoxy(70,10);printf("Opcion: ");

        scanf("%d", &option);
        
        

        switch (option){
        case 1:
            system("cls");//hacer dependiendo de si carga mas de 1 pedido  se dirija a una funcion de muchos pedidos
            pedidos aux[LONGITUD];
            gotoxy(70,2);printf("GESTION PEDIDOS"); 
            gotoxy(41,3);printf("**********************************************************************");
            marcoConsola();
            verArchivoCargarArchivoMenu();//MUESTRA EL MENU PARA PONER LOS DATOS
            cantidad = cantidaCarga();
            if (cantidad == 0 || cantidad < 0){
                puts("NO SE PUEDEN CARGAR CERO O MENOS DE CERO PEDIDOS ");
                system("pause");
             }else if(cantidad > LONGITUD){  
                puts("SOLO SE PUEDEN CARGAR HASTA 80 PEDIDOS A LA VEZ");
                system("pause");
            }else{
                validos = cargarMuchosPedidos(aux, LONGITUD, cantidad);
                cargarEnArchivoPedido(PEDIDOSHISTORIAL, aux, validos);
                cargando();
                
            }
            break;
        case 2:
            system("cls");
            cargando();
            system("cls");
            marcoConsola();
            leerArchivoPedido(PEDIDOSHISTORIAL);
            getch();            
            break;
        case 3:
            system("cls");
            modificarArchivo(PEDIDOSHISTORIAL, AUXELIMINARPEDIDO);
            
            getch();
            break;
        case 4:
            system("cls");
            eliminarPedidoArchivo(PEDIDOSHISTORIAL, AUXELIMINARPEDIDO);
            break;
        case 5:
            repite = false;

            break;
        
        default:
            printf("OPCION INCORRECTA!!");
            break;
        }
    }while(repite);

}
void menuStock(){
    int cantidadStock = 0;
    int validoStock = 0;
    bool repiteStock = true;
    int optionStock = 0;
    do{
        system("cls");
	    logo();
        marcoConsola();
        dibujarCuadro(25,6,127,8);
        gotoxy(45,3);printf("==============================================================");
        gotoxy(68,4);printf("GESTION STOCK");
        gotoxy(45,5);printf("==============================================================");
        gotoxy(120,28); printf(COPYRIGHT);
        gotoxy(29,7);printf("[1]Cargar stock");
        gotoxy(48,7);printf("[2]Ver stock");
        gotoxy(65,7);printf("[3]Modificar stock");
        gotoxy(88,7);printf("[4]Eliminar stock");
        gotoxy(112,7);printf("[5]Salir");
        gotoxy(70,10);printf("Opcion: ");

        scanf("%d", &optionStock);
        

        switch (optionStock)
        {
        case 1:
            system("cls");//hacer dependiendo de si carga mas de 1 pedido  se dirija a una funcion de muchos pedidos
            stock aux[LONGITUD];

            gotoxy(70,2);printf("GESTION STOCK"); 
            gotoxy(41,3);printf("**********************************************************************");
            marcoConsola();
            opcioneCargarStock();//MUESTRA EL MENU PARA PONER LOS DATOS
            cantidadStock = cantidaCargaStock();
            if (cantidadStock == 0 || cantidadStock < 0){
                puts("NO SE PUEDEN CARGAR CERO O MENOS DE CERO PRODUCTOS DE TELA ");
                system("pause");
             }else if(cantidadStock > LONGITUD){  
                puts("SOLO SE PUEDEN CARGAR HASTA 80 PRODUCTOS A LA VEZ");
                system("pause");
            }else{
                validoStock = cargarMuchosstock(aux, LONGITUD, cantidadStock);
                cargarEnArchivoStock(STOCK_HISTORIAL, aux, validoStock);
                cargando();
            }
            getch();
            break;
        case 2:
            system("cls");
            cargando();
            system("cls");
            marcoConsola();
            leerArchivoStock(STOCK_HISTORIAL);
            getch();
            break;
        case 3:
            system("cls");
            modificarArchivoStock(STOCK_HISTORIAL, AUX_ELIMINAR_STOCK);
            getch();
            break;
        case 4:
            system("cls");
            eliminarStockArchivo(STOCK_HISTORIAL, AUX_ELIMINAR_STOCK);
            getch();
            break;
        case 5:
            repiteStock = false;

            break;
        
        default:
            printf("OPCION INCORRECTA!!");
            break;
        }
    }while(repiteStock);
}
void menuProveedores(){
    int cantidadProveedor = 0;
    int validoProveedor = 0;
    bool repiteProveedor = true;
    int optionProveedor = 0;

    do{
        system("cls");
	    logo();
        marcoConsola();
        dibujarCuadro(25,6,127,8);
        gotoxy(45,3);printf("==============================================================");
        gotoxy(68,4);printf("GESTION PROVEEDORES");
        gotoxy(45,5);printf("==============================================================");
        gotoxy(120,28); printf(COPYRIGHT);
        gotoxy(27,7);printf("[1]Cargar nuevo proveedor");
        gotoxy(53,7);printf("[2]Ver proveedores");
        gotoxy(72,7);printf("[3]Modificar proveedor");
        gotoxy(95,7);printf("[4]Eliminar proveedor");
        gotoxy(117,7);printf("[5]Salir");
        gotoxy(70,10);printf("Opcion: ");

        scanf("%d", &optionProveedor);
        

        switch (optionProveedor)
        {
        case 1:
            system("cls");//hacer dependiendo de si carga mas de 1 pedido  se dirija a una funcion de muchos pedidos
            proveedor aux[LONGITUD];

            gotoxy(70,2);printf("GESTION PROVEEDORES"); 
            gotoxy(41,3);printf("**********************************************************************");
            marcoConsola();
            opcioneCargarproveedor();//MUESTRA EL MENU PARA PONER LOS DATOS
            cantidadProveedor = cantidaCargaproveedor();
            if (cantidadProveedor == 0 || cantidadProveedor < 0){
                puts("NO SE PUEDEN CARGAR CERO O MENOS DE CERO PRODUCTOS DE TELA ");
                system("pause");
             }else if(cantidadProveedor > LONGITUD){  
                puts("SOLO SE PUEDEN CARGAR HASTA 80 PRODUCTOS A LA VEZ");
                system("pause");
            }else{
                validoProveedor = cargarMuchosproveedor(aux, LONGITUD, cantidadProveedor);
                cargarEnArchivoproveedor(PROVEEDORES_HISTORIAL, aux, validoProveedor);
                cargando();
            }
            break;
        case 2:
            system("cls");
            cargando();
            system("cls");
            marcoConsola();
            leerArchivoproveedor(PROVEEDORES_HISTORIAL);
            getch();
            break;
        case 3:            
            system("cls");
            modificarArchivoproveedor(PROVEEDORES_HISTORIAL, AUX_ELIMINAR_PROVEEDOR);
            getch();
            break;
        case 4:
            system("cls");
            eliminarproveedorArchivo(PROVEEDORES_HISTORIAL, AUX_ELIMINAR_PROVEEDOR);
            getch();
            break;
        case 5:
            repiteProveedor = false;

            break;
        
        default:
            printf("OPCION INCORRECTA!!");
            break;
        }
    }while(repiteProveedor);
}
void menuClientes(){
    int cantidadClientes = 0;
    int validoClientes = 0;
    bool repiteClientes = true;
    int optionClientes = 0;
    do{
        system("cls");
	    logo();
        marcoConsola();
        dibujarCuadro(25,6,127,8);
        gotoxy(45,3);printf("==============================================================");
        gotoxy(68,4);printf("GESTION CLIENTES");
        gotoxy(45,5);printf("==============================================================");
        gotoxy(120,28); printf(COPYRIGHT);
        gotoxy(28,7);printf("[1]Cliente nuevo");
        gotoxy(48,7);printf("[2]Ver clientes");
        gotoxy(68,7);printf("[3]Modificar cliente");
        gotoxy(94,7);printf("[4]Eliminar cliente");
        gotoxy(117,7);printf("[5]Salir");
        gotoxy(70,10);printf("Opcion: ");

        scanf("%d", &optionClientes);
        

        switch (optionClientes)
        {
        case 1:
            system("cls");//hacer dependiendo de si carga mas de 1 pedido  se dirija a una funcion de muchos pedidos
            clientes aux[LONGITUD];

            gotoxy(70,2);printf("GESTION CLIENTES"); 
            gotoxy(41,3);printf("**********************************************************************");
            marcoConsola();
            opcioneCargarCliente();//MUESTRA EL MENU PARA PONER LOS DATOS
            cantidadClientes = cantidaCargaCliente();
            if (cantidadClientes == 0 || cantidadClientes < 0){
                puts("NO SE PUEDEN CARGAR CERO O MENOS DE CERO PRODUCTOS DE TELA ");
                system("pause");
             }else if(cantidadClientes > LONGITUD){  
                puts("SOLO SE PUEDEN CARGAR HASTA 80 PRODUCTOS A LA VEZ");
                system("pause");
            }else{
                validoClientes = cargarMuchosCliente(aux, LONGITUD, cantidadClientes);
                cargarEnArchivoCliente(CLIENTES_HISTORIAL, aux, validoClientes);
                cargando();
            }
            break;
        case 2:
            system("cls");
            cargando();
            system("cls");
            leerArchivoCliente(CLIENTES_HISTORIAL);
            getch();
            break;
        case 3:
            system("cls");
            modificarArchivoCliente(CLIENTES_HISTORIAL, AUX_ELIMINAR_CLEINTES);
            
            break;
        case 4:
            system("cls");
            eliminarClienteArchivo(CLIENTES_HISTORIAL, AUX_ELIMINAR_CLEINTES);
            break;
        case 5:
            repiteClientes = false;

            break;
        
        default:
            printf("OPCION INCORRECTA!!");
            break;
        }
    }while(repiteClientes);
}

////////////////////////////////////////////////////////////////
//////////                                            //////////
//////////        FIN   MENUS  LOGICA                 //////////   
//////////                                            //////////
////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
//////////                                            //////////
//////////        PEDIDOS      LOGICA                 //////////   
//////////                                            //////////
////////////////////////////////////////////////////////////////
void verMuchosPedidos(pedidos aux, int cont){
    
    
    gotoxy(4,8+cont);printf("%d ", aux.CodPedidos);
    gotoxy(12,8+cont);printf("%d ", aux.DNI);
    gotoxy(26,8+cont); printf("%s ", aux.nombreYapellido);
    gotoxy(46,8+cont);printf("%s ", aux.pedidoTipoTela.tipoTela);
    gotoxy(61,8+cont);printf("%d ", aux.pedidocantidadRollosTela.cantidadRollosTela);
    gotoxy(69,8+cont);printf("%s ", aux.paisPedido.pais);
    gotoxy(81,8+cont);printf("%s ", aux.ProvinciaPedido.provincia);
    gotoxy(95,8+cont);printf("%s ", aux.CiudadPedido.ciudad);
    gotoxy(112,8+cont);printf("%s ", aux.codigoPostalPedido.codigoPostal);
    gotoxy(125,8+cont);printf("%s ", aux.calleYnumeroPedido.calleYnumero);


}

void verUnPedido(pedidos aux){
    
    
    gotoxy(4,8);printf("%d ", aux.CodPedidos);
    gotoxy(12,8);printf("%d ", aux.DNI);
    gotoxy(22,8); printf("%s ", aux.nombreYapellido);
    gotoxy(44,8);printf("%s ", aux.pedidoTipoTela.tipoTela);
    gotoxy(63,8);printf("%d ", aux.pedidocantidadRollosTela.cantidadRollosTela);
    gotoxy(70,8);printf("%s ", aux.paisPedido.pais);
    gotoxy(81,8);printf("%s ", aux.ProvinciaPedido.provincia);
    gotoxy(98,8);printf("%s ", aux.CiudadPedido.ciudad);
    gotoxy(115,8);printf("%s ", aux.codigoPostalPedido.codigoPostal);
    gotoxy(130,8);printf("%s ", aux.calleYnumeroPedido.calleYnumero);


}

int cantidaCarga(){
    int cantidad = 0;
    gotoxy(4,4);printf("Cuantos pedidos desea agregar?: ");
    gotoxy(35,4);scanf("%d", &cantidad);

    return cantidad;
}

int CodigoPedido(int dim){ // GENERA CODIGO PEDIDO RANDOM
    int CodigoPedido = 0;

    srand(time(NULL));

    for (int i = 0; i < dim; i++){
          CodigoPedido = rand() % 100000 + 1;
    }
 
    return CodigoPedido;

}

pedidos cargarUnPedido(int cantidad){
   
    pedidos pedidosTemp;
    pedidosTemp.CodPedidos = CodigoPedido(rand() % 10000 + 1);
    

    gotoxy(4,8+cantidad);printf("%d", pedidosTemp.CodPedidos);
    gotoxy(12,8+cantidad);scanf("%d", &pedidosTemp.DNI);
    fflush(stdin);
    gotoxy(26,8+cantidad);gets(pedidosTemp.nombreYapellido); //nombre y apellido pedido
    fflush(stdin);
    gotoxy(46,8+cantidad);gets(pedidosTemp.pedidoTipoTela.tipoTela);//tipo de tela a exportar
 
    gotoxy(61,8+cantidad);scanf("%d", &pedidosTemp.pedidocantidadRollosTela.cantidadRollosTela);//cantidad de rollos
    fflush(stdin);
    gotoxy(69,8+cantidad);gets(pedidosTemp.paisPedido.pais); //pais del pedido
    fflush(stdin);
    gotoxy(81,8+cantidad);gets(pedidosTemp.ProvinciaPedido.provincia); //provincia del pedido
    fflush(stdin);
    gotoxy(95,8+cantidad);gets(pedidosTemp.CiudadPedido.ciudad); //ciudad del pedido
    fflush(stdin);
    gotoxy(112,8+cantidad);gets(pedidosTemp.codigoPostalPedido.codigoPostal); //codigo postal del pedido
    fflush(stdin);
    gotoxy(125,8+cantidad);gets(pedidosTemp.calleYnumeroPedido.calleYnumero); //calleYnumero del pedido

return pedidosTemp;

}

int cargarMuchosPedidos(pedidos arr[], int dim, int cantidad){
    int i = 0;
    pedidos aux;
    while (cantidad <= dim && cantidad != 0 ) {
        aux = cargarUnPedido(i);

        arr[i] = aux;
        
        cantidad--;
        i++;
    }
    return i;
}

void cargarEnArchivoPedido(char nombreArchivo[LONGITUD], pedidos aux[LONGITUD], int validos){
    FILE *archi = fopen(nombreArchivo, "ab");

    if(archi != NULL){
        for(int i = 0; i < validos; i++){

            fwrite(&aux[i], sizeof(pedidos), 1, archi);

        }

        fclose(archi);
    }else{
        printf("ERROR AL ESCRIBIR EL ARCHIVO");
    }

}

void leerArchivoPedido(char nombreArchivo[LONGITUD]){
    pedidos aux;
    int cont = 0;
    FILE *archi = fopen(nombreArchivo, "rb");
    verArchivoCargarArchivoMenu(); // MUESTRA las etiquedas  PARA VER LOS DATOS
    if(archi != NULL){
        while(fread(&aux, sizeof(pedidos), 1, archi)> 0){
            verMuchosPedidos(aux, cont);

            cont++;
        }
        fclose(archi);
    }else{
        puts("ERROR AL LEER EL ARCHIVO");
    }
}

void modificarArchivo(char nombreArchivo[LONGITUD], char nombreArchivoTemporal[LONGITUD]){
    int codigo = 0;
    pedidos pedidosTemp;
    FILE * temporal = fopen(nombreArchivoTemporal, "ab");
    FILE *archi = fopen(nombreArchivo, "r+b");

    

    if( archi == NULL){
    
        puts("PEDIDOS HISTORIAL NO EXISTE!");
        system("pause");

    }

    if (temporal == NULL)
    {
        puts("COPIA NO EXISTE!");
        system("pause");
    }
    if(archi != NULL && temporal != NULL){

        gotoxy(4,4);
        printf("Ingrese Codigo del pedido: ");
        gotoxy(4,30);
        scanf("%d", &codigo);
        opcionesModificarPedido();
        while (fread(&pedidosTemp, sizeof(pedidos), 1, archi) >0){
        
        if (codigo == pedidosTemp.CodPedidos){
            verUnPedido(pedidosTemp);
            int option = 0;

                gotoxy(50,4);
                printf("Que desea modificar: ");
                gotoxy(70,4);
                scanf("%d", &option);   

                switch (option){
                    case 1:
                        verUnPedido(pedidosTemp);
                        gotoxy(80,4);
                        printf("Modificar DNI: ");
                        gotoxy(95,4);
                        scanf("%d", &pedidosTemp.DNI);

                        fwrite(&pedidosTemp, sizeof(pedidos), 1, temporal);
                        system("cls");
                        marcoConsola();
                        opcionesModificarPedido();
                        verUnPedido(pedidosTemp);
                        break;
                    
                    
                    case 2:
                        verUnPedido(pedidosTemp);
                        gotoxy(80,4);
                        printf("Modificar nombre y apeliido: ");
                        gotoxy(108,4);
                        fflush(stdin);
                        gets(pedidosTemp.nombreYapellido);

                        fwrite(&pedidosTemp, sizeof(pedidos), 1, temporal);
                        system("cls");
                        marcoConsola();
                        opcionesModificarPedido();
                        verUnPedido(pedidosTemp);
                        break;
                    
                    
                    case 3:
                        verUnPedido(pedidosTemp);
                        gotoxy(80,4);
                        printf("Modificar Tipo de tela: ");
                        gotoxy(104,4);
                        fflush(stdin);
                        gets(pedidosTemp.pedidoTipoTela.tipoTela);

                        fwrite(&pedidosTemp, sizeof(pedidos), 1, temporal);
                        system("cls");
                        marcoConsola();
                        opcionesModificarPedido();
                        verUnPedido(pedidosTemp);
                        break;
                    
                    case 4:
                        verUnPedido(pedidosTemp);
                        gotoxy(80,4);
                        printf("Modificar rollos: ");
                        gotoxy(97,4);
                        scanf("%d", &pedidosTemp.pedidocantidadRollosTela.cantidadRollosTela);

                        fwrite(&pedidosTemp, sizeof(pedidos), 1, temporal);
                        system("cls");
                        marcoConsola();
                        opcionesModificarPedido();
                        verUnPedido(pedidosTemp);
                        break;
                    
                    
                    case 5:
                        verUnPedido(pedidosTemp);
                        gotoxy(80,4);
                        printf("Modificar Pais: ");
                        gotoxy(95,4);
                        fflush(stdin);
                        gets(pedidosTemp.paisPedido.pais);

                        fwrite(&pedidosTemp, sizeof(pedidos), 1, temporal);
                        system("cls");
                        marcoConsola();
                        opcionesModificarPedido();
                        verUnPedido(pedidosTemp);

                        break;
        
                    
                    case 6:
                        verUnPedido(pedidosTemp);
                        gotoxy(80,4);
                        printf("Modificar Provincia: ");
                        gotoxy(100,4);
                        fflush(stdin);
                        gets(pedidosTemp.ProvinciaPedido.provincia);

                        fwrite(&pedidosTemp, sizeof(pedidos), 1, temporal);
                        system("cls");
                        marcoConsola();
                        opcionesModificarPedido();
                        verUnPedido(pedidosTemp);
                        break;
                    
                    
                    case 7:
                        verUnPedido(pedidosTemp);
                        gotoxy(80,4);
                        printf("Modificar Ciudad: ");
                        gotoxy(97,4);
                        fflush(stdin);
                        gets(pedidosTemp.CiudadPedido.ciudad);

                        fwrite(&pedidosTemp, sizeof(pedidos), 1, temporal);
                        system("cls");
                        marcoConsola();
                        opcionesModificarPedido();
                        verUnPedido(pedidosTemp);
                        break;
                    
                    
                    case 8:
                        verUnPedido(pedidosTemp);
                        gotoxy(80,4);
                        printf("Modificar C. Postal: ");
                        gotoxy(101,4);
                        fflush(stdin);
                        gets(pedidosTemp.codigoPostalPedido.codigoPostal);

                        fwrite(&pedidosTemp, sizeof(pedidos), 1, temporal);
                        system("cls");
                        marcoConsola();
                        opcionesModificarPedido();
                        verUnPedido(pedidosTemp);
                        break;
                                
                    case 9:
                        verUnPedido(pedidosTemp);
                        gotoxy(80,4);
                        printf("Modificar calle y Numeracion: ");
                        gotoxy(109,4);
                        fflush(stdin);
                        gets(pedidosTemp.calleYnumeroPedido.calleYnumero);

                        fwrite(&pedidosTemp, sizeof(pedidos), 1, temporal);
                        system("cls");
                        marcoConsola();
                        opcionesModificarPedido();
                        verUnPedido(pedidosTemp);
                        break;
                    
                    default:
                    puts("esa opcion no existe");
                        break;
                }
        }else{

            fwrite(&pedidosTemp, sizeof(pedidos), 1, temporal);

        }
        
    }

}



    fclose(archi);
    fclose(temporal);

    remove(PEDIDOSHISTORIAL);
    rename(AUXELIMINARPEDIDO, PEDIDOSHISTORIAL);
    cargando();
}

void eliminarPedidoArchivo(char nombreArchivo[LONGITUD], char nombreArchivoTemporal[LONGITUD]){
    int codigo = 0;
    pedidos pedidosTemp;

    FILE *temporal = fopen(nombreArchivoTemporal, "ab");
    FILE *archi = fopen(nombreArchivo, "rb");

    printf("Codigo del archivo: ");
    scanf("%d", &codigo);

    if( archi == NULL){
    
        puts("PEDIDOS HISTORIAL NO EXISTE!");
        system("pause");

    }

    if (temporal == NULL)
    {
        puts("COPIA NO EXISTE!");
        system("pause");
    }
        
    while (fread(&pedidosTemp, sizeof(pedidos), 1, archi) >0){

        
        if (codigo == pedidosTemp.CodPedidos){
            printf("\nSe ah eliminado el registro: %d", pedidosTemp.CodPedidos);

            
        }else{


            fwrite(&pedidosTemp, sizeof(pedidos), 1, temporal);
        }
    }
    
    getch();
    
   fclose(archi);
   fclose(temporal);

   remove(PEDIDOSHISTORIAL);
   rename(AUXELIMINARPEDIDO, PEDIDOSHISTORIAL);
}

void verArchivoCargarArchivoMenu(){// CUADRO DONDE MUESTRA LOS DATOS
    dibujarCuadro(1,5,150, 7);

    gotoxy(4,6);
    printf("Codigo |");
    gotoxy(16,6);
    printf("DNI ");
    gotoxy(24,6);
    printf("|");
    gotoxy(26,6);
    printf("Nombre y Apellido |");
    gotoxy(46,6);
    printf("tipo de tela |");
    gotoxy(61,6);
    printf("rollos |");
    gotoxy(69,6);
    printf("pais       |");
    gotoxy(81,6);
    printf("Provincia    |");
    gotoxy(95,6);
    printf("ciudad         |");
    gotoxy(112,6);
    printf("C. Postal   |");
    gotoxy(125,6);
    printf("Calle y Numeracion");   
}

void opcionesModificarPedido(){ // CUADRO DONDE MUESTRA LOS DATOS para modificar
    marcoConsola();
    dibujarCuadro(0,5,151, 7);
    

    gotoxy(4,6);
    printf("Codigo|");
    gotoxy(12,6);
    printf("DNI[1]");

    gotoxy(22,6);
    printf("Nombre y Apellido[2]");
    gotoxy(44,6);
    printf("tipo de tela[3]");
    gotoxy(60,6); 
    printf("rollos[4]");
    gotoxy(70,6);
    printf("pais[5]");
    gotoxy(81,6);
    printf("Provincia[6]");
    gotoxy(98,6);
    printf("ciudad[7]");
    gotoxy(112,6);
    printf("C. Postal[8]");
    gotoxy(129,6);
    printf("Calle y Numeracion[9]");   
}
////////////////////////////////////////////////////////////////
//////////                                            //////////
//////////       FIN      PEDIDOS      LOGICA         //////////   
//////////                                            //////////
////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
//////////                                            //////////
//////////        STOCK        LOGICA                 //////////   
//////////                                            //////////
////////////////////////////////////////////////////////////////

void verTodoStock(stock aux, int cont){
    
    gotoxy(1,8+cont);printf("%s ", aux.proveedor);
    gotoxy(30,8+cont);printf("%s ", aux.telaStock.tipoTela);
    gotoxy(52,8+cont); printf("%d ", aux.cantidadRollosTelaStock.cantidadRollosTela);
    gotoxy(68,8+cont);printf("%.2f", aux.precioRolloStock.precioRollo);

}

void verUnStock(stock aux){

    gotoxy(4,8);printf("%s ", aux.proveedor);
    gotoxy(22,8);printf("%s ", aux.telaStock.tipoTela);
    gotoxy(45,8); printf("%d ", aux.cantidadRollosTelaStock.cantidadRollosTela);
    gotoxy(68,8);printf("%.2f ", aux.precioRolloStock.precioRollo);

}

int cantidaCargaStock(){
    int cantidad = 0;
    gotoxy(4,4);printf("Cauntos productos desea agregar?: ");
    gotoxy(38,4);scanf("%d", &cantidad);

    return cantidad;
}

stock cargarUnStock(int cantidad){

    stock stockTemp;
    
    fflush(stdin);
    gotoxy(4,8+cantidad);gets(stockTemp.proveedor); //nombre del proveedor
    fflush(stdin);
    gotoxy(22,8+cantidad);gets(stockTemp.telaStock.tipoTela);//tipo de tela
    gotoxy(45,8+cantidad);scanf("%d",&stockTemp.cantidadRollosTelaStock.cantidadRollosTela);//cantidad rollos de tela
    gotoxy(68,8+cantidad);scanf("%f",&stockTemp.precioRolloStock.precioRollo);//Precio del Rollo
return stockTemp;

}

int cargarMuchosstock(stock arr[], int dim, int cantidad){
    int i = 0;
    stock aux;
    while (cantidad <= dim && cantidad != 0 ) {
        aux = cargarUnStock(i);

        arr[i] = aux;
        
        cantidad--;
        i++;
    }
    return i;
}

void cargarEnArchivoStock(char nombreArchivo[LONGITUD], stock aux[LONGITUD], int validos){
    FILE *archi = fopen(nombreArchivo, "ab");

    if(archi != NULL){
        for(int i = 0; i < validos; i++){

            fwrite(&aux[i], sizeof(stock), 1, archi);

        }

        fclose(archi);
    }else{
        printf("ERROR AL ESCRIBIR EL ARCHIVO");
    }

}

void leerArchivoStock(char nombreArchivo[LONGITUD]){
    stock auxStock;
    int cont = 0;
    FILE *archi = fopen(nombreArchivo, "rb");

    opcioneCargarStock(); // MUESTRA las etiquedas  PARA VER LOS DATOS
    if(archi != NULL){
        while(fread(&auxStock, sizeof(stock), 1, archi)> 0){
            verTodoStock(auxStock, cont);

            cont++;
        }
        fclose(archi);
    }else{
        puts("ERROR AL LEER EL ARCHIVO");
    }
}

void modificarArchivoStock(char nombreArchivo[LONGITUD], char nombreArchivoTemporal[LONGITUD]){
    char tipoTela[LONGITUD];
    stock stockTemp;
    FILE * temporal = fopen(nombreArchivoTemporal, "ab");
    FILE *archi = fopen(nombreArchivo, "r+b");

    

    if( archi == NULL){
    
        puts("STOCK HISTORIAL NO EXISTE!");
        system("pause");

    }

    if (temporal == NULL)
    {
        puts("COPIA NO EXISTE!");
        system("pause");
    }
    if(archi != NULL && temporal != NULL){

        gotoxy(4,4);
        printf("Ingrese el nombre del cliente: ");
        gotoxy(4,30);
        fflush(stdin);
        gets(tipoTela);

        opcionesModificarStock();
        while (fread(&stockTemp, sizeof(stock), 1, archi) >0){
            
            if (strcmp(tipoTela, stockTemp.telaStock.tipoTela) == 0){
                verUnStock(stockTemp);
                int option = 0;

                    gotoxy(52,4);
                    printf("Que desea modificar: ");
                    gotoxy(72,4);
                    scanf("%d", &option);   

                    switch (option){
                        case 1:
                            verUnStock(stockTemp);
                            gotoxy(80,4);
                            printf("Modificar Proveedor: ");
                            gotoxy(95,4);
                            fflush(stdin);
                            gets(stockTemp.proveedor);

                            fwrite(&stockTemp, sizeof(stock), 1, temporal);
                            system("cls");
                            marcoConsola();
                            opcionesModificarStock();
                            verUnStock(stockTemp);
                            break;
                        
                        case 2:
                            verUnStock(stockTemp);
                            gotoxy(80,4);
                            printf("Modificar nombre de la tela: ");
                            gotoxy(108,4);
                            fflush(stdin);
                            gets(stockTemp.telaStock.tipoTela);

                            fwrite(&stockTemp, sizeof(stock), 1, temporal);
                            system("cls");
                            marcoConsola();
                            opcionesModificarStock();
                            verUnStock(stockTemp);
                            break;
                        
                        case 3:
                            verUnStock(stockTemp);
                            gotoxy(80,4);
                            printf("Modificar cantidad de rollos: ");
                            gotoxy(104,4);
                            scanf("%d", &stockTemp.cantidadRollosTelaStock.cantidadRollosTela);

                            fwrite(&stockTemp, sizeof(stock), 1, temporal);
                            system("cls");
                            marcoConsola();
                            opcionesModificarStock();
                            verUnStock(stockTemp);
                            break;
                        
                        case 4:
                            verUnStock(stockTemp);
                            gotoxy(80,4);
                            printf("Modificar Precio del rollo: ");
                            gotoxy(97,4);
                            scanf("%f", &stockTemp.cantidadRollosTelaStock.cantidadRollosTela);

                            fwrite(&stockTemp, sizeof(stock), 1, temporal);
                            system("cls");
                            marcoConsola();
                            opcionesModificarStock();
                            verUnStock(stockTemp);
                            break;
                        
                        default:
                        puts("esa opcion no existe");
                            break;
                    }
            }else{

                fwrite(&stockTemp, sizeof(stock), 1, temporal);

            }
        
        }

    }



    fclose(archi);
    fclose(temporal);

    remove(STOCK_HISTORIAL);
    rename(AUX_ELIMINAR_STOCK, STOCK_HISTORIAL);
     cargando();
}

void eliminarStockArchivo(char nombreArchivo[LONGITUD], char nombreArchivoTemporal[LONGITUD]){
    char nombreTela[LONGITUD];
    stock stockTemp;

    FILE *temporal = fopen(nombreArchivoTemporal, "ab");
    FILE *archi = fopen(nombreArchivo, "rb");

    printf("Nombre de la tela a eliminar: ");
    fflush(stdin);
    gets(nombreTela);

    if( archi == NULL){
        
        puts("STOCK HISTORIAL NO EXISTE!");
        system("pause");

    }

    if (temporal == NULL)
    {
        puts("COPIA NO EXISTE!");
        system("pause");
    }
        
    while (fread(&stockTemp, sizeof(stock), 1, archi) >0){

        
        if (strcmp(nombreTela , stockTemp.telaStock.tipoTela)==0){
            printf("\nSe ah eliminado: %s", stockTemp.telaStock.tipoTela);

            
        }else{


            fwrite(&stockTemp, sizeof(stock), 1, temporal);
        }
    }
    
    getch();
    
   fclose(archi);
   fclose(temporal);

   remove(STOCK_HISTORIAL);
   rename(AUX_ELIMINAR_STOCK, STOCK_HISTORIAL);
}

void opcioneCargarStock(){ // CUADRO DONDE MUESTRA LOS DATOS para cargar stock
    marcoConsola();
    dibujarCuadro(0,5,151, 7);


    gotoxy(1,6);
    printf("Proveedor");
    gotoxy(30,6);
    printf("Tipo de tela ");
    gotoxy(45,6);
    printf("Cantidad de rollos ");
    gotoxy(68,6);
    printf("Precio del rollo");
    
}

void opcionesModificarStock(){ // CUADRO DONDE MUESTRA LOS DATOS para modificar stock
    marcoConsola();
    dibujarCuadro(0,5,151, 7);


    gotoxy(4,6);
    printf("Proveedor[1]");
    gotoxy(22,6);
    printf("Tipo de tela [2]");
    gotoxy(45,6);
    printf("Cantidad de rollos [3]");
    gotoxy(68,6);
    printf("Precio del rollo [4]");
}
////////////////////////////////////////////////////////////////
//////////                                            //////////
//////////       FIN      STOCK        LOGICA         //////////   
//////////                                            //////////
////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
//////////                                            //////////
//////////        PROVEEDORES        LOGICA           //////////   
//////////                                            //////////
////////////////////////////////////////////////////////////////

void verTodoproveedor( proveedor aux, int cont){


    gotoxy(1,8+cont);printf("%s", aux.empresa);
    gotoxy(25,8+cont);printf("%s ", aux.paisproveedor.pais);
    gotoxy(45,8+cont);printf("%s ", aux.ProvinciaProveedor.provincia);
    gotoxy(68,8+cont);printf("%s ", aux.CiudadProveedor.ciudad);
    gotoxy(90,8+cont);printf("%s ", aux.codigoPostalProveedor.codigoPostal);
    gotoxy(104,8+cont);printf("%s ",aux.calleYnumeroProveedor.calleYnumero);

}

void verUnproveedor(proveedor aux){

    gotoxy(1,8);printf("%s", aux.empresa);
    gotoxy(25,8);printf("%s ", aux.paisproveedor.pais);
    gotoxy(45,8);printf("%s ", aux.ProvinciaProveedor.provincia);
    gotoxy(68,8);printf("%s ", aux.CiudadProveedor.ciudad);
    gotoxy(90,8);printf("%s ", aux.codigoPostalProveedor.codigoPostal);
    gotoxy(104,8);printf("%s ",aux.calleYnumeroProveedor.calleYnumero);
}

int cantidaCargaproveedor(){
    int cantidad = 0;
    gotoxy(4,4);printf("Cauntos proveedores desea agregar?: ");
    gotoxy(39,4);scanf("%d", &cantidad);

    return cantidad;
}

proveedor cargarUnproveedor(int cantidad){

    proveedor proveedorTemp;
    
    fflush(stdin);
    gotoxy(1,8+cantidad);
    gets(proveedorTemp.empresa);
    fflush(stdin);
    gotoxy(25,8+cantidad);
    gets(proveedorTemp.paisproveedor.pais);
    fflush(stdin);
    gotoxy(45,8+cantidad);
    gets(proveedorTemp.ProvinciaProveedor.provincia);
    fflush(stdin);
    gotoxy(68,8+cantidad);
    gets(proveedorTemp.CiudadProveedor.ciudad);
    fflush(stdin);
    gotoxy(90,8+cantidad);
    gets(proveedorTemp.codigoPostalProveedor.codigoPostal);
    gotoxy(104,8+cantidad);
    gets(proveedorTemp.calleYnumeroProveedor.calleYnumero);

return proveedorTemp;

}

int cargarMuchosproveedor(proveedor arr[], int dim, int cantidad){
    int i = 0;
    proveedor aux;
    while (cantidad <= dim && cantidad != 0 ) {
        aux = cargarUnproveedor(i);

        arr[i] = aux;
        
        cantidad--;
        i++;
    }
    return i;
}

void cargarEnArchivoproveedor(char nombreArchivo[LONGITUD], proveedor aux[LONGITUD], int validos){
    FILE *archi = fopen(nombreArchivo, "ab");

    if(archi != NULL){
        for(int i = 0; i < validos; i++){

            fwrite(&aux[i], sizeof(proveedor), 1, archi);

        }

        fclose(archi);
    }else{
        printf("ERROR AL ESCRIBIR EL ARCHIVO");
    }

}

void leerArchivoproveedor(char nombreArchivo[LONGITUD]){
    proveedor auxProveedor;
    int cont = 0;
    FILE *archi = fopen(nombreArchivo, "rb");
    gotoxy(70,2);printf("PROVEEDORES"); 
    gotoxy(41,3);printf("**********************************************************************");
    opcioneCargarproveedor(); // MUESTRA las etiquedas  PARA VER LOS DATOS
    if(archi != NULL){
        while(fread(&auxProveedor, sizeof(proveedor), 1, archi)> 0){
            verTodoproveedor(auxProveedor, cont);

            cont++;
        }
        fclose(archi);
    }else{
        puts("ERROR AL LEER EL ARCHIVO");
    }
}

void modificarArchivoproveedor(char nombreArchivo[LONGITUD], char nombreArchivoTemporal[LONGITUD]){
    char proveedorScan[LONGITUD];
    proveedor proveedorTemp;
    FILE * temporal = fopen(nombreArchivoTemporal, "ab");
    FILE *archi = fopen(nombreArchivo, "r+b");

    

    if( archi == NULL){
    
        puts("PROVEEDOR HISTORIAL NO EXISTE!");
        system("pause");

    }

    if (temporal == NULL)
    {
        puts("COPIA NO EXISTE!");
        system("pause");
    }
    if(archi != NULL && temporal != NULL){

        gotoxy(4,4);
        printf("Ingrese el nombre del proveedor: ");
        gotoxy(4,30);
        fflush(stdin);
        gets(proveedorScan);

        opcionesModificarproveedor();
        while (fread(&proveedorTemp, sizeof(proveedor), 1, archi) >0){
        
        if (strcmp(proveedorScan, proveedorTemp.empresa) == 0){
            verUnproveedor(proveedorTemp);
            int option = 0;

                gotoxy(50,4);
                printf("Que desea modificar: ");
                gotoxy(70,4);
                scanf("%d", &option);   

                switch (option){
                    case 1:
                        verUnproveedor(proveedorTemp);
                        gotoxy(80,4);
                        printf("Modificar Empresa: ");
                        gotoxy(98,4);
                        fflush(stdin);
                        gets(proveedorTemp.empresa);

                        fwrite(&proveedorTemp, sizeof(proveedor), 1, temporal);
                        system("cls");
                        marcoConsola();
                        opcionesModificarproveedor();
                        verUnproveedor(proveedorTemp);
                        break;
                    
                    case 2:
                        verUnproveedor(proveedorTemp);
                        gotoxy(80,4);
                        printf("Modificar pais del proveedor: ");
                        gotoxy(110,4);
                        fflush(stdin);
                        gets(proveedorTemp.paisproveedor.pais);

                        fwrite(&proveedorTemp, sizeof(proveedor), 1, temporal);
                        system("cls");
                        marcoConsola();
                        opcionesModificarproveedor();
                        verUnproveedor(proveedorTemp);
                        break;
                    
                    case 3:
                        verUnproveedor(proveedorTemp);
                        gotoxy(80,4);
                        printf("Modificar Provincia del proveedor: ");
                        gotoxy(114,4);
                        fflush(stdin);
                        gets(proveedorTemp.ProvinciaProveedor.provincia);

                        fwrite(&proveedorTemp, sizeof(proveedor), 1, temporal);
                        system("cls");
                        marcoConsola();
                        opcionesModificarproveedor();
                        verUnproveedor(proveedorTemp);
                        break;
                    
                    case 4:
                        verUnproveedor(proveedorTemp);
                        gotoxy(80,4);
                        printf("Modificar Ciudad del proveedor: ");
                        gotoxy(111,4);
                        fflush(stdin);
                        gets(proveedorTemp.CiudadProveedor.ciudad);

                        fwrite(&proveedorTemp, sizeof(proveedor), 1, temporal);
                        system("cls");
                        marcoConsola();
                        opcionesModificarproveedor();
                        verUnproveedor(proveedorTemp);
                        break;
                    case 5:
                        verUnproveedor(proveedorTemp);
                        gotoxy(80,4);
                        printf("Modificar C. postal: ");
                        gotoxy(100,4);
                        fflush(stdin);
                        gets(proveedorTemp.codigoPostalProveedor.codigoPostal);

                        fwrite(&proveedorTemp, sizeof(proveedor), 1, temporal);
                        system("cls");
                        marcoConsola();
                        opcionesModificarproveedor();
                        verUnproveedor(proveedorTemp);
                        break;
                    case 6:
                        verUnproveedor(proveedorTemp);
                        gotoxy(80,4);
                        printf("Modificar calle y numeracion: ");
                        gotoxy(109,4);
                        fflush(stdin);
                        gets(proveedorTemp.calleYnumeroProveedor.calleYnumero);

                        fwrite(&proveedorTemp, sizeof(proveedor), 1, temporal);
                        system("cls");
                        marcoConsola();
                        opcionesModificarproveedor();
                        verUnproveedor(proveedorTemp);
                        break;
                    
                    default:
                    puts("esa opcion no existe");
                        break;
                }
        }else{

            fwrite(&proveedorTemp, sizeof(stock), 1, temporal);

        }
        
    }

}



    fclose(archi);
    fclose(temporal);

    remove(PROVEEDORES_HISTORIAL);
    rename(AUX_ELIMINAR_PROVEEDOR, PROVEEDORES_HISTORIAL);
    cargando();
}

void eliminarproveedorArchivo(char nombreArchivo[LONGITUD], char nombreArchivoTemporal[LONGITUD]){
    char nombreProveedor[LONGITUD];
    proveedor proveedorTemporal;

    FILE *temporal = fopen(nombreArchivoTemporal, "ab");
    FILE *archi = fopen(nombreArchivo, "rb");

    printf("Nombre del proveedor que desea eliminar: ");
    fflush(stdin);
    gets(nombreProveedor);

    if( archi == NULL){
        
        puts("PROVEEDOR HISTORIAL NO EXISTE!");
        system("pause");

    }

    if (temporal == NULL)
    {
        puts("COPIA NO EXISTE!");
        system("pause");
    }
        
    while (fread(&proveedorTemporal, sizeof(proveedor), 1, archi) >0){

        
        if (strcmp(nombreProveedor , proveedorTemporal.empresa)==0){
            printf("\nSe ah eliminado: %s", proveedorTemporal.empresa);

            
        }else{


            fwrite(&proveedorTemporal, sizeof(proveedor), 1, temporal);
        }
    }
        
    getch();

    fclose(archi);
    fclose(temporal);

    remove(PROVEEDORES_HISTORIAL);
    rename(AUX_ELIMINAR_PROVEEDOR, PROVEEDORES_HISTORIAL);
}

void opcioneCargarproveedor(){ // CUADRO DONDE MUESTRA LOS DATOS para cargar proveedor
    marcoConsola();
    dibujarCuadro(0,5,151, 7);


    gotoxy(1,6);
    printf("Proveedor        |");
    gotoxy(25,6);
    printf("Pais proveedor    |");
    gotoxy(45,6);
    printf("Provincia proveedor   |");
    gotoxy(68,6);
    printf("Ciudad proveedor    |");
    gotoxy(90,6);
    printf("C. postal   |");
    gotoxy(104,6);
    printf("Calle y numero");
    
}

void opcionesModificarproveedor(){ // CUADRO DONDE MUESTRA LOS DATOS para modificar proveedor
    marcoConsola();
    dibujarCuadro(0,5,151, 7);


    gotoxy(1,6);
    printf("Proveedor[1]");
    gotoxy(25,6);
    printf("Pais proveedor[2]");
    gotoxy(45,6);
    printf("Provincia proveedor[3]");
    gotoxy(68,6);
    printf("Ciudad proveedor[4]");
    gotoxy(90,6);
    printf("C. postal[5]");
    gotoxy(104,6);
    printf("Calle y numero[6]");
}

////////////////////////////////////////////////////////////////
//////////                                            //////////
//////////       FIN    PROVEEDORES    LOGICA         //////////   
//////////                                            //////////
////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
//////////                                            //////////
//////////        CLIENTES           LOGICA           //////////   
//////////                                            //////////
////////////////////////////////////////////////////////////////    


void verTodoCliente( clientes aux, int cont){


   
    gotoxy(1,8+cont);printf("%s", aux.nombreYapellidoCliente);
    gotoxy(25,8+cont);printf("%s ", aux.paisCliente.pais);
    gotoxy(45,8+cont);printf("%s ", aux.ProvinciaCliente.provincia);
    gotoxy(68,8+cont);printf("%s ", aux.CiudadCliente.ciudad);
    gotoxy(90,8+cont);printf("%s ", aux.codigoPostalCliente.codigoPostal);
    gotoxy(104,8+cont);printf("%s ",aux.calleYnumeroCliente.calleYnumero);


}

void verUnCliente(clientes aux){

    gotoxy(1,8);printf("%s", aux.nombreYapellidoCliente);
    gotoxy(25,8);printf("%s ", aux.paisCliente.pais);
    gotoxy(45,8);printf("%s ", aux.ProvinciaCliente.provincia);
    gotoxy(68,8);printf("%s ", aux.CiudadCliente.ciudad);
    gotoxy(90,8);printf("%s ", aux.codigoPostalCliente.codigoPostal);
    gotoxy(104,8);printf("%s ",aux.calleYnumeroCliente.calleYnumero);
}

int cantidaCargaCliente(){
    int cantidad = 0;
    gotoxy(4,4);printf("Cauntos clientes desea agregar?: ");
    gotoxy(38,4);scanf("%d", &cantidad);

    return cantidad;
}

clientes cargarUnCliente(int cantidad){

    clientes clientesTemp;
    
    fflush(stdin);
    gotoxy(1,8+cantidad);
    gets(clientesTemp.nombreYapellidoCliente);
    fflush(stdin);
    gotoxy(25,8+cantidad);
    gets(clientesTemp.paisCliente.pais);
    fflush(stdin);
    gotoxy(45,8+cantidad);
    gets(clientesTemp.ProvinciaCliente.provincia);
    fflush(stdin);
    gotoxy(68,8+cantidad);
    gets(clientesTemp.CiudadCliente.ciudad);
    fflush(stdin);
    gotoxy(90,8+cantidad);
    gets(clientesTemp.codigoPostalCliente.codigoPostal);
    fflush(stdin);
    gotoxy(104,8+cantidad);
    gets(clientesTemp.calleYnumeroCliente.calleYnumero);


return clientesTemp;

}

int cargarMuchosCliente(clientes arr[], int dim, int cantidad){
    int i = 0;
    clientes aux;
    while (cantidad <= dim && cantidad != 0 ) {
        aux = cargarUnCliente(i);

        arr[i] = aux;
        
        cantidad--;
        i++;
    }
    return i;
}

void cargarEnArchivoCliente(char nombreArchivo[LONGITUD], clientes aux[LONGITUD], int validos){
    FILE *archi = fopen(nombreArchivo, "ab");

    if(archi != NULL){
        for(int i = 0; i < validos; i++){

            fwrite(&aux[i], sizeof(clientes), 1, archi);

        }

        fclose(archi);
    }else{
        printf("ERROR AL ESCRIBIR EL ARCHIVO");
    }

}

void leerArchivoCliente(char nombreArchivo[LONGITUD]){
    clientes aux;
    int cont = 0;
    FILE *archi = fopen(nombreArchivo, "rb");

    opcioneCargarCliente(); // MUESTRA las etiquedas  PARA VER LOS DATOS
    if(archi != NULL){
        while(fread(&aux, sizeof(clientes), 1, archi)> 0){
            verTodoCliente(aux, cont);

            cont++;
        }
        fclose(archi);
    }else{
        puts("ERROR AL LEER EL ARCHIVO");
    }
}

void modificarArchivoCliente(char nombreArchivo[LONGITUD], char nombreArchivoTemporal[LONGITUD]){
    char clienteScan[LONGITUD];
    clientes clientesTemp;
    FILE * temporal = fopen(nombreArchivoTemporal, "ab");
    FILE *archi = fopen(nombreArchivo, "r+b");

    

    if( archi == NULL){
    
        puts("STOCK HISTORIAL NO EXISTE!");
        system("pause");

    }

    if (temporal == NULL)
    {
        puts("COPIA NO EXISTE!");
        system("pause");
    }
    if(archi != NULL && temporal != NULL){

        gotoxy(4,4);
        printf("Ingrese el nombre de la tela: ");
        gotoxy(4,30);
        fflush(stdin);
        gets(clienteScan);

        opcionesModificarCliente();
        while (fread(&clientesTemp, sizeof(clientes), 1, archi) > 0){
        
        if (strcmp(clienteScan, clientesTemp.nombreYapellidoCliente) == 0){
            verUnCliente(clientesTemp);
            int option = 0;

                gotoxy(50,4);
                printf("Que desea modificar: ");
                gotoxy(70,4);
                scanf("%d", &option);   

                switch (option){
                    case 1:
                        verUnCliente(clientesTemp);
                        gotoxy(80,4);
                        printf("Modificar nombre y apellido: ");
                        gotoxy(98,4);
                        fflush(stdin);
                        gets(clientesTemp.nombreYapellidoCliente);

                        fwrite(&clientesTemp, sizeof(clientes), 1, temporal);
                        system("cls");
                        marcoConsola();
                        opcionesModificarCliente();
                        verUnCliente(clientesTemp);
                        break;
                    
                    case 2:
                        verUnCliente(clientesTemp);
                        gotoxy(80,4);
                        printf("Modificar pais del cliente: ");
                        gotoxy(110,4);
                        fflush(stdin);
                        gets(clientesTemp.paisCliente.pais);

                        fwrite(&clientesTemp, sizeof(proveedor), 1, temporal);
                        system("cls");
                        marcoConsola();
                        opcionesModificarCliente();
                        verUnCliente(clientesTemp);
                        break;
                    
                    case 3:
                        verUnCliente(clientesTemp);
                        gotoxy(80,4);
                        printf("Modificar provincia del cliente: ");
                        gotoxy(112,4);
                        fflush(stdin);
                        gets(clientesTemp.ProvinciaCliente.provincia);

                        fwrite(&clientesTemp, sizeof(proveedor), 1, temporal);
                        system("cls");
                        marcoConsola();
                        opcionesModificarCliente();
                        verUnCliente(clientesTemp);
                        break;
                    
                    case 4:
                        verUnCliente(clientesTemp);
                        gotoxy(80,4);
                        printf("Modificar ciudad del cliente: ");
                        gotoxy(107,4);
                        fflush(stdin);
                        gets(clientesTemp.CiudadCliente.ciudad);

                        fwrite(&clientesTemp, sizeof(proveedor), 1, temporal);
                        system("cls");
                        marcoConsola();
                        opcionesModificarCliente();
                        verUnCliente(clientesTemp);
                        break;
                    case 5:
                       verUnCliente(clientesTemp);
                        gotoxy(80,4);
                        printf("Modificar C. Postal del cliente: ");
                        gotoxy(112,4);
                        fflush(stdin);
                        gets(clientesTemp.codigoPostalCliente.codigoPostal);

                        fwrite(&clientesTemp, sizeof(proveedor), 1, temporal);
                        system("cls");
                        marcoConsola();
                        opcionesModificarCliente();
                        verUnCliente(clientesTemp);
                        break;
                    case 6:
                      verUnCliente(clientesTemp);
                        gotoxy(80,4);
                        printf("Modificar calle y numeracion del cliente: ");
                        gotoxy(121,4);
                        fflush(stdin);
                        gets(clientesTemp.calleYnumeroCliente.calleYnumero);

                        fwrite(&clientesTemp, sizeof(proveedor), 1, temporal);
                        system("cls");
                        marcoConsola();
                        opcionesModificarCliente();
                        verUnCliente(clientesTemp);
                        break;
                    
                    default:
                    puts("esa opcion no existe");
                        break;
                }
        }else{

            fwrite(&clientesTemp, sizeof(clientes), 1, temporal);

        }
        
    }

}



    fclose(archi);
    fclose(temporal);

    remove(CLIENTES_HISTORIAL);
    rename(AUX_ELIMINAR_CLEINTES, CLIENTES_HISTORIAL);
    cargando();
}

void eliminarClienteArchivo(char nombreArchivo[LONGITUD], char nombreArchivoTemporal[LONGITUD]){
    char nombreCliente[LONGITUD];
    clientes clienteTemporal;

    FILE *temporal = fopen(nombreArchivoTemporal, "ab");
    FILE *archi = fopen(nombreArchivo, "rb");

    printf("Nombre del cliente que desea eliminar: ");
    fflush(stdin);
    gets(nombreCliente);

    if( archi == NULL){
        
        puts("CLIENTE HISTORIAL NO EXISTE!");
        system("pause");

    }

    if (temporal == NULL)
    {
        puts("COPIA NO EXISTE!");
        system("pause");
    }
        
    while (fread(&clienteTemporal, sizeof(clientes), 1, archi) >0){

        
        if (strcmp(nombreCliente , clienteTemporal.nombreYapellidoCliente)==0){
            printf("\nSe ah eliminado: %s", clienteTemporal.nombreYapellidoCliente);

            
        }else{


            fwrite(&clienteTemporal, sizeof(clientes), 1, temporal);
        }
    }
        
    getch();

    fclose(archi);
    fclose(temporal);

    remove(CLIENTES_HISTORIAL);
    rename(AUX_ELIMINAR_CLEINTES, CLIENTES_HISTORIAL);
}

void opcioneCargarCliente(){ // CUADRO DONDE MUESTRA LOS DATOS para cargar clientes
    marcoConsola();
    dibujarCuadro(0,5,151, 7);


    gotoxy(1,6);
    printf("Nombre y Apellido     |");
    gotoxy(25,6);
    printf("Pais     |");
    gotoxy(45,6);
    printf("Provincia    |");
    gotoxy(68,6);
    printf("Ciudad     |");
    gotoxy(90,6);
    printf("C. postal   |");
    gotoxy(104,6);
    printf("Calle y numero");
    
}

void opcionesModificarCliente(){ // CUADRO DONDE MUESTRA LOS DATOS para modificar clientes
    marcoConsola();
    dibujarCuadro(0,5,151, 7);


    gotoxy(1,6);
    printf("Nombre y Apellido[1]");
    gotoxy(25,6);
    printf("Pais cliente[2]");
    gotoxy(45,6);
    printf("Provincia cliente[3]");
    gotoxy(68,6);
    printf("Ciudad cliente[4]");
    gotoxy(90,6);
    printf("C. postal[5]");
    gotoxy(104,6);
    printf("Calle y numero[6]");
}

////////////////////////////////////////////////////////////////
//////////                                            //////////
//////////       FIN    CLIENTES       LOGICA         //////////   
//////////                                            //////////
////////////////////////////////////////////////////////////////

////////////////////////////////EXTRAS/////////////////////////////////////////////////////////////////////

void creaCarpetas(){

    system("mkdir pedidos");
    system("mkdir stock");
    system("mkdir proveedores");
    system("mkdir clientes");


}

void cargando(){ // ANIMATIONS
    system("cls");
    gotoxy(50,10);printf("**************************************************************\n");
    gotoxy(50,11);printf("************************CARGANDO DATOS************************\n");
    gotoxy(50,12);printf("**************************************************************\n");


    for (int i = 0; i < 62; i++)
    {
        int cont = i;
        Sleep(020);
        gotoxy(80,15);printf("%%%d", cont+ 39);
        gotoxy(50+i,13);printf("%c",219);
    }
    printf("\n\n");
}

void marcoConsola(){ // para no andar modificando individualmente en cada menu
    dibujarCuadro(0,0,151,28);

}

void logo(){

 gotoxy(36,16);printf("88888888888       888                        8888888b.                    888      ");
 gotoxy(36,17);printf("    888           888                        888   Y88b                   888      ");
 gotoxy(36,18);printf("    888           888                        888    888                   888      ");
 gotoxy(36,19);printf("    888   .d88b.  888  8888b.  .d8888b       888   d88P 888  888 88888b.  888  888 ");
 gotoxy(36,20);printf("    888  d8P  Y8b 888      88b 88K           8888888P'  888  888 888  88b 888 .88P ");
 gotoxy(36,21);printf("    888  88888888 888 .d888888  Y8888b.      888        888  888 888  888 888888K  ");
 gotoxy(36,22);printf("    888  Y8b.     888 888  888     'X88      888        Y88b 888 888  888 888  88b ");
 gotoxy(36,23);printf("    888   'Y8888  888  Y888888  88888P       888         'Y88888 888  888 888  888 ");                                                                                                                                        
}