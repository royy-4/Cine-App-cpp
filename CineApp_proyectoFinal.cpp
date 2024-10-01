#include <iostream>
#include <string>
#include <array>
#include <time.h>


void menuPrincipal(); 
bool verificarUsuario(const std::string&, const std::string&); 
void verPeliculasCartelera(); 
void comprarBoletos(int&, int&, int&, int&, int&, int&, double& );  

std::string peliculaSeleccionada(); 
void imprimirTicketCompra(int, int, std::string); 

void inicializarAsientos(); 
void mostrarMapaAsientos(); 
void marcarAsientoOcupado(int fila, int columna); 

bool salaLlena(int);
void verReportes(int, int, int, int, int, int, double); 

bool verificarAdmin(const std::string&, const std::string&); 


//Valores globales usados en varias funciones
int boletosSala1 = 0, boletosSala2 = 0, boletosSala3 = 0, boletosSala4 = 0, boletosSala5 = 0, boletosTotal = 0;
double sumatoriaCompras = 0.0;
const int NUM_FILAS = 5; 
const int NUM_COLUMNAS = 10; 
char asientos[NUM_FILAS][NUM_COLUMNAS];
char respuestaCancelar;
bool continuarPrograma = true; //para controlar si se sale o no del programa por completo



//Regresa true si el usuario y contrasenia ingresados son iguales a las default
bool verificarAdmin(const std::string& usuarioAdmin, const std::string& contraseniaAdmin){
    return(usuarioAdmin == "admin" && contraseniaAdmin =="admin");
}

//Igual que la funcion anterior pero para las funciones de administrador
bool verificarUsuario(const std::string& usuario, const std::string& contrasenia) {
    return (usuario == "usuario" && contrasenia == "usuario");
}

bool salaLlena(int cantidad_boletos){

    //checa si la sala esta llena o no, si si deja de vender boletos para esa pelicula

    int totalAsientos = NUM_FILAS * NUM_COLUMNAS;

    totalAsientos -= cantidad_boletos;

    if(totalAsientos <= 0){
        return true;
    }else{
        return false;
    }

}

void verReportes(int boletosSala1,int boletosSala2,int boletosSala3,int boletosSala4,int boletosSala5,int boletosTotal,double sumatoriaCompras){


    char respuesta_Admin;

    std::cout<<         "\n REPORTES DE VENTAS Y ESTADISTICAS               \n";

    std::cout<<"Escoge las estadisticas que deseas ver\n";
    std::cout<<"1. Boletos vendidos por sala\n";
    std::cout<<"2. Boletos vendidos en total\n";
    std::cout<<"3. Ingresos totales netos\n";
    std::cout<<"4. Regresar al menu principal\n";
    std::cin>>respuesta_Admin;

    switch(respuesta_Admin){
        case '1':
            std::cout<<"\t Boletos vendidos por sala\n";
            std::cout<<"Sala 1: " << boletosSala1 <<"\n";
            std::cout<<"Sala 2: " << boletosSala2 <<"\n";
            std::cout<<"Sala 3: " << boletosSala3 <<"\n";
            std::cout<<"Sala 4: " << boletosSala4 <<"\n";
            std::cout<<"Sala 5: " << boletosSala5 <<"\n";
            verReportes(boletosSala1, boletosSala2, boletosSala3, boletosSala4, boletosSala5, boletosTotal, sumatoriaCompras);
            break;
        case '2':
            std::cout<<"\t Boletos vendidos en total\n";
            std::cout<<"Boletos: " << boletosTotal << "\n";
            verReportes(boletosSala1, boletosSala2, boletosSala3, boletosSala4, boletosSala5, boletosTotal, sumatoriaCompras);
            break;
        case '3':
            std::cout<<"\t Ingresos generados netos\n";
            std::cout<<"Total (en pesos mexicanos): "<< sumatoriaCompras <<"\n";
            verReportes(boletosSala1, boletosSala2, boletosSala3, boletosSala4, boletosSala5, boletosTotal, sumatoriaCompras);
            break;
        case '4':
            menuPrincipal();
            break;
        default:
            std::cout<<"Error, " << respuesta_Admin <<" no es una respuesta valida. Ingresa un numero del 1-4\n";
            break;

    }
}



