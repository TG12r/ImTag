#include "ImTag/lexer/lexer.hpp"
#include <cctype>
#include <cstdio>

namespace lexer {

std::string encontrarPalabra(const std::string &codigoFuente, size_t inicio) {
    std::string palabra;
    size_t total = codigoFuente.length();

    for (size_t i = inicio; i < total; i++) {
        char c = codigoFuente[i];
        // Se detiene al encontrar espacios, símbolos de tag o asignación
        if (std::isspace(static_cast<unsigned char>(c)) || c == '=' || c == '>' || c == '/' || c == '<') {
            break;
        }
        palabra += c;
    }
    return palabra;
}

std::vector<Token> tokenizer(const std::string &codigoFuente) {
    std::vector<Token> vectorReturn;
    size_t total = codigoFuente.length();

    int linea = 1;
    int columna = 1;
    int lineaInicioCpp = 1;
    int columnaInicioCpp = 1;
    bool enTag = false;
    std::string bufferCpp;

    // Función lambda para guardar el bloque de código C++ acumulado
    auto emitirCpp = [&]() {
        if (!bufferCpp.empty()) {
            vectorReturn.push_back(Token{TokenType::RAW_CPP, bufferCpp, lineaInicioCpp, columnaInicioCpp});
            bufferCpp.clear();
        }
    };

    size_t i = 0;
    while (i < total) {
        char c = codigoFuente[i];

        if (c == '\n') {
            linea++;
            columna = 1;
        } else {
            columna++;
        }

        if (!enTag) {
            // MODO C++ NORMAL xd
            // Detecta si es un tag: '<' seguido de una letra o de '/'
            // Ignora si viene de un #include <...> de C++
            bool esInclude = false;
            size_t ultimoNoEspacio = bufferCpp.find_last_not_of(" \t");
            if (ultimoNoEspacio != std::string::npos && ultimoNoEspacio >= 6) {
                if (bufferCpp.substr(ultimoNoEspacio - 6, 7) == "include") {
                    esInclude = true;
                }
            }

            if (!esInclude && c == '<' && i + 1 < total &&
                (std::isalpha(static_cast<unsigned char>(codigoFuente[i + 1])) || codigoFuente[i + 1] == '/')) {
                emitirCpp();

                int lineaTag = linea;
                int columnaTag = columna;

                if (codigoFuente[i + 1] == '/') {
                    // Cierre de tag: </nombreTag>
                    i += 2; // saltar '<' y '/'
                    std::string nombre = encontrarPalabra(codigoFuente, i);
                    i += nombre.length();

                    // Buscar el '>' que cierra </nombreTag>
                    while (i < total && codigoFuente[i] != '>') {
                        if (codigoFuente[i] == '\n') {
                            linea++;
                            columna = 1;
                        } else {
                            columna++;
                        }
                        i++;
                    }
                    if (i < total && codigoFuente[i] == '>') {
                        i++; // saltar '>'
                    }

                    vectorReturn.push_back(Token{TokenType::TAG_END, nombre, lineaTag, columnaTag});
                    continue;
                } else {
                    // Apertura de tag: <nombreTag ...
                    i++; // saltar '<'
                    std::string nombre = encontrarPalabra(codigoFuente, i);
                    i += nombre.length();

                    vectorReturn.push_back(Token{TokenType::TAG_OPEN, nombre, lineaTag, columnaTag});
                    enTag = true;
                    continue;
                }
            } else {
                // Es código C++ normal
                if (bufferCpp.empty()) {
                    lineaInicioCpp = linea;
                    columnaInicioCpp = columna;
                }
                bufferCpp += c;
                i++;
            }
        } else {
            // MODO DENTRO DE TAG (atributos, '=', comillas, '>', '/>')
            if (std::isspace(static_cast<unsigned char>(c))) {
                i++;
                continue;
            }

            // Fin de tag autocerrado: />
            if (c == '/' && i + 1 < total && codigoFuente[i + 1] == '>') {
                vectorReturn.push_back(Token{TokenType::TAG_SELF_CLOSE, "/>", linea, columna});
                enTag = false;
                i += 2;
                continue;
            }

            // Fin de cabecera de tag: >
            if (c == '>') {
                vectorReturn.push_back(Token{TokenType::TAG_CLOSE, ">", linea, columna});
                enTag = false;
                i++;
                continue;
            }

            // Operador de asignación en atributo: =
            if (c == '=') {
                vectorReturn.push_back(Token{TokenType::EQUAL, "=", linea, columna});
                i++;
                continue;
            }

            // Valor en comillas: "..." o '...'
            if (c == '"' || c == '\'') {
                char comilla = c;
                i++; // saltar la primera comilla
                std::string valor;
                while (i < total && codigoFuente[i] != comilla) {
                    if (codigoFuente[i] == '\n')
                        linea++;
                    valor += codigoFuente[i];
                    i++;
                }
                if (i < total && codigoFuente[i] == comilla) {
                    i++; // saltar la comilla de cierre
                }
                vectorReturn.push_back(Token{TokenType::STRING, valor, linea, columna});
                continue;
            }

            // Nombre de atributo (ej: name, width, label)
            if (std::isalpha(static_cast<unsigned char>(c)) || c == '_') {
                std::string atributo = encontrarPalabra(codigoFuente, i);
                i += atributo.length();
                vectorReturn.push_back(Token{TokenType::IDENTIFIER, atributo, linea, columna});
                continue;
            }
            
            // Si aparece '<' dentro de un tag, significa que nunca se cerró con '>' y ya empezó otro tag
            if (c == '<') {
                enTag = false;
                if (c == '\n') linea--; else columna--; // Para no contar doble la columna al re-evaluar 'c'
                continue;
            }


            // Cualquier otro carácter no contemplado dentro del tag
            i++;
        }
    }

    // Si quedó código C++ pendiente al final del archivo, emitirlo
    emitirCpp();

    // Token de fin de archivo
    vectorReturn.push_back(Token{TokenType::END_OF_FILE, "", linea, columna});

    return vectorReturn;
}
} // namespace lexer