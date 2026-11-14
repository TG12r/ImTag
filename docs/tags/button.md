# `<button />`: El elemento Botón de ImTag

El elemento **`<button />`** representa un botón pulsable de **Dear ImGui**. Es un elemento **autocerrado** (`/>`), diseñado para disparar una acción o invocar una función en C++ cuando el usuario hace clic sobre él.

El compilador de ImTag se encarga de traducirlo a una condición nativa `if (ImGui::Button(...)) { ... }`.

---

## 💻 Sintaxis

```html
<button name="Texto del Botón" onClick="expresiónCpp" />
```

> **Importante:** `<button />` es una etiqueta autocerrada. Siempre debe finalizar con `/>`. No utiliza `</button>`.

---

## 📋 Atributos

| Atributo | Tipo | Obligatorio | Valor por defecto | Descripción |
| :--- | :--- | :---: | :---: | :--- |
| **`name`** | Cadena de texto | **Sí** | *(ninguno)* | El texto visible que se mostrará dentro del botón. |
| **`onClick`** | Expresión / Código C++ | No | `"void()"` | Código, función o expresión de C++ que se ejecutará en el frame en que se haga clic en el botón. |

---

## 🛠️ Ejemplos

### 1. Botón básico con llamada a función
Un botón que ejecuta una función al pulsarse:

```html
<button name="Guardar Partida" onClick="guardarDatos()" />
```

**Traducción generada a C++:**
```cpp
if (ImGui::Button("Guardar Partida")) {
    guardarDatos();
}
```

---

### 2. Botón modificando una variable directamente
Puedes escribir cualquier instrucción válida de C++ en el atributo `onClick`:

```html
<button name="Subir Volumen" onClick="volumen += 5" />
```

---

### 3. Varios botones dentro de una ventana

```html
<window name="Menú Principal">
    <button name="Nueva Partida" onClick="iniciarJuego()" />
    <button name="Cargar" onClick="cargarJuego()" />
    <button name="Salir" onClick="salirDelJuego()" />
</window>
```

---

## ⚙️ Especificaciones técnicas

* **Tipo de etiqueta:** Autocerrada (`/>`). No admite etiquetas hijas en su interior.
* **Elemento padre:** Puede ubicarse dentro de `<window>` o en cualquier bloque de código C++ donde sea válido renderizar elementos de Dear ImGui.
* **Comportamiento en Dear ImGui:** Se evalúa de manera inmediata cada frame. Si `ImGui::Button()` devuelve `true`, se ejecuta la instrucción definida en `onClick`.

---

## 🔗 Ver también
* [`<window>`](window.md)
* [Guía de primeros pasos](../getting-started.md)
