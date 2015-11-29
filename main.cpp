#include <iostream>
#include <math.h>
using namespace std;

class Nodo {
private:

    char operador;
    Nodo *izdo, *dcho;
public:
    int valor;
    Nodo(int valor=NULL,char operador=NULL, Nodo* izdo=NULL,Nodo *dcho = NULL)
    {
        this->dcho=dcho;
        this->izdo=izdo;
        this->valor=valor;
        this->operador=operador;
    }
    friend class ArbolBinario;
};

class ArbolBinario{
private:
    Nodo *raiz;
public:
    ArbolBinario(Nodo *r=NULL){
        raiz = r;
    }

    void Praiz( Nodo *r){
        raiz = r;
    }

    Nodo * Oraiz(){
        return raiz;
    }

    Nodo raizArbol(){
        if(raiz)
            return *raiz;
        else
            throw " arbol vacio";
    }

    bool esVacio(){
        return (raiz == NULL);
        }

    Nodo * hijoIzdo(){
        if(raiz)
            return raiz->izdo;
        else
            throw " arbol vacio";
    }

    Nodo * hijoDcho(){
    if(raiz)
        return raiz->dcho;
    else
        throw " arbol vacio";
    }

    Nodo* nuevoArbol(int dato,char operador, Nodo* ramaIzqda, Nodo* ramaDrcha){
        return new Nodo(dato, operador, ramaIzqda, ramaDrcha);
    }

    //preorden
    void preorden(Nodo *r){
        if (r != NULL){
            cout<<r->valor;
            preorden (r->izdo);
            preorden (r->dcho);
        }
    }
    //inorden
    void inorden(Nodo *r){
        if (r != NULL){
            inorden (r->izdo);
            cout<<r->valor;
            inorden (r->dcho);
        }
    }
    //posorden
    void postorden(Nodo *r){
        if (r != NULL){
            postorden (r->izdo);
            postorden (r->dcho);
            cout<<r->valor;
        }
    }

    //vaciar arbol
    void vaciar(Nodo *r){
        if (r != NULL){
            vaciar(r->izdo);
            vaciar(r->dcho);
            cout << "\tNodo borrado. ";
            r = NULL;
        }
    }

    //altura de un nodo
    int altura(Nodo *raiz){
        if (raiz == NULL)
            return 0 ;
        else{
            int alturaIz = altura (raiz->izdo);
            int alturaDr = altura (raiz->dcho);
        if (alturaIz > alturaDr)
            return alturaIz + 1;
        else
            return alturaDr + 1;
        }
    }
    //arbol lleno
    bool arbolLleno(Nodo *raiz){
        if (raiz == NULL)
            return true;
        else
        if (altura(raiz->izdo)!=altura(raiz->dcho))
            return false;
    }
    //cantidad de nodos
    int numNodos(Nodo *raiz){
        if (raiz == NULL)
            return 0;
        else
    return 1 + numNodos(raiz->izdo) + numNodos(raiz->dcho);
    }

    Nodo* copiaArbol(){
        Nodo *raizCopia;
        if (this->raiz == NULL)
            raizCopia = NULL;
        else{
            Nodo* izdoCopia, *dchoCopia;
            izdoCopia = this->raiz->izdo;
            dchoCopia = this->raiz->dcho;
            raizCopia = new Nodo(this->raiz->valor,this->raiz->operador, izdoCopia, dchoCopia);
        }
        return raizCopia;
    }

  //arbol de exprecion modifique el contructor de nodos agregando un tipo char el cual tomara el carcater
   double evaluar(ArbolBinario a, double operandos[]){
    double x, y;
    char ch ;
    Nodo *raiz;
    raiz = a.Oraiz();
    if (raiz != NULL){
        ch = raiz->operador;
        if (ch >= 'A' && ch <= 'Z')
            return operandos[ch - 'A'];
        else{
            x = evaluar(raiz->izdo, operandos);
            y = evaluar(raiz->dcho, operandos);
            switch (ch) {
            case '+': return x + y;
            break;
            case '-': return x - y;
            break;
            case '*': return x * y;
            break;
            case '/': if (y != 0)
            return x/y;
            else
            throw "Error: división por 0";
            break;
            case '^': return pow(x, y);
            }
            }
        }
    }

    //arbol de busqueda bueno sus funsiones de busqueda

    Nodo* buscar(Nodo* raizSub, int buscado){
    if (raizSub == NULL)
        return NULL;
    else if (buscado == raizSub->valor)
        return raizSub;
    else if (buscado < raizSub->valor)
        return buscar(raizSub->izdo, buscado);
    else
        return buscar (raizSub->dcho, buscado);
    }

