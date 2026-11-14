#include "ImTag/tags/tag.hpp"
#include <string>


namespace ImTag {
    class CppTag : public Tag {
        public:
            std::string codigo;

            CppTag(const std::string &codigo, int l) {
                this->codigo = codigo;
                this->linea = l;
            }

            std::string traducirACpp() override { return codigo; }
        };
} // namespace ImTag
