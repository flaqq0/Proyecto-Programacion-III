# Proyecto Final - Programacion-III
Proyecto final del curso de Programación III de la Universidad de Ingeniería y Tecnología (UTEC)

## Integrantes:
- Flavia Honores (202310550)
- Sofia Ku (202310476)
- Breysi Salazar (202310648)
- Renato García (202310495)

## Presentación
Para poder visualizar la parte gráfica del proyecto, se debe runear el main y una vez esté funcionando, ingresar a http://localhost:8080/

## Descripción del Proyecto
El proyecto consiste en desarrollar una plataforma de streaming que permita la búsqueda y visualización de películas. El programa lee la base de datos indicada en formato .csv, esta se encuentra almacenada en un vector (vector<Movie>), una estructura de datos eficiente para la búsqueda rápida y permite buscar películas por palabras clave o tags específicos. La plataforma muestra las cinco películas más relevantes y proporciona opciones para visualizar más coincidencias.

## Diagrama (Flow chart?)......
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
| | |
v v v
Ejecutar TitleSearch (hilo) Ejecutar TagSearch (hilo) Ejecutar PlotSearch (hilo)
| | |
v v v
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
(manejo de Excepciones en la Solicitud HTTP en main)
- Eficiencia con gran volumen de información:
  1. En cleanData.cpp, se usa std::vector para almacenar los datos de las películas. std::vector es una estructura de datos que permite un acceso rápido y eficiente a los elementos y tiene un buen desempeño en términos de inserción y recorrido, lo que es crucial cuando se manejan grandes volúmenes de datos.
     
     std::vector<CMovie> movies = loadCsv(fil);

  2. La función "loadCsv" en cleanData.cpp procesa línea por línea el archivo CSV de películas, utilizando std::ifstream y std::stringstream para manejar la entrada de datos de manera eficiente. Asegura que cada línea del archivo se procese de manera eficiente, minimizando el uso de memoria y optimizando el tiempo de procesamiento.
          
