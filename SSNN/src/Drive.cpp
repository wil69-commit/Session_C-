#include <iostream>
#include <windows.h>
#include <filesystem>
#include <fstream>
#include <string>
#include "Drive.h"
#include<vector>
using namespace std;
namespace fs = std::filesystem;
Drive::Drive()
{

}

Drive::detect(){

}

Drive::~Drive()
{
    wait();
}

    string allDrives;

char Drive::getUsb(){
    char usb = '0';
    char sizeLocalDrive[MAX_PATH];
    DWORD dResult = GetLogicalDriveStrings(MAX_PATH, sizeLocalDrive);
    string currentUsb = "";
    for(int i = 0; i < dResult; i++){
        if(sizeLocalDrive[i] > 64 && sizeLocalDrive[i] < 90){
            currentUsb.append(1, sizeLocalDrive[i]);
            if(allDrives.find(sizeLocalDrive[i]) > 100){
                usb = sizeLocalDrive[i];
            }
        }
    }
    allDrives = currentUsb;

    return usb;
}

void Drive::wait(){
    char usbLetter = getUsb();

    while(true){
        usbLetter = getUsb();
        if(usbLetter != '0'){
            printf("%c\n ", usbLetter);
            sync(usbLetter);
            Sleep(1000);
        }
    }
}

void Drive::sync(char usb){// on a une methode sync qui recuperer le nom de la cle et fi
    string filename(1, usb);

    filename += ":\\keyce_drive";
    cout << filename;
    cout<<filename<<endl;
    if(filesystem::is_directory(filename)){ // filesystem::is_directory nous permet de lister les fichiers present dans un repertoire en donnant (filename) on recherche un fichier precis
        for(const auto & dir_entry : fs::recursive_directory_iterator(filename)){
//            cout << entry.path() << endl;
            kCopy(dir_entry.path().string(), dir_entry.path().filename().string());
        }
    }
}

void Drive::kCopy(string file, string name){
    cout << file;
    ofstream ofile ("C:\\Users\\Wil\\Desktop\\keyce\\"+ name, std::ios_base::binary);//on se dirige ves l'emplacement
    ifstream sfile (file, std::ios_base::binary);// on recupaire le fichier avec le nom qu'on a donner et on le convertie en binaire
    char buffer[1024];// en 64 bit
    while(sfile.read(buffer, sizeof(buffer))){//w
        ofile.write(buffer, sfile.gcount());
    }
//    ofile.write(buffer, sfile.gcount());

    ofile.close();
    sfile.close();
}
