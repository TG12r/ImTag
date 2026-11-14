#include "ImTag/lexer/lexer.hpp"
#include "ImTag/parser/parser.hpp"
#include "ImTag/tags/specificTags/cpptag.hpp"
#include <cstdio>
#include <fstream>
#include <string>
#include <vector>


const char* tokenTypeToString(lexer::TokenType type) {
  switch (type) {
  case lexer::TokenType::RAW_CPP:
    return "RAW_CPP";
  case lexer::TokenType::TAG_OPEN:
    return "TAG_OPEN";
  case lexer::TokenType::TAG_CLOSE:
    return "TAG_CLOSE";
  case lexer::TokenType::TAG_END:
    return "TAG_END";
  case lexer::TokenType::TAG_SELF_CLOSE:
    return "TAG_SELF_CLOSE";
  case lexer::TokenType::IDENTIFIER:
    return "IDENTIFIER";
  case lexer::TokenType::EQUAL:
    return "EQUAL";
  case lexer::TokenType::STRING:
    return "STRING";
  case lexer::TokenType::END_OF_FILE:
    return "END_OF_FILE";
  default:
    return "UNKNOWN";
  }
}

int main(int argc, char *argv[]) {
  // Argumentos de línea de comandos: el primer argumento es el nombre del archivo a procesar
  // Segundo: debug --debug para imprimir información de depuración (tokens, tags parseados, etc.)
  // Tercero, opcional --output <nombre_archivo_salida> para guardar el código C++ generado en un archivo
  if (argc > 1) {
    std::string filename = std::string(argv[1]);
    bool debug = false;
    std::string outputFilename;

    for (int i = 2; i < argc; i++) {
      std::string arg = std::string(argv[i]);
      if (arg == "--debug") {
        debug = true;
      } else if (arg == "--output" && i + 1 < argc) {
        outputFilename = std::string(argv[i + 1]);
        i++;
      }
    }

    std::ifstream file(filename);

    if (!file.is_open()) {
      printf("No se pudo abrir el archivo: %s\n", filename.c_str());
      return 1;
    }

    std::string codigoFuente((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    file.close();

    std::vector<lexer::Token> tokens = lexer::tokenizer(codigoFuente);
    if (debug){
      printf("Total de tokens: %zu\n\n", tokens.size());
      for (const auto &token : tokens) {
        printf("Token { %-15s, linea: %d }\n", tokenTypeToString(token.type),
               token.line);
      }
    }

    parser::Parser miParser(tokens);
    std::vector<std::shared_ptr<ImTag::Tag>> tags = miParser.parse();

    if(debug){
      for (const auto &parse : tags) {
        // Imprimir información sobre cada tag parseado
        printf("Tag parseado: %s, linea: %d\n", typeid(*parse).name(), parse->linea);
      }
    }
    // Fase de traducción a C++
    std::string codigoCppFinal = "";
    bool contextoInyectado = false;
    for (const auto& tag : tags) {
        if (!contextoInyectado && std::dynamic_pointer_cast<ImTag::CppTag>(tag) == nullptr) {
            codigoCppFinal += "\n    // [ImTag] Contexto de viewport para unidades de medida\n";
            codigoCppFinal += "    const ImGuiViewport* __imtag_vp = ImGui::GetMainViewport();\n";
            codigoCppFinal += "    const float __imtag_vw = __imtag_vp->WorkSize.x;\n";
            codigoCppFinal += "    const float __imtag_vh = __imtag_vp->WorkSize.y;\n\n";
            contextoInyectado = true;
        }
        codigoCppFinal += tag->traducirACpp();
    }
    if(debug){
      printf("\nCódigo C++ final generado:\n%s\n", codigoCppFinal.c_str());
    }

    if (!outputFilename.empty()) {
      std::ofstream outputFile(outputFilename);
      if (outputFile.is_open()) {
        outputFile << codigoCppFinal;
        outputFile.close();
        printf("Código C++ generado guardado en: %s\n", outputFilename.c_str());
      } else {
        printf("No se pudo abrir el archivo de salida: %s\n", outputFilename.c_str());
      }
    }else{
      // Guardar en la misma carpeta con el mismo nombre pero extensión .cpp
      std::string outputFileName = filename.substr(0, filename.find_last_of('.')) + ".cpp";
      std::ofstream outputFile(outputFileName);
      if (outputFile.is_open()) {
        outputFile << codigoCppFinal;
        outputFile.close();
        printf("Código C++ generado guardado en: %s\n", outputFileName.c_str());
      } else {
        printf("No se pudo abrir el archivo de salida: %s\n", outputFileName.c_str());
      }
    }
  } else {
    printf("Uso: ImTag <archivo.ctag>\n");
  }
  return 0;
}