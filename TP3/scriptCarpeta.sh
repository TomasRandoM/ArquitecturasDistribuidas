#!/bin/bash

# Se comprueba si se pasó un elemento
if [ "$#" -ne 1 ]; then
    echo "Uso: $0 ips.txt"
    exit 1
fi

# Ruta del cual se va a copiar
DIRECTORIO="/home/mpiuser/tomas_rando/"

# Se lee cada ip y se ejecuta el comando
while IFS= read -r ip; do
    echo "Copiando a: $ip"
    scp -r "$DIRECTORIO" mpiuser@"$ip":/home/mpiuser
    if [ $? -eq 0 ]; then
        echo "Copiado con éxito a $ip"
    else
        echo "Error al copiar a $ip"
    fi
done < "$1"