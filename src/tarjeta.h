#include "Tarjeta.h"

bool Tarjeta::begin() {
    if (!Tarjeta.begin()){
        return false;
    }
    return true;
}

//bool Tarjeta :: comprobar(){
//    
//}

void Tarjeta::abrir(filename){
    file = SD.open("filename",FILE_WRITE);
    if(!file){
        return false;
    }
    return true;
}

void Tarjeta :: writeData (string hora, string fecha, float pres, float temp){
    file.print(hora);
    file.print(";");
    file.print(fecha);
    file.print(";");
    file.print(pres);
    file.print(";");
    file.print(temp);
}
