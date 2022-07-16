/* 
    Programa: juego.c
    Descripción: Función principal del juego "Personal Forest" desarrollado como proyecto final de Programación.
    Autores: Samuel Echeverri Blandón & Juan Felipe López Castaño
    Fecha: 26-nov-2020
*/

#include <stdio.h>      // Se incluye la librería estándar para la entrada y salida de texto
#include <stdlib.h>     // Se incluye la librería stdlib, que contiene las funciones system, srand y rand 
#include <string.h>     // Se incluye la librería string, que contiene la función strtok
#include <time.h>       // Se incluye la librería time, que contiene la función time, necesaria para el funcionamiento de srand

#define MAX_NOMBRE 50       // Se define una constante simbólica con el número máximo de caracteres para el nombre del personaje

// Estructura del personaje jugable
typedef struct
{
    char nombre[ MAX_NOMBRE ];      // Nombre del personaje
    int salud;          // Puntos de salud del personaje
    int dinero;         // Cantidad de dinero del personaje
    int afecto;         // Puntos de afecto del personaje
} Personaje;

// Prototipos de las funciones y procedimientos
void mostrarMenu();         
void imprimirIndicaciones();
void imprimirCreditos();
int seleccionPersonaje();
Personaje definirPersonaje( int numPersonaje );
void controlarHistoria ( Personaje jugador, int numPersonaje );
void historia1( Personaje jugador );
void historia2( Personaje jugador );
void evaluarPerdio( Personaje jugador );

// Función principal
int main()
{
    srand( time(NULL) );        // Función para eliminar la semilla creada por la función rand (para generar números aleatorios)
    mostrarMenu();              // Se invoca al procedimiento para mostrar el menú principal del juego

    return 0;       // Fin de la función principal
}

/*
    Procedimiento recursivo para mostrar el menú principal del juego, y para poner éste en marcha
    param: Ninguno
*/
void mostrarMenu()
{
    // Declaración de variables locales
    char opcion, atras;         // Variables de control para el menú principal
    int numPersonaje;           // Número del personaje jugable, escogido al azar
    Personaje jugador;          // Estructura del personaje jugable
    
    do
    {
        system( "cls" );        // Se limpia la pantalla de la terminal

        // Se imprime el título 
        printf( "PERSONAL FOREST" );
        printf( "\nEn esta historia interactiva, encarnaras la vida de alguno de dos personajes y decidiras como terminara su historia\n");
        
        // Se muestra en pantalla el menú de inicio
        printf( "\nSelecciona una opcion" ); 
        printf( "\n1. Jugar" );
        printf( "\n2. Como jugar" );
        printf( "\n3. Creditos" );
        printf( "\n4. Salir\n" );
        scanf( "%c%*c", &opcion );          // Se lee la opción ingresada por el usuario

        // Se evalúa la opción ingresada
        switch ( opcion )
        {
        case '1': // Para el caso 1 (jugar), se invocan todas las funciones y procedimientos con los que funcionará el juego
            system( "cls" );        // Se limpia la pantalla de la terminal

            numPersonaje = seleccionPersonaje();         // Se invoca a la función que seleccionará al personaje jugable de manera aleatoria
            jugador = definirPersonaje( numPersonaje );  // Se invoca a la función que inicializará las variables del personaje jugable

            // Se invoca al procedimiento que controlará el resto del juego, pasando como argumentos los valores antes retornados por las funciones
            controlarHistoria( jugador, numPersonaje ); 
            break;

        case '2': // En el caso 2 (cómo jugar), se imprimen las indicaciones sobre cómo funciona el juego y qué es lo que debe hacer el jugador
            system( "cls" );        // Se limpia la pantalla de la terminal
            imprimirIndicaciones();         // Se invoca al procedimiento que imprimirá las indicaciones
            
            // Se pregunta al usuario si quiere volver al menú o salir del juego
            printf( "\nPresiona 1 para volver al menu / Cualquier otra tecla para salir\n" );
            scanf( "%c%*c", &atras );       // Se lee la opción ingresada
            
            // Se evalúa la opción ingresada
            if ( atras == '1' )
            {
                // En caso de elegir '1', se vuelve a mostrar el menú principal
                mostrarMenu();
            }
            else
            {
                // En cualquier otro caso, se termina la ejecución del programa
                system( "exit" );
            }
            break;

        case '3': // En el caso 3, se muestran los créditos correspondientes de los creadores del juego
            system( "cls" );        // Se limpia la pantalla de la terminal
            imprimirCreditos();     // Se invoca al procedimiento que imprimirá los créditos

            // Se pregunta al usuario si quiere volver al menú o salir del juego
            printf( "\nPresiona 1 para volver al menu / Cualquier otra tecla para salir\n" );
            scanf( "%c%*c", &atras );
            
            // Se evalúa la opción ingresada
            if ( atras == '1' )
            {
                // En caso de elegir '1', se vuelve a mostrar el menú principal
                mostrarMenu();
            }
            else
            {
                // En cualquier otro caso, se termina la ejecución del programa
                system( "exit" );
            }
            break;

        case '4': // En el caso 4 (salir), se ejecuta la instrucción que terminará la ejecución del programa
            system( "exit" );          // Función para terminar la ejecución
            break;
        
        default: // Cualquier otro número ingresado, será tomado como opción inválida
            printf( "Opcion invalida" );  // Se imprime el mensaje de error
            break;
        } 
    } while ( opcion < '1' || opcion > '4' );       // Lo anterior se repite si el jugador ingresa alguna tecla inválida
}

/* 
    Procedimiento para imprimir las indicaciones generales del juego
    param: Ninguno
*/
void imprimirIndicaciones()
{
    // Se imprimen las indicaciones del juego
    printf( "COMO JUGAR\n--------------------------------------------------------------------------------------------------------------\n" );
    printf( "\nEste juego se trata de tomar las riendas de la vida de alguno de dos posibles personajes jugables.\n" );
    printf( "\nTodos los personajes jugables cuentan con tres barras que deben mantener en un nivel alto para vivir plenamente." );
    printf( "\nLas barras son: Salud, dinero y afecto.\n" );
    printf( "\nEstas barras aumentan o disminuyen su nivel dependiendo de las decisiones que tome el jugador a lo largo de la historia." );
    printf( "\nAl empezar a jugar, se determina aleatoriamente con cual de los dos personajes jugables empezara la historia." );
    printf( "\nCada personaje tiene en buen nivel dos de sus barras, y una casi vacia.\n" );
    printf( "\nEl objetivo del juego es terminar cada historia de manera satisfactoria, manteniendo todas las barras en un buen nivel.\n" );
    printf( "\nCuidado con tus decisiones: Si alguna de las barras llega a 0, pierdes.\n" );
}

/* 
    Procedimiento para imprimir los créditos a los creadores del juego
    param: Ninguno
*/
void imprimirCreditos()
{
    // Se imprimen los créditos
    printf( "CREDITOS\n------------------------------------------------------------------------------------------\n" );
    printf( "\nGuion:\n Juan Felipe Lopez Casta%co & Samuel Echeverri Blandon\n", 164 );
    printf( "\nDirectores ejecutivos:\n Juan Felipe Lopez Casta%co & Samuel Echeverri Blandon\n", 164 );
    printf( "\nProductores:\n Juan Felipe Lopez Casta%co & Samuel Echeverri Blandon\n", 164 );
    printf( "\nMarketing:\n Juan Felipe Lopez Casta%co & Samuel Echeverri Blandon\n", 164 );
    printf( "\nDise%co:\n Juan Felipe Lopez Casta%co & Samuel Echeverri Blandon\n", 164, 164 );
    printf( "\nProgramacion:\n Juan Felipe Lopez Casta%co & Samuel Echeverri Blandon\n", 164 );
    printf( "\nAsesoria legal:\n Juan Felipe Lopez Casta%co & Samuel Echeverri Blandon\n", 164 );
    printf( "\nDirectores artisticos:\n Juan Felipe Lopez Casta%co & Samuel Echeverri Blandon\n", 164 );
    printf( "\nReparto:\n Juan Felipe Lopez Casta%co & Samuel Echeverri Blandon\n", 164 );
    printf( "\nCasting:\n Juan Felipe Lopez Casta%co & Samuel Echeverri Blandon\n", 164 );
    printf( "\nAsesores de vestuario:\n Juan Felipe Lopez Casta%co & Samuel Echeverri Blandon\n", 164 );
    printf( "\nMusica compuesta por:\n Juan Felipe Lopez Casta%co & Samuel Echeverri Blandon\n", 164 );
    printf( "\nEdicion y montaje:\n Juan Felipe Lopez Casta%co & Samuel Echeverri Blandon\n", 164 );
    printf( "\nAdaptacion:\n Juan Felipe Lopez Casta%co & Samuel Echeverri Blandon\n", 164 );
    printf( "\nEscenografia:\n Juan Felipe Lopez Casta%co & Samuel Echeverri Blandon\n", 164 );
    printf( "\nStoryboard:\n Juan Felipe Lopez Casta%co & Samuel Echeverri Blandon\n", 164 );
    printf( "\nEscrito y dirigido por:\n Juan Felipe Lopez Casta%co & Samuel Echeverri Blandon\n", 164 );
    printf( "\nAgradecimientos especiales para:\n Juan Felipe Lopez Casta%co & Samuel Echeverri Blandon\n", 164 );
    printf( "\nProyecto final de Programacion. Semestre II. 2020\n" );
}

/* 
    Función para seleccionar un personaje jugable aleatorio
    param: Ninguno
    return: Número del personaje jugable seleccionado al azar
*/
int seleccionPersonaje()
{
    // Declaración de variables locales
    int numAleatorio, numPersonaje;
    char seleccionPersonaje;

    seleccionPersonaje = '1';        // Se inicializa la variable que controlará las repeticiones del ciclo

    do{
        printf("\nGenerando personaje al azar...\n");        
        numAleatorio = 1 + (rand() % ((2 - 1) + 1));        // Se genera un numero aleatorio entre 1 y 2

        // Se evalúa el número aleatorio obtenido anteriormente
        switch ( numAleatorio )
        {
        case 1:
            // Presentación del personaje jugable 1
            printf("Eres un joven sin necesidad de tener un futuro prometedor debido al dinero de tu familia, pero sufres problemas de salud\n");
            numPersonaje = 1;        // Se jugará con el personaje número 1
            break;

        case 2:
            // Presentación del personaje jugable 2
            printf("Apenas eres una joven adulta, y tu gran problema es la ansiedad social que te carcome\n");
            numPersonaje = 2;        // Se jugará con el personaje número 3
            break;
        }

        // Se confirma si se jugará con el personaje escogido al azar
        printf("\nSelecciona 1 si quieres volver a escoger personaje / Cualquier otra tecla para quedarte con el personaje asignado\n");
        scanf("%c%*c", &seleccionPersonaje);        // Se lee la respuesta del jugador
        
    } while ( seleccionPersonaje == '1' );          // El ciclo se repite si el jugador ingresa '1'

    return numPersonaje;        // Se retorna el número del personaje escogido   
}

/* 
    Función para inicializar las variables del personaje según el número que se haya escogido
    param: Número del personaje jugable escogido
    return: Estructura del personaje jugable ya inicializada
*/
Personaje definirPersonaje( int numPersonaje )
{
    // Declaración de variable local
    Personaje jugador;          // Estructura del personaje jugable, la cual será inicializada
    
    // Se evalúa el número del personaje jugable escogido al azar
    switch ( numPersonaje ){
    case 1:
        // Se llenan los datos para el personaje jugable número 1
        printf("\nIngresa el nombre del personaje: ");
        fgets( jugador.nombre, sizeof (jugador.nombre), stdin);
        strtok( jugador.nombre, "\n" );
        jugador.salud = 25;
        jugador.dinero = 90;
        jugador.afecto = 60;
        break;

    case 2:
        // Se llenan los datos para el personaje jugable número 2
        printf("\nIngresa el nombre del personaje: ");
        fgets( jugador.nombre, sizeof (jugador.nombre), stdin);
        strtok( jugador.nombre, "\n" );
        jugador.salud = 70;
        jugador.dinero = 70;
        jugador.afecto = 20;
        break;
    }

    return jugador;         // Se retorna la estructura del personaje con sus respectivos valores iniciales
}

/* 
    Procedimiento para determinar la historia que será jugada
    param: Estructura inicializada del personaje jugable, número del personaje jugable escogido
*/
void controlarHistoria (Personaje jugador, int numPersonaje)
{
    // Se muestran al jugador los valores iniciales de su personaje jugable
    printf("\n%s, tus valores iniciales son:\n", jugador.nombre);
    printf("%d de salud, %d de dinero, %d de afecto\n\n", jugador.salud, jugador.dinero, jugador.afecto );
    
    system( "pause" );          // Se espera la confirmación del jugador para continuar

    // Se evalúa el número del personaje jugable escogido
    if( numPersonaje == 1 ){
        historia1( jugador );             // Para el personaje jugable número 1, se ejecuta la historia número 1
    }
    else{
        if( numPersonaje == 2 ){
            historia2( jugador );         // Para el personaje jugable número 2, se ejecuta la historia número 2
        }
    }
}

