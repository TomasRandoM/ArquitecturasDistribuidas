#!/bin/bash

# Comprobamos si se pasó un argumento
if [ "$#" -ne 1 ]; then
    echo "Uso: $0 ips.txt"
    exit 1
fi

# Se lee cada linea y se ejecuta el comando
while IFS= read -r ip; do
    echo "Copiando a: $ip"
    ssh-copy-id mpiuser@"$ip"
    if [ $? -eq 0 ]; then
        echo "Sin errores $ip"
    else
        echo "Error al copiar a $ip"
    fi

done < "$1"