#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Producto
{   
    char nombreProducto[20];
    int unidades;
    float precio;
};
    
struct Producto carrito[15];
struct Producto inventario[7]={
};//ARRAY DE structs (productos en inventario )

void agregarProducto()
{
    int i, opc, unidades;
    
    printf("\nIndique la seccion donde va a agregar producto: ");
    printf("\n1.CPU");
    printf("\n2.Mouse");
    printf("\n3.Teclado");
    printf("\n4.USB");
    printf("\n5.Monitor");
    printf("\n6.Impresora");
    printf("\n7.Proyector\n");
    scanf("%d", &opc);

    if (opc < 1 || opc > 7) 
    {
        printf("Opción inválida\n");
    }
    i = opc - 1;
    printf("Ingrese la cantidad de unidades que desea agregar: ");
    scanf("%d", &unidades);

    if (unidades <= 0) 
    {
        printf("\nCantidad inválida, intente de nuevo.");
        return;
    }

    printf("\nAgregando %d unidades a %s", unidades, inventario[i].nombreProducto);
    inventario[i].unidades += unidades;
}

void eliminar(int indice)
{
    strcpy(carrito[indice].nombreProducto,"");
    carrito[indice].unidades=0;
    carrito[indice].precio=0;
}

void leerInventario() //Lee del archivo el inventario que previamente se ha subido
{
    FILE *archivoIventario = fopen("Inventario.txt","r");
    int i;
    for(i=0;i<7;i++)
    {
      fscanf(archivoIventario,"%s %d %f \n",inventario[i].nombreProducto,&inventario[i].unidades,&inventario[i].precio); 
    }
    fclose(archivoIventario);
}

void subirInventario()//Sube el inventario actualizado al archivo 
{
    
    FILE *archivoIventario = fopen("Inventario.txt","w");
    int i;
    for(i=0;i<7;i++)
    {
        fprintf(archivoIventario,"%s %d %.2f",inventario[i].nombreProducto,inventario[i].unidades,inventario[i].precio);
        fprintf(archivoIventario,"\n");
    }
    fclose(archivoIventario);
}

void imprimirInventario()  //Muestra en pantalla el inventario actual de productos, 
{
    int i;
    printf("INVENTARIO\n");
    for(i=0;i<7;i++)
    {
        printf("Numero de producto: %d\n",i+1);
        printf("Nombre: %s\n",inventario[i].nombreProducto);
        printf("Unidades: %d\n",inventario[i].unidades);
        printf("Precio: %.2f\n",inventario[i].precio);
        printf("\n");
    }
}

struct Producto comprarProducto(struct Producto productoAComprar,int cantidadCompra) //crea una estructura "Producto" a partir del producto que se va a comprar y la cantidad que se desea comprar.
{
    productoAComprar.unidades=cantidadCompra;
    return productoAComprar;
}


int menu() //muestra un menú de opciones al usuario y devuelve la opción seleccionada por el usuario.
{
    int opcion ;

        printf("\n---M E N U---\n");
        printf("1. REALIZAR COMPRA DE PRODUCTOS\n");
        printf("2. GENERAR FACTURA\n");
        printf("3. REPORTE DE INVENTARIO\n");
        printf("4. Agregar productos\n");
        printf("5. SALIR DE LA TIENDA\n");
        printf("Digite una opcion: ");
        fflush(stdin);
        scanf("%d", &opcion);

    return opcion;
}

void generarFactura(int numProductos, struct Producto *carrito)
{
    int i, indice, nuevaUnidad;
    float total, subtotal;
    subtotal = 0;

    if (numProductos == 2)
    {
        i = 1;
        indice = i + 1;
        if (strcmp(carrito[i].nombreProducto, carrito[indice].nombreProducto) == 0)
        {
            nuevaUnidad = carrito[i].unidades + carrito[indice].unidades;
            carrito[i].unidades = nuevaUnidad;
            eliminar(indice);
        }
        
    }
    else if (numProductos > 2)
    {
        for (i = 1; i < numProductos; i++)
        {
            for (indice = i + 1; indice <= numProductos; indice++)
            {
                if (strcmp(carrito[i].nombreProducto, carrito[indice].nombreProducto) == 0)
                {
                    nuevaUnidad = carrito[i].unidades + carrito[indice].unidades;
                    carrito[i].unidades = nuevaUnidad;
                    eliminar(indice);
                }
            }
        }
    }

    printf("\n");
    printf("PRODUCTO - - - - CANTIDAD - - - PRECIO UNITARIO - - - - TOTAL ");
    for (i = 1; i <= numProductos; i++)
    {
        if(carrito[i].unidades>0)
        {
            total = carrito[i].unidades * carrito[i].precio;
            printf("\n");
            printf("%s", carrito[i].nombreProducto);
            printf("       ");
            printf("%d", carrito[i].unidades);
            printf("      ");
            printf("%.2f", carrito[i].precio);
            printf("     ");
            printf("%.2f", total);
            printf("\n");

            subtotal += carrito[i].precio * carrito[i].unidades;
        }   
    }
    printf("SUBTOTAL: %.2f", subtotal);
    printf("\n");
    printf("TOTAL (IVA AGREGADO): %.2f", subtotal * 1.16);
    printf("\n");
}

