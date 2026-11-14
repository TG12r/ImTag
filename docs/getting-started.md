# Primeros pasos con ImTag

En esta guía aprenderás cómo está estructurado un archivo de **ImTag**, cómo se combinan las etiquetas con tu código C++ existente y cómo el compilador traduce todo a Dear ImGui estándar.

---

## Estructura de un archivo `.ctag`

Un archivo `.ctag` es un archivo de código C++ regular con superpoderes: puedes escribir cualquier código C++ válido (inclusiones, funciones, bucles, variables) y, en el momento que quieras renderizar una interfaz gráfica, abres una etiqueta como `<window>` o `<button />`.

```cpp
#include <imgui.h>
#include <iostream>

void saludar() {
    std::cout << "¡Hola desde ImTag!" << std::endl;
}

void renderUI() {
    // Aquí empieza la magia de ImTag:
    <window name="Panel de Control" width="500" height="400">
        <button name="Saludar" onClick="saludar()" />
    </window>
}
```

---

## Mezclar C++ con ImTag

Una de las ventajas clave de ImTag es que **no intenta sustituir a C++**. El código C++ que coloques fuera o dentro de las etiquetas se conserva exactamente igual:

* **Fuera de las etiquetas:** Todo lo que esté fuera de `<...>` es tratado como código C++ puro (`RAW_CPP`) y se mantiene intacto.
* **Dentro de etiquetas contenedoras:** Todo el código C++ colocado dentro de un tag (por ejemplo, entre `<window>` y `</window>`) se convierte automáticamente en "hijo" de esa ventana, colocándose dentro del bloque `if (ImGui::Begin(...)) { ... }`.

### Ejemplo con lógica C++ dentro de una ventana:
```xml
<window name="Contador">
    static int cuenta = 0;
    cuenta++;
    
    // ImGui nativo conviviendo con ImTag:
    ImGui::Text("Valor actual: %d", cuenta);

    <button name="Reiniciar" onClick="cuenta = 0" />
</window>
```

---

## Tipos de etiquetas

En ImTag existen dos tipos de etiquetas:

### 1. Etiquetas Contenedoras (`<tag> ... </tag>`)
Son aquellas que pueden tener contenido o hijos adentro.
* **Apertura:** `<nombreTag atributo="valor">`
* **Cierre:** `</nombreTag>`
* **Ejemplo principal:** [`<window>`](tags/window.md).

### 2. Etiquetas Autocerradas (`<tag />`)
Son elementos individuales que no contienen hijos y se cierran inmediatamente con `/>`.
* **Sintaxis:** `<nombreTag atributo="valor" />`
* **Ejemplo principal:** [`<button />`](tags/button.md).

---

## Reglas de sintaxis

1. **Atributos:** Se escriben como `nombre="valor"`.
   * Los valores siempre van entre comillas dobles (`"..."`).
2. **Cierre estricto:** Si abres una etiqueta contenedora como `<window>`, debes cerrarla con su correspondiente `</window>`. Olvidar cerrarla provocará un error de sintaxis indicando la línea exacta del fallo.
3. **Mayúsculas y minúsculas:** Los nombres de etiquetas y atributos son sensibles a las mayúsculas (por ejemplo, `onClick` debe escribirse respetando la 'C' mayúscula).
