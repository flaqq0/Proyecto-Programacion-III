# Proyecto Final - Programacion-III
Proyecto final del curso de Programación III de la Universidad de Ingeniería y Tecnología (UTEC)

## Integrantes:
- Flavia Honores (202310550)
- Sofia Ku (202310476)
- Breysi Salazar (202310648)
- Renato García (202310495)

## Presentación
Link del video: https://drive.google.com/drive/folders/1PE1XXt9ZP8l9jOIuMQm87TujKp4--Bus?usp=sharing
Para poder visualizar la parte gráfica del proyecto, se debe runear el main y una vez esté funcionando, ingresar a http://localhost:8080/

## Descripción del Proyecto
El proyecto consiste en desarrollar una plataforma de streaming que permita la búsqueda y visualización de películas. El programa lee la base de datos indicada en formato .csv, esta se encuentra almacenada en un vector (vector<Movie>), una estructura de datos eficiente para la búsqueda rápida y permite buscar películas por palabras clave o tags específicos. La plataforma muestra las cinco películas más relevantes y proporciona opciones para visualizar más coincidencias.

## Diagrama 
```
    Inicio
      |
      v
Obtener instancia de MovieSearchEngine
      |
      v
Cargar películas desde archivo CSV (con función loadMovies)
      |
      v
Añadir estrategias de búsqueda (addStrategy)
      |
      v
Realizar búsqueda (search)
      |                                   |                                |
      v                                   v                                v
Ejecutar TitleSearch (hilo)       Ejecutar TagSearch (hilo)      Ejecutar PlotSearch (hilo)
      |
      v
Combinar resultados de búsqueda (bloqueo mutex)
      |
      v
Eliminar duplicados y ordenar resultados
      |
      v
Mostrar resultados al usuario
      |
      v
     Fin
```
 
## Estructura
A continuación detallaremos los contenidos de las carpetas principales creadas con un fin organizacional.

