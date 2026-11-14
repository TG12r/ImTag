#pragma once

#include <string>
#include <vector>
#include <memory>

namespace ImTag {

    class Tag {
    public:
        int linea = 0;
        int columna = 0;
        
        // Un tag contenedor puede tener hijos (otros tags o bloques C++)
        std::vector<std::shared_ptr<Tag>> hijos;

        virtual ~Tag() = default;

        // Cada clase hija implementa OBLIGATORIAMENTE cómo se traduce
        virtual std::string traducirACpp() = 0;
    };

}
