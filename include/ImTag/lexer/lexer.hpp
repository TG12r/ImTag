#pragma once

#include <string>
#include <vector>

namespace lexer {

    enum class TokenType {
        RAW_CPP,         // Todo el código C++ normal que no se toca
        TAG_OPEN,        // Ej: "<window", "<button", "<menu"
        TAG_CLOSE,       // ">"
        TAG_END,         // Ej: "</window>", "</menu>"
        TAG_SELF_CLOSE,  // "/>"
        IDENTIFIER,      // Nombres de atributos (ej: "name", "width", "label")
        EQUAL,           // "="
        STRING,          // Valores entre comillas (ej: "\"Hola Mundo\"")
        END_OF_FILE      // Fin del archivo
    };

    struct Token {
        TokenType type;
        std::string value; // El texto exacto (ej: "window", "name", o el bloque C++)
        int line;          // Número de línea (clave para dar mensajes de error al usuario)
        int column;        // Columna
    };

    // Declaración de funciones
    std::string encontrarPalabra(const std::string& codigoFuente, size_t inicio);
    std::vector<Token> tokenizer(const std::string& codigoFuente);

}
