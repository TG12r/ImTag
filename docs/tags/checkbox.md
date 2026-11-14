# `<checkbox />`: El elemento Casilla de Verificación de ImTag

El elemento **`<checkbox />`** representa una casilla de verificación interactiva de **Dear ImGui**. Es un elemento **autocerrado** (`/>`), diseñado para alternar valores booleanos (`true` / `false`).

El compilador de ImTag lo traduce automáticamente a `if (ImGui::Checkbox(name, &bind)) { onChange(); }`.

---

## 💻 Sintaxis

```html
<checkbox name="Etiqueta visible" bind="variableBool" [onChange="expresionCpp"] />
```

> **Importante:** `<checkbox />` es una etiqueta autocerrada. Siempre debe finalizar con `/>`.

---

## 📋 Atributos

| Atributo | Tipo | Obligatorio | Valor por defecto | Descripción |
| :--- | :--- | :---: | :---: | :--- |
| **`name`** | Cadena de texto | **Sí** | *(ninguno)* | Texto identificativo mostrado junto a la casilla. |
| **`bind`** | Variable booleana C++ | **Sí** | *(ninguno)* | Variable `bool` enlazada que se activará o desactivará (`&` se añade automáticamente). |
| **`onChange`** | Expresión C++ | No | *(ninguno)* | Código o función C++ a ejecutar únicamente en el frame en que el usuario cambie el estado de la casilla. |

---

## 🛠️ Ejemplo

```html
// En tu código C++:
static bool activarSonido = true;

// En tu interfaz ImTag:
<window name="Configuración">
    <checkbox name="Activar Sonido" bind="activarSonido" onChange="actualizarAudio()" />
</window>
```

**Traducción generada a C++:**
```cpp
if (ImGui::Checkbox("Activar Sonido", &activarSonido)) {
    actualizarAudio();
}
```

---

## 🔗 Ver también
* [`<input />`](input.md)
* [`<slider />`](slider.md)
* [`<button />`](button.md)
