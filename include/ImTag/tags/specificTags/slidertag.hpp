#pragma once
#include "ImTag/tags/tag.hpp"
#include <string>
#include <unordered_map>

namespace ImTag {
    class sliderTag : public Tag {
    public:
        std::unordered_map<std::string, std::string> attrs;

        sliderTag(std::unordered_map<std::string, std::string> &attrs, int l) {
            this->attrs = attrs;
            this->linea = l;
        }

        std::string traducirACpp() override { 
            std::string label = attrs["label"];
            std::string variable = attrs["bind"];
            
            // Si el usuario no puso '&' delante de la variable, lo añadimos nosotros
            if (!variable.empty() && variable[0] != '&') {
                variable = "&" + variable;
            }

            std::string tipo = attrs.count("type") ? attrs["type"] : "float";

            if (tipo == "int") {
                std::string minVal = attrs.count("min") ? attrs["min"] : "0";
                std::string maxVal = attrs.count("max") ? attrs["max"] : "100";
                return "ImGui::SliderInt(\"" + label + "\", " + variable + ", " + minVal + ", " + maxVal + ");\n";
            } else {
                std::string minVal = attrs.count("min") ? attrs["min"] : "0.0f";
                std::string maxVal = attrs.count("max") ? attrs["max"] : "1.0f";
                return "ImGui::SliderFloat(\"" + label + "\", " + variable + ", " + minVal + ", " + maxVal + ");\n";
            }
        }
    };
} // namespace ImTag
