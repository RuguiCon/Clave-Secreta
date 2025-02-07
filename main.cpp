// Autor: Rugui
// Fecha de creación: 2025-02-06
// Descripción: Programa para codificar, decodificar y contar letras de un texto usando el sistema "Clave-Secreta".
// Compatibilidad: Compatible con C++11 o superior

// TODO: Agregar un sistema para hacer la operación de escribir la conversión de 'Clave-Secreta' a 'Texto Humano'

// No tengo idea de como hacer documentación, pero más o menos este es el funcionamiento.

#include <iostream>
#include <map>
#include <string>
#include <sstream>
#ifdef _WIN32
    #include <windows.h>
#else
    #include <cstdlib>
#endif
using namespace std;

// Mapa de equivalencias del sistema "Clave-Secreta"
map<char, string> codificacion = {
    {'A', "Abeja"}, {'B', "Burro"}, {'C', "Calamardo"}, {'D', "Don Cangrejo"}, {'E', "Edna"},
    {'F', "Chat"}, {'G', "Cíclope"}, {'H', "Invisible"}, {'I', "Bob"}, {'J', "Caballo"},
    {'K', "Vitamina"}, {'L', "Caballo"}, {'M', "Bovino"}, {'N', "Narnia"}, {'O', "Selector"},
    {'P', "Carro"}, {'Q', "Pregunta"}, {'R', "F5"}, {'S', "Salsa"}, {'T', "Geometría"},
    {'U', "Mantequilla"}, {'V', "Jurásico"}, {'W', "Encontrar"}, {'X', "Música"}, {'Y', "Ash"}, {'Z', "Último"}
};

// Mapa inverso para decodificación
map<string, char> decodificacion;
string textoCodificado;

// Función para inicializar el mapa de decodificación
void inicializarDecodificacion() {
    for (const auto &par : codificacion) {
        decodificacion[par.second] = par.first;
    }
}

// Función para limpiar la pantalla dependiendo del sistema operativo
void limpiarConsola() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Función para contar el número de letras en un texto
int contarLetras(const string &texto) {
    int count = 0;
    for (char c : texto) {
        if (isalpha(c)) count++;
    }
    return count;
}

// Función para convertir el texto ingresado a la codificación de "Clave-Secreta"
string convertirTexto(const string &texto) {
    string resultado;
    for (char c : texto) {
        if (c == '/') {
            resultado += "\n"; // Salto de línea al encontrar '/'
        } else if (c == ' ') {
            resultado += "| "; // Indicador de espacio entre palabras
        } else if (c == '.' || c == ',' || c == ';') {
            resultado += c; // Mantener signos de puntuación
        } else {
            char mayus = toupper(c);
            if (codificacion.count(mayus)) {
                resultado += codificacion[mayus] + " ";
            } else {
                resultado += c; // Mantener caracteres que no son letras
            }
        }
    }
    textoCodificado = resultado; // Guardar la última conversión
    return resultado;
}

// Función para decodificar un texto desde el sistema "Clave-Secreta"
string decodificarTexto() {
    stringstream ss(textoCodificado);
    string palabra, resultado;
    while (ss >> palabra) {
        if (palabra == "|") {
            resultado += " "; // Restaurar espacio entre palabras
        } else if (decodificacion.count(palabra)) {
            resultado += decodificacion[palabra];
        } else {
            resultado += palabra; // Mantener signos de puntuación y caracteres desconocidos
        }
    }
    return resultado;
}

int main() {
    inicializarDecodificacion(); // Inicializar mapa de decodificación
    string texto;
    int opcion;
    
    // Solicitar texto al usuario
    cout << "Ingrese el texto: ";
    getline(cin, texto);
    
    do {
        limpiarConsola(); // Limpiar pantalla antes de mostrar el menú
        // Menú de opciones
        cout << "Menú:\n1. Contar letras en el texto\n2. Convertir texto a sistema codificado\n3. Decodificar texto guardado\n4. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;
        cin.ignore(); // Limpiar buffer
        
        limpiarConsola(); // Limpiar pantalla antes de mostrar resultados
        
        switch (opcion) {
            case 1:
                cout << "Número de letras en el texto: " << contarLetras(texto) << "\n";
                break;
            case 2:
                cout << "Texto convertido: \n" << convertirTexto(texto) << "\n";
                break;
            case 3:
                if (textoCodificado.empty()) {
                    cout << "No hay texto codificado almacenado.\n";
                } else {
                    cout << "Texto decodificado: \n" << decodificarTexto() << "\n";
                }
                break;
            case 4:
                cout << "Saliendo...\n";
                break;
            default:
                cout << "Opción no válida. Intente de nuevo.\n";
        }
    } while (opcion != 4);
    
    return 0;
}

/*
 Para usarlo deberá hacerse de la siguiente manera.
 
 El 'Texto Humano' como lo leeríamos normalmente tiene caracteres especiales y saltos de línea, este programa no los soporta.
 
 Ejemplo de Texto Humano:
 
 Hola
 
 Este solo es un programa para un trabajo escolar
 
Está basado en referencias externas en varias partes de su contenido, aunque la gran mayoría (además de las adaptaciones necesarias realizadas para ajustarlo al objetivo del programa) fue escrito personal
 Ejemplo de Texto Clave-Secreta

  Hola / Este solo es un programa para un trabajo escolar / Está basado en referencias externas en varias partes de su contenido, aunque la gran mayoría (además de las adaptaciones necesarias realizadas para ajustarlo al objetivo del programa) fue escrito personal
 */
