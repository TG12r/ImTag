# `<spacing />`: El elemento Espaciado de ImTag

El elemento **`<spacing />`** inserta un espacio o hueco vertical vacío entre elementos de la interfaz en **Dear ImGui**. Es un elemento **autocerrado** (`/>`).

El compilador de ImTag lo traduce directamente a `ImGui::Spacing()`.

---

## 💻 Sintaxis

```html
<spacing />
```

---

## 🛠️ Ejemplo

```html
<window name="Formulario">
    <text value="Paso 1: Configuración" />
    <spacing />
    <button name="Siguiente" onClick="siguientePaso()" />
</window>
```

**Traducción generada a C++:**
```cpp
if (ImGui::Begin("Formulario", ...)) {
    ImGui::Text("Paso 1: Configuración");
    ImGui::Spacing();
    if (ImGui::Button("Siguiente")) {
        siguientePaso();
    }
}
ImGui::End();
```

---

## 🔗 Ver también
* [`<separator />`](separator.md)
* [`<sameline />`](sameline.md)
