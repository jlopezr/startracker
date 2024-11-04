import csv
import math

# http://tdc-www.harvard.edu/catalogs/bsc5.html

input_file = "ybsc5"
output_csv = "stars.csv"

# Abrir el archivo de estrellas
with open(input_file) as file:
    data = file.readlines()

# Abrir el archivo CSV para escritura
with open(output_csv, mode='w', newline='') as file:
    writer = csv.writer(file)
    
    # Escribir la cabecera del CSV
    writer.writerow(["Star Number", "Star Name", "Durchmusterung Identification", "RA (degrees)", "Dec (degrees)", "Parallax (arsec)", "Distance (parsecs)", "X (parsecs)", "Y (parsecs)", "Z (parsecs)"])

    # Procesar el archivo línea por línea
    for i, line in enumerate(data):

        # Escribe en pantalla el numero de linea que se esta procesando
        print(f"Procesando línea {i+1}...")

        if line.startswith("#") or line.strip() == "":
            continue  # Saltar comentarios y líneas vacías

        # Extraer los datos relevantes basados en las posiciones fijas de la línea en el archivo
        star_number = line[0:4].strip() # Número de la estrella
        star_name = line[4:14].strip() # Nombre de la estrella
        star_id = line[14:25].strip()  # Durchmusterung Identification

        #76- 77  I2     h       RAh      ?Hours RA, equinox J2000, epoch 2000.0 (1)
        #78- 79  I2     min     RAm      ?Minutes RA, equinox J2000, epoch 2000.0 (1)
        #80- 83  F4.1   s       RAs      ?Seconds RA, equinox J2000, epoch 2000.0 (1)
        
        # Verificar si RA está vacío
        if line[75:83].strip() == "":
            continue  # Saltar la línea si RA está vacío
    
        ra_h = int(line[75:77].strip())
        ra_m = int(line[77:79].strip())
        ra_s = float(line[79:83].strip())
        ra = ra_h + ra_m/60 + ra_s/3600

        #84  A1     ---     DE-      ?Sign Dec, equinox J2000, epoch 2000.0 (1)
        #85- 86  I2     deg     DEd      ?Degrees Dec, equinox J2000, epoch 2000.0 (1)
        #87- 88  I2     arcmin  DEm      ?Minutes Dec, equinox J2000, epoch 2000.0 (1)
        #89- 90  I2     arcsec  DEs      ?Seconds Dec, equinox J2000, epoch 2000.0 (1)

        dec_sign = line[83:84].strip()
        dec_d = int(line[84:86].strip())
        dec_m = int(line[86:88].strip())
        dec_s = float(line[88:90].strip())
        dec = dec_d + dec_m/60 + dec_s/3600
        if dec_sign == "-":
            dec = -dec

        # 161  A1     ---   n_Parallax [D] D indicates a dynamical parallax,
        # 162-166  F5.3   arcsec  Parallax ? Trigonometric parallax (unless n_Parallax)
        parallax_type = line[160:161].strip()        
        parallax_mas = line[161:166].strip()

        if parallax_type == "D" or parallax_mas == "":
            continue  # Saltar la línea si el paralaje está vacío

        parallax = float(parallax_mas)
        # Calcular la distancia en parsecs
        if parallax > 0:
            distance = 1 / parallax
        else:
            continue

        # Convertir las coordenadas de equinoccio J2000 a coordenadas cartesianas
        ra_rad = math.radians(ra)
        dec_rad = math.radians(dec)

        # Calcular las coordenadas cartesianas
        x = distance * math.cos(ra_rad) * math.cos(dec_rad)
        y = distance * math.sin(ra_rad) * math.cos(dec_rad)
        z = distance * math.sin(dec_rad)
        
        # Escribir los datos de la estrella en el archivo CSV
        writer.writerow([star_number, star_name, star_id, ra, dec, parallax, distance, x, y, z])

print(f"Archivo CSV generado: {output_csv}")