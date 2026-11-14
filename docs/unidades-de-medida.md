# Unidades de medida en ImTag

ImTag incorpora un sistema inteligente y responsivo de **unidades de medida** inspirado en CSS/Web, que resuelve uno de los problemas más frecuentes en Dear ImGui: adaptar la interfaz a diferentes resoluciones de pantalla (720p, 1080p, 2K, 4K).

En lugar de calcular manualmente posiciones relativas con código matemático largo, puedes indicar directamente las dimensiones deseadas utilizando la función interna `unidadesDeMedida`.

---

## 📏 Unidades soportadas

| Unidad | Nombre | Qué representa | Equivalencia en C++ / Dear ImGui | Ejemplo |
| :---: | :--- | :--- | :--- | :--- |
| **`vw`** | *Viewport Width* | Porcentaje del ancho total de la ventana de la aplicación. | `(__imtag_vw * factor)` | `width="50vw"` *(mitad del ancho)* |
| **`vh`** | *Viewport Height* | Porcentaje del alto total de la ventana de la aplicación. | `(__imtag_vh * factor)` | `height="80vh"` *(80% del alto)* |
| **`%`** | Porcentaje relativo | Porcentaje del espacio disponible en el contenedor actual. | `(ImGui::GetContentRegionAvail().eje * factor)` | `width="100%"` |
| **`px`** | Píxeles | Píxeles exactos en pantalla. | `400.0f` | `width="400px"` |
| *(sin unidad)* | Número puro | Píxeles exactos por compatibilidad. | `400.0f` | `width="400"` |

---

## ⚡ Contexto de Viewport inyectado automáticamente

Para que no tengas que escribir ni una sola llamada repetida a `ImGui::GetMainViewport()`, **ImTag inyecta automáticamente** las variables de contexto al comenzar la interfaz en cada frame:

```cpp
// [ImTag] Contexto de viewport para unidades de medida
const ImGuiViewport* __imtag_vp = ImGui::GetMainViewport();
const float __imtag_vw = __imtag_vp->WorkSize.x;
const float __imtag_vh = __imtag_vp->WorkSize.y;
```

De esta forma, todas las ventanas y elementos del frame comparten las mismas variables sin redefiniciones y responden en tiempo real si el usuario estira o encoge la ventana de Windows/GLFW.

---

## 🛠️ Ejemplos de uso

### 1. Barra lateral fija de 25% del ancho y 100% del alto
```html
<window name="Sidebar" x="0" y="0" width="25vw" height="100vh" noTitleBar="true" noResize="true">
    <button name="Guardar" />
</window>
```

**C++ generado:**
```cpp
ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f), ImGuiCond_FirstUseEver);
ImGui::SetNextWindowSize(ImVec2((__imtag_vw * 0.250000f), (__imtag_vh * 1.000000f)), ImGuiCond_FirstUseEver);
if (ImGui::Begin("Sidebar", nullptr, 0 | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize)) {
    // ...
}
ImGui::End();
```

---

### 2. Panel central centrado
```html
<window name="Editor Central" x="25vw" y="0" width="75vw" height="100vh">
    // Área de trabajo principal
</window>
```

---

## 🧠 La función `unidadesDeMedida`

Toda la conversión es gestionada de forma centralizada por:

```cpp
std::string ImTag::unidadesDeMedida(const std::string& valor, bool esAlto = false);
```

Ubicada en `include/ImTag/utils/unidades.hpp`. Es reutilizable por cualquier tag actual o futuro (como `<window>`, `<button>`, `<slider>`, etc.) para garantizar consistencia en todo el framework.
