# `<text />`: El elemento Texto de ImTag

El elemento **`<text />`** muestra una cadena de texto en pantalla dentro de la interfaz gráfica de **Dear ImGui**. Es un elemento **autocerrado** (`/>`), que no admite hijos en su interior.

El compilador de ImTag lo traduce directamente a la función nativa `ImGui::Text(...)`.

---

## 💻 Sintaxis

```html
<text value="Cadena de texto a mostrar" />
```

> **Importante:** `<text />` es una etiqueta autocerrada. Siempre debe finalizar con `/>`.

---

## 📋 Atributos

| Atributo | Tipo | Obligatorio | Valor por defecto | Descripción |
| :--- | :--- | :---: | :---: | :--- |
| **`value`** | Cadena de texto | **Sí** | *(ninguno)* | El texto que se imprimirá en pantalla. |

---

## 🛠️ Ejemplos

### 1. Texto simple dentro de una ventana
```html
<window name="Información">
    <text value="Bienvenido al motor de juego" />
</window>
```

**Traducción generada a C++:**
```cpp
ImGui::SetNextWindowSize(ImVec2(400.0f, 300.0f), ImGuiCond_FirstUseEver);
if (ImGui::Begin("Información", nullptr, 0)) {
    ImGui::Text("Bienvenido al motor de juego");
}
ImGui::End();
```

---

### 2. Combinado con botones
```html
<window name="Ajustes">
    <text value="¿Desea guardar los cambios antes de salir?" />
    <button name="Guardar" onClick="guardar()" />
</window>
```

---

## ⚙️ Especificaciones técnicas

* **Tipo de etiqueta:** Autocerrada (`/>`).
* **Elemento padre:** Puede ubicarse dentro de `<window>` o en cualquier sección de la interfaz.
* **Comportamiento en Dear ImGui:** Se dibuja como texto estático sin bordes ni decoraciones.

---

## 🔗 Ver también
* [`<button />`](button.md)
* [`<window>`](window.md)
* [Guía de primeros pasos](../getting-started.md)
