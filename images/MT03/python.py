import os

# 👉 Nombre de la carpeta que se usará en las rutas Markdown
# (aunque el script se ejecute dentro de la carpeta real de imágenes)
carpeta = "../images/MT03"  # Cambiá esto según cómo quedarán publicadas las imágenes

# Extensiones válidas
extensiones = (".jpg", ".jpeg", ".png", ".gif", ".svg")

# Directorio actual (donde se ejecuta el script)
directorio_actual = os.getcwd()

# Listar imágenes en el directorio actual
archivos = [f for f in os.listdir(directorio_actual) if f.lower().endswith(extensiones)]

if not archivos:
    print("⚠️ No se encontraron imágenes en esta carpeta.")
    exit()

# Ordenar alfabéticamente
archivos.sort()

# Generar bloque Markdown con enlaces
salida = ["## 📂 Galería de imágenes (enlaces)\n"]
for img in archivos:
    nombre = os.path.splitext(img)[0].replace("_", " ").capitalize()
    salida.append(f"- [{nombre}]({carpeta}/{img})")

# Unir todo el bloque
bloque = "\n".join(salida)

# Guardar el resultado en un archivo Markdown
archivo_salida = "galeria.md"
with open(archivo_salida, "w", encoding="utf-8") as f:
    f.write(bloque)

print(f"\n✅ Archivo '{archivo_salida}' generado correctamente en:\n{directorio_actual}\n")
print("\n--- Contenido generado ---\n")
print(bloque)
