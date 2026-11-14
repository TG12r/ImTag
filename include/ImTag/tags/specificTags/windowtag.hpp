#pragma once
#include "ImTag/tags/tag.hpp"
#include "ImTag/utils/unidades.hpp"
#include <string>
#include <unordered_map>

namespace ImTag {
    class windowTag : public Tag {
    public:
        std::unordered_map<std::string, std::string> attrs;

        windowTag(std::unordered_map<std::string, std::string> &attrs, int l) {
            this->attrs = attrs;
            this->linea = l;
        }

        std::string traducirACpp() override { 
            std::string code = "\n";
            // Si es ventana fullscreen
            if (attrs["fullscreen"] == "true") {
                code += "ImGui::SetNextWindowPos(__imtag_vp->WorkPos);\n";
                code += "ImGui::SetNextWindowSize(__imtag_vp->WorkSize);\n";
                code += "ImGui::SetNextWindowViewport(__imtag_vp->ID);\n";
                code += "ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);\n";
                code += "ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);\n";
                code += "ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));\n";

                std::string flags = "ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoBringToFrontOnFocus";
                if (attrs["menuBar"] == "true") flags += " | ImGuiWindowFlags_MenuBar";

                code += "if (ImGui::Begin(\"" + attrs["name"] + "\", nullptr, " + flags + ")) {\n";
                code += "    ImGui::PopStyleVar(3);\n";
                for (const auto &hijo : hijos) {
                    code += hijo->traducirACpp();
                }
                code += "}\n";
                code += "else {\n";
                code += "    ImGui::PopStyleVar(3);\n";
                code += "}\n";
                code += "ImGui::End();\n";
                return code;
            }


            // Posición inicial (si se especificó x o y)
            if (attrs.count("x") || attrs.count("y")) {
                std::string posX = attrs.count("x") ? unidadesDeMedida(attrs["x"], false) : "0.0f";
                std::string posY = attrs.count("y") ? unidadesDeMedida(attrs["y"], true) : "0.0f";
                code += "ImGui::SetNextWindowPos(ImVec2(" + posX + ", " + posY + "), ImGuiCond_FirstUseEver);\n";
            }

            // Tamaño inicial (si se especificó width o height, o valores por defecto)
            std::string width  = attrs.count("width")  ? unidadesDeMedida(attrs["width"], false)  : "400.0f";
            std::string height = attrs.count("height") ? unidadesDeMedida(attrs["height"], true) : "300.0f";
            code += "ImGui::SetNextWindowSize(ImVec2(" + width + ", " + height + "), ImGuiCond_FirstUseEver);\n";

            // Flags de ventana
            std::string flags = "0";
            if (attrs["noTitleBar"] == "true") flags += " | ImGuiWindowFlags_NoTitleBar";
            if (attrs["noResize"]   == "true") flags += " | ImGuiWindowFlags_NoResize";
            if (attrs["noMove"]     == "true") flags += " | ImGuiWindowFlags_NoMove";
            if (attrs["noCollapse"] == "true") flags += " | ImGuiWindowFlags_NoCollapse";
            if (attrs["noScrollbar"] == "true") flags += " | ImGuiWindowFlags_NoScrollbar";
            if (attrs["menuBar"]    == "true") flags += " | ImGuiWindowFlags_MenuBar";

            // Parámetro p_open (para poder cerrar la ventana con la 'X')
            std::string p_open = attrs.count("open") ? attrs["open"] : "nullptr";

            // ImGui::Begin con optimización if (...)
            code += "if (ImGui::Begin(\"" + attrs["name"] + "\", " + p_open + ", " + flags + ")) {\n";

            // Contenido interior (hijos)
            for (const auto &hijo : hijos) {
                code += hijo->traducirACpp();
            }

            // Cierre obligatorio de ventana
            code += "}\n";
            code += "ImGui::End();\n";

            return code;
        }
    };
} // namespace ImTag
