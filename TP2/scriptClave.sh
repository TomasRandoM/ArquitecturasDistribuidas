<<<<<<< HEAD
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
=======
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
>>>>>>> 2bd3732fc37e46b2f7bd4b841f74f8c6dc5e31b7
done < "$1"