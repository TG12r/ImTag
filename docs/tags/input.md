# `<input />`: El elemento Campo de Entrada de ImTag

El elemento **`<input />`** representa un campo interactivo para introducir datos con el teclado en **Dear ImGui**. Es un elemento **autocerrado** (`/>`), que permite escribir cadenas de texto o modificar números enteros (`int`) y decimales (`float`).

El compilador de ImTag lo traduce automáticamente a `ImGui::InputText(...)`, `ImGui::InputInt(...)` o `ImGui::InputFloat(...)`.

---

## 💻 Sintaxis

```html
<input [label="Texto descriptivo"] bind="variableBuffer" [type="text|int|float"] [size="tamano"] [password="true"] [readOnly="true"] />
```

> **Importante:** `<input />` es una etiqueta autocerrada. Siempre debe finalizar con `/>`.

---

## 📋 Atributos

| Atributo | Tipo | Obligatorio | Valor por defecto | Descripción |
| :--- | :--- | :---: | :---: | :--- |
| **`bind`** | Variable C++ | **Sí** | *(ninguno)* | La variable donde se almacenará el texto o número introducido. |
| **`label`** | Cadena de texto | No | `""` | Etiqueta de texto descriptiva mostrada a la derecha del campo. |
| **`type`** | `"text"` \| `"int"` \| `"float"` | No | `"text"` | Tipo de entrada de datos a solicitar. |
| **`size`** | Expresión / Número | No | `sizeof(variable)` | Tamaño máximo del buffer en bytes (solo para `type="text"`). |
| **`password`** | Booleano (`"true"`/`"false"`) | No | `"false"` | Oculta los caracteres escritos con asteriscos (`ImGuiInputTextFlags_Password`). |
| **`readOnly`** | Booleano (`"true"`/`"false"`) | No | `"false"` | Convierte el campo en solo lectura (`ImGuiInputTextFlags_ReadOnly`). |

---

## 🛠️ Ejemplos

### 1. Campo de texto estándar
```html
// En tu código C++:
static char nombre[128] = "Jugador 1";

// En tu interfaz ImTag:
<window name="Perfil">
    <input label="Nombre" bind="nombre" />
</window>
```

**Traducción generada a C++:**
```cpp
ImGui::InputText("Nombre", nombre, sizeof(nombre));
```

---

### 2. Campo de contraseña (`password="true"`)
```html
// En tu código C++:
static char passwordBuffer[64] = "";

// En tu interfaz ImTag:
<input label="Contraseña" bind="passwordBuffer" password="true" />
```

**Traducción generada a C++:**
```cpp
ImGui::InputText("Contraseña", passwordBuffer, sizeof(passwordBuffer), 0 | ImGuiInputTextFlags_Password);
```

---

### 3. Campo numérico (`type="int"` o `type="float"`)
```html
// En tu código C++:
static int edad = 20;

// En tu interfaz ImTag:
<input label="Edad" bind="edad" type="int" />
```

**Traducción generada a C++:**
```cpp
ImGui::InputInt("Edad", &edad);
```

---

## ⚙️ Especificaciones técnicas

* **Tipo de etiqueta:** Autocerrada (`/>`).
* **Cálculo de buffer automático:** Si no se especifica el atributo `size`, ImTag calcula automáticamente `sizeof(variable)` para arrays de caracteres estáticos de C/C++ (`char buffer[N]`).
* **Elemento padre:** Puede ubicarse dentro de `<window>` o en cualquier sección de interfaz.

---

## 🔗 Ver también
* [`<slider />`](slider.md)
* [`<button />`](button.md)
* [`<text />`](text.md)
