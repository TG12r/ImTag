#pragma once
#include <string>
#include <cctype>

namespace ImTag {

    inline std::string unidadesDeMedida(const std::string& valor, bool esAlto = false) {
        if (valor.empty()) return "0.0f";

        // 1. Viewport Width (vw) - Porcentaje del ancho total de la ventana
        if (valor.size() > 2 && valor.substr(valor.size() - 2) == "vw") {
            float num = std::stof(valor.substr(0, valor.size() - 2));
            return "(__imtag_vw * " + std::to_string(num / 100.0f) + "f)";
        }

        // 2. Viewport Height (vh) - Porcentaje del alto total de la ventana
        if (valor.size() > 2 && valor.substr(valor.size() - 2) == "vh") {
            float num = std::stof(valor.substr(0, valor.size() - 2));
            return "(__imtag_vh * " + std::to_string(num / 100.0f) + "f)";
        }

        // 3. Porcentaje relativo (%) - Espacio disponible actual en el contenedor
        if (valor.back() == '%') {
            float num = std::stof(valor.substr(0, valor.size() - 1));
            std::string eje = esAlto ? "y" : "x";
            return "(ImGui::GetContentRegionAvail()." + eje + " * " + std::to_string(num / 100.0f) + "f)";
        }

        // 4. Píxeles explícitos (px)
        if (valor.size() > 2 && valor.substr(valor.size() - 2) == "px") {
            return valor.substr(0, valor.size() - 2) + ".0f";
        }

        // 5. Si ya contiene 'f' o punto decimal (ej: "400.0f")
        if (valor.back() == 'f' || valor.find('.') != std::string::npos) {
            return valor;
        }

        // 6. Si es un número entero simple (ej: "400")
        bool esSoloDigitos = true;
        for (char c : valor) {
            if (!std::isdigit(static_cast<unsigned char>(c)) && c != '-') {
                esSoloDigitos = false;
                break;
            }
        }
        if (esSoloDigitos) {
            return valor + ".0f";
        }

        return valor;
    }

} // namespace ImTag
