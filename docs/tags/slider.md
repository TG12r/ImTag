# `<slider />`: El elemento Barra Deslizadora de ImTag

El elemento **`<slider />`** representa un control deslizador (slider) numérico interactivo de **Dear ImGui**. Es un elemento **autocerrado** (`/>`), diseñado para permitir al usuario modificar variables numéricas (`float` o `int`) arrastrando el ratón.

El compilador de ImTag lo traduce automáticamente a `ImGui::SliderFloat(...)` o `ImGui::SliderInt(...)`, inyectando el operador de dirección `&` si no se incluye.

---

## 💻 Sintaxis

```html
<slider label="Texto Descriptivo" bind="miVariable" [min="0.0f"] [max="1.0f"] [type="float|int"] />
```

> **Importante:** `<slider />` es una etiqueta autocerrada. Siempre debe finalizar con `/>`.

---

## 📋 Atributos

| Atributo | Tipo | Obligatorio | Valor por defecto | Descripción |
| :--- | :--- | :---: | :---: | :--- |
| **`label`** | Cadena de texto | **Sí** | *(ninguno)* | Texto identificativo mostrado junto al slider. |
| **`bind`** | Variable C++ | **Sí** | *(ninguno)* | Nombre de la variable C++ que se enlazará y modificará (`&` se añade automáticamente si se omite). |
| **`min`** | Número | No | `"0.0f"` (float) / `"0"` (int) | Valor mínimo permitido en el slider. |
| **`max`** | Número | No | `"1.0f"` (float) / `"100"` (int) | Valor máximo permitido en el slider. |
| **`type`** | `"float"` \| `"int"` | No | `"float"` | Tipo de dato numérico (`float` usa `SliderFloat`, `int` usa `SliderInt`). |

---

## 🛠️ Ejemplos

### 1. Slider decimal (float por defecto)
Modificar un valor de volumen entre 0.0 y 1.0:

```html
// En tu código C++:
static float volumen = 0.5f;

// En tu interfaz ImTag:
<window name="Audio">
    <slider label="Volumen General" bind="volumen" min="0.0f" max="1.0f" />
</window>
```

**Traducción generada a C++:**
```cpp
ImGui::SliderFloat("Volumen General", &volumen, 0.0f, 1.0f);
```

---

### 2. Slider de enteros (`type="int"`)
Modificar un nivel o valor entero entre 1 y 10:

```html
// En tu código C++:
static int nivelDificultad = 1;

// En tu interfaz ImTag:
<window name="Juego">
    <slider label="Nivel" bind="nivelDificultad" min="1" max="10" type="int" />
</window>
```

**Traducción generada a C++:**
```cpp
ImGui::SliderInt("Nivel", &nivelDificultad, 1, 10);
```

---

## ⚙️ Especificaciones técnicas

* **Tipo de etiqueta:** Autocerrada (`/>`).
* **Sintaxis inteligente de enlace (`bind`):** Tanto si escribes `bind="miVar"` como `bind="&miVar"`, ImTag detecta y asegura que se pase como puntero válido a Dear ImGui.
* **Elemento padre:** Puede ubicarse dentro de `<window>` o en cualquier sección de interfaz válida.

---

## 🔗 Ver también
* [`<text />`](text.md)
* [`<button />`](button.md)
* [`<window>`](window.md)
