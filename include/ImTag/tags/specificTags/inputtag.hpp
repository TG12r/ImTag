#pragma once
#include "ImTag/tags/tag.hpp"
#include <string>
#include <unordered_map>

namespace ImTag {
    class inputTag : public Tag {
    public:
        std::unordered_map<std::string, std::string> attrs;

        inputTag(std::unordered_map<std::string, std::string> &attrs, int l) {
            this->attrs = attrs;
            this->linea = l;
        }

        std::string traducirACpp() override { 
            std::string label = attrs.count("label") ? attrs["label"] : "";
            std::string variable = attrs["bind"];
            std::string tipo = attrs.count("type") ? attrs["type"] : "text";

            if (tipo == "int") {
                if (!variable.empty() && variable[0] != '&') variable = "&" + variable;
                return "ImGui::InputInt(\"" + label + "\", " + variable + ");\n";
            } else if (tipo == "float") {
                if (!variable.empty() && variable[0] != '&') variable = "&" + variable;
                return "ImGui::InputFloat(\"" + label + "\", " + variable + ");\n";
            } else {
                // type == "text" (por defecto)
                std::string tamano = attrs.count("size") ? attrs["size"] : "sizeof(" + variable + ")";
                
                std::string flags = "0";
                if (attrs["password"] == "true") flags += " | ImGuiInputTextFlags_Password";
                if (attrs["readOnly"] == "true") flags += " | ImGuiInputTextFlags_ReadOnly";

                if (flags == "0") {
                    return "ImGui::InputText(\"" + label + "\", " + variable + ", " + tamano + ");\n";
                } else {
                    return "ImGui::InputText(\"" + label + "\", " + variable + ", " + tamano + ", " + flags + ");\n";
                }
            }
        }
    };
} // namespace ImTag
