Para generar las imágenes PCB tener en cuenta los siguente:
1. Importar desde kicad (Archivo pcb) usando la opción file ->plot, y marcando lo que se muestra en la imagen Export_opcion.png. 
2. Buscar los archivos en la carpeta seleccionada. Abrirlos con Inkview/Inkscape.
3. Editar imágenes tal que: 
a. Top se deja sin edición y se pasa a png.
b. drill se obtiene a partir de top, borrando todo menos los agujeros y se pasa a png. Es necesario invertir los colores.
c. El contorno pasa a png.
d. buttom debe ser reflejada.

4. Poner PPP en al menos 1000 para cada una de las imágenes. La edición se puede hacer sin problemas en paint. Como recomendación, que top y buttom no tengan el contorno, y dejar un buen margen, considerando tamaño de las líneas, distancia entre ellas, distancia al edge cut.