- Control de errores: 
  1. Lectura de Archivos: Incluimos la validación para asegurar que el archivo CSV se abra correctamente. Esto se hizo en el archivo main.cpp hacer verificando si el archivo se abrió correctamente y lanzando una excepción en caso de error.
  
     if (!file.is_open()) {
        throw runtime_error("No se pudo abrir el csv: " + path);
    
- Uso de estructuras de lenguaje:
  1. Las clases encapsulan datos y comportamientos relacionados, facilitando la modularidad y la reutilización del código. Por ejemplo, la clase Planes en Planes.h encapsula los datos y métodos relacionados con los planes de suscripción, como Premium, Standard y Basic. Permitiendo definir fácilmente nuevos tipos de planes sin cambiar la estructura básica del código.
  2. Los métodos y funciones encapsulan comportamientos específicos, mejorando la claridad. Por ejemplo, los métodos en la clase Planes permiten acceder y modificar los datos de los planes de manera controlada, encapsulando la lógica de negocio. A su vez, la función "loadCsv" en cleanData.cpp encapsula la lógica de carga y procesamiento de un archivo CSV, permitiendo su reutilización en cualquier parte del proyecto.
  3. El uso del archivo ALL.h centraliza la inclusión de cabeceras y la inicialización de datos y objetos esenciales, mejorando la organización y la reutilización del código.
 
- Uso de paradigmas:
  1. Programación Orientada a Objetos (POO): Se evidencia el uso al incluir clases como "Movie","Planes" o "Usuario". Encapsulando atributos y métodos en la clase.
  2. Programación Genérica: En el archivo MovieSearch.h, se define una clase genérica "SearchStrategy" que utiliza una plantilla para definir estrategias de búsqueda sobre cualquier tipo de datos. Luego, se derivan clases específicas para buscar películas por diferentes criterios. Además se usa unique_ptr para manejar la memoria de las estrategias de búsqueda.
  3. Programación Concurrente: En el archivo MovieSearch.h se utilizan hilos para ejecutar las estrategias de búsqueda en paralelo, mejorando la eficiencia de las búsquedas sobre grandes volúmenes de datos. 
     
- Uso de librería Estándar: Los contenedores como std::vector y std::priority_queue se utilizan para almacenar y organizar datos de películas y resultados de búsqueda, permitiendo una manipulación eficiente de grandes volúmenes de información. Las cadenas de caracteres y flujos, a través de std::string, std::ifstream, y std::stringstream, permiten el manejo y procesamiento de texto, así como la lectura de archivos CSV. La concurrencia se maneja mediante std::thread y std::mutex, lo que permite la ejecución paralela de tareas y asegura el acceso sincronizado a los recursos compartidos, mejorando así el rendimiento del sistema. Además, los algoritmos de la biblioteca estándar, como std::sort y std::unique, se emplean para ordenar y eliminar duplicados en los resultados de búsqueda, mientras que std::lock_guard garantiza la seguridad en la manipulación de datos concurrentes. El manejo de errores se realiza mediante excepciones, usando std::runtime_error para gestionar situaciones inesperadas como la imposibilidad de abrir un archivo, asegurando que el sistema pueda reaccionar adecuadamente a fallos en tiempo de ejecución. Estos casos se han llegado a dar con la biblioteca estándar que C++ proporciona.
  
- Big O:
  1. El algoritmo std::sort de la biblioteca estándar de C++ es un ejemplo de un algoritmos de Ordenamiento con complejidad O(n log n). En el archivo MovieSearch.cpp, el método search utiliza std::sort para ordenar los resultados de búsqueda. Esto asegura que los resultados estén ordenados antes de eliminar duplicados y presentarlos al usuario.
  2. En la clase TitleSearch, se implementa una búsqueda lineal para encontrar películas cuyo título contiene una cadena específica, tiene una complejidad O(n) donde n es el número de películas. Esta búsqueda lineal implica recorrer cada película y verificar si el título contiene la cadena de búsqueda. Similar sucede con los otros 2 criterios de busqueda.
      
- Patrones de Diseño:
  1. Singleton: Se implementa en la clase MovieSearchEngine. Esto asegura que solo exista una instancia de MovieSearchEngine durante la ejecución del programa, lo cual es crucial para la consistencia y la gestión centralizada de las búsquedas de películas, ahorrando así memoria y recursos al evitar la creación de múltiples instancias de la misma clase.
  2. Estrategia: Se implementa mediante la clase base SearchStrategy y sus clases derivadas como TitleSearch, TagSearch y PlotSearch. Esto permite definir diferentes estrategias de búsqueda y aplicarlas de manera flexible según las necesidades.
     
## Bibliografía
CodeLikeAGirl. (2024, 20 febrero). _Developing a basic search engine in C++: an adventure in coding - code with C. Code With C._ https://www.codewithc.com/developing-a-basic-search-engine-in-c/?amp=1

Mayurji. (s. f.). _GitHub - Mayurji/Understanding-Search-Engine-Using-Cplusplus: Understanding Search Engine concepts and implementing the same using C++ and STL._ GitHub. https://github.com/Mayurji/Understanding-Search-Engine-Using-Cplusplus

_MPST: Movie Plot Synopses with Tags._ (2019, 16 abril). Kaggle. https://www.kaggle.com/datasets/cryptexcode/mpst-movie-plot-synopses-with-tags/data?select=partition.json

GeeksforGeeks. (2024, 7 junio). Trie Data Structure  Insert and Search. GeeksforGeeks. https://www.geeksforgeeks.org/trie-insert-and-search/

_Yhirose. (s. f.). _GitHub - yhirose/cpp-httplib: A C++ header-only HTTP/HTTPS server and client library._ GitHub. https://github.com/yhirose/cpp-httplib