void realizarCompra(int productosEnCarrito) //Permite al usuario realizar compras de productos que estén en el inventario. Muestra en pantalla el inventario actual de productos y pide al usuario que ingrese el número del producto que desea comprar y la cantidad deseada. Verifica que el número de producto sea válido y que haya suficientes unidades disponibles
{
    int numProducto,cantidad;
    
        imprimirInventario();
        do{
            printf("Ingresa el numero de producto a comprar: \n");
            scanf("%d",&numProducto);
            if(numProducto<=0||numProducto>7)
            {
                printf("Error producto no existe ingresa un valor valido\n");
            }
            if(inventario[numProducto-1].unidades==0)
            {
                printf("PRODUCTO AGOTADO \n");
            }
        }
        while (numProducto<=0||numProducto>7 || inventario[numProducto-1].unidades==0);    

        do{
            printf("Ingresa la cantidad a comprar: \n");
            scanf("%d",&cantidad);
                if (cantidad<=0)
                {
                    system("cls");
                    printf("ERROR VALOR ERRONEO \n");
                }              
                else if(inventario[numProducto-1].unidades>=cantidad)
                {
                    inventario[numProducto-1].unidades-=cantidad;
                        
                    carrito[productosEnCarrito]=comprarProducto(inventario[numProducto-1],cantidad);
                        
                    printf("Compra realizada con exito\n");//PUESTO QUE EL ARREGLO EMPIEZA EN 0
                    break;
                }
                else 
                {
                    system("cls");
                    printf("Productos agotados o insuficientes \n");
                    printf("Productos disponibles: %d  \n",inventario[numProducto-1].unidades);
                    
                }
        }while(cantidad<=0||cantidad>inventario[numProducto-1].unidades);
    
}

void guardarFactura(int totalProductos) // Guarda una copia de la factura generada en el archivo de texto "tickets.txt", utilizando la función "fprintf()".
{

    FILE *archivoTickets =fopen("tickets.txt","a++");
    int i;
    float total,subtotal;
    fprintf(archivoTickets,"PRODUCTO - - - - CANTIDAD - - - PRECIO UNITARIO - - - - TOTAL ");
    for(i=1;i<=totalProductos;i++)
    {
        if(carrito[i].unidades>0)
        {
            total=carrito[i].unidades*carrito[i].precio;
            fprintf(archivoTickets,"\n");
            fprintf(archivoTickets,"%s",carrito[i].nombreProducto);
            fprintf(archivoTickets,"       ");
            fprintf(archivoTickets,"%d",carrito[i].unidades);
            fprintf(archivoTickets,"      ");
            fprintf(archivoTickets,"%.2f",carrito[i].precio);
            fprintf(archivoTickets,"     ");
            fprintf(archivoTickets,"%.2f",total);
            fprintf(archivoTickets,"\n");
        }
        subtotal += carrito[i].precio * carrito[i].unidades;
    }

    fprintf(archivoTickets,"SUBTOTAL: %.2f",subtotal);
    fprintf(archivoTickets,"\n");
    fprintf(archivoTickets,"TOTAL (IVA AGREGADO): %.2f",subtotal*1.16);

    printf("Ticket guardado correctamente el carrito se ha vaciado\n");
    fprintf(archivoTickets,"\n");
    fclose(archivoTickets);
}

int main ()
{
    int opcion;
    int bandera=0;
    char opcGuardarTicket[3];
    char opc[4];
    int productosEnCarrito=0;
    leerInventario();

    printf("\n..........B I E N V E N I D O  A  N U E S T R A  T I E N D A  D E  E Q U I P O  D E  C O M P U T O..........");
    do{
        opcion=menu();
        switch (opcion) 
        {
            case 1:
                strcpy(opc,"SI");
                while(strcmp(opc,"SI")==0){
                    bandera=1;
                    productosEnCarrito++;
                    realizarCompra(productosEnCarrito);  
                    fflush(stdin);
                    printf("\nDesea seguir comprando SI/NO: ");
                    gets(opc);
                    fflush(stdin);
                }
                
                break;
            case 2:
                if(bandera==1)
                {
                    generarFactura(productosEnCarrito,carrito);
                    printf("¿Deseas imprimir tu ticket? (El carrito se vaciara una vez realizado el proceso)\n");
                    printf("SI/NO\n");
                    fflush(stdin);
                    gets(opcGuardarTicket);
                    fflush(stdin);
                               
                    if(strcmp(opcGuardarTicket,"SI")==0)
                    {
                        guardarFactura(productosEnCarrito);
                        productosEnCarrito=0;
                        bandera=0;
                    }
                }
                else printf("NO HAY PRODUCTOS EN EL CARRITO, PRIMERO EFECTUA UNA COMPRA\n");      
                break;
            case 3:
                imprimirInventario();
                break;
            case 4:
                agregarProducto();
                break;
            case 5:
                printf("\n.............C E R R A N D O  T I E N D A.............");
                printf("\n.....G R A C I A S,  V U E L V A  P R O N T O  :)....."); 
                break;
            default:
                printf("Opcion invalida, intente de nuevo.\n");
                break;
        }
    }while (opcion != 5);
    
    subirInventario();
    return 0;
}


       