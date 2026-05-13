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

DataSet::DataSet(int nInstances, int nLocations){
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

/**
 * @brief Comprueba instanceIndex para evitar errores.
 */
void DataSet::compruebaInstanceIndex(int instanceIndex) const{
    if(instanceIndex < 0 || instanceIndex >= _nInstances){
        throw std::out_of_range("DataSet::getValue instanceIndex invalido");
    }
}

/**
 * @brief Comprueba locationIndex para evitar errores.
 */
void DataSet::compruebaLocationIndex(int locationIndex) const{
    if(locationIndex < 0 || locationIndex >= _nLocations){
        throw std::out_of_range("DataSet::getvalue locationIndex invalido");
    }
}



/**
 * @brief Gets the number of instances in this DataSet
 * Query method
 * @return The number of instances in this DataSet
 */

int DataSet::getNumInstances() const{
    return _nInstances;
}

/**
 * @brief Gets the number of localizations in this DataSet
 * Query method
 * @return The number of localizations in this DataSet
 */

int DataSet::getNumLocations() const{
    return _nLocations;
}

/**
 * @brief Gets the value for the instance instanceIndex at the localization
 * locationIndex.
 * @throw Throws a std::out_of_range exception if instanceIndex is not 
 * a valid index for an instance in this DataSet.
 * @throw Throws a std::out_of_range exception if locationIndex is not a
 * valid index for an location in this DataSet.
 * Query method
 * @param instanceIndex An integer with the index of the selected instance. 
 * Input parameter
 * @param locationIndex An integer with the index of the selected location. 
 * Input parameter
 * @return The value for the instance instanceIndex at the localization
 * locationIndex
 */

int DataSet::getValue(int instanceIndex, int locationIndex) const{

    compruebaInstanceIndex(instanceIndex);

    compruebaLocationIndex(locationIndex);

    return _values[instanceIndex][locationIndex];
}

/**
 * @brief Gets the label (integer value) of the instance at the provided
 * position (instanceIndex)
 * @throw Throws a std::out_of_range exception if instanceIndex is not 
 * a valid index for an instance in this DataSet.
 * Query method
 * @param instanceIndex An integer with the index of the selected instance.
 * Input parameter
 * @return The label (integer value) of the instance at the provided
 * position
 */

int DataSet::getLabel(int instanceIndex) const{

    compruebaInstanceIndex(instanceIndex);

    return _labels.at(instanceIndex);
}

/**
 * @brief Gets a const reference to the vector of Location objects in this
 * DataSet
 * Query method
 * @return A const reference to the vector of Location objects in this
 * DataSet
 */

VectorLocation DataSet::getVectorLocation() const{
    return _locations;
}

/**
 * @brief Gets a const reference to the vector of labels in this DataSet
 * Query method
 * @return A const reference to the vector of labels in this DataSet
 */

VectorInt DataSet::getVectorLabels() const{
    return _labels;
}

/**
 * @brief Obtains a string with information about this DataSet object, 
 * in the following format:
 * -Information about the set of locations of this DataSet:
 *    - A line with the number of locations
 *    - For each location, a line with its information, converted to
 *      a string with the Location::toString() method.
 * - Information about the labels of each instance in this DataSet:
 *    - A line with the number of instances
 *    - A line with the labels (space separated) of the set of instances.
 * - Instances of the Dataset. This is the information contained in the 
 *   2D matrix of this DataSet.
 *     - For each instance, a line with the values (space separated) of 
 *       that instance.
 * Query method
 * @return string with information about this CrimeSet object
 */

std::string DataSet::toString() const {
    string result;
    
    result += _locations.toString();
    result += _labels.toString();

    for(int instance = 0; instance < getNumInstances(); instance++){

        for(int location=0; location<getNumLocations(); location++){

            result += to_string(_values[instance][location]);
            
            if(location < getNumLocations()-1){
                result += " ";
            }
        }
        result += "\n";
    }    

    return result;
}

/**
 * @brief Sets a new value for the instance instanceIndex at the 
 * localization locationIndex.
 * Modifier method
 * @param instanceIndex An integer with the index of the selected instance. 
 * Input parameter
 * @param locationIndex An integer with the index of the selected location. 
 * Input parameter
 * @param value An integer with the new value for the selected instance.
 * Input parameter
 */

void DataSet::setValue(int instanceIndex, int locationIndex, int value){
    
    compruebaInstanceIndex(instanceIndex);

    compruebaLocationIndex(locationIndex);

    _values[instanceIndex][locationIndex] = value;
}

/**
 * @brief Sets a new the label for the provided instance.
 * Modifier method
 * @param instanceIndex An integer with the index of the selected instance. 
 * Input parameter
 * @param label An integer with the new value for the label of the selected
 * instance.
 * Input parameter
 */

void DataSet::setLabel(int instanceIndex, int label){

    compruebaInstanceIndex(instanceIndex); 

    _labels.at(instanceIndex) = label;
}

/**
 * Assigns the provided value to each instance and location. That is, all 
 * instances of this DataSet are initialized with the provided value.
 * Modifier method
 * @param value An integer with the value to assign to every instance and
 * location
 * Input parameter
 */

void DataSet::initInstances(int value){
    for (int i = 0; i < _nInstances; i++){

        for(int j = 0; j < _nLocations; j++){

            _values[i][j] = value;
        }
    }
}

/**
 * @brief Removes all the information in this DataSet object:
 * - The vector of Location objects (_locations) is left empty. That is,
 * it should represent a vector with 0 locations.
 * - The vector of labels (_labels) is left empty. That is, it should 
 * represent a vector with 0 labels.
 * - The matrix (_values) with the values for each instance is left empty. 
 * That is, it should represent a matrix with 0 instances and 0 locations.
 * - The remaining fields of this object are updated accordingly.
 * Modifier method
 */
void DataSet::clear(){

    liberarMatriz();

    _nInstances = 0;
    _nLocations = 0;
    _labels.clear();
    _locations.clear();
}

/**
 * @brief Saves this DataSet object in the given file. See files *.dts in 
 * the folder DataSets as example of files with DataSet information. 
 * Note that the format of the output file is the same as the string that
 * returns the toString() method, except that the save() method should 
 * insert the magic string at the beginning of the output file.
 * @throw std::ios_base::failure Throws a std::ios_base::failure exception 
 * if the given file cannot be opened or if an error occurs while writing
 * to the file.
 * Query method
 * @param fileName The name of the file where the DataSet will be saved. 
 * Input parameter
 */
void DataSet::save(std::string fileName) const{
    
    ofstream file(fileName); //Abre el archivo en modo escritura (si no existe lo crea, si existe lo sobreescribe)

    if(!file){
        //si no se ha podido abrir (error de permisos, la carpeta no existe, etc; dispara error).
        throw std::ios_base::failure("DataSet::save no se puede abrir el archivo " + fileName);
    }

    file << MAGIC_STRING_T << "\n"; //escribe la primera línea (obligatoria para el archivo .dts)
    file << toString(); //escribe el resto del contenido del DataSet.

    if(!file){
        //comprueba si ha habido un error durante la escritura
        throw std::ios_base::failure("DataSet::save ERROR al escribir en el archivo " + fileName);
    }
}

/**
 * @brief Loads into this object the DataSet information stored in the 
 * given file. See files *.dts in the folder DataSets as example of files
 * with DataSet information. 
 * @note Note that this method should remove any previous information that
 * this object previously contained.
 * @note This method throws an exception in some error cases (see below). 
 * Before throwing the corresponding exception, this method clears
 * the object (it calls to clear() method) to leave the object in a 
 * consistent state.
 * @throw throw std::invalid_argument Throws a std::invalid_argument 
 * exception if an invalid magic string is found in the given file
 * @throw std::out_of_range Throws a std::out_of_range exception if the 
 * number of locations or the number of instances in the given file is 
 * negative.
 * Modifier method
 * @param fileName The name of the file where the DataSet is stored. 
 * Input parameter
 * @throw std::ios_base::failure Throws a std::ios_base::failure exception 
 * if the given file cannot be opened or if an error occurs while reading
 * from the file. 
 */
void DataSet::load(std::string fileName){
    clear();

    ifstream file(fileName); //abrir el archivo en MODO LECTURA

    if(!file){
        throw std::ios_base::failure("DataSet::load no se puede abrir el archivo " + fileName);
    }
    
    // Comprobamos la magic string
    string magic;
    getline(file, magic); //leemos la primera línea (tiene que ser = MAGIC_STRING_T)

    if (magic != MAGIC_STRING_T) {
        clear();
        throw std::invalid_argument("DataSet::load: magic string invalida en " + fileName);
    }
 
    // Leemos las localizaciones usando VectorLocation::load()
    _locations.load(file);
    _nLocations = _locations.getSize();
 
    // Leemos el número de instancias
    int n;
    file >> n;

    if (n < 0) { //comprobamos que el numero de instancias no sea negativo
        clear();
        throw std::out_of_range(
            "DataSet::load: numero de instancias negativo");
    }
    _nInstances = n;
 
    // Leemos las etiquetas
    _labels = VectorInt(_nInstances);

    for (int i = 0; i < _nInstances; i++) {
        int label;
        file >> label; //leemos una a una las etiquetas del archivo
        _labels.at(i) = label;
    }
 
    // Reservamos la matriz y rellenamos los valores
    reservarMatriz();

    for (int i = 0; i < _nInstances; i++)
        for (int j = 0; j < _nLocations; j++)
            file >> _values[i][j];
 
    if (!file)
        throw std::ios_base::failure(
            "DataSet::load: error al leer el fichero " + fileName);
}

/**
 * @brief Gets a new DataSet from this DataSet. The DataSet will contain 
 * the same number of instances as this DataSet, but the number of locations
 * is given by the number of clusters in the provided Clustering object.
 * Therefore, the returned DataSet will have a reduced number of columns 
 * and an equal number of rows compared to this DataSet. 
 * The provided Clustering object defines how to reduce the set of columns.
 * Column 0 will contain the sum of the columns of this DataSet belonging 
 * to cluster 0, column 1 the sum of the columns belonging to cluster 1, 
 * and so on.
 * The vector of locations will be a copy of the vector of centroids of the
 * provided Clustering object.
 * The vector of labels will be a copy of the vector of labels in this 
 * DataSet.
 * @throw throw std::invalid_argument Throws a std::invalid_argument 
 * exception if the method Clustering::isDone() return false with the 
 * provided Clustering object.
 * @throw throw std::invalid_argument Throws a std::invalid_argument 
 * exception if the number of locations in the provided Clustering object
 * is not equal to the number of locations in this DataSet.
 * Query method
 * @param clustering A Clustering object.
 * Input parameter
 * @return A reduced DataSet
 */
DataSet DataSet::getReducedDataSet(Clustering clustering) const{
    //comprobamos que clustering ya haya sido ejecutado.
    if (clustering.isDone() == false){
        throw std::invalid_argument("getReducedDataSet: el clustering no ha sido ejecutado");
    }

    //comprobamos que el numero de localizaciones de Clustering coincida con el del DataSet.
    if (clustering.getNumLocations() != _nLocations){
        throw std::invalid_argument("getReducedDataSet: numero de localizaciones incompatible");
    }

    /** PASOS.
     * 1. Creamos un dsR con _nInstances filas y K columnas, todo a 0.
     * 2. Localizaciones de dsR = centroides del Clustering.
     * 3. Etiquetas de dsR = etiquetas de DataSet.
     * 4. Para cada columna col de este DataSet:
     *    clusterNum = cluster al que pertenece la localizacion col
     *    Para cada fila fil:
     *    dsR[fil][clusterNum] += this[fil][col]
     */

    //Paso 1.
    int K = clustering.getK();
    DataSet dataset_reducido(_nInstances, K);

    //Paso 2.
    dataset_reducido._locations = clustering.getCentroids();

    //Paso 3.
    dataset_reducido._labels = _labels;

    //Paso 4.
    for (int col = 0; col < _nLocations; col++){
        int clusterNum = clustering.clusterOf(col);

        for (int fil = 0; fil < _nInstances; fil++){
            dataset_reducido._values[fil][clusterNum] += _values[fil][col];
        }
    }

    return dataset_reducido;
}