/*
 * Metodología de la Programación
 * Curso 2025/2026
 */

/**
 * @file DataSet.cpp
 * @author Silvia Acid Carrillo <acid@decsai.ugr.es>
 * @author Andrés Cano Utrera <acu@decsai.ugr.es>
 * @author Luis Castillo Vidal <L.Castillo@decsai.ugr.es>
 * 
 * Created on 30 de julio de 2025, 10:00
 */

#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>

#include "DataSet.h"

using namespace std;

const string DataSet::MAGIC_STRING_T = "MP-FRAUD_DATASET-T-1.0";

//--------------------- Metodos privados de gestion de memoria: ---------------------

/**
 * @brief Reserva la matriz dinámica 2D con _nInstances filas y _nLocations
 * columnas. Todos los valores se inicializan a 0. _nInstances y _nLocations ya deben
 * estar fijados.
 */

void DataSet::reservarMatriz(){
    if(_nInstances > 0 && _nLocations > 0){

        _values = new int*[_nInstances]; //Primer nivel de la matriz: reserva un array de punteros.

        for(int i = 0; i < _nInstances; i++){
            _values[i] = new int[_nLocations]; //Segundo nivel de la matriz: para cada fila, reserva un array de enteros.

            for(int j = 0; j < _nLocations; j++){
                _values[i][j] = 0;
            }
        }
    }

    else{
        _values = nullptr;
    }
}

/**
 * @brief Libera la memoria dinamica de la matriz 2D. Establece _values = nullptr.
 */

void DataSet::liberarMatriz(){
    
    for (int i = 0; i < _nInstances; i++){
        delete[] _values[i];
    }

    delete[] _values;
    _values = nullptr;
}

/**
 * @brief Copia la matriz 2D original en otra. Se asume que el tamaño de memoria
 * reservada ya es el adecuado.
 */

void DataSet::copiarMatriz(const DataSet& matriz_orig){
    
    for (int i = 0; i < _nInstances; i++){

        for (int j = 0; j < _nLocations; j++){

            _values[i][j] = matriz_orig._values[i][j];
        }
    }
}

//--------------------- Constructores, Destructor, Operador de Asignacion: ---------------------

/**
     * @brief It builds a DataSet object with the provided number of instances
     * and number of locations. This class uses a bidimensional matrix with 
     * nInstances rows and nLocations columns to store the values of the set 
     * of instances.
     * Note that this constructor also builds the vector (with a size equal to 
     * nInstances) of labels and the vector of locations (with a size equal to 
     * nLocations).
     * This constructor initializes with a value of 0 all the values in the 2D
     * matrix. 
     * The vector of labels is initialized with a value of 0 for each instance.
     * The Location objects in the vector of locations are built with the 
     * Location default constructor.
     * @param nInstances An integer with the number of instances.
     * Input parameter
     * @param nLocations An integer with the number of locations.
     * Input parameter
     */
    DataSet::DataSet(int nInstances = 0, int nLocations = 0){
        //inicializamos variables:
        _nInstances = nInstances;
        _nLocations = nLocations;
        _labels = nInstances;
        _locations = nLocations;

        //reservamos la matriz en memoria dinamica:
        reservarMatriz();
    }
    
    /**
     * @brief Copy constructor
     * @param orig the DataSet object used as source for the copy. 
     * Input parameter
     */
    DataSet::DataSet(const DataSet& orig){
        _nInstances = orig._nInstances;
        _nLocations = orig._nLocations;
        _labels = orig._labels;
        _locations = orig._locations;

        reservarMatriz();

        copiarMatriz(orig);
    }
    
    /**
     * @brief Destructor
     */
    DataSet::~DataSet(){
        liberarMatriz();
    }
    
    /**
     * @brief Overloading of the assignment operator for DataSet class
     * Modifier method
     * @param orig the DataSet object used as source for the assignment.
     * Input parameter
     * @return A reference to this object
     */
    DataSet& DataSet::operator=(const DataSet& orig){
        
        if (this != &orig){
            liberarMatriz();

            _nInstances = orig._nInstances;
            _nLocations = orig._nLocations;
            _labels     = orig._labels;
            _locations  = orig._locations;

            reservarMatriz();
            copiarMatriz(orig);
    }
    return *this;
}

//------------------------------------------------------------------------------------

std::string DataSet::toString() const {
    string result;
    
    result += _locations.toString();
    result += _labels.toString();
    for(int instance=0; instance<getNumInstances(); instance++){
        for(int location=0; location<getNumLocations(); location++){
            result += to_string((*this)(instance,location));
            if(location<getNumLocations()-1){
                result += " ";
            }
        }
        result += "\n";
    }    
    return result;
}
