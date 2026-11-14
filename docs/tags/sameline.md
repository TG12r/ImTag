# `<sameline />`: Disposición Horizontal en ImTag

Por defecto, Dear ImGui coloca cada elemento debajo del anterior en vertical. El elemento **`<sameline />`** indica a ImGui que coloque el siguiente elemento **en la misma línea horizontal** (al lado del anterior). Es un elemento **autocerrado** (`/>`).

El compilador de ImTag lo traduce directamente a `ImGui::SameLine()`.

---

## 💻 Sintaxis

```html
<sameline />
```

---

## 🛠️ Ejemplo: Botones en la misma fila

```html
<window name="Confirmación">
    <text value="¿Desea guardar los cambios?" />
    <button name="Aceptar" onClick="guardar()" />
    <sameline />
    <button name="Cancelar" onClick="cancelar()" />
</window>
```

**Traducción generada a C++:**
```cpp
if (ImGui::Begin("Confirmación", ...)) {
    ImGui::Text("¿Desea guardar los cambios?");
    if (ImGui::Button("Aceptar")) {
        guardar();
    }
    ImGui::SameLine();
    if (ImGui::Button("Cancelar")) {
        cancelar();
    }
}
ImGui::End();
```

---

## 🔗 Ver también
* [`<button />`](button.md)
* [`<separator />`](separator.md)
* [`<spacing />`](spacing.md)
