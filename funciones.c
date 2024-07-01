#include <stdio.h>
#include <string.h>
#include "funciones.h"

void buscarPorTamano(int *numHabitacion, char habitaciones[9][3][40], double precios[9]) {
    char tipo[40];
    printf("Ingrese el tamano de la habitacion (simple/doble/triple): ");
    scanf("%s", tipo);
    printf("#\t\tTamano\t\tHotel\t\t\tPrecio\n");
    
    for (int i = 0; i < 9; i++) {

        if (strcmp(habitaciones[i][1], tipo) == 0) {
            printf("%s\t\t%s\t\t%s\t\t%f\n",habitaciones[i][0],habitaciones[i][1],habitaciones[i][2],precios[i]);
        }
    }
    printf("Ingrese el numero de la habitacion que desea: \n");
    scanf("%d", numHabitacion);
    (*numHabitacion)--;
}

void buscarHotel(int *numHabitacion, char habitaciones[9][3][40], double precios[9]) {
    char hotel[40];
    printf("Ingrese el nombre del Hotel: \n");
    scanf("%s", hotel);
    printf("#\t\tTamano\t\tHotel\t\t\tPrecio\n");

    for (int i = 0; i < 9; i++) {
        if (strcmp(habitaciones[i][2], hotel) == 0) {
            printf("%s\t\t%s\t\t%s\t\t%f\n",habitaciones[i][0],habitaciones[i][1],habitaciones[i][2],precios[i]);
        }
    }
    printf("Ingrese el numero de la habitacion que desea: \n");
    scanf("%d", numHabitacion);
    (*numHabitacion)--;
}

void realizarReserva(int numHabitacion, char habitaciones[9][3][40], char clientes[5][2][40], int reservas[10][4]) {
    char cedula[40];
    printf("Ingrese su cedula: \n");
    scanf("%s", cedula);
    
    for (int i = 0; i < 5; i++) {
        if (strcmp(clientes[i][1], cedula) == 0 || strcmp(clientes[i][1], "") == 0) {
            if (strcmp(clientes[i][1], "") == 0) {
                printf("Ingrese su nombre: \n");
                scanf("%s", clientes[i][0]);
                strcpy(clientes[i][1], cedula);
            }
            for (int j = 0; j < 10; j++) {
                if (reservas[j][0] == -1) {
                    reservas[j][0] = i;
                    reservas[j][1] = numHabitacion;
                    printf("Ingrese el numero de dias de estancia: \n");
                    scanf("%d", &reservas[j][2]);
                    reservas[j][3] = 0; 
                    printf("Reserva realizada con exito.\n");
                    return;
                }
            }
            printf("No hay mas espacio para reservas.\n");
            return;
        }
    }
    printf("No se pudo realizar la reserva.\n");
}

void buscarReservaPorCedula(int *numReserva, char clientes[5][2][40], int reservas[10][4]) {
    char cedula[40];
    printf("Ingrese su cedula: \n");
    scanf("%s", cedula);
    
    for (int i = 0; i < 5; i++) {
        if (strcmp(clientes[i][1], cedula) == 0) {
            for (int j = 0; j < 10; j++) {
                if (reservas[j][0] == i) {
                    *numReserva = j;
                    return;
                }
            }
        }
    }
    printf("Reserva no encontrada.\n");
    *numReserva = -1;
}

void imprimirReserva(int numReserva, int reservas[10][4], char habitaciones[9][3][40], double precios[9]) {
    if (numReserva == -1) {
        printf("No hay reserva que mostrar.\n");
        return;
    }
    
    int clienteIndex = reservas[numReserva][0];
    int habitacionIndex = reservas[numReserva][1];
    int dias = reservas[numReserva][2];
    double total = dias * precios[habitacionIndex];

    printf("Reserva %d:\n", numReserva);
    printf("Cliente: %d\n", clienteIndex);
    printf("Habitacion: %s - %s - %s\n", habitaciones[habitacionIndex][0], habitaciones[habitacionIndex][1], habitaciones[habitacionIndex][2]);
    printf("Dias de estancia: %d\n", dias);
    printf("Total a pagar: %.2f\n", total);
    printf("Estado de pago: %s\n", reservas[numReserva][3] ? "Pagado" : "Pendiente");
}

void pagarReserva(int numReserva, int reservas[10][4], char habitaciones[9][3][40], double precios[9]) {
    if (numReserva == -1) {
        printf("No hay reserva que pagar.\n");
        return;
    }

    imprimirReserva(numReserva, reservas, habitaciones, precios);
    printf("Desea proceder con el pago (1.Si 2.No): \n");
    int opcion;
    scanf("%d", &opcion);
    
    if (opcion == 1) {
        reservas[numReserva][3] = 1;
        printf("Pago realizado con exito.\n");
        guardarReservas(reservas, "C:/Users/ALIENWARE/OneDrive - Universidad de Las Américas/Escritorio/Taller/Progra/reservas.txt");
    } else {
        printf("No se realizo el pago.\n");
    }
}

void leerClientes(char clientes[][2][40], const char *filename) {
    FILE *file = fopen("C:/Users/ALIENWARE/OneDrive - Universidad de Las Américas/Escritorio/Taller/Progra/clientes.txt", "r");
    if (file == NULL) {
        perror("Error al abrir el archivo de clientes");
        return;
    }
 
    for (int i = 0; i < 5; i++) {
        if (fscanf(file, "%s %s", clientes[i][0], clientes[i][1]) != 2) {
            break;
        }
    }
    fclose(file);
}
 
void leerReservas(int reservas[][4], const char *filename) {
    FILE *file = fopen("C:/Users/ALIENWARE/OneDrive - Universidad de Las Américas/Escritorio/Taller/Progra/reservas.txt", "r");
 
    if (file == NULL) {
        perror("Error al abrir el archivo de reservas");
        return;
    }
 
    for (int i = 0; i < 10; i++) {
        if (fscanf(file, "%d %d %d %d", &reservas[i][0], &reservas[i][1], &reservas[i][2], &reservas[i][3]) != 4) {
            break;
        }
    }
    fclose(file);
}
 
void guardarClientes(char clientes[][2][40], const char *filename) {
    FILE *file = fopen("C:/Users/ALIENWARE/OneDrive - Universidad de Las Américas/Escritorio/Taller/Progra/clientes.txt", "w");
 
    if (file == NULL) {
        perror("Error al abrir el archivo de clientes para escritura");
        return;
    }
 
    for (int i = 0; i < 5; i++) {
        if (clientes[i][0][0] != '\0') {
            fprintf(file, "%s %s\n", clientes[i][0], clientes[i][1]);
        }
    }
    fclose(file);
}
 
void guardarReservas(int reservas[][4], const char *filename) {
    FILE *file = fopen("C:/Users/ALIENWARE/OneDrive - Universidad de Las Américas/Escritorio/Taller/Progra/reservas.txt", "a+");
 
    if (file == NULL) {
        perror("Error al abrir el archivo de reservas para escritura");
        return;
    }
 
    for (int i = 0; i < 10; i++) {
        fprintf(file, "%d %d %d %d\n", reservas[i][0], reservas[i][1], reservas[i][2], reservas[i][3]);
    }
    fclose(file);
}