void inicializarAsientos() {
    for (int i = 0; i < NUM_FILAS; ++i) {
        for (int j = 0; j < NUM_COLUMNAS; ++j) {
            asientos[i][j] = 'O'; // 'O' representa que el asiento esta disponible
        }
    }
}
// Funcion para mostrar el mapa de asientos
void mostrarMapaAsientos() {
    std::cout << "Asientos Disponibles (O) y Ocupados (X):" << std::endl;
    std::cout << "   ";
    for (int j = 0; j < NUM_COLUMNAS; ++j) {
        std::cout << char('A' + j) << " "; // Letras para las columnas
    }
    std::cout << std::endl;
    for (int i = 0; i < NUM_FILAS; ++i) {
        std::cout << i + 1 << "  "; // Numeros para las filas
        for (int j = 0; j < NUM_COLUMNAS; ++j) {
            std::cout << asientos[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

// Funcion para marcar un asiento como ocupado
void marcarAsientoOcupado(int fila, int columna) {
    if (asientos[fila][columna] == 'O') {
        asientos[fila][columna] = 'X'; // Marcar asiento como ocupado
        std::cout << "¡Reserva exitosa del asiento " << char('A' + columna) << "-" << fila + 1 << "!" << std::endl;
    } else {
        std::cout << "Lo siento, el asiento " << char('A' + columna) << "-" << fila + 1 << " ya esta ocupado." << std::endl;
    }
}


std::string peliculaSeleccionada(){

    std::string peliculas [6] = {"El Padrino", "Avengers: Endgame", "La La Land","Blade Runner 2049","Drive"," "};
  
    char seleccionCartelera;
    
    std::string peliculaEscogida;

    std::cout<<"\n";
    std::cout<<"\t CARTELERA\n";

    std::cout<<"\nSeleccione una pelicula para comprar boletos\n";

    std::cout<<"             Peliculas disponibles                      \n";
    std::cout<<"1. "<<peliculas[0]<<"\n"<<"2. "<<peliculas[1]<<"\n"<<"3. "<<peliculas[2]<<"\n"<<"4. "<<peliculas[3]<<"\n"<<"5. "<<peliculas[4]<<"\n";

    std::cout<<"6. Regresar menu principal\n";

    std::cout<<"Ingrese la película para la que comprara boleto (numero del 1 al 5, o 6 para regresar): \n";
    std::cin>>seleccionCartelera;
   
    switch(seleccionCartelera){
        case '1':
            peliculaEscogida = peliculas[0];
            break;
        case '2':
            peliculaEscogida = peliculas[1];
            break;
        case '3':
            peliculaEscogida = peliculas[2];
            break;
        case '4':
            peliculaEscogida = peliculas[3];
            break;
        case '5':
            peliculaEscogida = peliculas[4];
            break;
        case '6':
            menuPrincipal();
            break;
        default:
            std::cout<<seleccionCartelera<<" no es una opcion valida. Por favor ingrese un numero del 1 al 5 o la palabra regresar\n";
            peliculaSeleccionada();
            break;
    }


    return peliculaEscogida;
    
}




void comprarBoletos(int& boletosSala1, int& boletosSala2, int& boletosSala3, int& boletosSala4, int& boletosSala5, int& boletosTotal, double& sumatoriaCompras){ //funcion para comprar los boletos 


    std::string pelicula = peliculaSeleccionada();
   
    double precioEstandard=100.0, descuentoEstudiante=0.2, descuentoAdultoMayor=0.3, compraTotal=0.0; 
    inicializarAsientos();
    int cantidad_boletos=0; //cantidad de boletos de la pelicula
    char respuestaEstudiante,respuestaAdultoMayor, respuestaAdmin, contraseniaAdmin[40], usuarioAdmin[40], letraColumna, respuestaCancelar, respuesta_cliente;
    int fila, intentos=0;
    bool esAdmin = false;

   while (true) {
        std::cout << "Selecciona la cantidad de boletos a comprar: ";
        std::cin >> cantidad_boletos;

        if (std::cin.fail() || cantidad_boletos < 1 || cantidad_boletos>50) {
            std::cin.clear(); 
            while (std::cin.get() != '\n') ; 
            std::cout << "Por favor ingresa un número, mayor que 0 y menor o igual a 50.\n";
        } else {
            break; 
        }
    }
    
    for(int i=1;i<=cantidad_boletos;i++){

        std::cout<<"\t Persona " << i << "\n";

        do{
            std::cout<<"Estudiante (s/n)\n";
            std::cin>>respuestaEstudiante;

            if(respuestaEstudiante!='s' && respuestaEstudiante !='S' && respuestaEstudiante !='n' && respuestaEstudiante != 'N'){
                std::cout<<"Por favor ingresa una opcion valida (s/n)\n";
            }


        }while(respuestaEstudiante!='s' && respuestaEstudiante !='S' && respuestaEstudiante !='n' && respuestaEstudiante != 'N');


        do{
            std::cout<<"Adulto mayor (s/n)\n";
            std::cin>>respuestaAdultoMayor;

            if(respuestaAdultoMayor!='s' && respuestaAdultoMayor !='S' && respuestaAdultoMayor !='n' && respuestaAdultoMayor != 'N'){
                std::cout<<"Por favor ingresa una opcion valida (s/n)\n";
            }

        }while(respuestaAdultoMayor!='s' && respuestaAdultoMayor !='S' && respuestaAdultoMayor !='n' && respuestaAdultoMayor != 'N');

        if(respuestaEstudiante=='s' || respuestaEstudiante == 'S'){
            precioEstandard -= (precioEstandard * descuentoEstudiante);
        }

        else if(respuestaAdultoMayor=='s'|| respuestaAdultoMayor == 'S'){
            precioEstandard -= (precioEstandard * descuentoAdultoMayor);
        }

         // Mostrar mapa de asientos y permitir al usuario elegir
        mostrarMapaAsientos();
        
        std::cout << "Seleccione el asiento (fila columna): ";
        std::cin >> fila >> letraColumna;

        // Convertir la letra de la columna a índice
        int columna = letraColumna - 'A';

        // Verificar si la fila y la columna están dentro del rango válido
        if (fila >= 1 && fila <= NUM_FILAS && columna >= 0 && columna < NUM_COLUMNAS) {
            // Marcar el asiento como ocupado
            marcarAsientoOcupado(fila - 1, columna);
        } else {
            std::cout << "Por favor, ingrese una fila y columna validas.\n";
            --i; // Para repetir la iteración y permitir al usuario ingresar un asiento válido
        }


       if(pelicula=="El Padrino"){
            boletosSala1 ++;
        }else if(pelicula=="Avengers: Endgame"){
            boletosSala2 ++;
        }else if(pelicula=="La La Land"){
            boletosSala3 ++;
        }else if(pelicula=="Blade Runner 2049"){
            boletosSala4 ++;
        }else if(pelicula=="Driver"){
            boletosSala5 ++;
        }
       
       boletosTotal++;
       
       
       
        //contador para ir quitando num asientos disponibles de los 50 y mostrar si la sala ya esta llena
        if(salaLlena(cantidad_boletos)){
            std::cout<<"Lo sentimos pero esta sala ya esta llena, por favor eliga otra pelicula\n";
            peliculaSeleccionada();
        }

        
        std::cout << "¿Desea cancelar la compra? (s/n): ";
        std::cin >> respuestaCancelar;

        if (respuestaCancelar == 's' || respuestaCancelar == 'S') {
        std::cout << "Compra cancelada. Gracias por visitar nuestro cine.\n";
        return; // Sale de la función sin imprimir el ticket
        }




    }


    compraTotal += (cantidad_boletos*precioEstandard);
    sumatoriaCompras+=compraTotal;
    imprimirTicketCompra(compraTotal, cantidad_boletos,pelicula);

   

    std::cout<<"\n1. Comprar boletos para otra pelicula\n2. Regresar al menu principal\n3. VER ESTADISTICAS PROGRAMA (SOLO ADMIN)\n";
    std::cin>>respuesta_cliente;
    fflush(stdin);

    switch(respuesta_cliente){
        case '1':
            comprarBoletos(boletosSala1, boletosSala2, boletosSala3, boletosSala4, boletosSala5, boletosTotal, sumatoriaCompras);
            break;
        case '2':
            menuPrincipal();
            break;

        case '3':
            
            while(!esAdmin && intentos<3){
                std::cout<<"Ingresa tu usuario: ";
                std::cin.getline(usuarioAdmin,40,'\n');
                std::cout<<"Ingresa tu contrasenia: ";
                std::cin.getline(contraseniaAdmin,40,'\n');

                if(verificarAdmin(usuarioAdmin,contraseniaAdmin)){
                    esAdmin = true;
                    verReportes(boletosSala1,boletosSala2,boletosSala3,boletosSala4,boletosSala5,boletosTotal,sumatoriaCompras);
                }else{
                    std::cout<<"Credenciales incorrectas, intenta de nuevo\n";
                    intentos++;
                    std::cout<<intentos<<" intentos restantes\n";
                    fflush(stdin);
                }
            }

            if (!esAdmin) {
                std::cout << "Exceso de intentos. Regresando al menú principal.\n";
                menuPrincipal();
            }
            

            break;
            

        default:
            std::cout<<respuesta_cliente<<" no es una respuesta valida. Ingrese 1 o 2\n";
            break;
    }
    

   
}

void imprimirTicketCompra(int compraTotal, int cantidad_boletos, std::string pelicula){

    char numSala;
   
    if(pelicula=="El Padrino"){
        numSala = '1';
    }else if(pelicula=="Avengers: Endgame"){
        numSala = '2';
    }else if(pelicula=="La La Land"){
        numSala = '3';
    }else if(pelicula=="Blade Runner 2049"){
        numSala = '4';
    }else if(pelicula=="Driver"){
        numSala = '5';
    }

    std::cout<<"\n";
    std::cout<<"            RESUMEN DE COMPRA           \n";
    std::cout<<"PELICULA: " << pelicula << "\n";
    std::cout<<"\n";
    std::cout<< "Boletos comprados: " << cantidad_boletos <<"\n";

    std::cout << "Asientos comprados:\n";

    for (int i = 0; i < NUM_FILAS; ++i) {
        for (int j = 0; j < NUM_COLUMNAS; ++j) {
            if (asientos[i][j] == 'X') {
                std::cout << i + 1 << char('A' + j) << " "; 
            }
        }
    }

    std::cout << "Total: " << compraTotal << "\n";
    std::cout<<"\n";
    std::cout<<"SALA: " << numSala << "\n";
    std::cout<<"           GRACIAS POR TU COMPRA Y PREFERENCIA              \n";
    

    //imprimir el ticket del cliente
}



void verPeliculasCartelera() {
    
    std::string peliculas [5] = {"El Padrino", "Avengers: Endgame", "La La Land","Blade Runner 2049","Drive"};
    char respuesta_regresarMenu=' ';

    while(respuesta_regresarMenu != 's' && respuesta_regresarMenu!='S'){


        std::cout<<"\n";
        std::cout<<"\t CARTELERA\n";


        std::cout<<"             Peliculas disponibles                      \n";
        
        for(int i=0;i<5;i++){
            std::cout<<peliculas[i]<<"\n";
        }

        std::cout<<"\nRegresar menu principal (ingrese s)\n";
        std::cin>>respuesta_regresarMenu;
       

        if (respuesta_regresarMenu == 's' || respuesta_regresarMenu == 'S'){
            menuPrincipal();
        }
        else{
            std::cout<<"Ingresa una respuesta valida, 's', " << respuesta_regresarMenu << " no es una opcion valida \n";
            fflush(stdin);
        }


    }

   
}


void menuPrincipal(){

    char opcionSeleccionadaUsuario;
    
    std::cout<<"            CINE APP            \n";
    std::cout<<"\t Por favor eliga una opcion\n";


    std::cout<<"1. Ver cartelera\n";
    std::cout<<"2. Compra de boletos\n";
    std::cout<<"3. Cerrar sesion\n";
    std::cout<<"4. Salir\n";
    
    
    std::cin>>opcionSeleccionadaUsuario;
    fflush(stdin);

    switch(opcionSeleccionadaUsuario){
        case '1':
            verPeliculasCartelera();
            break;
        case '2':
            comprarBoletos(boletosSala1, boletosSala2, boletosSala3, boletosSala4, boletosSala5, boletosTotal, sumatoriaCompras);  
            break;
        case '3':
            std::cout<<"Fin de sesion exitoso\n";
            return;
            break;
        case '4':
            std::cout<<"Gracias por usar CINE APP, esperamos volver a verte pronto\n";
            continuarPrograma = false;
            break;
        default:
            std::cout<<"Por favor ingrese una opcion valida (1-4)\n";
            break;
    }

}


int main(){
    //INTENTOS MAXIMOS PARA INICIAR SESION 3
    int intentos=3;
    char usuario[40],contrasenia[40]; //el maximo de caracteres que se pueden ingresar es 40 para contreasenia y usuario
    

    std::cout<<"\n\t Bienvenido a Cine App!\n";

    //inicio de sesion;
    while(intentos>0 && continuarPrograma){ //mientras que los intentos sean mayores que 0

        if (intentos<=3){ //si el intento es igual o menor a 3

            std::cout<<"\nIngresa tu usuario: "; //se pide el usuario
            std::cin.getline(usuario,40,'\n'); //se lee un usuario que siempre debe ser de 13 caracteres

            std::cout<<"\nIngresa tu contrasenia: ";
            std::cin.getline(contrasenia,40,'\n');

            intentos--;
        }


        if(verificarUsuario(usuario,contrasenia)){
            std::cout<<"Inicio de sesion exitoso. Bienvenido " << usuario << ".\n";
            
            menuPrincipal();
            
        }
        
        else{
            std::cout<<"Credenciales incorrectas. Inicio de sesion fallido.\n";
            std::cout<<"Intentos restantes: "<<intentos<<"\n";
            fflush(stdin); //se limpia el buffer para que no haya residuos de nada
        }


    }

    if(intentos==0){
        std::cout<<"Demasiados intentos de inicio de sesion. Cuenta bloqueada\n";
    
    }


    
    
    
    return 0;
}