    Nodo* buscarIterativo (int buscado){
    int dato;
    bool encontrado = false;
    Nodo* raizSub = raiz;
    dato = buscado;
    while (!encontrado && raizSub != NULL){
        if (dato == raizSub->valor)
            encontrado = true;
        else if (dato < raizSub->valor)
            raizSub = raizSub->izdo;
        else
            raizSub = raizSub->dcho;
    }
    return raizSub;
    }

    Nodo* insertar(Nodo* raizSub,int dato){
    if (raizSub == NULL)
        raizSub = new Nodo(dato,NULL,NULL,NULL);
    else if (dato < raizSub->valor){
        Nodo *iz;
        iz = insertar(raizSub->izdo, dato);
        raizSub->izdo=iz;
    }
    else if (dato > raizSub->valor){
        Nodo *dr;
        dr = insertar(raizSub->dcho, dato);
        raizSub->dcho=dr;
    }
    else
        throw "Nodo duplicado"; // tratamiento de repetición
        return raizSub;
    }


    Nodo* eliminar (Nodo *raizSub, int dato){
    if (raizSub == NULL)
        throw "No se ha encontrado el nodo con la clave";
    else if (dato < raizSub->valor){
        Nodo* iz;
        iz = eliminar(raizSub->izdo, dato);
        raizSub->izdo=iz;
    }
    else if (dato > raizSub->valor)
    {
    Nodo *dr;
    dr = eliminar(raizSub->dcho, dato);
    raizSub->dcho=dr;
    }
    else
    // Nodo encontrado
    {
    Nodo *q;
    q = raizSub;
    // nodo a quitar del árbol
    if (q->izdo == NULL)
    raizSub = q->dcho;
    // figura 16.30
    else if (q->dcho == NULL)
    raizSub = q->izdo;
    // figura 16.31
    else
    {
    // tiene rama izquierda y derecha
    q = reemplazar(q);
    //figura 16.32
    }
    q = NULL;
    }
    return raizSub;
    }

    Nodo* reemplazar(Nodo* act){
    Nodo *a, *p;
    p = act;
    a = act->izdo;
    // rama de nodos menores
    while (a->dcho != NULL)
    {
    p = a;
    a = a->dcho;
    }
    // copia en act el valor del nodo apuntado por a
    act->valor=a->valor;
    if (p == act) // a es el hijo izquierdo de act
    p->izdo=a->izdo; // enlaza subarbol izquierdo. Fig. 16.32b
    else
    p->dcho=a->izdo; // se enlaza subarbol derecho. Fig. 16.32a
    return a;
    }
};

int main(){
    ArbolBinario a1,a2,a3, a4,a,copia;
    Nodo * n1,*n2,*n3, *n4,*n5;

    n1 = a1.nuevoArbol(4,NULL, NULL,NULL);
    n2 = a2.nuevoArbol(5,NULL,NULL,NULL);
    n3 = a3.nuevoArbol(2,NULL,n1,n2);
    n1 = a1.nuevoArbol(6,NULL,NULL,NULL);
    n2 = a2.nuevoArbol(7,NULL,NULL,NULL);
    n4 = a4.nuevoArbol(3,NULL,n1,n2);
    n1 = a1.nuevoArbol(1,NULL,n3,n4);
    a.Praiz(n1);
    //metodos de busqueda
    n5=a.buscar(a.Oraiz(),3);
    cout<<n5->valor<<"existe\n";
    n5=a.buscarIterativo(3);
    cout<<n5->valor<<"existe\n";
    //funcion insertar
    a.insertar(a.Oraiz(),8);
    //el mismo nodo lo elimina asi que no aparece
    a.eliminar(a.Oraiz(),8);
    //
    a.preorden(a.Oraiz());
    cout<<" Preorden "<<endl;
    a.inorden(a.Oraiz());
    cout<<" Inorden"<<endl;
    a.postorden(a.Oraiz());
    cout<<" Posoden"<<endl;
    cout<<a.altura(a.Oraiz())<<" Altura\n";
    cout<<a.arbolLleno(a.Oraiz())<<" Lleno 1=true 0=false\n";
    cout<<a.numNodos(a.Oraiz())<<" Numero Nodos\n";
    copia=a.copiaArbol();
    cout<<"copiado lanza el preOrden como prueba\n";
    copia.preorden(copia.Oraiz());

}

