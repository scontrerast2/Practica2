# LEEME
Descripción detallada de los campos del dataset seleccionado:
El dataset es de jugadores de FIFA, con los siguientes campos:
- player_id: ID único del jugador (entero)
- player_url: URL del jugador (string)
- fifa_version: Versión de FIFA (entero)
- ... (list all columns as provided in the query)

Justificación de los criterios de búsqueda implementados:
- Búsqueda primaria por short_name utilizando tabla hash para eficiencia (<2 segundos).
- Estructura: Tabla hash con encadenamiento para colisiones, almacenando offsets en el archivo binario.
- Para búsquedas secundarias.

Rangos de valores válidos para cada campo de entrada:
- short_name: String de longitud < 256 caracteres.
- age: 15-50 (no validado en código, agregar if en client).
- overall: 0-99.
- Etc. (adaptar por campo, validación en opción 2).

Ejemplos específicos de uso del programa con su dataset:
- Ejecutar server: ./p2-dataProgram (requiere players.csv si no existe bin).
- Ejecutar client: ./client
- Búsqueda: Opción 1, ingresar "Messi", muestra jugadores con ese nombre.
- Escribir: Opción 2, ingresar campos (tedioso, pero funcional).
- Leer registro: Opción 3, ingresar 0 para primer registro.

Adaptaciones: Dataset en binario fijo, index en memoria (<10MB), sockets para comunicación, solo datos en disco.
