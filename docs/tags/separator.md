# `<separator />`: El elemento Separador de ImTag

El elemento **`<separator />`** dibuja una línea horizontal divisoria entre elementos de la interfaz en **Dear ImGui**. Es un elemento **autocerrado** (`/>`).

El compilador de ImTag lo traduce directamente a `ImGui::Separator()`.

---

## 💻 Sintaxis

```html
<separator />
```

---

## 🛠️ Ejemplo

```html
<window name="Perfil">
    <text value="Nombre: Jugador 1" />
    <separator />
    <text value="Puntuación: 1500" />
</window>
```

**Traducción generada a C++:**
```cpp
if (ImGui::Begin("Perfil", ...)) {
    ImGui::Text("Nombre: Jugador 1");
    ImGui::Separator();
    ImGui::Text("Puntuación: 1500");
}
ImGui::End();
```

---

## 🔗 Ver también
* [`<spacing />`](spacing.md)
* [`<sameline />`](sameline.md)
