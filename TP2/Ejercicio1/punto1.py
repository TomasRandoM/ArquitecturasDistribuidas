import direccion_IP
from mpi4py import MPI

comm = MPI.COMM_WORLD
size = MPI.COMM_WORLD.Get_size()
rank = MPI.COMM_WORLD.Get_rank()

name = MPI.Get_processor_name()

print("Hola Mundo! Soy el proceso ", rank, " de ", size, " corriendo en la máquina ", name, " IP= ", direccion_IP.obtener_IP())