/* 
    Procedimiento para jugar la historia número 1 
    param: Estructura inicializada del personaje jugable
*/
void historia1( Personaje jugador )
{  
    // Declaración de variables locales
    int *salud, *dinero, *afecto;      // Punteros que mostrarán al jugador el estado de sus variables    
    char decision;                     // Variable que amacenará las decisiones tomadas por el jugador
    
    // Se asignan los punteros a las direcciones en memoria de las variables del personaje jugable
    salud = &jugador.salud;
    dinero = &jugador.dinero;
    afecto = &jugador.afecto;
    
    system( "cls" );        // Se limpia la pantalla de la terminal
    system( "color c" );    // Se cambia el color de las letras de la terminal a rojo claro
    
    // Inicia la historia
    printf( "New Orleans, 2001\n" );

    jugador.dinero -= 85;       // Se modifica el valor de la variale dinero, para que vaya acorde con los primeros sucesos de la historia
    
    printf("\nDINERO: %d\n", *dinero);          // Se muestra al jugador su cantidad de dinero actual

    system( "pause" );          // Se espera la confirmación del jugador para continuar
    system( "cls" );            // Se limpia la pantalla de la terminal

    // Se imprimen los diálogos
    printf( "\n???: Despierta, despierta!!!\n" );
    printf( "\n???: Nos van a atrapar! Muevete rapido de ahi!\n" );

    // Se le pide al jugador que tome una decisión
    printf( "PRESIONA 1 PARA DESPERTAR Y MOVERTE / CUALQUIER OTRA TECLA PARA QUEDARTE DONDE ESTAS\n" );
    scanf( "%c%*c", &decision );       // Se lee la decisión tomada por el jugador
    
    // Se evalúa la decisión tomada
    if ( decision == '1' )
    {
        // Se imprimen los diálogos
        printf( "\n???: Corre! Corre!\n" );
        printf( "\n  %s: Que esta pasando?\n", jugador.nombre);
        printf( "\n???: En serio no sabes?\n");
        printf( "\n  %s: No. Solo se que me duele la cabeza\n", jugador.nombre);
        printf( "\n???: Te golpearon mientras robabamos\n");
    }
    else{
        // Se imprimen los diálogos y continúa la historia
        printf( "\nOficial de policia: Hoy no se escapan, perros\n" );
        printf( "\nEL OFICIAL DE POLICIA TE AGARRA DEL CUELLO E INTENTA GOLPEARTE\n" );
        printf( "\n???: Sueltalo!\n" );
        printf( "\nEL OFICIAL DE POLICIA RECIBE UNA PALIZA Y TE SUELTA\n" );
        printf( "\n???: Larguemonos de aqui!!\n" );

        system( "pause" );          // Se espera la confirmación del jugador para continuar
        
        // Se informa al jugador las consecuencias de su decisión 
        printf( "\nYA QUE NO DECIDISTE LEVANTARTE CUANDO TE LO PIDIERON, TE SIENTES CULPABLE POR HABER PUESTO EN PELIGRO" );
        printf( " A TUS COMPA%cEROS\n", 165 ); 
        printf( "\nPIERDES 10 PUNTOS DE AFECTO\n" );
        
        jugador.afecto -= 10;       // Se resta 10 a la variable afecto, como consecuencia de la decisión tomada

        // Se muestran al jugador los valores actuales de su personaje jugable
        printf( "\nTU ESTADO ACTUAL ES:\n" );
        printf( "SALUD: %d | DINERO: %d | AFECTO: %d!!\n", *salud, *dinero, *afecto );
    }

    system( "pause" );          // Se espera la confirmación del jugador para continuar
    system( "cls" );            // Se limpia la pantalla de la terminal

    // Se imprimen los diálogos y continúa la historia
    printf("\nHAS LLEGADO A UN LUGAR SEGURO\n");
    printf("\n???: Estamos todos?\n");
    printf("\n???: Jason, donde esta Kevin???");
    printf("\n  Jason: Paro una cuadra atras, esta bien\n");
    printf("\n???: Que paso contigo, %s? Pense que te perderiamos\n", jugador.nombre);
    printf("\n  %s: Ni siquiera se de quien era la voz que me gritaba en la tienda\n", jugador.nombre);
    printf("\n???: En serio no me reconoces a mi? Soy Brian, aunque claro, no nos conocemos de muchos meses :(\n");
    printf("\n  %s: Claro que te reconozco, pero estaba muy confundido alli\n", jugador.nombre);
    printf("\nBrian: Todo es confuso para todos desde que se vive en la calle...\n");
    printf("\n  %s: Mejor no hablemos de eso, repartamonos el dinero\n", jugador.nombre);

    jugador.dinero += 5;        // Se suma 5 a la variable dinero, para mantener coherencia con los hechos de la historia

    // Se muestran al jugador los valores actuales de su personaje jugable
    printf( "\nTU ESTADO ACTUAL ES:\n" );
    printf( "SALUD: %d | DINERO: %d!! | AFECTO: %d\n", *salud, *dinero, *afecto );

    system( "pause" );          // Se espera la confirmación del jugador para continuar
    system( "cls" );            // Se limpia la pantalla de la terminal

    // Se continúa con la historia
    printf( "AL DIA SIGUIENTE DEL ROBO...\n");
    
    // Se le pide al jugador que tome una decisión
    printf( "\nPRESIONA 1 PARA HABLAR CON JASON / CUALQUIER OTRA TECLA PARA HABLAR CON BRIAN\n" );
    scanf( "%c%*c", &decision );         // Se lee la decisión tomada

    // Se evalúa la decisión tomada
    if( decision == '1' )
    {
        // Se imprimen los diálogos y continúa la historia
        printf( "\n%s: Jason!\n", jugador.nombre );
        printf( "\n  Jason: Hey!\n" );
        printf( "\n%s: Buscas algo?\n", jugador.nombre );
        printf( "\n  Jason: Hmm... Creo que perdi mi encendedor en medio de lo de ayer...\n" );
        printf( "\n%s: Ten, te presto el mio\n", jugador.nombre );
        printf( "\nJASON SACA UN CIGARRILLO Y USA TU ENCENDEDOR PARA EMPEZAR A FUMAR\n" );
        printf( "\n  Jason: Bonito encendedor" );
        printf( "\n  Jason: A quien se lo robaste?\n" );
        printf( "\n%s: Es mio. Aunque no lo parezca, no todo lo que tengo es robado\n", jugador.nombre );
        printf( "\n  Jason: No sabia que tenias tanto dinero para gastar en encendedores finos\n" );
        printf( "\nJASON TE DEVUELVE EL ENCENDEDOR Y LO USAS PARA ENCENDER TU CIGARRILLO\n" );
        printf( "\n  Jason: Bueno, necesitas algo? A que viniste?\n" );
        printf( "\n%s: Solo buscaba alguien con quien hablar. No hay nada mas que hacer en esta pocilga\n", jugador.nombre );
        printf( "\n  Jason: De acuerdo" );
        printf( "\n  Jason: Sabes? Me causa curiosidad saber de donde vienes. Eres el mas nuevo de por aqui\n" );

        // Se le pide al jugador que tome una decisión
        printf("\nPRESIONA 1 PARA CONTARLE LA VERDAD A JASON / CUALQUIER OTRA TECLA PARA INVENTARTE ALGO\n");
        scanf( "%c%*c", &decision );       // Se lee la decisión tomada
        
        system( "cls" );        // Se limpia la pantalla de la terminal

        // Se evalúa la decisión tomada
        if( decision == '1' )
        {
            // Se imprimen los diálogos
            printf("\nNo te mentire, vengo de una familia con mucho dinero. Tambien tenia una vida de ensueño");
            printf("\nMi infancia no tiene nada de interesante, simplemente tenia amigos, estudiaba en un buen colegio y tenia lo que pedia");
            printf("\nHace unos dos años empece a ir mucho a fiestas, y ya sabes, ser joven y estar en espacios como esos...");
            printf("\nEso trae muchos problemas. Empece a juntarme con malas amistades y a hacer cosas que no debia");
            printf("\nMi familia se dio cuenta en un punto, estaba muy mal fisicamente: era muy notorio. Me pillaron y me internaron");
            printf("\nMe escape del internado, no soporto estar alli. Seguramente han de estar buscandome y dandome por muerto. " );
            printf( "Es mejor para todos");
            printf("\nPor eso fumo tanto, quiero liberarme de esa carga, ademas tengo sindrome de abstinencia\n"); 

            // Se informa al jugador las consecuencias de su decisión
            printf("\nJASON NOTA QUE LE ESTAS SIENDO SINCERO\n");
            jugador.afecto += 5;        // Se suma 5 a la variable afecto, como consecuencia de la decisión tomada
            
            // Se muestra al jugador los valores actuales de su personaje jugable
            printf( "\nTU ESTADO ACTUAL ES:\n" );
            printf( "SALUD: %d | DINERO: %d | AFECTO: %d!!\n", *salud, *dinero, *afecto );
        }
        else{
            // Se imprimen los diálogos
            printf("\nPues mira, soy de pueblo. Pero mi familia es peque%ca", 164);
            printf("\nMis padres siempre discutian mucho, y mi hermano mayor siempre me desprecio");
            printf("\nPeleabamos mucho y me canse de vivir con ellos, me fui de casa e incluso del estado en el que vivia");
            printf("\nSeguramente no saben nada de mi, pero a ninguno de ellos le ha de importar");
            printf("\nMe acogio a muy temprana edad una familia muy humilde, no estaban mucho tiempo en casa, casi nunca, de hecho.");
            printf("\nPor eso, yo salia mucho de fiestas, y me adentre muy pronto al mundo de las drogas");
            printf("\nPasaron a%cos. Pero cuando se enteraron, me echaron de casa, y aqui estoy.\n", 164);

            // Se informa al jugador las consecuencias de su decisión
            printf("\nJASON NOTA ALGO RARO EN TU HISTORIA\n");
            jugador.afecto -= 10;       // Se resta 10 a la variable afecto, como consecuencia de la decisión tomada
            
            // Se muestra al jugador los valores actuales de su personaje jugable
            printf( "\nTU ESTADO ACTUAL ES:\n" );
            printf( "SALUD: %d | DINERO: %d | AFECTO: %d!!\n", *salud, *dinero, *afecto );
        }

        system( "pause" );          // Se espera la confirmación del usuario para continuar
        system( "cls" );            // Se limpia la pantalla de la terminal
        
        // Se evalua la decision tomada antes (si se le cuenta o no la verdad a Jason)
        if( decision == '1' )
        {
            // Se imprimen los diálogos
            printf( "\nJason: Interesante historia. Pero solo con un 'No te metas en mis asuntos' bastaba\n" );
            printf( "\nTE RIES DEL COMENTARIO DE JASON\n" );
            printf( "\nJason: Sabes algo, %s? Tienes mi apoyo. Yo, en tu lugar, tampoco habria querido vivir internado", jugador.nombre );
            printf( "\nJason: Eres un verdadero hombre\n" );
            printf( "\n  %s: No lo se, yo aun tengo mis dudas sobre haber hecho lo correcto\n", jugador.nombre );
            printf( "\nJason: Y que importa si es lo correcto? Tu no te tienes que preocupar por nada. Ahora vives como quieres." );
            printf( "\nJason: Fuera de un asqueroso internado. Disfruta de tu libertad, a pesar de que tu familia no la respete\n" );
            printf( "\n  %s: Gracias, Jason...\n", jugador.nombre );
        }
        else{
            // Se imprimen los diálogos
            printf( "\nJason: Hmm... Asi que esta es la tipica historia del pueblerino en busca de aventuras\n" );
            printf( "\n  %s: Eso supongo...\n", jugador.nombre );
            printf( "\nJason: Bueno. Solo trata de evitar problemas como el de ayer mientras sigas viviendo con nosotros\n" );
            printf( "\n  %s: Lo hare\n", jugador.nombre );
        }
    }
    else{ 
        // Se imprimen los diálogos 
        printf("\n%s: Hola, Brian. Perdoname por hablarte ayer de esa manera\n", jugador.nombre);
        printf("\n  Brian: De que manera? No pasa nada. Estas pasando por una vida totalmente diferente, y eso es dificil\n");
        printf("\n%s: Gracias por entenderlo, tienes un corazon muy puro. Me gustaria saber como creciste para ser asi\n", jugador.nombre);
        printf("\n  Brian: Me sonrojas, pero no. No se debe a ninguna crianza. Vivo en la calle desde muy joven, me crie solo");
        printf("\n  Brian: Pero si algo aprendi en la calle es que debo de ser agradecido con lo que tengo, y entender que...");
        printf("\n  Brian: Hay gente que lo pasa peor que yo, por dentro. Gente con preocupaciones de verdad. Yo no tengo preocupaciones\n");
        printf("\n%s: Es una manera muy original de verlo\n", jugador.nombre);
        printf("\n  Brian: Puede ser. Ahora tu: De donde vienes?\n");

        // Se le pide al jugador que tome una decisión
        printf("\nPRESIONA 1 PARA DECIRLE LA VERDAD A BRIAN / CUALQUIER OTRA TECLA PARA INVENTARTE ALGO\n");
        scanf( "%c%*c", &decision );         // Se lee la decisión tomada

        system( "cls" );        // Se limpia la pantalla de la terminal

        // Se evalúa la decisión recién tomada
        if( decision == '1' ){
            // Se imprimen los diálogos
            printf("\nNo te mentire, vengo de una familia con mucho dinero. Tambien tenia una vida de ensue%co", 164);
            printf("\nMi infancia no tiene nada de interesante, simplemente tenia amigos, estudiaba en un buen colegio y tenia lo que pedia");
            printf("\nHace unos dos a%cos empece a ir mucho a fiestas, y ya sabes, ser joven y estar en espacios como esos...", 164);
            printf("\nEso trae muchos problemas. Empece a juntarme con malas amistades y a hacer cosas que no debia");
            printf("\nMi familia se dio cuenta en un punto, estaba muy mal fisicamente: era muy notorio. Me pillaron y me internaron");
            printf("\nMe escape del internado, no soporto estar alli. Seguramente han de estar buscandome y dandome por muerto. " );
            printf( "Es mejor para todos");
            printf("\nPor eso fumo tanto, quiero liberarme de esa carga, ademas tengo sindrome de abstinencia\n"); 
            
            // Se informa al jugador las consecuencias de su decisión
            printf("\nBRIAN NOTA QUE LE ESTAS SIENDO SINCERO\n");
            jugador.afecto += 5;        // Se suma 5 a la variable afecto, como consecuencia de la decisión tomada
            
            // Se muestra al jugador los valores actuales de su personaje jugable
            printf( "\nTU ESTADO ACTUAL ES:\n" );
            printf( "SALUD: %d | DINERO: %d | AFECTO: %d!!\n", *salud, *dinero, *afecto );
        }
        else{
            // Se imprimen los diálogos
            printf("\nPues mira, soy de pueblo. Pero mi familia es peque%ca", 164);
            printf("\nMis padres siempre discutian mucho, y mi hermano mayor siempre me desprecio");
            printf("\nPeleabamos mucho y me canse de vivir con ellos, me fui de casa e incluso del estado en el que vivia");
            printf("\nSeguramente no saben nada de mi, pero a ninguno de ellos le ha de importar");
            printf("\nMe acogio a muy temprana edad una familia muy humilde, no estaban mucho tiempo en casa, casi nunca, de hecho.");
            printf("\nPor eso, yo salia mucho de fiestas, y me adentre muy pronto al mundo de las drogas");
            printf("\nPasaron a%cos. Pero cuando se enteraron, me echaron de casa, y aqui estoy.\n", 164);

            // Se informa al jugador las consecuencias de su decisión
            printf("\nBRIAN NOTA ALGO RARO EN TU HISTORIA\n");
            jugador.afecto -= 10;       // Se resta 10 a la variable afecto, como consecuencia de la decisión tomada
            
            // Se muestra al jugador los valores actuales de su personaje jugable
            printf( "\nTU ESTADO ACTUAL ES:\n" );
            printf( "SALUD: %d | DINERO: %d | AFECTO: %d!!\n", *salud, *dinero, *afecto );
        }
        
        system( "pause" );          // Se espera la confirmación del jugador para continuar
        system( "cls" );            // Se limpia la pantalla de la terminal
        
        // Se valúa la decisión tomada antes (si contarle o no la verdad a Brian)
        if( decision == '1' ){
            // Se imprimen los diálogos
            printf("\nBrian: Yo crei que tendrias una familia mala, menos mal que no. Por que no tratas de volver y pedirles ayuda?\n");
            printf("\n  %s: No quiero que me vean asi, pensarian mal de mi\n", jugador.nombre );
        }
        else{
            // Se imprimen los diálogos
            printf("\nBrian: Pues si que pareces de pueblo, intuia que tenias algo con tu familia\n");
            printf("\n  %s: Seeeh, pero que se le puede hacer\n", jugador.nombre );
        }
    }
    
    system( "pause" );          // Se espera la confirmación del usuario
    system( "cls" );            // Se limpia la pantalla de la terminal

    //Se imprimen los dialogos y continúa la historia
    printf( "\nLUEGO, EN LA MADRUGADA...\n" );
    printf( "\nKevin: Despierten! Estan tocando la puerta freneticamente! (gritando en susurros)\n" );
    printf( "\n  Brian: Que hacemos ahora?\n" );

    // Se pide al jugador que tome una decisión
    printf( "\nPRESIONA 1 PARA MIRAR POR LA VENTANA / CUALQUIER OTRA TECLA PARA PROPONER QUE VAYA OTRO\n" );
    scanf( "%c%*c", &decision );       // Se lee la decisión tomada
    
    // Se evalúa la decisión
    if( decision == '1' )
    {
        //Se imprimen los dialogos y continúa la historia
        printf("\nTE ASOMAS CON CUIDADO A VER POR LA VENTANA Y TE DESCUBREN\n");
        printf("\n%s: Corran, muchachos! Son los polochos!\n", jugador.nombre );
    }
    else{
        //Se imprimen los dialogos y continúa la historia
        printf( "\n%s: Alguno quiere ir a ver por la ventana?\n", jugador.nombre );
        printf( "\nJASON SE LEVANTA Y SE ASOMA POR LA VENTANA\n" );
        printf( "\n  Jason: Corran, muchachos! Son los polochos!\n" );       
    }
    
    // Continúa la historia
    printf("\nLA POLICIA TIRA LA PUERTA\n");

    // Se evalúa la decisión tomada antes (si se miró por la ventana o si se hizo que otro mirara)
    if( decision == '1' ){
        // Continúa la historia
        printf( "\nLA POLICIA TRATA DE AGARRARTE\n");
    }
    else{
        // Continúa la historia
        printf( "\nLA POLICIA TRATA DE AGARRAR A JASON\n");
    }
    
    // Se pide al jugador que tome una decisión
    printf( "\nPRESIONA 1 PARA CORRER / CUALQUIER OTRA TECLA PARA QUEDARTE A PELEAR\n" );
    scanf( "%c%*c", &decision );

    // Se evalua la decision tomada antes (si se corrió o se quedó a defender a su amigo)
    if( decision == '1' ){
        // Continúa la historia
        printf("\nCORRISTE Y DEJASTE ATRAS A TUS AMIGOS, TE SIENTES CULPABLE");

        jugador.afecto-= 10;       // Se resta 10 a la variable afecto, como consecuencia de la decisión tomada

        // Se muestra al jugador los valores actuales de su personaje jugable
        printf( "\nTU ESTADO ACTUAL ES:\n" );
        printf( "SALUD: %d | DINERO: %d | AFECTO: %d!!\n", *salud, *dinero, *afecto );
    }
    else{
        // Continúa la historia
        printf( "\nTRATASTE DE PELEAR, PERO LA POLICIA TE GOLPEO. AUN ASI ALCANZASTE A ESCAPAR\n" );
       
        jugador.salud -= 10;     // Se resta 10 a la variable salud, como consecuencia de la decisión tomada

        // Se muestra al jugador los valores actuales de su personaje jugable
        printf( "\nTU ESTADO ACTUAL ES:\n" );
        printf( "SALUD: %d!! | DINERO: %d | AFECTO: %d\n", *salud, *dinero, *afecto );
    }
    
    system( "pause" );        // Se espera la confirmación del usuario
    system( "cls" );          // Se limpia la pantalla de la terminal

    //Se imprimen los dialogos y continúa la historia
    printf( "CORRES SIN PARAR, NO SABES SI HAS DEJADO A LOS POLICIAS ATRAS O NO\n");
    printf( "PARECE QUE HAS LLEGADO A UN LUGAR SEGURO\n" );
    printf( "SE APAGAN LAS LUCES\n");
    printf( "\nLOS POLICIAS TE ATRAPAN\n" );
    printf( "\n%s: Maldita sea!\n", jugador.nombre );
    printf( "\n%s: Donde estan los otros?!\n", jugador.nombre );
    printf( "\n  Agente de policia: Parece que no eras el mas atletico de la pandilla." );
    printf( "\n  Agente de policia: Aun asi, tus colegas tampoco iran muy lejos. Hoy todos se ganaron una entrada gratis al calabozo\n" );
    printf( "\n%s: Jodete, cerdo!\n", jugador.nombre );
    printf( "\nLOS POLICIAS TE LLEVAN A RASTRAS A LA PATRULLA\n" );
    printf( "\n  Agente de policia: Disfruta el viaje, zorrita\n" );
    printf( "\nLUEGO DE MEDIA HORA, NOTAS QUE LA PATRULLA SE DETIENE\n" );
    printf( "\n  Agente de policia: Bienvenido a casa, cari%co\n", 164 );
    printf( "\nLOS POLICIAS TE INGRESAN A LA CARCEL\n");
    printf( "\n%s: (Dios mio, pero que es esto)", jugador.nombre);
    printf( "\n%s: (Tengo que salir de aqui rapido, sea como sea)\n");
    
    system( "pause" );      // Se espera la confirmación del usuario
    system( "cls" );        // Se limpia la pantalla de la terminal

    // Continúa la historia
    printf( "\nHA PASADO UN MES DESDE QUE TE ENCARCELARON\n" );
    printf( "\nTU SALUD EN LA CARCEL SE HA REDUCIDO MUCHO. TU SINDROME DE ABSTINENCIA NO AYUDA, Y CADA DIA TE SIENTES PEOR\n" );
    
    jugador.salud -= 10;     // Se resta 10 a la variable salud, como consecuencia de la decisión tomada

    // Se muestra al jugador los valores actuales de su personaje jugable
    printf( "\nTU ESTADO ACTUAL ES:\n" );
    printf( "SALUD: %d!! | DINERO: %d | AFECTO: %d\n", *salud, *dinero, *afecto );

    system( "pause" );     // Se espera la confirmación del usuario

    //Se imprimen los dialogos y continúa la historia
    printf( "\nGuardia: Hey! Hay una llamada para %s!\n", jugador.nombre );  
    printf( "\n  %s: Quien debe de estar llamandome?\n", jugador.nombre );
    printf( "\nVAS HACIA EL GUARDIA Y CONTESTAS EL TELEFONO\n");
    printf( "\nGuardia: Tienes 5 minutos\n");
    printf( "\n???: Que pasa contigo, cabron? Estuvimos buscandote todo este tiempo\n");
    printf( "\n  %s: (Como supo David que yo estaba aqui? Por que me estara buscando?)", jugador.nombre);
    printf( "\n  %s: Como supiste de mi?\n", jugador.nombre);
    printf( "\nDavid: Eres tonto? No escuchaste que te llevamos buscando todos estos dos años?\n");
    printf( "\n  %s: Nunca les pedi que lo hicieran, no quiero que me vean\n", jugador.nombre);
    printf( "\nDavid: No me interesa, todos hemos sufrido mas de lo que tu orgullo deberia permitir\n");
    printf( "\n  %s: Te he dicho que no quiero que me vean, dejame en paz\n", jugador.nombre );
    printf( "\nDavid: De todas formas ya no depende de mi, tu madre y el resto de tu familia saben que estas aqui");
    printf( "\nDavid: Es mas, estan justo aqui. Te pasare a tu madre a la llamada\n");

    // Se pide al jugador que tome una decisión
    printf( "\nPRESIONA 1 PARA SEGUIR EN LA LLAMADA / CUALQUIER OTRA TECLA PARA COLGAR\n");
    scanf("%c%*c", &decision);

    // Se evalua la decision tomada antes (si se sigue en la llamada o se decide colgar)
    if( decision == '1' ){
        //Se imprimen los dialogos y continúa la historia
        printf("\nMadre: Como estas hijo? No sabes cuanto me alegra saber que estas vivo!\n");
        printf("\nTRATAS DE CONTENER LAS LAGRIMAS\n");
        printf("\nMadre: Hijo? Sigues ahi?\n");
        printf("\n  %s: Perdoname, madre. No quiero hacerte daño (sollozando)\n");
        printf("\nMadre: No me digas eso, hijo. Pagare la fianza y pronto podremos volver a vernos\n");
        printf("\n  %s: No debes de hacer eso, madre. Por favor, no quiero\n");
        printf("\nHermana: Mejor callate, imbecil\n");
        printf("\nGuardia: Se acabaron tus 5 minutos, capullo\n");
        printf("\nMadre: Hijo, te...\n");
        printf("\nSE HA CORTADO LA LLAMADA\n");
    }
    else{
        //Se imprimen los dialogos y continúa la historia
        printf("\n  %s: Jodanse, no quiero volver a saber nada de ustedes!\n", jugador.nombre );
        printf("\nHAS COLGADO LA LLAMADA\n");
    }
    
    system( "pause" );    // Se espera la confirmación del usuario
    system( "cls" );      // Se limpia la pantalla de la terminal
    
    // Continúa la historia
    printf( "\nLUEGO DE UNAS HORAS, ES TIEMPO DEL DESCANSO. TODOS LOS PRESOS PUEDEN SALIR DE SUS CELDAS" );
    printf( "\nMIENTRAS ESTAS EN EL PATIO, OTRO PRISIONERO LLEGA A QUITARTE DE TU LUGAR\n" );

    // Se pide al jugador que tome una decisión
    printf( "\nPRESIONA 1 PARA ENFRENTARTE A EL / CUALQUIER OTRA TECLA PARA IGNORARLO\n" );
    scanf( "%c%*c", &decision );

    // Se evalua la decision tomada antes (si se enfrenta o no al bravucón)
    if ( decision == '1' ){

        // Continúa la historia
        printf( "\nHAS INTENTADO PELEAR A PESAR DE TU ESTADO CRITICO DE SALUD" );
        printf( "\nNO PUDISTE MANTENERTE DE PIE NI 10 SEGUNDOS\n" );

        jugador.salud -= 10;  // Se resta 10 a la variable salud, como consecuencia de la decisión tomada
        
        if ( jugador.salud < 0 ) //Se evalua si la salud es menor a 0
        {
            jugador.salud = 0;   //Si la salud es menor a 0, se iguala la salud a 0
        }
        
        // Se muestran al jugador los valores actuales de su personaje jugable
        printf( "\nTU ESTADO ACTUAL ES:\n" );
        printf( "SALUD: %d!! | DINERO: %d | AFECTO: %d\n", *salud, *dinero, *afecto );
        
        evaluarPerdio( jugador );  //Se llama al procedimiento que evalua si el jugador perdio, para que en ese caso termine el juego
    }
    else{
        // Continúa la historia
        printf( "\nA PESAR DE QUE LO IGNORAS, EL ACOSADOR NO TE DEJA EN PAZ\n" );

        // Se pide al jugador que tome una decisión
        printf( "\nPRESIONA 1 PARA ENFRENTARTE A EL / CUALQUIER OTRA TECLA PARA CEDERLE TU LUGAR\n" );
        scanf( "%c%*c", &decision );
        
        // Se evalua la decision tomada antes (si se enfrenta o no al bravucón (de nuevo))
        if ( decision == '1' )
        {
            // Continúa la historia
            printf( "\nHAS INTENTADO PELEAR A PESAR DE TU ESTADO CRITICO DE SALUD\n" );
            printf( "\nNO PUDISTE MANTENERTE EN PIE NI 10 SEGUNDOS\n" );

            jugador.salud -= 10;  // Se resta 10 a la variable salud, como consecuencia de la decisión tomada
            
            if ( jugador.salud < 0 )  //Se evalua si la salud es menor a 0
            {
                jugador.salud = 0;    //Si la salud es menor a 0, se iguala la salud a 0
            }
            
            // Se muestra al jugador los valores actuales de su personaje jugable
            printf( "\nTU ESTADO ACTUAL ES:\n" );
            printf( "SALUD: %d!! | DINERO: %d | AFECTO: %d\n", *salud, *dinero, *afecto );
            
            evaluarPerdio( jugador ); //Se llama al procedimiento que evalua si el jugador perdio, para que en ese caso termine el juego
        }
        else{
            // Continúa la historia
            printf( "\nTE HAS IDO DEL LUGAR Y QUEDASTE COMO UN COBARDE. TE SIENTES MAL CONTIGO MISMO\n" );
            
            jugador.afecto -= 10;  // Se resta 10 a la variable afecto, como consecuencia de la decisión tomada
            
            // Se muestra al jugador los valores actuales de su personaje jugable
            printf( "\nTU ESTADO ACTUAL ES:\n" );
            printf( "SALUD: %d | DINERO: %d | AFECTO: %d!!\n", *salud, *dinero, *afecto );
        }
    }
    
    system( "pause" );   // Se espera la confirmación del usuario
    system( "cls" );     // Se limpia la pantalla de la terminal
    
    // Se imprimen los diálogos y continúa la historia
    printf( "LUEGO, EN LA MA%cANA...\n", 165 );
    printf("\nNO HAS PODIDO DORMIR POR LA LLAMADA\n");
    printf("\nGuardia: Levantense, florecitas. Son las 5:00 ya");
    printf("\nVAS AL PATIO DE LA PRISION\n");
    printf("\nSE TE ACERCAN 6 PERSONAS AGRESIVAMENTE\n");
    printf("\nPrisionero: Ahora seras mi perrita, entiendes?\n");
    printf("\nNO SABES QUE DECIR, TRATAS DE EVADIR AL PRISIONERO\n");
    printf("\nPrisionero: Me escuhas?!\n");
    printf("\nEL GUARDIA TE APUNTA CON EL DEDO\n");
    printf("\nGuardia: Tu, como te llames, ven\n");
    printf("\nGuardia: Han pagado tu fianza, largo de aqui\n");
    printf("\n  %s: (Por que han pagado mi fianza?)\n", jugador.nombre);
    printf("\nSALES DE LA CARCEL POR LA PUERTA PRINCIPAL\n");
    printf("\nVES A TODA TU FAMILIA JUSTO EN LA ENTRADA ESPERANDOTE\n");
    printf("\nROMPES EN LLANTO\n");

    system( "pause" );    // Se espera la confirmación del usuario
    system( "cls" );      // Se limpia la pantalla de la terminal

    jugador.dinero += 80;  // Se suma 80 a la variable dinero, como consecuencia del hilo de la historia
            
    // Se muestra al jugador los valores actuales de su personaje jugable
    printf( "HAS VUELTO CON TU FAMILIA, TIENES BUEN APOYO ECONOMICO\n");
    printf( "\nTU ESTADO ACTUAL ES:\n" );
    printf( "SALUD: %d | DINERO: %d!! | AFECTO: %d\n", *salud, *dinero, *afecto );

    // Se imprimen los diálogos y continúa la historia
    printf("\nMadre: Hijo, estas hecho un desastre (en llantos). Te llevaremos a un hospital inmediatamente\n");
    printf("\n  %s: Pero, madre. Hay cosas mas importantes por hacer, esto no es nada\n", jugador.nombre);
    printf("\nMadre: Que cosas mas importantes hay para hacer que tu salud? Dejate de cosas\n");
    printf("\nACEPTAS IR AL MEDICO SIN RENEGAR\n");

    system( "pause" );    // Se espera la confirmación del usuario
    system( "cls" );      // Se limpia la pantalla de la terminal

    // Se imprimen los diálogos y continúa la historia
    printf("\nHAS LLEGADO AL HOSPITAL");
    printf("\nMedico: Quedate ahi, te haremos un examen general muy completo\n");
    printf("\n  %s: Bueno, yo espero aqui\n", jugador.nombre);
    printf("\nENTRE PROCEDIMIENTOS Y PROCEDIMIENTOS MEDICOS, HA PASADO 1 HORA\n");
    printf("\nMedico: Tienes un pasado fuerte con las drogas, no?\n");
    printf("\n  %s: Por que lo preguntas?\n", jugador.nombre);
    printf("\nMedico: Hay algo que seguramente no sabes, y es grave\n");
    printf("\n  %s: Por que tanto misterio? Que es lo que pasa?\n", jugador.nombre);
    printf("\nMedico: Tienes un tumor muy avanzado en el pulmon, pero es tratable\n");
    printf("\n  %s: Como que cancer? Pero por que?\n", jugador.nombre);
    printf("\nMedico: No te vayas a mover de aqui\n");
    printf("\nTU MEDICO HABLA CON SU ASISTENTE EN SUSURROS, SU ASISTENTE SALE DE LA HABITACION\n");
    printf("\nTU FAMILIA ENTRA AL CUARTO\n");
    printf("\nPadre: Hijo, ya lo sabemos. Haremos todo lo posible para que estes bien, por dinero no hay que preocuparse\n");
    printf("\n  Medico: Bien, entonces no hay problema. Tenemos que empezar a analizar si se trata de cancer o no\n");
    printf("\n  Medico: Pero de momento, tenemos que tratarte, estas muy mal fisicamente\n");

    system( "pause" );    // Se espera la confirmación del usuario
    system( "cls" );      // Se limpia la pantalla de la terminal

    jugador.salud += 10;  // Se suma 10 a la variable salud, como consecuencia del hilo de la historia
            
    // Se muestra al jugador los valores actuales de su personaje jugable
    printf( "\nTU ESTADO ACTUAL ES:\n" );
    printf( "SALUD: %d!! | DINERO: %d | AFECTO: %d\n", *salud, *dinero, *afecto );

    // Se imprimen los diálogos y continúa la historia
    printf("UNA SEMANA DESPUES\n");
    printf( "\nMedico: Han llegado ya las pruebas de los analisis\n");
    printf( "\n  Madre: Que dicen los analisis?\n");
    printf( "\nMedico: Se lo tienen que tomar con calma. Pero, %s tiene cancer de pulmon\n", jugador.nombre);
    printf( "\n  Madre: Entonces que hay que hacer?\n");
    printf( "\nMedico: Les recomendare a buenos oncologos que pueden tratar a %s\n", jugador.nombre );
    printf( "\nTUS PADRES HABLAN MUCHO TIEMPO ENTRE ELLOS Y SE PASAN TODA LA TARDE HACIENDO LLAMADAS");
    printf( "\nTUS PADRES FINALMENTE ENCUENTRAN A UN BUEN ONCOLOGO\n");
    printf( "\nPadre: Hijo, encontramos a un buen oncologo y ya hemos acordado todo con el\n");
    printf( "\nMadre: Debes asistir a todos los tratamientos, y a tratar de colaborar con los especialistas\n");
    
    system( "pause" );   // Se espera la confirmación del usuario
    system( "cls" );     // Se limpia la pantalla de la terminal

    // Se imprimen los diálogos y continúa la historia
    printf("HA PASADO UN MES, HAS ESTADO ASISITIENDO AL TRATAMIENTO Y TE LLEVAS BIEN CON TU FAMILIA\n");
    printf("\nOncologo: Bien, tendras que venir cada semana para cada sesion de quimioterapia\n");
    printf("\nOncologo: Las sesiones son cortas, mas o menos dos horas y lo unico que tienes que hacer despues de cada sesion es llevar " );
    printf( " habitos sanos\n");
    printf("\nOncologo: Que son buenos habitos? Comer bien, ser fisicamente activo, entretenerse, alejarse de sustancias toxicas y demas\n");
    printf("\nOncologo: Queda todo claro? Alguna duda?\n");
    printf("\n  %s: No hay dudas. Todo queda claro. Gracias\n", jugador.nombre);
    printf("\nSALES DE LA CLINICA Y RECIBES UNA LLAMADA DE PRONTO\n");
    printf("\n???: Hey, me he enterado que estas de nuevo por la ciudad. Quieres pasar a dar una vuelta?\n");
    printf("\n  %s: Oooh, Alex. Hace cuanto tiempo! Me suena la idea, que piensas hacer?\n", jugador.nombre);
    
    // Se pide al jugador que tome una decisión
    printf("\nPULSA 1 PARA ACEPTAR LA INVITACION / CUALQUIER OTRA TECLA PARA DECLINARLA\n");
    scanf("%c%*c", &decision);

    // Se evalua la decision tomada antes (si se acepta la invitacion o no)
    if(decision == '1'){
        // Se imprimen los diálogos y continúa la historia
        printf("\n%s: Dale, Alex. Cuenta conmigo\n", jugador.nombre);
        printf("\nTE REUNES CON ALEX EN EL CENTRO DE LA CIUDAD\n");
        printf("\n  Alex: Estas guapo, corazon. Que ha pasado en todo este tiempo?\n");
        printf("\n%s: Jajajajaja, deja la chuleria. Pero no, no ha pasado mucho en este tiempo", jugador.nombre);
        printf("\n%s: He tenido problemas con drogas que me han dejado secuelas, pero nada mas\n", jugador.nombre);
        printf("\n  Alex: El problema seria que no los tuvieras, jajajajaja. Pero es normal, no pasa nada\n");
        printf("\n%s: Y tu que me cuentas de tu vida? Que ha pasado de nuevo?\n", jugador.nombre);
        printf("\n  Alex: Yo si no mucho. Solamente fiestas y fiestas, yo vivo de esto, aparte de ser lo unico que me mantiene vivo\n");
        printf("\n%s: Definitivamente hay cosas que nunca cambian\n", jugador.nombre);
        printf("\n  Alex: Definitivamente si, que tal si les hablamos a esas mu%cecas?\n", 164);
        printf("\n%s: Vamos, yo no tengo problema\n", jugador.nombre);
        printf("\nHAN PASADO 3 HORAS Y HAS PASADO POR VARIAS FIESTAS\n");
        printf("\n  Alex: Que tal si vamos a otro lugar todavia mas interesante?\n");
        
        // Se pide al jugador que tome una decisión
        printf("\nPRESIONA 1 PARA ACEPTAR LA INVITACION / CUALQUIER OTRA TECLA PARA DECLINAR");
        scanf("%c%*c", &decision);

        system( "pause" );  // Se espera la confirmación del usuario
        system( "cls" );    // Se limpia la pantalla de la terminal
        
        // Se evalua la decision tomada antes (si se acepta la invitacion o no)
        if(decision == '1'){
            // Se imprimen los diálogos y continúa la historia
            printf("ALEX TE LLEVA AL LUGAR DEL QUE TE HABLO\n");
            printf("\nAlex: Que te parece?\n");
            printf("\n  %s: Ver para creer. Todavia no ha empezado la fiesta\n", jugador.nombre);
            printf("\nAlex: Entonces vamos a empezarla\n");
            printf("\nALEX Y TU PASAN UN BUEN RATO Y CONOCEN A DOS CHICAS INTERESANTES\n");
            printf("\nChica: Quieres que te de una prueba de algo que te estallara la cabeza? Es espectacular\n");
            
            // Se pide al jugador que tome una decisión
            printf("\nPRESIONA 1 PARA PROBAR LA DROGA / CUALQUIER OTRA TECLA PARA DECLINAR LA PROPUESTA\n");
            scanf("%c%*c", &decision);

            // Se evalua la decision tomada antes (si se prueba la droga o no)
            if(decision == '1'){
                system( "pause" );   // Se espera la confirmación del usuario
                system( "cls" );     // Se limpia la pantalla de la terminal

                // Se imprimen los diálogos y continúa la historia
                printf("\nPRUEBAS UN POCO DE LA DROGA QUE TE OFRECIO LA CHICA DE LA FIESTA\n");
                printf("\nLA DROGA TE EMPIEZA A CAER MAL, TE SIENTES RARO\n");
                printf("\nTE DESMAYASTE Y DESPIERTAS AMARRADO EN UN LUGAR MUY OSCURO\n");
                printf("\n???: Buenos dias, sabemos quienes eres. Al parecer tu familia tiene mucho dinero\n");
                printf("\n???: Vamos a ver cuanto se disponen a pagar por tu rescate\n");
                printf("\nEL SECUESTRADOR COGE UN CELULAR Y HACE UNA LLAMADA\n");
                printf("\n???: Aqui tenemos a tu hijo, exigimos un rescate o lo matamos ahora mismo\n");
                printf("\nNO SE ALCANZA A DITINGUIR LO QUE SE DICE AL OTRO LADO DE LA LLAMADA\n");
                printf("\n???: Lo pongo en altavoz\n");
                printf("\nMadre: Hijo? Estas ahi? Dime que estas bien\n");
                printf("\n  %s: Madre, estoy bien. No te preocupes\n", jugador.nombre);
                printf("\n???: Exigimos 10 millones de dolares para su rescate. No queremos nada de policias\n");
                printf("\nPadre: Si, no hay problema. Pero por favor no lastimen a mi hijo (entre llantos)\n");
                printf("\n???: Eso dependera de que tan rapido paguen por el rescate\n");
                
                // Se pide al jugador que tome una decisión
                printf("\nPRESIONA 1 PARA DECIRLE A TU FAMILIA QUE NO PAGUE EL RESCATE // CUALQUIER OTRA TECLA PARA DECIRLES QUE LO PAGUEN\n");
                scanf("%c%*c", &decision);

                // Se evalua la decision tomada antes (si se le dice a la familia que pague el rescate o no)
                if(decision == '1'){
                    // Se imprimen los diálogos y continúa la historia
                    printf("\n  %s: No paguen nada de esto! Llamen a la policia!\n", jugador.nombre);
                    printf("\nEL SECUESTRADOR CUELGA LA LLAMADA\n");
                    printf("\n???: Jodete, te has condenado a ti mismo, pedazo de imbecil\n");
                    printf("\nEL SECUESTRADOR TE APUÑALA HASTA MATARTE\n");

                    jugador.salud = 0;    //Se iguala la variable de salud a 0 ya que has muerto
                    evaluarPerdio( jugador ); //Se llama al procedimiento que evalua si el jugador perdio, para que en ese caso termine el juego
                }
                else{
                    // Se imprimen los diálogos y continúa la historia
                    printf("\n  %s: Por favor saquenme de aqui, estoy muy asustado\n", jugador.nombre);
                    printf("\n???: Ya lo escucharon, les doy 12 horas para que consigan el dinero\n");
                    printf("\n???: Si lo pagan no te haremos nada, solo si no se te ocurren estupideces\n");
                    printf("\nPASAN LAS 12 HORAS Y EL SECUESTRADOR SE PONE EN CONTACTO CON TU FAMILIA\n");
                    printf("\n???: Ya tienen el dinero? Vayan a la siguiente direccion\n");
                    printf("\nEL SECUESTRADOR LE DICTA LOS DATOS DE DIRECCION E INSTRUCCIONES A QUIEN PAGARA EL RESCATE\n");
                    printf("\nSE CONCRETA TODO EL PAGO Y TE LIBERAN EN EL DESIERTO. TU FAMILIA LLEGA A RESCATARTE\n");
                    printf("\nHermana: Estas bien? Te hicieron algo? (con agitacion)");
                    printf("\n  %s: Estoy bien, no me hicieron nada por suerte\n", jugador.nombre);
                    
                    system( "pause" ); // Se espera la confirmación del usuario
                    system( "cls" );   // Se limpia la pantalla de la terminal

                    printf("TU FAMILIA HA PERDIDO LA MAYOR PARTE DEL DINERO QUE TENIA POR PAGAR EL RESCATE\n");
                    printf("\nUNA SEMANA DESPUES...\n");
                    printf("\nTE LLEGA UNA LLAMADA DE TU CU%cADO", 165);
                    printf("\nCu%cado: Oye, quieres salir a desestresarnos un poco? Te recojo en el coche\n", 164);
                    printf("\n  %s: Claro, me encantaria\n");
                    printf("\nBien, quedamos a dos cuadras de la clinica\n");
                    printf("\nTE REUNES CON TU CU%cADO\n", 165);
                    printf("\nCu%cado: Hola, %s. Subete", 165, jugador.nombre);
                    printf("\nAPENAS TE SUBES AL AUTO TE AGARRAN A LA FUERZA Y TE ASFIXIAN HASTA PERDER EL CONOCIMIENTO\n");
                    printf("\nPASAN VARIAS HORAS Y ESTAS ALEJADO DE LA CIUDAD\n");
                    printf("\nCu%cado: Eres una basura, la familia ha perdido todo el dinero gracias a ti, solo a tu estupidez" ); 
                    printf("\nNo mereces nada en esta vida\n", 165);
                    printf("\nCu%cado: Ahora ya no tengo nada. Todo lo he perdido. Di tus ultimas palabras, basura\n", 165);
                    printf("\nTU CU%cADO TE AGUJEREA A BALAZOS\n", 165);

                    jugador.salud = 0;  //Se iguala la variable de salud a 0 ya que has muerto
                    evaluarPerdio( jugador ); //Se llama al procedimiento que evalua si el jugador perdio, para que en ese caso termine el juego
                }
            }
            else{
                // Se imprimen los diálogos y continúa la historia
                printf("\n  %s: La verdad, no me interesa mucho\n", jugador.nombre);
                printf("\nChica: No sabes de lo que te pierdes, mu%cecon\n", 164);
            }
        }
        else{
            // Se imprimen los diálogos y continúa la historia
            printf("\n%s: No, gracias. Ya he tenido suficiente por esta noche\n", jugador.nombre);
            printf("\n  Alex: Al parecer ya nos estan cobrando los años\n");
            printf("\n%s: Jajajaja, no creo que sea precisamente eso\n", jugador.nombre);
            printf("\n  Alex: De todas formas no pasa nada. Me gusto que pasaramos de nuevo un rato juntos\n");
            printf("\n%s: A mi tambien, deberiamos repetirlo algun dia\n");
        }
    }
    else{
        // Se imprimen los diálogos y continúa la historia
        printf("\n  %s: No, gracias. Tengo que cuidarme\n", jugador.nombre);
        printf("Alex: No hay problema, tu tranquilo. Cuidate\n");
        printf("\n  %s: Igualmente, Alex\n", jugador.nombre);
    }

    system( "pause" );  // Se espera la confirmación del usuario
    system( "cls" );    // Se limpia la pantalla de la terminal

    // Se imprimen los diálogos y continúa la historia
    printf("LLEGASTE A CASA POR LA NOCHE, HA SIDO UNA JORNADA CANSADA\n");
    printf("\nA LA MA%cANA SIGUIENTE\n", 165);
    printf("\nHermana: Oye, %s. Tenemos que hablar sobre algo\n", jugador.nombre);
    printf("\n  %s: Que es lo que pasa?\n", jugador.nombre);
    printf("\nHermana: Es sobre nuestro padre...\n");
    printf("\n  %s: Yo no veo que tenga nada malo, que esta pasandole?\n", jugador.nombre);
    printf("\nHermana: El ha estado desapareciendose muy a seguido desde que reapareciste\n", jugador.nombre);
    printf("\nHermana: Pense que podrias  ayudarle en algo si algo malo esta pasando\n");
    printf("\n  %s: Tratare de ver que es lo que pasa. Gracias por confiarmelo\n", jugador.nombre);
    printf("\nTE LLEGA UNA LLAMADA DE TU MADRE\n");
    printf("\nMadre: %s, sabes donde esta tu padre? No lo veo desde anoche\n", jugador.nombre);
    printf("\n  %s: Justo eso iba a preguntarte.\n", jugador.nombre);
    printf("\nMadre: Buscalo, por favor. Estoy empezando a preocuparme\n");
    printf("\n  %s: Claro, madre. Lo hare\n", jugador.nombre);

    system( "pause" );  // Se espera la confirmación del usuario
    system( "cls" );    // Se limpia la pantalla de la terminal
    
    // Se imprimen los diálogos y continúa la historia
    printf("TE HAS PASADO TODA LA TARDE Y NOCHE BUSCANDO A TU PADRE, POR FIN LO ENCUENTRAS A ALTAS HORAS DE LA NOCHE\n");
    printf("\n%s: Padre? Que haces aqui?\n", jugador.nombre);
    printf("\n  Padre: Y tu quien eres para decirme a donde ir o a donde no?");
    printf("\nTE EXTRA%cAS DE LA CONTESTACION DE TU PADRE\n", 165);
    printf("\n%s: Mama esta muy preocupada por ti, no has vuelto a casa\n", jugador.nombre);
    printf("\n  Padre: Ni pienso hacerlo, no volvere a casa. No mientras tu estes\n");
    printf("\n  Padre: La verdad yo estaba muy feliz cuando te fuiste de aqui, siempre me has traido problemas\n");
    printf("\n  Padre: Todo lo que he hecho por ti ha sido por tu madre");
    printf("\n  Padre: pero no soporto estar detras suyo porque no sabes como cuidar de ti solo o como hacer las cosas bien\n");
    printf("\n%s: Lo entiendo, mama te esta buscando. La llamare\n");
    printf("\nPerdoname por hacerte sentir mal. No era mi intencion\n");
    printf("\nLLAMAS A TU MADRE  Y LE DICES DONDE ESTA TU PADRE, TE VAS DEL LUGAR\n");
    printf("\nESTAS MUY PENSATIVO POR LO QUE TE HA DICHO TU PADRE, ESTAS DANDOLE VUELTAS A TU SITUACION\n");
    printf("\n%s: (Pero es que no puedo irme, tengo cancer y tengo que asistir a tratamiento, o morire)\n");
    printf("\n%s: (Pero si me voy no tendría dinero, y eventualmente terminaria igual o peor de como estaba antes)\n");

    system( "pause" );  // Se espera la confirmación del usuario
    system( "cls" );    // Se limpia la pantalla de la terminal
    
    jugador.afecto -= 10; // Se resta 10 a la variable afecto, como consecuencia de la decisión tomada
    
    // Se muestra al jugador los valores actuales de su personaje jugable
    printf( "\nTE SIENTES MAL POR EL PROBLEMA QUE LE HAS CAUSADO A TU PADRE\n");
    printf( "\nTU ESTADO ACTUAL ES:\n" );
    printf( "SALUD: %d | DINERO: %d | AFECTO: %d!!\n", *salud, *dinero, *afecto );

    // Se pide al jugador que tome una decisión
    printf("\nPRESIONA 1 PARA IGNORAR LO QUE HA DICHO TU PADRE / CUALQUIER OTRA TECLA PARA EXTRAVIARTE Y ARRIESGARTE\n");
    scanf("%c%*c", &decision);

    // Se evalua la decision tomada antes (dejar de lado o no la conversación con el padre)
    if(decision == '1'){
        // Se imprimen los diálogos y continúa la historia
        printf("\n%s: (Mejor seguire aqui, no seria lo mas sensato irme sin estar recuperado todavia)\n", jugador.nombre);
        printf("\nTU PADRE NUNCA VUELVE A CASA, PERO SIGUE EN CONTACTO CON EL RESTO DE TU FAMILIA\n");
        printf("\nCONVENCIO A TU MADRE DE QUE SIMPLEMENTE QUERIA EMPEZAR UNA NUEVA VIDA\n");
        printf("\nUN MES DESPUES...\n");
        printf("\nSUENA EL TELEFONO, VAS Y LO CONTESTAS\n");
        printf("\n%s: Si? Con quien hablo?\n", jugador.nombre);
        printf("\n  ???: Hablo con algun familiar de (nombra a tu padre)?\n");
        printf("\n%s: Si, con su hijo\n", jugador.nombre);
        printf("\n  ???: Bien, tengo una noticia sobre tu padre: llego muy herido al hospital anoche\n");
        printf("\n  ???: Tratamos de salvarle, pero no pudimos hacer nada. Mis condolencias\n");
        printf("\nEMPIEZAS A LLORAR A CAUDALADAS\n");
        printf("\n  Medica: Se%cor? Necesitamos ponernos en contacto con alguien que se pueda hacer cargo del cuerpo\n", 164);
        printf("\nTRATAS DE PARAR DE LLORAR, AUNQUE TE RESULTA DIFICIL\n");
        printf("\n%s: Te dare los datos de contacto de mi madre, ella se podra hacer cargo (sollozando)\n", jugador.nombre);
        printf("\nLE DAS TODOS LOS DATOS DE CONTACTO Y TRATAS DE SOLUCIONAR TODO\n");
        printf("\nTE SIENTES CULPABLE POR LA MUERTE DE TU PADRE\n");

        jugador.afecto -= 10; // Se resta 10 a la variable afecto, como consecuencia de la decisión tomada
        
        // Se muestra al jugador los valores actuales de su personaje jugable
        printf( "\nTU ESTADO ACTUAL ES:\n" );
        printf( "SALUD: %d | DINERO: %d | AFECTO: %d!!\n", *salud, *dinero, *afecto );
        evaluarPerdio( jugador );
    
        system( "pause" );  // Se espera la confirmación del usuario
        system( "cls" );    // Se limpia la pantalla de la terminal

        // Se imprimen los diálogos y continúa la historia
        printf("HAN PASADO MESES, A DURAS PENAS HAS PODIDO SALIR DE CASA A LOS TRATAMIENTOS DEL CANCER, ESTAS MUY DEBIL\n");
        printf("\nLA ENFERMERA DE TU ESPECIALISTA ES REEMPLAZADA POR OTRA, Y TE INTERESAS EN ELLA DE PRONTO\n");
        printf("\nOncologo: Bien, hemos terminado por hoy, %s", jugador.nombre);
        printf("\n  %s: Bueno, me despido\n", jugador.nombre);
        printf("\nEnfermera: Oye, quisieras salir algun dia?\n");
        printf("\n  %s: Por mi esta bien, si quieres hoy\n", jugador.nombre);
        printf("\nEnfermera: En la noche?\n");
        printf("\n  %s: Si, me suena\n", jugador.nombre);

        system( "pause" );  // Se espera la confirmación del usuario
        system( "cls" );    // Se limpia la pantalla de la terminal

        // Se imprimen los diálogos y continúa la historia
        printf("TE ENCUENTRAS CON LA ENFERMERA EN LA NOCHE\n");
        printf("TODO SALE MUY BIEN EN LA CITA, SIGUEN SALIENDO DURANTE MESES\n");
        printf("TU FAMILIA TE CUENTA LA VERDADERA RAZON POR LA QUE TU PADRE SE ALEJO ANTES DE MORIR:\n");
        printf("TU PADRE TENIA DIABETES YA AVANZADA, E INTUIA QUE MORIRIA PRONTO. NO QUERIA QUE LO VIERAS SUFRIR\n");
        printf("SIGUES YENDO A LAS TERAPIAS PARA EL CANCER Y VAS MEJORANDO CADA VEZ MAS\n");
        printf("EMPIEZAS A TENER UNA VIDA MAS EQUILIBRADA Y ALEGRE GRACIAS AL APOYO DE TU PAREJA Y TU FAMILIA\n");
        printf("\nHAS GANADO EL JUEGO, ESTAMOS ORGULLOSOS DE TI ;)))\n");
    }
    else{
        // Se imprimen los diálogos y continúa la historia
        printf("\n%s: Bien, me largo entonces\n", jugador.nombre);
        printf("\nVAS CORRIENDO A CASA A POR DINERO Y A POR TUS COSAS Y TE VAS\n");
        printf("\nLLAMAS A CASA DE KEVIN\n");
        printf("\n???: Hola, con quien hablo?\n");
        printf("\n%s: Con %s, soy amigo de su hijo Kevin. Esta en casa?\n", jugador.nombre, jugador.nombre);
        printf("\n  Madre de Kevin: No, no lo he visto en meses\n");
        printf("\n%s: (Sera que el esta en la carcel y ella no lo sabe?)\n", jugador.nombre);
        printf("\n  Madre de Kevin: Estoy preocupada por el\n");
        printf("\nNO SABES QUE DECIR NI QUE RESPONDER\n");
        printf("\n%s: Si, yo tambien estoy muy preocupado. Estamos en contacto\n", jugador.nombre);
        printf("\nCUELGAS LA LLAMADA\n");
        printf("\nNO TIENES A DONDE NI CON QUIEN IR\n");

        // Se pide al jugador que tome una decisión
        printf("\nPRESIONA 1 PARA BUSCAR UN LUGAR DONDE QUEDARTE / CUALQUIER OTRA TECLA PARA QUEDARTE EN LA CALLE\n");
        scanf("%c%*c", &decision);

        // Se evalua la decision tomada antes (buscar lugar donde hospedarse o no)
        if("decision == '1'"){
            // Se imprimen los diálogos y continúa la historia
            printf("\n%s: Hay hoteles cerca: reservare alguna habitacion\n");
            printf("\nVAS AL HOTEL QUE TIENES MAS CERCA Y RESERVAS UNA HABITACION. TODAVIA ES TEMPRANO EN LA NOCHE\n");
            printf("\n%s: (Todavia es muy temprano, ire a desestresarme un rato)\n", jugador.nombre);
            printf("\nVAS A BUSCAR DROGAS EN LA CIUDAD\n");
            printf("\nENCUENTRAS A ALGUIEN QUE PUEDE QUE VENDA DROGAS\n");
            printf("\n%s: Tienes pasta (heroina)?\n", jugador.nombre);
            printf("\n  Dealer: Cuanta quieres?\n");
            printf("\n%s: Tengo 1000 billetes\n", jugador.nombre);
            printf("\n  Dealer: Ya te traigo lo tuyo\n");
            printf("\nEL DEALER TE ENTREGA LA DROGA\n");
            printf("\nVAS A TU CUARTO DE HOTEL, NO TIENES ANIMOS COMO PARA IR DE FIESTA\n");
            printf("\nTE SIENTES MUY MAL, EMPIEZAS A DROGARTE\n");
            printf("\nPIERDES EL CONTROL Y TERMINAS MURIENDO DE SOBREDOSIS\n");

            jugador.salud= 0;  //Se iguala la variable de salud a 0 ya que has muerto
            
            // Se muestra al jugador los valores actuales de su personaje jugable
            printf( "\nTU ESTADO ACTUAL ES:\n" );
            printf( "SALUD: %d | DINERO: %d | AFECTO: %d!!\n", *salud, *dinero, *afecto );
            evaluarPerdio( jugador );
        }
        else{
            // Se imprimen los diálogos y continúa la historia
            printf("\nNO TIENES ANIMOS COMO PARA BUSCAR UN LUGAR EN EL QUE HOSPEDARTE\n");
            printf("\n%s: (Mejor trato de desestresarme de alguna manera)\n");
            printf("\nVAS A BUSCAR DROGAS EN LA CIUDAD\n");
            printf("\nENCUENTRAS A ALGUIEN QUE PUEDE QUE VENDA DROGAS\n");
            printf("\n%s: Tienes pasta (heroina)?\n", jugador.nombre);
            printf("\n  Dealer: Cuanta quieres?\n");
            printf("\n%s: Tengo 1000 billetes\n", jugador.nombre);
            printf("\n  Dealer: Ya te traigo lo tuyo\n");
            printf("\nEL DEALER TE ENTREGA LA DROGA\n");
            printf("\nCAMINAS VARIAS CUADRAS HASTA ALGUN LUGAR SOLITARIO EN EL QUE QUEDARTE\n");
            printf("\nTE SIENTES MUY MAL, ROMPES EN LLANTO, EMPIEZAS A DROGARTE\n");
            printf("\nPIERDES EL CONTROL Y TERMINAS MURIENDO DE SOBREDOSIS\n");

            jugador.salud= 0;  //Se iguala la variable de salud a 0 ya que has muerto
            // Se muestra al jugador los valores actuales de su personaje jugable
            printf( "\nTU ESTADO ACTUAL ES:\n" );
            printf( "SALUD: %d | DINERO: %d | AFECTO: %d!!\n", *salud, *dinero, *afecto );
            evaluarPerdio( jugador );
        }
    }

    system( "pause" );  // Se espera la confirmación del usuario
    system( "cls" );    // Se limpia la pantalla de la terminal

    // Se pide al jugador que tome una decisión (para volver al menú o simplemente salirse del juego)
    printf( "\nPresiona 1 para volver al menu / Cualquier otra tecla para salir del juego\n" );
    scanf( "%c%*c", &decision );

    // Se evalua la decision tomada antes (volver al menú o salirse del juego)
    if ( decision == '1' )
    {
        mostrarMenu(); //Se llama al procedimiento que muestra el menú de nuevo al usuario 
    }
    else
    {
        system( "exit" ); //Se llama a la funcion de la libreria stdlib para salir del juego
    }
}

