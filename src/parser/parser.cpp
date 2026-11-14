#include "ImTag/parser/parser.hpp"
#include "ImTag/lexer/lexer.hpp"
#include "ImTag/tags/specificTags/cpptag.hpp"
#include "ImTag/tags/specificTags/windowtag.hpp"
#include "ImTag/tags/specificTags/buttontag.hpp"
#include "ImTag/tags/specificTags/texttag.hpp"
#include "ImTag/tags/specificTags/separatortag.hpp"
#include "ImTag/tags/specificTags/spacingtag.hpp"
#include "ImTag/tags/specificTags/samelinetag.hpp"
#include "ImTag/tags/specificTags/slidertag.hpp"

#include "ImTag/tags/specificTags/checkboxtag.hpp"
#include "ImTag/tags/specificTags/inputtag.hpp"

#include "ImTag/tags/tag.hpp"
#include <cstddef>

namespace parser {

std::vector<std::shared_ptr<ImTag::Tag>> Parser::parse() {
    cursor = 0;

    while (cursor < tokens.size()) {
        lexer::Token token = tokens[cursor];
        cursor++;

        // Raw C++
        if (token.type == lexer::TokenType::RAW_CPP) {
            auto objetoRawCpp = std::make_shared<ImTag::CppTag>(token.value, token.line);
            verificarPadreEIncluir(objetoRawCpp);
        }

        // Tag Open
        if (token.type == lexer::TokenType::TAG_OPEN) {
            if (token.value == "window") {
                auto attrs = leerAtributos(
                    {"name", "width", "height", "x", "y", "open", "noTitleBar", "noResize", "noMove", "noCollapse", "noScrollbar", "menuBar", "fullscreen"},
                    {"name"}
                );
                esperar(lexer::TokenType::TAG_CLOSE, "Se esperaba '>' para cerrar la etiqueta <window>");

                auto objetoWindowTag = std::make_shared<ImTag::windowTag>(attrs, token.line);
                verificarPadreEIncluir(objetoWindowTag);
                tagsAbiertos.push_back(objetoWindowTag);
            }
            if (token.value == "button") {
                auto attrs = leerAtributos({"name", "onClick"}, {"name"});
                esperar(lexer::TokenType::TAG_SELF_CLOSE, "Se esperaba '/>' para cerrar la etiqueta <button />");

                auto objetoButtonTag = std::make_shared<ImTag::buttonTag>(attrs, token.line);
                verificarPadreEIncluir(objetoButtonTag);
            }
            if (token.value == "text") {
                auto attrs = leerAtributos({"value"}, {"value"});
                esperar(lexer::TokenType::TAG_SELF_CLOSE, "Se esperaba '/>' para cerrar la etiqueta <text />");

                auto objetoTextTag = std::make_shared<ImTag::textTag>(attrs, token.line);
                verificarPadreEIncluir(objetoTextTag);
            }
            if (token.value == "separator") {
                leerAtributos({}, {});
                esperar(lexer::TokenType::TAG_SELF_CLOSE, "Se esperaba '/>' para cerrar la etiqueta <separator />");

                auto objetoSeparatorTag = std::make_shared<ImTag::separatorTag>(token.line);
                verificarPadreEIncluir(objetoSeparatorTag);
            }
            if (token.value == "spacing") {
                leerAtributos({}, {});
                esperar(lexer::TokenType::TAG_SELF_CLOSE, "Se esperaba '/>' para cerrar la etiqueta <spacing />");

                auto objetoSpacingTag = std::make_shared<ImTag::spacingTag>(token.line);
                verificarPadreEIncluir(objetoSpacingTag);
            }
            if (token.value == "sameline") {
                leerAtributos({}, {});
                esperar(lexer::TokenType::TAG_SELF_CLOSE, "Se esperaba '/>' para cerrar la etiqueta <sameline />");

                auto objetoSameLineTag = std::make_shared<ImTag::sameLineTag>(token.line);
                verificarPadreEIncluir(objetoSameLineTag);
            }

            if (token.value == "slider") {
                auto attrs = leerAtributos({"label", "bind", "min", "max", "type"}, {"label", "bind"});
                esperar(lexer::TokenType::TAG_SELF_CLOSE, "Se esperaba '/>' para cerrar la etiqueta <slider />");

                auto objetoSliderTag = std::make_shared<ImTag::sliderTag>(attrs, token.line);
                verificarPadreEIncluir(objetoSliderTag);
            }

            if (token.value == "checkbox"){
                auto attrs = leerAtributos({"name","bind", "onChange"}, {"name", "bind"});
                esperar(lexer::TokenType::TAG_SELF_CLOSE, "Se esperaba '/>' para cerrar la etiqueta <checkbox />");

                auto objetoCheckboxTag = std::make_shared<ImTag::checkboxTag>(attrs, token.line);
                verificarPadreEIncluir(objetoCheckboxTag);
            }

            if (token.value == "input") {
                auto attrs = leerAtributos(
                    {"label", "bind", "type", "size", "password", "readOnly"},
                    {"bind"}
                );
                esperar(lexer::TokenType::TAG_SELF_CLOSE, "Se esperaba '/>' para cerrar la etiqueta <input />");

                auto objetoInputTag = std::make_shared<ImTag::inputTag>(attrs, token.line);
                verificarPadreEIncluir(objetoInputTag);
            }

        }

        // Tag End  
        if (token.type == lexer::TokenType::TAG_END) {
            if (!tagsAbiertos.empty()) {
                tagsAbiertos.pop_back();
            }
        }
    }

    return listaTagsPrincipales;
}

void Parser::verificarPadreEIncluir(std::shared_ptr<ImTag::Tag> objeto) {
    if (!tagsAbiertos.empty()) {
        tagsAbiertos.back()->hijos.push_back(objeto);
    } else {
        listaTagsPrincipales.push_back(objeto);
    }
}

lexer::Token Parser::esperar(lexer::TokenType tipoEsperado, const std::string& mensajeError) {
    if (cursor >= tokens.size() || tokens[cursor].type != tipoEsperado) {
        int numLinea = (cursor < tokens.size()) ? tokens[cursor].line : (!tokens.empty() ? tokens.back().line : 1);
        printf("Error de sintaxis en línea %d: %s\n", numLinea, mensajeError.c_str());
        exit(1); // O lanzar excepción
    }
    return tokens[cursor++]; // Consume el token esperado y avanza al siguiente
}

std::unordered_map<std::string, std::string> Parser::leerAtributos(
    const std::vector<std::string>& permitidos,
    const std::vector<std::string>& obligatorios
) {
    std::unordered_map<std::string, std::string> mapa;

    // Lee todos los atributos mientras vengan identificadores
    while (cursor < tokens.size() && tokens[cursor].type == lexer::TokenType::IDENTIFIER) {
        std::string nombre = tokens[cursor++].value;
        esperar(lexer::TokenType::EQUAL, "Se esperaba '=' después de " + nombre);
        std::string valor = esperar(lexer::TokenType::STRING, "Se esperaba valor entre comillas").value;

        // Comprueba si está en la lista de permitidos
        if (!permitidos.empty()) {
            bool valido = false;
            for (const auto& p : permitidos) {
                if (p == nombre) {
                    valido = true;
                    break;
                }
            }
            if (!valido) {
                printf("Aviso en línea %d: atributo '%s' no es válido para este tag\n", tokens[cursor - 1].line, nombre.c_str());
            }
        }

        mapa[nombre] = valor;
    }

    // Comprueba los atributos obligatorios
    for (const auto& ob : obligatorios) {
        if (mapa.find(ob) == mapa.end()) {
            int numLinea = cursor < tokens.size() ? tokens[cursor].line : -1;
            printf("Error de sintaxis en línea %d: falta el atributo obligatorio '%s'\n", numLinea, ob.c_str());
            exit(1);
        }
    }

    return mapa;
}

} // namespace parser