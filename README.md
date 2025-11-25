# Conecta 4 en C++

Proyecto en C++ que implementa el clásico juego **Conecta 4**, incluyendo:

- Tablero dibujado en consola mediante caracteres ASCII  
- Sistema de inicio de sesión con nick  
- Gestión de jugadores registrados  
- Guardado automático de estadísticas (victorias y derrotas)  
- Detección completa de ganador (horizontal, vertical y diagonales)  
- Control de columnas llenas y huecos disponibles  

Este proyecto fue desarrollado como práctica universitaria de programación en C++.

---

## Características del juego

### Funcionalidades principales
- Juego completo para **dos jugadores** (jugador 1 vs jugador 2).
- Tablero de **6 filas x 8 columnas**.
- Inserción automática de fichas en la fila correspondiente.
- Detección de victoria en:
  - Vertical  
  - Horizontal  
  - Diagonal ↘  
  - Diagonal ↗
- Comprobación de columnas llenas.
- Empate cuando no quedan huecos.

### Gestión de jugadores
- Los jugadores se identifican por **nick**.
- Si el jugador no existe, se crea automáticamente.
- Se guardan:
  - Partidas ganadas  
  - Partidas perdidas
- Los datos se almacenan en *jugadores.txt*.

### 🗂 Archivos usados
- `jugadores.txt` → almacena la base de datos local de jugadores.

---

## Vista del tablero (ASCII)

```text
CONECTA4
┌───┬───┬───┬───┬───┬───┬───┬───┐
│   │   │   │   │   │   │   │   │
├───┼───┼───┼───┼───┼───┼───┼───┤
│   │   │   │   │   │   │   │   │
...
└───┴───┴───┴───┴───┴───┴───┴───┘
  1   2   3   4   5   6   7   8
