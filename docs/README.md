# Referencia de ImTag (ImTag Docs)

Bienvenido a la documentación oficial de **ImTag**, el lenguaje de marcado declarativo para **Dear ImGui** en C++. 

Al igual que HTML estructura el contenido de la web, **ImTag** te permite estructurar interfaces gráficas nativas en C++ de forma visual, limpia y jerárquica, eliminando el desorden de llamadas repetitivas como `Begin()`, `End()` o configuraciones de estilos manuales.

---

## 📚 Índice de contenidos

### Primeros pasos
* [¿Qué es ImTag y cómo funciona?](getting-started.md)
* [Mezclar C++ con ImTag (Código Raw)](getting-started.md#mezclar-c-con-imtag)
* [Estructura de un archivo `.ctag`](getting-started.md#estructura-de-un-archivo-ctag)
* [Sistema de Unidades de Medida (`vw`, `vh`, `%`, `px`)](unidades-de-medida.md)


### Referencia de Elementos (Tags)
Los elementos son los bloques de construcción con los que diseñas tu interfaz:

| Elemento | Tipo | Descripción | Estado |
| :--- | :--- | :--- | :--- |
| [`<window>`](tags/window.md) | Contenedor (`<window>...</window>`) | Crea una ventana de Dear ImGui con soporte de tamaño, posición y flags. | ✅ Disponible |
| [`<button />`](tags/button.md) | Autocerrado (`<button />`) | Crea un botón interactivo que ejecuta código C++ al pulsarse. | ✅ Disponible |
| [`<text />`](tags/text.md) | Autocerrado (`<text />`) | Muestra una línea de texto en pantalla (`ImGui::Text`). | ✅ Disponible |
| [`<separator />`](tags/separator.md) | Autocerrado (`<separator />`) | Dibuja una línea horizontal divisoria (`ImGui::Separator`). | ✅ Disponible |
| [`<spacing />`](tags/spacing.md) | Autocerrado (`<spacing />`) | Añade un espacio o hueco vertical entre elementos (`ImGui::Spacing`). | ✅ Disponible |
| [`<sameline />`](tags/sameline.md) | Autocerrado (`<sameline />`) | Coloca el siguiente elemento al lado (en horizontal) (`ImGui::SameLine`). | ✅ Disponible |
| [`<slider />`](tags/slider.md) | Autocerrado (`<slider />`) | Control deslizador para modificar variables numéricas (`ImGui::SliderFloat/Int`). | ✅ Disponible |
| [`<checkbox />`](tags/checkbox.md) | Autocerrado (`<checkbox />`) | Casilla de verificación para variables booleanas (`ImGui::Checkbox`). | ✅ Disponible |
| [`<input />`](tags/input.md) | Autocerrado (`<input />`) | Campo de entrada de texto o números (`ImGui::InputText/Int/Float`). | ✅ Disponible |





---

## ⚡ Vista previa rápida

Así de simple es escribir una interfaz con ImTag frente a C++ tradicional:

### En ImTag (`.ctag`)
```html
<window name="Mi Primera Ventana" width="400" height="250" noCollapse="true">
    // Código C++ libre aquí dentro
    <button name="¡Púlsame!" onClick="hacerAlgo()" />
</window>
```

### Código C++ Dear ImGui generado automáticamente
```cpp
ImGui::SetNextWindowSize(ImVec2(400, 250), ImGuiCond_FirstUseEver);
if (ImGui::Begin("Mi Primera Ventana", nullptr, 0 | ImGuiWindowFlags_NoCollapse)) {
    // Código C++ libre aquí dentro
    if (ImGui::Button("¡Púlsame!")) {
        hacerAlgo();
    }
}
ImGui::End();
```

---

## 🧠 ¿Cómo funciona por debajo?

ImTag no añade ninguna penalización de rendimiento en tu juego o aplicación. Funciona mediante un transpilador de 3 fases:

1. **Lexer (Tokenizador):** Lee tu archivo `.ctag` carácter por carácter y separa el código C++ nativo de las etiquetas de ImTag.
2. **Parser (Analizador Sintáctico):** Valida la sintaxis (atributos obligatorios, cierre de tags) y construye un árbol jerárquico de nodos (`Tag`).
3. **Generador de C++:** Recorre el árbol y emite código nativo de Dear ImGui listo para compilar con tu compilador favorito (`MSVC`, `GCC`, `Clang`).
