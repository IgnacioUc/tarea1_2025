# tarea1_2025
# 🎫 Sistema de Gestión de Tickets de Soporte Técnico

Este proyecto implementa una aplicación en **C** que permite administrar tickets de soporte técnico en una empresa, utilizando un sistema de **colas con prioridades**. Cada ticket tiene un nivel de urgencia que determina el orden de atención.

---

## 📌 Funcionalidades principales

1. **Registrar ticket**
   - Crea un nuevo ticket con:
     - `ID`
     - `Descripción`
     - `Hora de registro` (actual)
     - `Prioridad` (por defecto: **Bajo**)

2. **Asignar prioridad a ticket**
   - Cambia la prioridad de un ticket existente (`Alto`, `Medio` o `Bajo`).
   - Si el ticket no existe, se muestra un mensaje de error.

3. **Mostrar lista de tickets pendientes**
   - Muestra todos los tickets ordenados:
     1. Por prioridad (**Alto > Medio > Bajo**)
     2. Por orden de llegada dentro de la misma prioridad

4. **Procesar siguiente ticket**
   - Atiende el ticket más urgente y antiguo.
   - Lo elimina de la lista y muestra sus datos.
   - Si no hay tickets, muestra un mensaje.

5. **Buscar ticket por ID**
   - Permite buscar un ticket específico por su `ID`.
   - Muestra toda su información si existe, o un mensaje de error si no.

---
### 👤 Nombre

- Ignacio Calderón

  
## 🛠️ Compilación y ejecución

### 🧪 Requisitos
- Compilador C (por ejemplo, `gcc`)
- Sistema compatible con funciones estándar de C (`stdio.h`, `stdlib.h`, `string.h`, `time.h`)



### 🔧 Compilar el programa
```bash
gcc tarea1.c -o tarea

---
