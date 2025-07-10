# Proyecto analizador de enlaces web

## 1. Introducción

Este proyecto tiene como objetivo construir una aplicación en C++ que, dada una URL raíz, explore recursivamente los enlaces presentes en esa página web y construya un árbol de navegación representando la estructura del sitio.

## 2. Descripción del problema

A partir de una URL inicial, se deben seguir los enlaces internos (mismo dominio) de manera recursiva hasta una profundidad determinada. Se debe evitar visitar enlaces repetidos y mantener un registro de enlaces rotos. Los enlaces externos solo se agregan como nodos pero no se exploran.

## 3. Requerimientos del sistema

### 3.1 Requerimientos funcionales

1. Construcción del árbol de navegación desde una URL raíz.
2. Inclusión selectiva de subdominios según parámetros del usuario.
3. Exclusión de enlaces externos del proceso recursivo (pero agregados como nodos terminales).
4. Estadísticas:

   - Total de enlaces
   - Enlaces internos
   - Enlaces externos
   - Profundidad del árbol

5. Búsqueda por palabra clave e indicación del camino desde la raíz.
6. Detección de enlaces rotos (respuesta no satisfactoria).
7. Exportación del árbol a archivo (JSON/Texto).

### 3.2 Requerimientos no funcionales

- Interfaz de consola.
- Código modular distribuido en 3 capas.
- Uso completo de la biblioteca estándar C++ (STL).
- Uso documentado de cualquier estructura personalizada.
- Pruebas unitarias y de integración.

## 4. Capas del sistema

- **Presentación:** interfaz de consola (menú).
- **Negocios:** exploración web, construcción del árbol, análisis.
- **Datos:** acceso HTTP con libcurl, exportación de datos.

## 5. Estructuras de datos

### Estándar (STL):

- `std::string` para URLs y textos.
- `std::set<std::string>` para URLs visitadas (sin duplicados).
- `std::unordered_map<std::string, std::vector<std::string>>` como base del árbol.
- `std::queue` para exploración en amplitud.
- `std::stack` si se realiza en profundidad.
- `std::vector` para listas generales.
- `std::filesystem` para manipulación de rutas al exportar.

### Personalizadas:

Si fuera necesario (por ejemplo, para análisis de texto o simulación de estructuras gráficas), se justificará su implementación en el informe.

## 6. Funcionalidades clave

- `WebCrawler::crawl(const std::string& url, int maxDepth)`
- `WebCrawler::extractLinks(const std::string& html)`
- `WebCrawler::isInternal(const std::string& url)`
- `WebCrawler::containsKeyword(const std::string& html, const std::string& word)`
- `WebCrawler::exportToFile(const std::string& filename)`

## 7. Casos de uso

1. Ingresar URL inicial y parámetros (profundidad, dominio base, incluir subdominios).
2. Construcción del árbol y despliegue de estadísticas.
3. Búsqueda de palabra clave.
4. Exportación del árbol.
5. Visualización por consola del resumen de enlaces.

## 8. Plan de pruebas

- Unitarias:

  - `extractDomain(url)` retorna dominio correcto.
  - `isInternal(url)` reconoce correctamente enlaces internos/externos.
  - `extractLinks(html)` encuentra enlaces válidos.

- Integración:

  - Exploración completa con enlaces mixtos (internos y externos).
  - Exportación a archivo verificando contenido.

## 9. Implementación

Directorio:

- `include/` headers
- `src/ui/` capa de presentación
- `src/business/` crawler, analizador, estadísticas
- `src/data/` libcurl wrapper, exportador
- `tests/` pruebas unitarias

Estrategia TDD: pruebas antes de implementar funcionalidades.

---
