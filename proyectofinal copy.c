#include <stdio.h>
#include <string.h>
//FALTA AGREGAR FUNCION PARA GUARDAR LOS TICKETS DE COMPRA EN ARCHIVO Y PARA LIMPIAR EL CARRITO UNA VEZ SE GUARDE EL TICKET
//FUNCIONES A AGREGAR SEGUIR CON LA FIUNCION DE COMPRA FALTA MOSTRAR LOS PRODUCTOS EN EL CARRITO SUMAR PRECIOS Y HACER EL WHILE DE SEUIR COMPRANDO
struct Producto
{   
    char nombreProducto[20];
    int unidades;
    float precio;
};
    
struct Producto carrito[15];
struct Producto inventario[7]={
    {"Teclado",10,200.00},
    {"Mouse",10,150.00},
    {"CPU", 10, 500},
    {"USB", 15, 10},
    {"Monitor", 5, 200},
    {"Impresora", 10, 100},
    {"Proyector", 10, 300}
    
};//ARRAY DE structs (productos en inventario )

void leerIventario(){
    FILE *archivoIventario = fopen("Inventario.txt","r");
}
void suburInventario(){
    
    FILE *archivoIventario =fopen("Inventario.txt","w");
    int i;
    for(i=0;i<7;i++)
    {
        fprintf(archivoIventario,"%s %d %.2f",inventario[i].nombreProducto,inventario[i].unidades,inventario[i].precio);
        fprintf(archivoIventario,"\n");
    }
    
    fclose(archivoIventario);
}

void imprimirInventario()
{
    int i;
    printf("INVENTARIO\n");
    for(i=0;i<7;i++)
    {
        printf("Numero de producto: %d\n",i+1);
        printf("Nombre: %s\n",inventario[i].nombreProducto);
        printf("Unidades: %d\n",inventario[i].unidades);
        printf("Precio: %f\n",inventario[i].precio);
        printf("\n");
    }
}

struct Producto comprarProducto(struct Producto productoAComprar,int cantidadCompra)
{
    productoAComprar.unidades=cantidadCompra;
    return productoAComprar;
}

int menu()
{
    int opcion ;

        printf("\n---MENU---\n");
        printf("1. Realizar compra de productos\n");
        printf("2. Generar factura\n");
        printf("3. Reporte\n");
        printf("4. Agregar productos\n");
        printf("5. Salir\n");
        printf("Ingrese una opcion: ");
        scanf("%d", &opcion);

    return opcion;
}

void generarFactura(int numProductos,struct Producto carrito[10])
{

    int i;
    float total,subtotal;
    subtotal=0;
    printf("\n");
        printf("PRODUCTO - - - - CANTIDAD - - - PRECIO UNITARIO - - - - TOTAL ");
    for(i=1;i<=numProductos;i++){
        total=carrito[i].unidades*carrito[i].precio;
        printf("\n");
        printf("%s",carrito[i].nombreProducto);
        printf("       ");
        printf("%d",carrito[i].unidades);
        printf("      ");
        printf("%.2f",carrito[i].precio);
        printf("     ");
        printf("%.2f",total);
        printf("\n");

        subtotal += carrito[i].precio * carrito[i].unidades;
    }
    printf("SUBTOTAL: %.2f",subtotal);
    printf("\n");
    printf("TOTAL (IVA AGREGADO): %.2f",subtotal*1.16);
    printf("\n");
    
}

void realizarCompra(int productosEnCarrito)
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
            if(inventario[numProducto-1].unidades==0){
                printf("PRODUCTO AGOTADO \n");
            }
        }
        while (numProducto<=0||numProducto>7 || inventario[numProducto-1].unidades==0);    

        do {
                printf("Ingresa la cantidad a comprar: \n");
                scanf("%d",&cantidad);
                 if (cantidad<=0)
                {
                    printf("ERROR VALOR ERRONEO \n");
                }              
                else if(inventario[numProducto-1].unidades>=cantidad){
                        inventario[numProducto-1].unidades-=cantidad;
                        
                        carrito[productosEnCarrito]=comprarProducto(inventario[numProducto-1],cantidad);
                        
                        printf("Compra realizada con exito\n");//PUESTO QUE EL ARREGLO EMPIEZA EN 0
                        break;
                }
                else {
                    printf("Productos agotados o insuficientes \n");
                    printf("Productos disponibles: %d  \n",inventario[numProducto-1].unidades);
                    
                }
        }while(cantidad<=0||cantidad>inventario[numProducto-1].unidades);
    
}
void limpiarCarrito(){

}
void guardarFactura(int totalProductos){

    FILE *archivoTickets =fopen("tickets.txt","a++");
    int i;
    float total,subtotal;
    fprintf(archivoTickets,"PRODUCTO - - - - CANTIDAD - - - PRECIO UNITARIO - - - - TOTAL ");
    for(i=1;i<=totalProductos;i++)
    {
        if(carrito[i].unidades>0){
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
int main (){
   int opcion;
   int bandera=0;
   char opcGuardarTicket[3];
   int continuar =0;
    char opc[4];
   int productosEnCarrito=0;
    do {
      opcion=menu();
     switch (opcion) {
            case 1:
                strcpy(opc,"SI");
                while(strcmp(opc,"SI")==0){
                    bandera=1;
                    productosEnCarrito++;
                    realizarCompra(productosEnCarrito);  
                    fflush(stdin);
                    printf("Desea seguir comprando SI/NO: ");
                    gets(opc);
                }
                
                break;
            case 2:
                if(bandera==1){
                generarFactura(productosEnCarrito,carrito);
                printf("DESEAS IMPRIMIR TU TICKET (El carrito se vaciara una vez realizado el proceso)\n");
                printf("SI/NO\n");
                fflush(stdin);
                gets(opcGuardarTicket);
                if(strcmp(opcGuardarTicket,"SI")==0){
                    guardarFactura(productosEnCarrito);
                    productosEnCarrito=0;
                    bandera=0;

                }}
                else printf("NO HAY PRDODUCTOS EN EL CARRITO PRIMERO EFECTUA UNA COMPRA\n");
                break;
            case 3:
                
                break;
            case 4:
            
                break;
            case 5:
                printf("Gracias vuelva pronto \n");
                break;
            default:
                printf("Opcion invalida, intente de nuevo.\n");
                break;
        }
    } while (opcion != 5);
    suburInventario();
    return 0;
}



       