/* 
    Procedimiento para jugar la historia número 2
    param: Estructura inicializada del personaje jugable
*/
void historia2( Personaje jugador )
{ 
    // Declaración de variables locales
    int *salud, *dinero, *afecto;        // Punteros que mostrarán al jugador el estado de sus variables    
    char decision, adelantoTrabajo;      // Variables que amacenarán las decisiones tomadas por el jugador
    
    // Se asignan los punteros a las direcciones en memoria de las variables del personaje jugable
    salud = &jugador.salud;
    dinero = &jugador.dinero;
    afecto = &jugador.afecto;
    
    system( "cls" );        // Se limpia la pantalla de la terminal
    system( "color d" );    // Se cambia el color de las letras de la terminal a púrpura claro
    
    // Inicia la historia
    printf( "Barcelona, 2012\n" );
    
    system( "pause" );          // Se espera la confirmación del jugador para continuar

    // Continua la historia para tomar la primera decisión
    printf( "\nES TEMPRANO EN LA MA%cANA. TE DESPIERTA EL SONIDO DE LA ALARMA\n", 165 );
    printf( "\nPRESIONA 1 PARA LEVANTARTE / CUALQUIER OTRA TECLA PARA APAGAR LA ALARMA Y SEGUIR DURMIENDO\n" );
    scanf( "%c%*c", &decision );        // Se lee la decisión tomada

    // Se evalúa la decisión
    if ( decision == '1' )
    {
        // Continúa la historia según la decisión
        printf( "\nTE LEVANTAS Y VAS POR TU LAPTOP" );
        printf( "\nRECUERDAS QUE TIENES TRABAJO PENDIENTE PARA LA PROXIMA SEMANA\n" );

        // Se le pide al usuario que tome otra decisión
        printf( "\nPRESIONA 1 PARA ADELANTAR EL TRABAJO PENDIENTE / CUALQUIER OTRA TECLA PARA REVISAR TUS REDES SOCIALES\n" );
        scanf( "%c%*c", &decision );        // Se lee la decisión tomada

        // Se evalúa la decisión
        if ( decision == '1' )
        {
            // Continúa la historia
            printf( "\nEMPIEZAS A ADELANTAR TU TRABAJO\n" );        
        }
        else
        {
            // Continúa la historia
            printf( "\nAL REVISAR TUS REDES SOCIALES, VES QUE NO HAS RECIBIDO NINGUN MENSAJE O NOTIFICACION DE TU FAMILIA O AMIGOS" );
            printf( "\nHAS RECORDADO LO SOLA QUE ESTAS, Y TE SIENTES MAL POR ELLO\n" );

            jugador.afecto -= 5;        // Se restan puntos de afecto como consecuencia de la decisión

            // Se muestra al jugador los valores actuales de su personaje jugable
            printf( "\nTU ESTADO ACTUAL ES:\n" );
            printf( "SALUD: %d | DINERO: %d | AFECTO: %d!!\n", *salud, *dinero, *afecto );
        }

        system( "pause" );  // Se espera la confirmación del usuario
        system( "cls" );    // Se limpia la pantalla de la terminal

        // Continúa la historia y se imprimen los diálogos correspondientes
        printf( "\nLUEGO DE TRES HORAS ESCUCHAS TU CELULAR SONANDO Y CONTESTAS LA LLAMADA\n" );
        printf( "\n%s: Hola?\n", jugador.nombre );
        printf( "\n  ???: Buenos dias, se%corita %s. Como has estado?\n", 164, jugador.nombre );
        printf( "\n%s: Buenos dias, se%cora Garcia. Yo he estado bien, como ha estado usted?\n", jugador.nombre, 164 );
        printf( "\n  Sra. Garcia: Bien tambien, se%corita. Te llamo para preguntarte como te va con el proyecto que te encargue\n", 164 );

        // Se evalúa la decisión recién tomada antes (adelantar trabajo o revisar redes sociales)
        if ( decision == '1' )
        {
            // Se imprimen los diálogos correspondientes y continúa la historia
            printf( "\n%s: Muy bien! En este preciso momento lo estoy adelantando\n", jugador.nombre );
            printf( "\n  Sra. Garcia: Que bueno es escuchar eso." );
            printf( "\n  Sra. Garcia: Porque justamente hoy necesito que vengas a la fundacion para ajustar algunas cosas de la pagina\n" );
            printf( "\n%s: No le esta gustando como esta quedando?\n", jugador.nombre );
            printf( "\n  Sra. Garcia: Me gusta mucho, pero vamos a tener que agregarle algunas cosas mas\n" );
            printf( "\n%s: Entiendo\n", jugador.nombre );
            printf( "\n  Sra. Garcia: Podrias pasarte por aqui a las tres de la tarde?\n" );
            printf( "\n%s: Seguro! Alli estare\n", jugador.nombre );
            printf( "\nTE SIENTES BIEN CONTIGO MISMA POR HABER EMPEZADO A ADELANTAR EL PROYECTO A TIEMPO\n" );

            jugador.afecto += 5;        // Se suman puntos de afecto como consecuencia de la decisión

            // Se muestra al jugador los valores actuales de su personaje jugable
            printf( "\nTU ESTADO ACTUAL ES:\n" );
            printf( "SALUD: %d | DINERO: %d | AFECTO: %d!!\n", *salud, *dinero, *afecto );
        }
        else
        {
            // Continúa la historia y se imprimen los diálogos
            printf( "\nCIERRAS LAS REDES SOCIALES Y ABRES RAPIDAMENTE EL ARCHIVO DEL PROYECTO\n" );
            printf( "\n%s: ...Bien. He estado adelantando bastante...\n", jugador.nombre ); 
            printf( "\n  Sra. Garcia: Que bien. Porque hoy necesito que vengas a la fundacion para acordar algunos ajustes a la pagina\n" );
            printf( "\n%s: ...Justo hoy?\n", jugador.nombre );
            printf( "\n  Sra. Garcia: Si, por que? No puedes venir hoy?\n" );
            printf( "\n%s: No, no hay problema. Hoy puedo ir. A que hora?\n", jugador.nombre );
            printf( "\n  Sra. Garcia: A las tres de la tarde estaria bien para ti?\n" );
            printf( "\n%s: Si, a esa hora estare alli\n", jugador.nombre );
            printf( "\nEMPIEZAS A ADELANTAR EL PROYECTO PARA LLEVAR UN BUEN AVANCE EN LA TARDE\n" );
        }

        adelantoTrabajo = '1';        // Como el jugador decidió adelantar su trabajo, se activa (1) la correspondiente variable de control
    }
    else
    {
        // Continúa la historia y se imprimen los diálogos
        printf( "\nSIGUES DURMIENDO HASTA EL MEDIO DIA\n" );
        printf( "\nCUANDO TE DESPIERTAS, VES QUE TIENES UNA LLAMADA PERDIDA EN TU CELULAR" );
        printf( "\nDEVUELVES LA LLAMADA\n" );
        printf( "\n???: Hola?\n" );
        printf( "\n  %s: Hola, se%cora Garcia. Vi una llamada perdida de su numero y...\n", jugador.nombre, 164 );
        printf( "\nSra. Garcia: Ah, se%corita %s, que bueno escuharla.", 164, jugador.nombre );
        printf( "\nSra. Garcia: La habia llamado para preguntar como iba con el proyecto que le encargue\n" );
        printf( "\n  %s: ...\n", jugador.nombre );
        printf( "\nSra. Garcia: Hola? Me escucha?\n" );
        printf( "\n  %s: ...Si se%cora. Claro! El proyecto...", jugador.nombre, 164 );
        printf( "\n  %s: En este preciso momento lo estoy adelantando\n", jugador.nombre );
        printf( "\n  Sra. Garcia: Que bien. Porque hoy necesito que venga a la fundacion para acordar algunos ajustes a la pagina\n" );
        printf( "\n%s: ...Justo hoy?\n", jugador.nombre );
        printf( "\n  Sra. Garcia: Si, por que? No puede venir hoy?\n" );
        printf( "\n%s: No, no hay problema. Hoy puedo ir. A que hora?\n", jugador.nombre );
        printf( "\n  Sra. Garcia: A las tres de la tarde estaria bien?\n" );
        printf( "\n%s: Si, a esa hora estare alli\n", jugador.nombre );
        printf( "\nYA ES MEDIO DIA Y NO HAS ADELANTADO EL PROYECTO. TE SIENTES ESTRESADA PORQUE NO PODRAS MOSTRAR AVANCES\n" );
        
        jugador.salud -= 5;         // Se restan puntos de salud como consecuencia de la decisión
        jugador.afecto -= 5;        // Se restan puntos de afecto como consecuencia de la decisión

        // Se muestra al jugador los valores actuales de su personaje jugable
        printf( "\nTU ESTADO ACTUAL ES:\n" );
        printf( "SALUD: %d!! | DINERO: %d | AFECTO: %d!!\n", *salud, *dinero, *afecto );
        
        adelantoTrabajo = '0';          // Como el jugador no adelantó su trabajo, se deja desactivada la variable de control
    }
    
    system( "pause" );  // Se espera la confirmación del usuario
    system( "cls" );    // Se limpia la pantalla de la terminal
    
    // Se continúa la historia y se pide al usuario que tome otra decisión
    printf( "SON LAS DOS DE LA TARDE. ESTAS A TIEMPO PARA IR A LA ESTACION DEL METRO Y VIAJAR HASTA LA FUNDACION\n" );
    printf( "\nPRESIONA 1 PARA SALIR YA / CUALQUIER OTRA TECLA PARA SALIR MAS TARDE\n" );
    scanf( "%c%*c", &decision );        // Se lee la decisión tomada

    // Se evalúa la decisión
    if ( decision == '1' )
    {
        // Continúa la historia
        printf( "\nABORDAS UN TAXI HASTA LA ESTACION DE METRO" );
        printf( "\nLLEGASTE A A LA ESTACION CON TIEMPO DE SOBRA. TU METRO AUN NO HA LLEGADO\n" );
        printf( "\nMIENTRAS ESPERAS, UN JOVEN COMO DE TU EDAD SE SIENTA CERCA DE TI" );
        printf( "\nTRATAS DE IGNORARLO, PERO EL SE QUEDA MIRANDOTE. TE SIENTES INCOMODA\n" );
        printf( "\nJoven: Hola!\n" );
        printf( "\nDEBIDO A TU ANSIEDAD SOCIAL, TE PONE MUY NERVIOSA HABLAR CON EXTRA%cOS\n", 165 );

        // Se pide al usuario que tome otra decision
        printf( "\nPRESIONA 1 PARA SALUDARLO / CUALQUIER OTRA TECLA PARA IGNORARLO\n" );
        scanf( "%c%*c", &decision );        // Se lee la decisión tomada

        // Se evalúa la decisión recién tomada
        if ( decision == '1' )
        {
            // Se imprimen los diálogos correspondientes y continúa la historia
            printf( "\n  %s: Hola.\n", jugador.nombre );
            printf( "\nJoven: Como te llamas?\n" );
            printf( "\n  %s: %s.\n", jugador.nombre, jugador.nombre );
            printf( "\nJoven: Que bonito nombre. Yo soy Alejandro, un placer conocerte\n" );
            printf( "\nEL TE EXTIENDE LA MANO, PERO TU TE PONES MUY NERVIOSA\n" );
            printf( "\n  %s: Lo siento...\n", jugador.nombre );
            printf( "\nAlejandro: Hmm... Veo que eres timida" );
            printf( "\nAlejandro: No te preocupes, si no quieres hablar solo dilo\n" );
            printf( "\n  %s: Gracias\n", jugador.nombre );
            printf( "\nALEJANDRO DEJA DE HABLARTE, PERO TE EMPIEZAS A SENTIR MUY INCOMODA ESTANDO CERCA DE EL\n" );
        }
        else
        {
            // Continúa la historia y se imprimen diálogos
            printf( "\nA PESAR DE QUE LO IGNORAS, EL CONTINUA MIRANDOTE Y TE PONES MUY NERVIOSA\n" );
            printf( "\nJoven: Oye! Estas bien? Por que no hablas?\n" );
            printf( "\n  %s: Perdon, no hablo con desconocidos\n", jugador.nombre );
            printf( "\nJoven: Ah, ya veo. Lo siento mucho\n" );
            printf( "\nEL JOVEN DESCONOCIDO DEJA DE HABLARTE, PERO TE EMPIEZAS A SENTIR MUY INCOMODA ESTANDO CERCA DE EL\n" );
        }

        jugador.afecto -= 5;        // Se restan puntos de afecto, como consecuencia de la decisión anterior
        
        // Se muestra al jugador los valores actuales de su personaje jugable
        printf( "\nTU ESTADO ACTUAL ES:\n" );
        printf( "SALUD: %d | DINERO: %d | AFECTO: %d!!\n", *salud, *dinero, *afecto );

        system( "pause" );          // Se espera la confirmación del jugador para continuar

        // Continúa la historia
        printf( "\nLUEGO DE DIEZ LARGOS MINUTOS, FINALMENTE LLEGA TU METRO" );
        printf( "\nTE SUBES A EL Y RAPIDAMENTE LLEGAS A LA FUNDACION\n" );
    }
    else
    {
        // Continúa la historia y se le pide al usuario que tome una decisión
        printf( "\nHAN PASADO QUINCE MINUTOS\n" );
        printf( "\nPRESIONA 1 PARA SALIR YA / CUALQUIER OTRA TECLA PARA SALIR MAS TARDE\n" );
        scanf( "%c%*c", &decision );        // Se lee la decisión tomada

        // Se evalúa la decisión
        if ( decision == '1' )
        {
            // Continúa la historia
            printf( "\nABORDAS UN TAXI HASTA LA ESTACION DE METRO" );
            printf( "\nLLEGASTE A LA ESTACION JUSTO A TIEMPO. TU METRO ESTA A PUNTO DE IRSE" );
            printf( "\nTE SUBES A EL Y RAPIDAMENTE LLEGAS A LA FUNDACION\n" );
        }
        else
        {
            // Continúa la historia
            printf( "\nDESPUES DE MEDIA HORA, POR FIN DECIDES SALIR" );
            printf( "\nABORDAS UN TAXI HASTA LA ESTACION DE METRO" );
            printf( "\nLLEGASTE MUY TARDE. TU METRO SE FUE HACE QUINCE MINUTOS\n" );
            printf( "\nTE ESTRESAS MUCHO PORQUE AHORA VAS A LLEGAR TARDE A LA FUNDACION\n" );

            jugador.afecto -= 5;        // Se resta afecto, como consecuencia de la decisión anterior
            jugador.salud -= 5;         // Se resta salud, como consecuencia de la decisión anterior

            // Se muestra al jugador los valores actuales de su personaje jugable
            printf( "\nTU ESTADO ACTUAL ES:\n" );
            printf( "SALUD: %d!! | DINERO: %d | AFECTO: %d!!\n", *salud, *dinero, *afecto );
            
            system( "pause" );          // Se espera la confirmación del jugador para continuar

            // Continúa la historia y se pide tomar otra decisión
            printf( "\nTU UNICA OPCION PARA NO LLEGAR TAN TARDE SERIA GASTAR MUCHO DINERO EN UN TAXI\n" );
            printf( "\nPRESIONA 1 PARA QUE UN TAXI TE LLEVE HASTA LA FUNDACION / CUALQUIER OTRA TECLA PARA ESPERAR EL SIGUIENTE METRO\n" );
            scanf( "%c%*c", &decision );        // Se lee la decisión tomada

            // Se evalúa la decisión
            if ( decision == '1' )
            {   
                // Continúa la historia
                printf( "\nVIAJASTE HASTA EL OTRO LADO DE LA CIUDAD EN TAXI Y LLEGASTE DIEZ MINUTOS TARDE" );
                printf( "\nPERDISTE DINERO\n" );

                jugador.dinero -= 10;       // Se resta dinero, como consecuencia de la decisión anterior

                // Se muestra al jugador los valores actuales de su personaje jugable
                printf( "\nTU ESTADO ACTUAL ES:\n" );
                printf( "SALUD: %d | DINERO: %d!! | AFECTO: %d\n", *salud, *dinero, *afecto );
            }
            else
            {
                // Continúa la historia
                printf( "\nTUVISTE QUE ESPERAR MEDIA HORA PARA QUE PASARA TU METRO" );
                printf( "\nLLEGASTE MUY TARDE A LA FUNDACION Y AHORA ESTAS MUY ESTRESADA Y AVERGONZADA\n" );

                jugador.afecto -= 5;        // Se resta afecto, como consecuencia de la decisión anterior
                jugador.salud -= 5;         // Se resta salud, como consecuencia de la decisión anterior

                // Se muestra al jugador los valores actuales de su personaje jugable
                printf( "\nTU ESTADO ACTUAL ES:\n" );
                printf( "SALUD: %d!! | DINERO: %d | AFECTO: %d!!\n", *salud, *dinero, *afecto );
            }
        }   
    }
    
    system( "pause" );  // Se espera la confirmación del usuario
    system( "cls" );    // Se limpia la pantalla de la terminal
    
    // Continúa la historia
    printf( "\nEN LA FUNDACION, BUSCAS A LA SE%cORA GARCIA", 165 );
    printf( "\nCUANDO LA ENCUENTRAS, ELLA TE LLEVA A SU OFICINA\n" );

    system( "pause" );          // Se espera la confirmación del usuario para continuar

    // Se imprimen los diálogos
    printf( "\nSra. Garcia: Ponte comoda, %s\n", jugador.nombre );
    printf( "\n  %s: Gracias, se%cora Garcia\n", jugador.nombre, 164 );
    printf( "\nSra. Garcia: Empezamos a trabajar?\n" );
    printf( "\n  %s: Claro\n", jugador.nombre );
    
    // Se evalúa la variable de control inicializada antes
    if ( adelantoTrabajo == '1' )
    {
        // Continúa la historia
        printf( "\nMUESTRAS TUS AVANCES Y LA SE%cORA GARCIA TE FELICITA POR TU BUEN TRABAJO, POR LO CUAL TE SIENTES BIEN\n", 165 );
        
        jugador.afecto += 5;        // Se suma afecto, como consecuencia de la decisión tomada al inicio
        
        // Se muestra al jugador los valores actuales de su personaje jugable
        printf( "\nTU ESTADO ACTUAL ES:\n" );
        printf( "SALUD: %d | DINERO: %d | AFECTO: %d!!\n", *salud, *dinero, *afecto );

        system( "pause" );          // Se espera la confirmación del usuario para continuar
    }
    else
    {
        // Se imprime el diálogo respectivo
        printf( "  %s: (Ojala no me pida mostrarle avances)\n", jugador.nombre );
    }

    // Continúa la historia y se imprimen los diálogos
    printf( "\nSra. Garcia: Estuve pensando, y creo que algo le hace falta a la pagina web...\n" );
    printf( "\n  %s: Que seria?\n", jugador.nombre );
    printf( "\nSra. Garcia: Un video en el inicio!\n" );
    printf( "\n  %s: Un video?\n", jugador.nombre );
    printf( "\nSra. Garcia: Claro! Un video mostrando las mejores obras que ha hecho la fundacion en el mes\n" );
    printf( "\n  %s: Habria que cambiarlo regularmente, no?\n", jugador.nombre );
    printf( "\nSra. Garcia: Si, para que la pagina se vea siempre renovada. Eso les gusta a las personas, demuestra profesionalismo\n" );
    printf( "\n  %s: Me parece bien... Solo que mi trabajo con ustedes termina la proxima semana...\n", jugador.nombre );
    printf( "\nSra. Garcia: Ah, claro. Pero antes de terminar podrias venir y ense%carnos a nosotros cambiar el video, no?\n", 164 );
    printf( "\n  %s: Si, eso si podria hacerlo\n", jugador.nombre ); 
    printf( "\nSra. Garcia: Que bueno. Tambien queria acordar contigo algunos cambios en el dise%co...\n", 164 );
    printf( "\nLA SRA. GARCIA EMPIEZA A PEDIRTE QUE CAMBIES VARIAS PARTES DEL PROYECTO" );
    printf( "\nCUANDO TERMINAN DE ACORDAR CAMBIOS, YA SON LAS 6 DE LA TARDE" );
    printf( "\nSE DESPIDEN Y LUEGO TE DIRIGES A LA ESTACION DE METRO PARA VOLVER A CASA\n" );

    system( "pause" );  // Se espera la confirmación del usuario
    system( "cls" );    // Se limpia la pantalla de la terminal

    // Se imprimen los diálogos y continúa la historia
    printf( "A LA MA%cANA SIGUIENTE...\n", 165 );
    printf( "\nTE LEVANTAS TEMPRANO Y REVISAS TU CELULAR" );
    printf( "\nNOTAS QUE TIENES UN MENSAJE DE VOZ DE TU HERMANASTRA\n" );
    printf( "\n%s: (Que quiere de mi esta desgraciada?)\n", jugador.nombre );
    printf( "\nESCUCHAS EL MENSAJE DE VOZ\n" );
    printf( "\n  Hermanastra: Como va todo, %s? Bueno, creo que luego tendremos tiempo de hablar", jugador.nombre );
    printf( "\n  Hermanastra: Te llamo para contarte que mama sufrio un infarto y tuvimos que traerla corriendo a Emergencias\n" );
    printf( "\nTE QUEDAS EN SHOCK\n" );
    printf( "\n  Hermanastra: Asi que tal vez quieras venir a acompa%carnos. Cuando despierte, se pondra muy feliz de verte\n", 164 );
    printf( "\nLUEGO DE ESCUCHAR EL MENSAJE, SIENTES GANAS DE LLORAR" );
    printf( "\nAHORA NO SABES QUE HACER. QUIERES SABER SI TU MADRASTRA ESTA BIEN, PERO NO QUIERES VOLVER A VER A TU HERMANASTRA\n" );

    // Se le pide al usuario que tome otra decisión
    printf( "\nPRESIONA 1 PARA ARREGLARTE E IR AL HOSPITAL / CUALQUIER OTRA TECLA PARA IGNORAR EL MENSAJE\n" );
    scanf( "%c%*c", &decision );        // Se lee la decisión tomada
    
    // Se evalúa la decisión
    if ( decision == '1' )
    {
        system( "cls" );        // Se limpia la pantalla de la terminal
        
        // COntinúa la historia y se imprimen los diálogos correspondientes
        printf( "\nTOMAS UN BA%cO, TE VISTES Y TE DIRIGES LO MAS RAPIDO POSIBLE AL HOSPITAL", 165 );
        printf( "\nCUANDO LLEGAS A LA SALA DE EMERGENCIAS, VES A TU HERMANASTRA CON SU ESPOSO" );
        printf( "\nTRATAS DE PASAR DESAPERCIBIDA, PERO ELLOS TAMBIEN TE VEN\n" );
        printf( "\nHermanastra: %s! Que bueno que viniste!\n", jugador.nombre );
        printf( "\nTU HERMANASTRA TRATA DE ABRAZARTE\n" );
        printf( "\n  %s: No me toques!\n", jugador.nombre );
        printf( "\nTU HERMANASTRA SE ALEJA AVERGONZADA\n" );
        printf( "\n  %s: Solo estoy aqui por mama", jugador.nombre );
        printf( "\n  %s: No quiero que tu ni tu marido me dirijan la palabra. Entendido?\n", jugador.nombre, 164 );
        
        system( "pause" );  // Se espera la confirmación del usuario
        system( "cls" );    // Se limpia la pantalla de la terminal

        // Continúa la historia
        printf( "LUEGO DE UN PAR DE HORAS, SACAN A TU MADRASTRA DE EMERGENCIAS Y LA LLEVAN A UNA HABITACION\n" );
        printf( "\nMedico: Por ahora su madre se encuentra estable. Veremos como reacciona proximamente" );
        printf( "\nMedico: Si todo va bien, en unos dias podria despertar\n" );
        printf( "\n  Hermanastra: Gracias por todo, doctor\n" );
        printf( "\nMedico: Es con mucho gusto. Por ahora les recomiendo que vuelvan a casa y esperen buenas noticias\n" );
        printf( "\nVUELVES A CASA, PERO NO TE SIENTES CON ANIMO DE HACER NADA" );
        printf( "\nTE SIENTAS EN EL SOFA A VER TELEVISION, PERO LUEGO DE UN RATO TE QUEDAS DORMIDA\n" );

        adelantoTrabajo = '0';          // Ya que no se adelanta trabajo, se deja desactivada esta variable de control
    }
    else
    {
        system( "cls" );        // Se limpia la pantalla de la terminal

        // Se continúa la historia y se pide al jugador que tome una decisión
        printf( "TE QUEDAS EN CASA, PERO NO SABES EN QUE OCUPARTE PARA DESPEJAR TU MENTE\n" );
        printf( "\nPRESIONA 1 PARA CONTINUAR CON EL PROYECTO DE LA PAGINA WEB / CUALQUIER OTRA TECLA PARA JUGAR VIDEOJUEGOS\n" );
        scanf( "%c%*c", &decision );        // Se lee la decisión tomada
        
        // Se evalúa la decisión
        if ( decision == '1' )
        {
            // Continúa la historia
            printf( "\nESTUVISTE TODO EL DIA AVANZANDO CON LA PAGINA WEB" );
            printf( "\nTODO PARECE INDICAR QUE TERMINARAS EL PROYECTO ANTES DE LA FECHA ACORDADA" );
            printf( "\nTE VAS A DORMIR LUEGO DE TODO UN DIA DE TRABAJO\n" );

            adelantoTrabajo = '1';          // Como se adelanta trabajo, se activa la variable de control
        }
        else
        {
            // Continúa la historia
            printf( "\nTE PASASTE TODO EL DIA JUGANDO" );
            printf( "\nAHORA TE VAS A DORMIR\n" );
            
            adelantoTrabajo = '0';          // Ya que no se adelanta trabajo, se deja desactivada esta variable de control
        }
    }
    
    system( "pause" );  // Se espera la confirmación del usuario
    system( "cls" );    // Se limpia la pantalla de la terminal

    // Continúa la historia y se pide al jugador que tome otra decisión
    printf( "LUEGO DE UNOS DIAS, RECIBES UNA LLAMADA DE TU HERMANASTRA\n" );
    printf( "\nPRESIONA 1 PARA CONTESTAR LA LLAMADA / CUALQUIER OTRA TECLA PARA IGNORARLA\n" );
    scanf( "%c%*c", &decision );        // Se lee la decisión tomada

    // Se evalúa la decisión
    if ( decision == '1' )
    {
        // Se imprimen diálogos y continúa la historia
        printf( "\nHermanastra: %s, escuchame, por favor\n", jugador.nombre );
        printf( "\n  %s: Te escucho.\n", jugador.nombre );
        printf( "\nHermanastra: Mama desperto. Quiere verte\n" );
        printf( "\nSE TE LLENAN LOS OJOS DE LAGRIMAS\n" );
        printf( "\nHermanastra: Hola? Sigues ahi?\n" );
        printf( "\n  %s: ...Perdon\n", jugador.nombre );
        printf( "\nHermanastra: Si vendras entonces?\n" );

        // Se le pide al jugador que tome otra decisión
        printf( "\nPRESIONA 1 PARA RESPONDER QUE IRAS / CUALQUIER OTRA TECLA PARA RECHAZARLA\n" );
        scanf( "%c%*c", &decision );        // Se lee la decisión tomada

        // Se evalúa la decisión
        if ( decision == '1' )
        {
            system( "cls" );       // Se limpia la pantalla de la terminal 

            // Continúa la historia y se imprimen diálogos
            printf( "\nVAS AL HOSPITAL A VISITAR A TU MADRASTRA\n" );
            printf( "\nANTES DE QUE ENTRES A LA HABITACION, SALE TU HERMANASTRA\n" );
            printf( "\n  Hermanastra: Mama te esta esperando\n" );
            printf( "\nENTRAS A LA HABITACION Y VES A TU MADRASTRA LUEGO DE DOS A%cOS\n", 165 );
            printf( "\n%s: Mama?\n", jugador.nombre );
            printf( "\n  Madrastra: %s, querida... Pense que no vendrias\n", jugador.nombre );
            printf( "\nEMPIEZAS A LLORAR\n" );
            printf( "\n%s: Perdon por no haber tenido contacto contigo durante estos a%cos", jugador.nombre, 164 );
            printf( "\n  Madrastra: Tranquila. Se que es porque no quieres ver a tu hermana\n" );
            printf( "\n%s: Esa malnacida no es mi hermana\n", jugador.nombre );
            printf( "\n  Madrastra: Sabes que me entristrece profundamente que la trates de esa manera\n" );
            printf( "\n%s: Lo siento, mama, pero unico que puedo sentir hacia ella es odio\n", jugador.nombre );
            printf( "\n  Madrastra: Ojala algun dia puedas sanar la herida tan profunda que hay en tu corazon\n" );
            printf( "\nDESPUES DE HABER HABLADO CON TU MADRASTRA LUEGO DE TANTO TIEMPO, TE SIENTES QUERIDA DE NUEVO\n" );
            
            jugador.afecto += 5;        // Se suman puntos de afecto, como consecuencia de la decisión

            // Se muestra al jugador los valores actuales de su personaje jugable l
            printf( "\nTU ESTADO ACTUAL ES:\n" );
            printf( "SALUD: %d | DINERO: %d | AFECTO: %d!!\n", *salud, *dinero, *afecto );

            system( "pause" );  // Se espera la confirmación del usuario
            system( "cls" );    // Se limpia la pantalla de la terminal

            // Continúa la historia
            printf( "\nVUELVES A CASA, PERO QUEDAS TAN PENSATIVA CON LAS PALABRAS DE TU MADRASTRA QUE NO TIENES GANAS DE HACER NADA\n" );
            printf( "\nTE QUEDAS JUGANDO VIDEOJUEGOS EL RESTO DE DIA\n" );

            adelantoTrabajo = '0';          // Como no se adelantó trabajo, se deja en 0 esta variable de control
        }
        else
        {
            // Se imprimen los diálogos correspondientes y continúa la historia
            printf( "\n  %s: Lo siento, no puedo. Tengo mucho trabajo por hacer\n", jugador.nombre );
            printf( "\nCADA VEZ TE INQUIETA MAS EL ESTADO DE SALUD DE TU MADRASTRA. NO PUEDES DEJAR DE PENSAR EN ELLO" );
            printf( "\nNECESITAS OCUPARTE EN ALGO PARA DESPEJAR TU MENTE\n" );

            // Se pide al usuario que tome otra decisión
            printf( "\nPRESIONA 1 PARA TERMINAR LA PAGINA WEB / CUALQUIER OTRA TECLA PARA JUGAR VIDEOJUEGOS\n" );
            scanf( "%c%*c", &decision );        // Se lee la decisión tomada

            // Se evalúa la decisión
            if ( decision == '1' )
            {
                // Continúa la historia
                printf( "\nTE QUEDAS HASTA LA MADRUGADA TERMINANDO LA PAGINA WEB" );
                printf( "\nLA DEJASTE TAL Y COMO LA PIDIO LA SRA. GARCIA\n" );

                adelantoTrabajo = '1';          // Como  se adelantó trabajo, se deja en '1 esta variable de control
            }
            else
            {
                // Continúa la historia
                printf( "\nTE QUEDAS HASTA LA MADRUGADA JUGANDO VIDEOJUEGOS\n" );

                adelantoTrabajo = '0';          // Como no se adelantó trabajo, se deja en '0' esta variable de control
            }
        }
    }
    else
    {
        // Continúa la historia y se pide al jugador que tome una decisión
        printf( "\nCADA VEZ TE INQUIETA MAS EL ESTADO DE SALUD DE TU MADRASTRA. NO PUEDES DEJAR DE PENSAR EN ELLO" );
        printf( "\nNECESITAS OCUPARTE EN ALGO PARA DESPEJAR TU MENTE\n" );
        printf( "\nPRESIONA 1 PARA TERMINAR LA PAGINA WEB / CUALQUIER OTRA TECLA PARA JUGAR VIDEOJUEGOS\n" );
        scanf( "%c%*c", &decision );        // Se lee la decisión tomada

        // Se evalúa la decisión
        if ( decision == '1' )
        {
            // Continúa la historia
            printf( "\nTE QUEDAS HASTA LA MADRUGADA TERMINANDO LA PAGINA WEB" );
            printf( "\nLA DEJASTE TAL Y COMO LA PIDIO LA SRA. GARCIA\n" );

            adelantoTrabajo = '1';          // Como se adelantó trabajo, se activa (1) esta variable de control
        }
        else
        {
            // Continúa la historia
            printf( "\nTE QUEDAS HASTA LA MADRUGADA JUGANDO VIDEOJUEGOS\n" );

            adelantoTrabajo = '0';          // Como no se adelantó trabajo, se deja en '0' esta variable de control
        }
    }
    
    system( "pause" );  // Se espera la confirmación del usuario
    system( "cls" );    // Se limpia la pantalla de la terminal

    // Continúa la historia
    printf( "HA PASADO UNA SEMANA, Y YA ES EL DIA DE ENTREGAR EL PROYECTO\n" );

    // Se evalúa la variable de control inicializada anteriormente
    if ( adelantoTrabajo == '1' )
    {
        // Continúa la historia y se escriben los diálogos correspondientes
        printf( "\nVAS A LA FUNDACION A PRESENTARLE LA PAGINA WEB A LA SRA. GARCIA" );
        printf( "\nEN EL CAMINO, RECIBES VARIAS LLAMADAS DE TU HERMANASTRA" );
        printf( "\nDECIDES IGNORARLAS. NO QUIERES QUE NADA TE PERTURBE ANTES DE PRESENTAR TU TRABAJO\n" );
        printf( "\nFINALMENTE, LLEGAS A LA FUNDACION Y LE PRESENTAS A LA SRA. GARCIA LA PAGINA WEB CON TODOS LOS CAMBIOS ACORDADOS\n" );
        printf( "\nSra. Garcia: Esta es la mejor pagina web que he visto en mucho tiempo!\n" );
        printf( "\n  %s: Muchas gracias\n", jugador.nombre );
        printf( "\nSra. Garcia: Lo unico que falta es que me ense%ces a cambiar el video del inicio\n", 164 );
        printf( "\n  %s: Claro! No hay ningun problema\n", jugador.nombre );
        printf( "\nLE EXPLICAS A LA SRA. GARCIA COMO CAMBIAR EL VIDEO CADA MES\n" );
        printf( "\nSra. Garcia: No puedo estar mas agradecida contigo, %s!", jugador.nombre );
        printf( "\nSra. Garcia: Tu trabajo es de calidad y brindas un servicio excelente. Mereces mas dinero del que habiamos acordado!\n" );
        printf( "\nLA SRA. GARCIA TE PAGA DE MAS POR TU BUEN TRABAJO\n" );

        jugador.dinero += 15;           // Se suma 15 al dinero, como consecuencia de buenas decisiones

        // Se muestra al jugador los valores actuales de su personaje jugable
        printf( "\nTU ESTADO ACTUAL ES:\n" );
        printf( "SALUD: %d | DINERO: %d!! | AFECTO: %d\n", *salud, *dinero, *afecto );

        printf( "\nSra. Garcia: Me mantendre en contacto contigo para cualquier otro servicio de dise%co!\n", 164 );
    }
    else
    {   
        // Continúa la historia y se imprimen diálogos
        printf( "\nNO HAS PODIDO TERMINAR LA PAGINA WEB" );
        printf( "\nAUN ASI, DECIDES IR DONDE LA SRA. GARCIA PARA ENSE%cARLE A CAMBIAR EL VIDEO QUE NECESITA EN EL INICIO", 165 );
        printf( "\nLLEGAS A LA FUNDACION Y ALLI TE PERCATAS DE QUE OLVIDASTE TRAER TU CELULAR" );
        printf( "\nVAS A LA OFICINA DE LA SRA. GARCIA\n" );
        printf( "\nSra. Garcia: Hola, %s! Que bueno verte", jugador.nombre );
        printf( "\nSra. Garcia: Ya tienes lista la pagina web?\n" );
        printf( "\n  %s: Me temo que aun no...", jugador.nombre );
        printf( "\n  %s: Pero ya puse el video en el inicio de la pagina, asi que puedo ense%carle a cambiarlo\n", jugador.nombre, 164 );
        printf( "\nSra. Garcia: Hmm... Me parece bien. Pero te tardaras mucho en terminarlo todo?\n" );
        printf( "\n  %s: Claro que no. Con una semana mas de trabajo sera suficiente\n", jugador.nombre );
        printf( "\nLE EXPLICAS A LA SRA. GARCIA COMO CAMBIAR EL VIDEO CADA MES\n" );
        printf( "\nSra. Garcia: Muchas gracias, %s\n", jugador.nombre );
        printf( "\n  %s: Con mucho gusto, se%cora Garcia!\n", jugador.nombre, 164 );
        printf( "\nSra. Garcia: Nos vemos la proxima semana\n" );
    }
    
    system( "pause" );  // Se espera la confirmación del usuario
    system( "cls" );    // Se limpia la pantalla de la terminal

    // Continúa la historia y se imprimen diálogos
    printf( "\nTE VAS A CASA Y TE RELAJAS VIENDO UNA PELICULA" );
    printf( "\nMIENTRAS VES, REVISAS TU CELULAR Y ENCUENTRAS TODAS LAS LLAMADAS PERDIDAS DE TU HERMANASTRA, LO CUAL TE CAUSA CURIOSIDAD" );
    printf( "\nLUEGO DE UNOS MINUTOS, TU HERMANASTRA TE VUELVE A LLAMAR" );
    printf( "\nLE CONTESTAS POR CURIOSIDAD\n" );
    printf( "\nHermanastra: Por fin contestas, %s (llorando)\n", jugador.nombre );
    printf( "\n  %s: Que te pasa? Por que lloras?\n", jugador.nombre );
    printf( "\nHermanastra: Mama..." );
    printf( "\nHermanastra: ...Mama murio\n" );
    printf( "\nTU HERMANASTRA ROMPE EN LLANTO\n" );
    printf( "\nQUEDAS PARALIZADA. NO SABES QUE RESPONDER O COMO REACCIONAR\n" );
    printf( "\nHermanastra: Te llamo luego (llorando)\n" ); 
    printf( "\nCONTINUAS PARALIZADA. NUNCA TE HABIAS SENTIDO DE ESTA FORMA. NO SABES QUE HACER\n" );
    printf( "\nLUEGO DE UN RATO REACCIONAS Y EMPIEZAS A LLORAR DESCONSOLADAMENTE" );
    printf( "\nTE SIENTES TERRIBLE POR TODO EL TIEMPO QUE PASASTE SIN VISITARLA NI HABLAR CON ELLA\n" );
    
    jugador.afecto -= 10;       // Se restan puntos de afecto debido a la muerte de tu madrastra

    // Se muestra al jugador los valores actuales de su personaje jugable
    printf( "\nTU ESTADO ACTUAL ES:\n" );
    printf( "SALUD: %d | DINERO: %d | AFECTO: %d!!\n", *salud, *dinero, *afecto );

    // Se invoca al procedimiento que verifica si el jugador ya perdió el juego
    evaluarPerdio( jugador );       

    system( "pause" );  // Se espera la confirmación del usuario
    system( "cls" );    // Se limpia la pantalla de la terminal

    // Continúa la historia
    printf( "HAN PASADO DOS MESES DESDE QUE TU MADRASTRA FALLECIO" );
    printf( "\nTU ESTADO ES DEPLORABLE. TE LA HAS PASADO LOS DIAS LLORANDO Y DURMIENDO" );
    printf( "\nPERDISTE EL CONTACTO CON LA SRA. GARCIA Y CON TUS DEMAS CLIENTES" );
    printf( "\nSOLO COMES DOS VECES AL DIA, Y TODOS LOS DIAS SIENTES QUE ESTAS MAS SOLA QUE NUNCA" );

    // Se alteran los puntos de afecto y salud para que vayan acorde a los sucesos de la historia
    jugador.afecto = 5;
    jugador.salud = 25;

    // Se muestra al jugador los valores actuales de su personaje jugable
    printf( "\nTU ESTADO ACTUAL ES:\n" );
    printf( "SALUD: %d!! | DINERO: %d | AFECTO: %d!!\n", *salud, *dinero, *afecto );

    system( "pause" );  // Se espera la confirmación del usuario
    system( "cls" );    // Se limpia la pantalla de la terminal

    // Continúa la historia y se imprimen diálogos
    printf( "UN DIA CUALQUIERA, OYES QUE TOCAN LA PUERTA DE TU CASA\n" );
    printf( "\nNUNCA HAS RECIBIDO UNA VISITA DE ALGUIEN DESDE QUE VIVES SOLA" );
    printf( "\nEN ESTE MOMENTO NO QUIERES QUE NADIE TE VEA\n" );
    printf( "\n%s: Quien sea que este tocando, largo de aqui!!\n", jugador.nombre );
    printf( "\n  Hermanastra (desde afuera): Gracias a Dios estas viva!\n" );
    printf( "\n%s: Que haces tu aqui? Largate! No quiero saber nada de ti!!\n", jugador.nombre );
    printf( "\n  Hermanastra: Abreme, por favor! Yo solo quiero ayudarte!\n" );
    printf( "\n%s: No! Tu arruinaste mi vida! Te odio!!\n", jugador.nombre );
    printf( "\n  Hermanastra: Por favor, abre la puerta... (llorando)\n" );
    printf( "\n%s: No se como conseguiste mi direccion, pero sera mejor que te olvides de mi", jugador.nombre );
    printf( "\n%s: No vuelvas nunca!\n", jugador.nombre );
    printf( "\nTU HERMANASTRA ESCRIBE UNA NOTA Y TE LA PASA POR DEBAJO DE LA PUERTA" );
    printf( "\nLUEGO SE VA LLORANDO\n" );

    system( "pause" );  // Se espera la confirmación del usuario
    system( "cls" );    // Se limpia la pantalla de la terminal

    // Continúa la historia y se pide al usuario que tome otra decisión
    printf( "LUEGO DE UN RATO, REVISAS LA NOTA QUE DEJO TU HERMANASTRA BAJO LA PUERTA" );
    printf( "\nVES QUE ES EL NOMBRE Y NUMERO DE UNA PSICOLOGA" );
    printf( "\nPRESIONA 1 PARA LLAMAR A LA PSICOLOGA Y PEDIR AYUDA / CUALQUIER OTRA TECLA PARA DESHACERTE DE LA NOTA\n" );
    scanf( "%c%*c", &decision );        // Se lee la decisión tomada

    // Se evalúa la decision
    if ( decision == '1' )
    {
        // La historia continúa y se imprimen los diálogos correspondientes
        printf( "\nLLAMAS A LA PSICOLOGA\n" );
        printf( "\nPsicologa: Hola?\n" );
        printf( "\n  %s: Hablo con Margarita?\n", jugador.nombre );
        printf( "\nPsicologa: Con ella. Quien eres tu?\n" );
        printf( "\n  %s: Necesito ayuda (llorando)\n" );
        printf( "\nPsicologa: ...Como te llamas?\n" );
        printf( "\n  %s: %s\n", jugador.nombre, jugador.nombre );
        printf( "\nPsicologa: %s? Hmm... Creo que he oido hablar de ti", jugador.nombre );
        printf( "\nPsicologa: Te gustaria agendar una cita?\n" );
        printf( "\n  %s: Si\n", jugador.nombre );
        printf( "\nLUEGO DE HABLAR POR UN RATO, LA PSICOLOGA SE COMPROMETE A VISITARTE MA%cANA\n", 165 );
    }
    else
    {
        // Continúa la historia
        printf( "\nRASGAS LA NOTA\n" );

        system( "pause" );  // Se espera la confirmación del usuario
        system( "cls" );    // Se limpia la pantalla de la terminal

        printf( "\nLLEVAS MUCHO TIEMPO SUFRIENDO" );
        printf( "\nTE ARREPIENTES DE NO HABER PASADO MAS TIEMPO CON TU MADRASTRA" );
        printf( "\nTAMBIEN DE HABER RECHAZADO LA AYUDA DE TU HERMANASTRA\n" );
        printf( "\nSUCUMBES ANTE LA TRISTEZA Y DECIDES SUICIDARTE CORTANDOTE LA GARGANTA\n" );

        jugador.salud = 0;          // Se reduce la salud a 0, ya que el personaje se suicida 

        // Se invoca al procedimiento que verifica si el jugador ya perdió el juego
        evaluarPerdio( jugador );
    }
    
    system( "pause" );  // Se espera la confirmación del usuario
    system( "cls" );    // Se limpia la pantalla de la terminal

    // Continúa la historia y se pide al jugador que tome otra decisión
    printf( "\nAL OTRO DIA, LA PSICOLOGA LLEGA A TU CASA\n" );
    printf( "\nPsicologa: Estas lista para comenzar con la terapia?\n" );
    printf( "\n  %s: Eso creo...\n", jugador.nombre );
    printf( "\nPsicologa: Bien, empecemos\n" );
    printf( "\nPRESIONA 1 PARA COOPERAR CON LA TERAPIA / CUALQUIER OTRA TECLA PARA EVITARLA\n" );
    scanf( "%c%*c", &decision );        // Se lee la decisión tomada

    // Se evalúa la decisión
    if ( decision == '1' )
    {
        // Continúa la historia
        printf( "\nDECIDES COOPERAR CON LA TERAPIA Y CADA VEZ TE SIENTES MEJOR\n" );

        system( "pause" );  // Se espera la confirmación del usuario
        system( "cls" );    // Se limpia la pantalla de la terminal

        printf( "LUEGO DE ALGUNOS MESES DE TERAPIA, HAS LOGRADO RECUPERARTE\n" );
        
        // Se modifican los valores del personaje para que vayan acorde a los sucesos de la historia
        jugador.salud = 70;
        jugador.afecto = 20;

        // Se muestra al jugador los valores actuales de su personaje jugable
        printf( "\nTU ESTADO ACTUAL ES:\n" );
        printf( "SALUD: %d!! | DINERO: %d | AFECTO: %d!!\n", *salud, *dinero, *afecto );
    }
    else
    {
        // Continúa la historia
        printf( "\nA PESAR DE QUE TU PSICOLOGA INSISTE, TU NO QUIERES CONTINUAR CON LA TERAPIA" );
        printf( "\nA MEDIDA QUE PASA EL TIEMPO TE SIENTES CADA VEZ PEOR, ESTAS DEJANDO QUE TU TRISTEZA TE CONSUMA" );
        printf( "\nLUEGO DE UN TIEMPO, TOMAS LA DECISION DE SUICIDARTE PARA TERMINAR CON TU SUFRIMIENTO\n" );

        jugador.salud = 0;          // Se reduce la salud a 0, ya que el personaje se suicida

        // Se invoca al procedimiento que verifica si el jugador ya perdió el juego
        evaluarPerdio( jugador );
    }

    system( "pause" );  // Se espera la confirmación del usuario
    system( "cls" );    // Se limpia la pantalla de la terminal

    // La historia continúa y se le pide al usuario que tome la última decisión del juego
    printf( "\nTE SIENTES MUY AGRADECIDA CON LA PSICOLOGA POR HABERTE AYUDADO TANTO" );
    printf( "\nTAMBIEN TE ARREPIENTES DE HABER TRATADO TAN MAL A TU HERMANASTRA DURANTE TANTO TIEMPO\n" );
    printf( "\nPRESIONA 1 PARA IR Y RECONCILIARTE CON TU HERMANASTRA / CUALQUIER OTRA TECLA PARA CONTINUAR EVITANDOLA\n" );
    scanf( "%c%*c", &decision );        // Se lee la decisión tomada

    // Se evalúa la decisión
    if ( decision == '1' )
    {
        // Continúa la historia
        printf( "\nHAS IDO A RECONCILIARTE CON TU HERMANASTRA Y AHORA TIENES A UNA PERSONA EN LA QUE PUEDES CONFIAR" );
        printf( "\nYA NO TE SENTIRAS SOLA\n" );

        jugador.afecto = 60;        // Se aumenta la barra de afecto, para mostrar que se logró el objetivo de la historia

        // Se muestra al jugador los valores actuales de su personaje jugable
        printf( "\nTU ESTADO ACTUAL ES:\n" );
        printf( "SALUD: %d | DINERO: %d | AFECTO: %d!!\n", *salud, *dinero, *afecto );

        // Se muestra el mensaje final del juego
        printf("\nHAS GANADO EL JUEGO, ESTAMOS ORGULLOSOS DE TI ;)))\n");
    }
    else
    {
        // Se termina la historia, pero no de la mejor manera
        printf( "\nCONTINUAS TU VIDA SIN ARREGLAR EL PROBLEMA CON TU HERMANASTRA" );
        printf( "\nA PESAR DE QUE TU VIDA SIGUE NORMALMENTE, TE SIENTES MUY SOLA" );
        printf( "\nEMPIEZAS A CREER QUE TODO LO QUE HAS VIVIDO HA SIDO EN VANO" );
        printf( "\nTUS DIAS SON CADA VEZ MAS TRISTES Y VACIOS\n" );
    }

    // Se pide al jugador que tome una decisión (para volver al menú o simplemente salirse del juego)
    printf( "\nPresiona 1 para volver al menu / Cualquier otra tecla para salir del juego\n" );
    scanf( "%c%*c", &decision );

    // Se evalua la decision tomada antes (volver al menú o salirse del juego)
    if ( decision == '1' )
    {
        mostrarMenu(); //Se llama al procedimiento que muestra el menú de nuevo al usuario 
    }
    else
    {
        system( "exit" ); //Se llama a la funcion de la libreria stdlib para salir del juego
    }
}

