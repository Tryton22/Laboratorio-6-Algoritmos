#include <iostream>
#include <chrono>
#include <unistd.h>

using namespace std;
using namespace std::chrono;

//mezcla dos subarreglos de arreglo[].
//primero subareglo es arr[begin.med]
//segundo subarreglo es arr[med+1.end]
void fusion(int arr[], int const izq, int const med,
           int const der)
{
    auto const sub_arr1 = med - izq + 1;
    auto const sub_arr2 = der - med;
 
    //creacion arrs temp
    auto *izqarr = new int[sub_arr1],
         *derarr = new int[sub_arr2];
 
    //copiar data de arrs temp izqarr[] and derarr[]
    for (auto i = 0; i < sub_arr1; i++)
        izqarr[i] = arr[izq + i];
    for (auto j = 0; j < sub_arr2; j++)
        derarr[j] = arr[med + 1 + j];
 
    auto indice_sub_arr1
        = 0, // indice inicial de primer sub arreglo
        indice_sub_arr2
        = 0; // idnice inicial de segundo sub arreglo
    int indice_arr_merge
        = izq; // indice inicial de arreglo por mezcla merge
 
    //mezcla arrs temp vuelta a arr[izq..der]
    while (indice_sub_arr1 < sub_arr1
           && indice_sub_arr2 < sub_arr2) {
        if (izqarr[indice_sub_arr1]
            <= derarr[indice_sub_arr2]) {
            arr[indice_arr_merge]
                = izqarr[indice_sub_arr1];
            indice_sub_arr1++;
        }
        else {
            arr[indice_arr_merge]
                = derarr[indice_sub_arr2];
            indice_sub_arr2++;
        }
        indice_arr_merge++;
    }
    //copia los elementos restantes de iqz[], si existen
    while (indice_sub_arr1 < sub_arr1) {
        arr[indice_arr_merge]
            = izqarr[indice_sub_arr1];
        indice_sub_arr1++;
        indice_arr_merge++;
    }
    //copia los elementos restantes de der[], si existen
    while (indice_sub_arr2 < sub_arr2) {
        arr[indice_arr_merge]
            = derarr[indice_sub_arr2];
        indice_sub_arr2++;
        indice_arr_merge++;
    }
    delete[] izqarr;
    delete[] derarr;
}
 

//comienza es por indice izq y termino es en indice der
//de el sub arreglo del arreglo a ser ordendo
void OrdenamientoFusion(int arr[], int const begin, int const end)
{
    if (begin >= end)
        return; // Returns recursively
 
    auto med = begin + (end - begin) / 2;
    OrdenamientoFusion(arr, begin, med);
    OrdenamientoFusion(arr, med + 1, end);
    fusion(arr, begin, med, end);
}

//funcion para implementar algoritmo de ordenamiento burbuja
void OrdenamientoBurbuja(int arr[], int n)
{
    int i, j;
    for (i = 0; i < n - 1; i++)
 
        // Last i elements are already
        // in place
        for (j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
}
 
//funcion que imprime arreglo
void ImprimirArreglo(int arr[], int size)
{
    int i;
    for (i = 0; i < size; i++)
        cout << arr[i] << " ";
    cout << endl;
}


int main(){
	
    int i, n, V_max;
    cout<<"Ingrese cantidad de elementos en arreglo: ";
    cin>>n;
    cout<<"Ingrese valor maximo (entero) posible de elemento en arreglo: ";
    cin>>V_max;
	srand(time(NULL));
	//inicializa arr con valores ordenados modo ascendente
	int arr[n];
    //V_max=10000;
    //size arr
    int N = sizeof(arr) / sizeof(arr[0]);
    //se asignan valores aleatorrios a elementos arreglo
    cout<<"valor de elementos han sido asignados de manera aleatoria en arreglo."<<endl;
    for (i=0; i<N; i++)
        arr[i]=rand()%(V_max);

    int x;
    cout<<"MENU"<<endl;
    cout<<"1.Mostrar datos de arreglo original sin ordenar."<<endl;
    cout<<"2.Mostrar datos del arreglo ordenado mediante algoritmo burbuja."<<endl;
    cout<<"3.Mostrar datos del arreglo ordenado mediante algoritmo por mezcla (merge)."<<endl;
    cout<<"4.Mostrar el tiempo de ejecución en milisegundos de los algoritmos."<<endl;
    cout<<"5.salir"<<endl;
    cin>>x;
    switch (x) {
    case 1:
        ImprimirArreglo(arr,N);
        break;
    case 2:
        OrdenamientoBurbuja(arr, N);
        cout << "algoritmo burbuja: \n";
        ImprimirArreglo(arr, N);
        break;
    case 3:
        OrdenamientoFusion(arr, 0, N - 1);
        cout << "algoritmo OrdenamientoFusion: \n";
        ImprimirArreglo(arr, N);
        break;
    case 4:{
        //obtener punto de tiempo de inicio
        auto inicio = high_resolution_clock::now();
        //llama a funcion, ordenamiento burbuja
        OrdenamientoBurbuja(arr, N);
        cout << "algoritmo burbuja: \n";
        ImprimirArreglo(arr, N);
        //obtener punto de tiempo de termino
        auto fin = high_resolution_clock::now();
        //obtener duración.
        auto duracion = duration_cast<milliseconds>(fin - inicio);
        cout << "Tiempo tomado por algoritmo ordenamiento burbuja : "
            << duracion.count() << " milisegundos" << endl;
        //misma estrcutura pero en ordenaiento merge
        cout<<endl;
        sleep(3);
        auto inicio2 = high_resolution_clock::now();
        OrdenamientoFusion(arr, 0, N - 1);
        cout << "algoritmo OrdenamientoFusion: \n";
        ImprimirArreglo(arr, N);
        auto fin2 = high_resolution_clock::now();
        auto duracion2 = duration_cast<milliseconds>(fin2 - inicio2);
        cout << "Tiempo tomado por algoritmo ordenamiento por mezcla (merge): "
         << duracion2.count() << " milisegundos" << endl;
        }break;
    case 5:
        return 0;
        break;
    default:
        cout << "Error. Eleccion incompatible.";
        break;
    }
    return 0;
    
};