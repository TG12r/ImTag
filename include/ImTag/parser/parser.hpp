#pragma once

#include "ImTag/lexer/lexer.hpp"
#include "ImTag/tags/tag.hpp"
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace parser {

    class Parser {
    private:
        std::vector<lexer::Token> tokens;
        std::vector<std::shared_ptr<ImTag::Tag>> listaTagsPrincipales;
        std::vector<std::shared_ptr<ImTag::Tag>> tagsAbiertos;
        size_t cursor = 0;

        void verificarPadreEIncluir(std::shared_ptr<ImTag::Tag> objeto);
        lexer::Token esperar(lexer::TokenType tipoEsperado, const std::string& mensajeError);
        std::unordered_map<std::string, std::string> leerAtributos(
            const std::vector<std::string>& permitidos = {},
            const std::vector<std::string>& obligatorios = {}
        );
    public:
        Parser(const std::vector<lexer::Token>& tokens) : tokens(tokens) {}

        std::vector<std::shared_ptr<ImTag::Tag>> parse();
    };

} // namespace parser