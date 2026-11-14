# `<window>`: El elemento Ventana de ImTag

El elemento **`<window>`** representa una ventana flotante o acoplable de **Dear ImGui**. Es un elemento **contenedor**, lo que significa que todo el código C++ u otras etiquetas de ImTag colocadas en su interior se renderizarán dentro de dicha ventana.

El compilador de ImTag se encarga de llamar automáticamente a `ImGui::Begin()`, envolver el contenido en una condición `if` para optimizar el rendimiento y cerrar siempre la ventana con `ImGui::End()`.

---

## 💻 Sintaxis

```html
<window name="Título de la Ventana" [atributos]>
    <!-- Contenido y elementos hijos aquí -->
</window>
```

---

## 📋 Atributos

| Atributo | Tipo | Obligatorio | Valor por defecto | Descripción |
| :--- | :--- | :---: | :---: | :--- |
| **`name`** | Cadena de texto | **Sí** | *(ninguno)* | El título visible de la ventana y su identificador interno único en ImGui. |
| **`width`** | Número / Expresión | No | `"400"` | Ancho inicial de la ventana en píxeles (`ImGuiCond_FirstUseEver`). |
| **`height`** | Número / Expresión | No | `"300"` | Alto inicial de la ventana en píxeles (`ImGuiCond_FirstUseEver`). |
| **`x`** | Número / Expresión | No | `"0"` | Posición horizontal inicial en la pantalla (`ImGuiCond_FirstUseEver`). |
| **`y`** | Número / Expresión | No | `"0"` | Posición vertical inicial en la pantalla (`ImGuiCond_FirstUseEver`). |
| **`open`** | Puntero booleano C++ | No | `nullptr` | Puntero a variable `bool` (ej. `"&mostrarVentana"`). Muestra el botón de cierre `'X'`. Si el usuario pulsa la 'X', ImGui cambia la variable a `false`. |
| **`noTitleBar`** | Booleano (`"true"`/`"false"`) | No | `"false"` | Oculta por completo la barra superior de título. |
| **`noResize`** | Booleano (`"true"`/`"false"`) | No | `"false"` | Impide que el usuario cambie el tamaño de la ventana arrastrando sus bordes. |
| **`noMove`** | Booleano (`"true"`/`"false"`) | No | `"false"` | Bloquea la ventana en su posición, impidiendo que el usuario la mueva. |
| **`noCollapse`** | Booleano (`"true"`/`"false"`) | No | `"false"` | Desactiva la flechita para colapsar o minimizar la ventana. |
| **`noScrollbar`** | Booleano (`"true"`/`"false"`) | No | `"false"` | Oculta las barras de desplazamiento (scroll) vertical y horizontal. |
| **`menuBar`** | Booleano (`"true"`/`"false"`) | No | `"false"` | Habilita el espacio para una barra de menú superior en la ventana. |
| **`fullscreen`** | Booleano (`"true"`/`"false"`) | No | `"false"` | Acopla la ventana al 100% de la ventana principal del sistema operativo (GLFW), sin bordes ni decoraciones. Se redimensiona automáticamente con la ventana del OS. |


> **Nota sobre el tamaño y posición:** `width`, `height`, `x` y `y` utilizan `ImGuiCond_FirstUseEver`. Esto significa que establecen las dimensiones **la primera vez que se abre la ventana**. Si el usuario la redimensiona o mueve, ImGui recordará su nueva posición entre frames.

---

## 🛠️ Ejemplos

### 1. Ventana básica
Una ventana sencilla con título y dimensiones por defecto (400x300):

```html
<window name="Mi Primera Ventana">
    <text value="Hola Mundo, esta es mi primera ventana en ImTag">
</window>
```

**Traducción generada a C++:**
```cpp
ImGui::SetNextWindowSize(ImVec2(400, 300), ImGuiCond_FirstUseEver);
if (ImGui::Begin("Mi Primera Ventana", nullptr, 0)) {
    ImGui::Text("¡Hola, mundo!");
}
ImGui::End();
```

---

### 2. Ventana con tamaño y posición personalizados
Configuración de una ventana en una esquina concreta con tamaño específico:

```html
<window name="Inventario" x="50" y="50" width="320" height="480" noCollapse="true">
    <button name="Usar Poción" onClick="beberPocion()" />
</window>
```

---

### 3. Ventana cerrable con la 'X' (`open`)
Al pasarle una variable booleana en `open`, la ventana mostrará el botón de cruz ('X') en la esquina:

```html
// En tu código C++:
static bool ventanaAbierta = true;

// En tu interfaz ImTag:
if (ventanaAbierta) {
    <window name="Opciones" open="&ventanaAbierta">
        ImGui::Text("Configuración del juego");
    </window>
}
```

---

### 4. Ventana HUD fija (sin barra ni movimiento)
Ideal para barras de vida o información superpuesta que el usuario no deba mover:

```html
<window name="HUD" x="10" y="10" width="200" height="80" noTitleBar="true" noResize="true" noMove="true">
    ImGui::Text("Salud: 100 / 100");
</window>
```

### 5. Ventana acoplada a pantalla completa (`fullscreen="true"`)
Ocupa toda la ventana de tu aplicación / OS (sin barras de título ni bordes), ideal para aplicaciones completas o interfaces tipo DAW/Editor:

```html
<window name="MiAplicacion" fullscreen="true">
    <button name="Guardar" onClick="guardarProyecto()" />
</window>
```


---

## ⚙️ Especificaciones técnicas

* **Tipo de etiqueta:** Contenedora (requiere `<window>` de apertura y `</window>` de cierre).
* **Elemento padre permitido:** Puede estar en la raíz del archivo o anidada dentro de otra ventana (creando una subventana o ventana hija de ImGui).
* **Optimización de render:** Todo el contenido interior queda protegido por `if (ImGui::Begin(...))`. Si la ventana está minimizada u oculta, el contenido hijo no consume ciclos de CPU ni dibuja llamadas innecesarias.

---

## 🔗 Ver también
* [`<button />`](button.md)
* [Guía de primeros pasos](../getting-started.md)
