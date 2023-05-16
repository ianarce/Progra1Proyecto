#include <stdio.h>
#include <string.h>
//POR HACER 
//AGRGAR MAS PRODUCTOS
//AGREGAR FUNCION DE COMPRA PARA CADA SECCION
//AGREGAR FUNCION PARA ACTUALIZAR EL INVENTARUI Y AGREGAR PRODUCTOS
struct Producto
{
    char nombre[30];
    int unidades;
    float precio;
};

struct Producto teclados[20];
struct Producto mouses[30];
struct Producto carrito[10];

int menu(){
    int opcion;
    printf("Escoga la opcion \n");
    printf("1.Comprar\n");
    printf("2.Agregar\n");

    scanf("%d",&opcion);
    return opcion;
}

void mostrarProductos1(struct Producto producto){
    printf("Nombre: %s\n",producto.nombre);
    printf("Unidades Disponibles: %d\n",producto.unidades);
    printf("Precio: %.2f\n",producto.precio);
    printf("\n");
}

//FUNCION QUE RESTA LAS UNIDADES DEL PRODUCTO COMPRADO Y REGRESA UN NUEVO PRODUCTO CON LAS UNIDADES RESTADAS
struct Producto comprar(struct Producto producto,int unidades){
            producto.unidades=unidades;
     
            return producto;
}

void eliminar(int indice){
    strcpy(carrito[indice].nombre,"");
    carrito[indice].unidades=0;
    carrito[indice].precio=0;
}

//FUNICON PARA COMPRAR Y VERIFICAR SI HAY UNIDADES DISPONIBLES
//LA VARIABLES prodcutosEnCarrito es el numero de producto que se ha comprado y que aumenta cada vez que compramos un nuevo producto
void realizarCompra(int productosEnCarrito){
    int productoCom,unidadesCompra,i;
            printf("Ingresa el numero de producto a comprar: ");
            scanf("%d",&productoCom);
            printf("Ingresa las unidades a comprar");
            scanf("%d",&unidadesCompra);

            if(teclados[productoCom].unidades>=unidadesCompra){
                
                carrito[productosEnCarrito]=comprar(teclados[productoCom],unidadesCompra);
                teclados[productoCom].unidades=teclados[productoCom].unidades-unidadesCompra;
            }

            else printf("No se cuenta con unidades suficientes");
            
}

//FUNCION QUE MUESTRA EL CARRITO O TICKERT DE COMPRA
void mostrarCarrito(struct Producto *carrito,int productosComprados){
    int i,j,nuevaUnidad,indice;
    //VERIFICAR SI HAY PRODUCTOS REPETIDOS
        if(productosComprados==2){ 
                    i=0;
                    indice=i+1;
                    if (strcmp(carrito[i].nombre,carrito[indice].nombre)==0){
                        nuevaUnidad=carrito[i].unidades+carrito[indice].unidades;
                        carrito[i].unidades=nuevaUnidad;
                        eliminar(indice);
                    }
                    
                }
            if(productosComprados>2){
                for(i=0;i<productosComprados;i++){
                    for(indice=i+1;indice<productosComprados;indice++){
                        if (strcmp(carrito[i].nombre,carrito[indice].nombre)==0){
                        nuevaUnidad=carrito[i].unidades+carrito[indice].unidades;
                        carrito[i].unidades=nuevaUnidad;
                        eliminar(indice);
                    }
                    
                    }
                }
            }
    printf("\nPRODUCTO     CANTIDAD  PRECIO    UNITARIO  TOTAL");
    
    for(i=0;i<productosComprados;i++){
        if(carrito[i].unidades!=0){
            float total=carrito[i].unidades*carrito[i].precio;
            printf("\n");
            printf("%s     %d              %.2f     %.2f",carrito[i].nombre,carrito[i].unidades,carrito[i].precio,total);
            printf("\n");
        }
    }
}


void menuCompras(){
    int opcion,i,productosEnCarrito;
    char opc [3];
    productosEnCarrito=0;
    int continuar=1;

    
    while (continuar==1)
    {
        printf("Escoga la categoria \n");
        printf("1.Teclados\n");
        printf("2.Mouses\n");

        scanf("%d",&opcion);
        
    

        switch (opcion)
        {
        case 1:
            for(i=0;i<3;i++){
                printf("Numero Producto: %d \n",i);
                mostrarProductos1(teclados[i]);
            }
            realizarCompra(productosEnCarrito);
            productosEnCarrito++;
            break;
        case 2:
            for(i=0;i<2;i++){
                printf("Numero Producto: %d \n",i);
                mostrarProductos1(mouses[i]);
            }realizarCompra(productosEnCarrito);
            productosEnCarrito++;
            break;

        case 3:
            break;
        default:
            printf("Ingresa una opcion correcta");
            
        }

         printf("Desea seguir comprando SI/NO: ");
            fflush(stdin);
            gets(opc);
            if( (strcmp(opc,"NO")==0))continuar=0;
    }
    
    mostrarCarrito(carrito,productosEnCarrito);
    
}

//CREAR UNA BASE DE DATOS EN TEXTO PARA LOS PRODUCTOS

int main(){
    int i;
    
    strcpy(teclados[0].nombre,"teclado 1");
    teclados[0].unidades=3;
    teclados[0].precio=200;
    //Cacular el tamaño del arreglo


    strcpy(teclados[1].nombre,"teclado 2");
    teclados[1].unidades=5;
    teclados[1].precio=400;

    
    strcpy(teclados[2].nombre,"teclado 3");
    teclados[2].unidades=5;
    teclados[2].precio=200;

    strcpy(mouses[1].nombre,"mouse 2");
    mouses[1].unidades=3;
    mouses[1].precio=220;
    
    strcpy(mouses[0].nombre,"mouse 1");
    mouses[0].unidades=3;
    mouses[0].precio=120;

   int opc=menu();
    switch (opc)
    {
    case 1:
        menuCompras();
        main();
        break;
    case 2:
        break;
    case 3:
        break;
    }

    return 0;
}