- Directorio External:
  Contiene bibliotecas externas que el proyecto utiliza. Estas bibliotecas provienen de un repositorio externo (https://github.com/yhirose/cpp-httplib) integrado en el proyecto, proporcionando funcionalidades necesarias adicionales.
    1. Librería "crow": Se utiliza en el archivo main.cpp para configurar un servidor web y define rutas HTTP para manejar solicitudes y responder con datos o archivos. En un principio define una ruta incial que devuelve un mensaje simple, después define una ruta que devuelve datos en formato JSON e inicia el servidor en el puerto 8080.
    2. Librería "cpp-httplib": Se utiliza en el archivo main.cpp para realizar solicitudes HTTP como cliente y permite hacer peticiones GET a servidores externos y procesar las respuestas. En main crea un cliente HTTP para realizar solicitudes a un servidor externo, ejecuta una solicitud GET y si la solicitud se lleva de forma exitosa, devuelve el cuerpo de la respuesta, de lo contrario, devuelve un error de tipo 500.
    3. Librería "nlohmann::json": Se utiliza en el archivo main.cpp para manejar datos en formato JSON. En main crea un objeto JSON y se convierte en una cadena para devolverlo como respuesta en la ruta /data.

- Directorio logOrRegis:
Incluye archivos relacionados con la gestión de usuarios (Autenticación). Específicamente, contiene los archivos Planes.cpp y Planes.h estos representan diferentes planes de suscripción que un usuario puede tener. Usuario.cpp y Usuario.h representa a los usuarios del sistema y maneja su información personal y de autenticación. Por ello, el directorio otorga las funciones necesarias para el registro, autenticación y administración de planes de suscripción.

- ....Prueba.....

- Directorio web:
Contiene los archivos relacionados con la interfaz web del proyecto. Estos archivos incluyen HTML, CSS y JavaScript para crear y estilizar una plataforma intuituva, así como manejar la lógica del lado del cliente para la autenticación y el registro de usuarios. Contiene un subdirectorio "auth" en el cual hay archivos específicos para las páginas de autenticación y registro.

- Demás archivos:
  1. ALL.h: Centraliza la inclusión de cabeceras y la inicialización de datos y objetos esenciales. Define y carga los datos de las películas desde un archivo CSV, haciendo que estos estén disponibles para el resto del proyecto. Configura las suscripciones inciando los objetos que representan diferentes planes de suscripción, permitiendo su uso en cualquier parte del proyecto sin necesidad de re-inicializarlos.
  2. cleanData.h y cleanData.cpp: Contienen en si la lógica para limpiar y procesar datos. Crea la clase "CMovie" la cual representa un formato para almacenar la información de una película. Crea la función "loadCsv" usada para cargar datos de películas desde un archivo CSV y devolver un vector de objetos CMovie. 
  3. CMakeLists.txt: Archivo de configuración de CMake que define cómo debe construirse el proyecto.
  4. librerias.h: Archivo de cabecera que incluye las bibliotecas externas utilizadas en el proyecto.
  5. main.cpp: Archivo principal del programa que contiene la configuración del servidor web.
  6. peliculas.csv: Es nuestro archivo de datos que contiene información de las películas en formato CSV, utilizado para cargar y procesar los datos de las películas.

## Características 
- Eficiencia con gran volumen de información:
  1. En cleanData.cpp, se usa std::vector para almacenar los datos de las películas. std::vector es una estructura de datos que permite un acceso rápido y eficiente a los elementos y tiene un buen desempeño en términos de inserción y recorrido, lo que es crucial cuando se manejan grandes volúmenes de datos.
  ```
  std::vector<CMovie> movies = loadCsv(fil);
  ```
  2. La función "loadCsv" en cleanData.cpp procesa línea por línea el archivo CSV de películas, utilizando std::ifstream y std::stringstream para manejar la entrada de datos de manera eficiente. Asegura que cada línea del archivo se procese de manera eficiente, minimizando el uso de memoria y optimizando el tiempo de procesamiento.
          
- Control de errores: 
  1. Lectura de archivo: Incluimos la validación para asegurar que el archivo CSV se abra correctamente en el archivo cleanData.cpp. Verificando si el archivo se abrió correctamente y lanzando una excepción en caso de error.
```
  if (!inFile) {
  cerr << "Error opening input file: " << inputFile << endl;
```
  2. Datos de usuario: En el archivo usuario.cpp se incluyen 3 funciones de verificación de los datos del usuario que se ha ingresado, proporcionando mensajes de error en caso de que los datos no cumplan con ciertos criterios como la cantidad de caracteres.
```
   bool verify= name.size()>=2;
   if (!verify) cout<<"* El nombre debe tener mas de 1 caracter!"<<endl;
```
    
- Uso de estructuras de lenguaje:
  1. Las clases encapsulan datos y comportamientos relacionados, facilitando la modularidad y la reutilización del código. Por ejemplo, la clase Planes en Planes.h encapsula los datos y métodos relacionados con los planes de suscripción, como Premium, Standard y Basic. Permitiendo definir fácilmente nuevos tipos de planes sin cambiar la estructura básica del código.
  2. Los métodos y funciones encapsulan comportamientos específicos, mejorando la claridad. Por ejemplo, los métodos en la clase Planes permiten acceder y modificar los datos de los planes de manera controlada, encapsulando la lógica de negocio. A su vez, la función "loadCsv" en cleanData.cpp encapsula la lógica de carga y procesamiento de un archivo CSV, permitiendo su reutilización en cualquier parte del proyecto.
  3. El uso del archivo ALL.h centraliza la inclusión de cabeceras y la inicialización de datos y objetos esenciales, mejorando la organización y la reutilización del código.
 
- Uso de paradigmas:
  1. Programación Orientada a Objetos (POO): Se evidencia el uso al incluir clases como "Movie","Planes" o "Usuario". Encapsulando atributos y métodos en la clase.
  2. Programación Genérica: Incluimos este paradigma en las clases de estrategias de búsqueda (Estrategia, PorTitulo, PorTag, PorPlot) y en la función contador de la clase Buscador. Las estrategias de búsqueda se han definido como plantillas que pueden trabajar con cualquier tipo de dato, permitiendo así buscar en diferentes campos de las películas como título, etiquetas y sinopsis. La función contador, también genérica, cuenta las apariciones de una palabra en un texto y ha sido instanciada explícitamente para el tipo string. Estas implementaciones hacen que el código sea más flexible y reutilizable, mejorando la capacidad de mantenimiento del proyecto.
  3. Programación Concurrente: Se ha implementado principalmente en la clase Buscador utilizando std::async y std::future para realizar búsquedas paralelas en diferentes estrategias, lo que mejora el rendimiento y reduce el tiempo de búsqueda al aprovechar el paralelismo de los hilos en C++.
     
- Uso de librería Estándar: Los contenedores como std::vector y std::priority_queue se utilizan para almacenar y organizar datos de películas y resultados de búsqueda, permitiendo una manipulación eficiente de grandes volúmenes de información. Las cadenas de caracteres y flujos, a través de std::string, std::ifstream, y std::stringstream, permiten el manejo y procesamiento de texto, así como la lectura de archivos CSV. La concurrencia se maneja mediante std::thread y std::mutex, lo que permite la ejecución paralela de tareas y asegura el acceso sincronizado a los recursos compartidos, mejorando así el rendimiento del sistema. Además, los algoritmos de la biblioteca estándar, como std::sort y std::unique, se emplean para ordenar y eliminar duplicados en los resultados de búsqueda, mientras que std::lock_guard garantiza la seguridad en la manipulación de datos concurrentes. El manejo de errores se realiza mediante excepciones, usando std::runtime_error para gestionar situaciones inesperadas como la imposibilidad de abrir un archivo, asegurando que el sistema pueda reaccionar adecuadamente a fallos en tiempo de ejecución. Estos casos se han llegado a dar con la biblioteca estándar que C++ proporciona.
  
- Big O:
  1. Algoritmos de Búsqueda: Búsqueda en Trie (árbol de prefijos) se utiliza para realizar búsquedas rápidas en los títulos, etiquetas y sinopsis de las películas. La complejidad de búsqueda en un Trie es O(m), donde m es la longitud de la cadena a buscar, lo que es más eficiente que O(n) para búsquedas en listas no ordenadas.
  2. Algoritmos de Ordenamiento: Empleamos un ordenamiento de resultados por relevancia para presentar los resultados de búsqueda, aqui se utilizó la función sort de la biblioteca estándar de C++, que tiene una complejidad de O(nlog⁡n). Este ordenamiento asegura que los resultados más relevantes se muestren primero.
  3. Recorrido del Trie: El recorrido del Trie para obtener todas las películas que coinciden con una consulta también es un ejemplo de un algoritmo de complejidad mayor que lineal. Después de encontrar el nodo correspondiente a la última letra de la consulta, se recorre el subárbol para obtener todas las coincidencias. Este recorrido puede tener una complejidad de O(n), donde n es el número de nodos en el subárbol.
      
- Patrones de Diseño:
  1. Singleton: Se implementa en la clase Buscador para asegurar que solo exista una única instancia de esta clase a lo largo de la aplicación, accesible mediante Buscador::getInstance().
  2. Estrategia: Se utiliza en las clases Estrategia, PorTitulo, PorTag y PorPlot, permitiendo definir una familia de algoritmos de búsqueda intercambiables que se pueden aplicar de manera flexible a las películas.
  3. Factory Method: Se evidencia en el uso de unique_ptr para añadir diferentes estrategias al Buscador a través de la función addEstrategia(), permitiendo la creación dinámica de objetos de estrategia sin especificar la clase exacta de los objetos que se crearán. Estos patrones de diseño mejoran la extensibilidad y mantenibilidad del proyecto al proporcionar una estructura flexible y modular.
     
## Bibliografía
CodeLikeAGirl. (2024, 20 febrero). _Developing a basic search engine in C++: an adventure in coding - code with C. Code With C._ https://www.codewithc.com/developing-a-basic-search-engine-in-c/?amp=1

Mayurji. (s. f.). _GitHub - Mayurji/Understanding-Search-Engine-Using-Cplusplus: Understanding Search Engine concepts and implementing the same using C++ and STL._ GitHub. https://github.com/Mayurji/Understanding-Search-Engine-Using-Cplusplus

_MPST: Movie Plot Synopses with Tags._ (2019, 16 abril). Kaggle. https://www.kaggle.com/datasets/cryptexcode/mpst-movie-plot-synopses-with-tags/data?select=partition.json

GeeksforGeeks. (2024, 7 junio). Trie Data Structure  Insert and Search. GeeksforGeeks. https://www.geeksforgeeks.org/trie-insert-and-search/

_Yhirose. (s. f.). _GitHub - yhirose/cpp-httplib: A C++ header-only HTTP/HTTPS server and client library._ GitHub. https://github.com/yhirose/cpp-httplib