/* 
    Procedimiento para determinar si el jugador perdió el juego
    param: Estructura inicializada del personaje jugable
*/
void evaluarPerdio( Personaje jugador )
{
    char jugarOtraVez; 
    
    // Se evalúa si la salud del jugador llegó a 0
    if( jugador.salud == 0 )
    {
        // En tal caso, se informa al jugador que perdió el juego
        printf( "\nTU SALUD HA LLEGADO A 0. HAS MUERTO.\n" ); 

        // Se le pide al jugador que decida si quiere volver al menú principal o salir del juego
        printf( "\nPresiona 1 para volver al menu principal / Cualquier otra tecla para salir del juego\n" );
        scanf( "%c%*c", &jugarOtraVez );        // Se lee la decisión tomada

        // Se evalúa la decisión
        if ( jugarOtraVez == '1' )
        {
            // En caso que que haya ingresado '1', se vuelve a mostrar el menú principal
            mostrarMenu();
        }
        else
        {
            // En caso contrario, se ejecuta la función para terminar el programa
            system( "exit" );
        }
    }
    
    // Se evalúa si el dinero del jugador llegó a 0
    if( jugador.dinero == 0 )
    {
        // En tal caso, se informa al jugador que perdió el juego
        printf( "\nTU DINERO HA LLEGADO A 0. HAS PERDIDO EL JUEGO.\n" );

        // Se le pide al jugador que decida si quiere volver al menú principal o salir del juego
        printf( "\nPresiona 1 para volver al menu principal / Cualquier otra tecla para salir del juego\n" );
        scanf( "%c%*c", &jugarOtraVez );        // Se lee la decisión tomada

        // Se evalúa la decisión
        if ( jugarOtraVez == '1' )
        {
            // En caso que que haya ingresado '1', se vuelve a mostrar el menú principal
            mostrarMenu();
        }
        else
        {
            // En caso contrario, se ejecuta la función para terminar el programa
            system( "exit" );
        }
    }

    // Se evalúa si el afecto del jugador llegó a 0   
    if( jugador.afecto == 0 )
    {
        // En tal caso, se informa al jugador que perdió el juego
        printf("\nTU AFECTO HA LLEGADO A 0. HAS PERDIDO EL JUEGO.\n" );
        
        // Se le pide al jugador que decida si quiere volver al menú principal o salir del juego
        printf( "\nPresiona 1 para volver al menu principal / Cualquier otra tecla para salir del juego\n" );
        scanf( "%c%*c", &jugarOtraVez );        // Se lee la decisión tomada

        // Se evalúa la decisión
        if ( jugarOtraVez == '1' )
        {
            // En caso que que haya ingresado '1', se vuelve a mostrar el menú principal
            mostrarMenu();
        }
        else
        {
            // En caso contrario, se ejecuta la función para terminar el programa
            system( "exit" );
        }
    }
}