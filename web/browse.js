document.addEventListener('DOMContentLoaded', function () {
    const moviesContainer = document.getElementById('movies-container');
    const prevButton = document.getElementById('prev-button');
    const nextButton = document.getElementById('next-button');
    let currentPage = 1;
    const pageSize = 10;

    // Función para cargar y mostrar películas
    function loadMovies(page) {
        fetch(`/search?query=&page=${page}&page_size=${pageSize}`)
            .then(response => {
                if (!response.ok) {
                    throw new Error('Network response was not ok');
                }
                return response.json(); // Parsear la respuesta JSON
            })
            .then(data => {
                moviesContainer.innerHTML = ''; // Limpiar contenedor antes de agregar contenido nuevo
                data.forEach(movie => {
                    const movieCard = document.createElement('div');
                    movieCard.className = 'movie-card';
                    movieCard.innerHTML = `
                        <h2>${movie.title}</h2>
                        <p>${movie.tags}</p>
                    `;
                    moviesContainer.appendChild(movieCard);
                });
            })
            .catch(error => {
                console.error('Error al cargar películas:', error);
            });
    }

    // Funciones para la paginación
    prevButton.addEventListener('click', () => {
        if (currentPage > 1) {
            currentPage--;
            loadMovies(currentPage);
        }
    });

    nextButton.addEventListener('click', () => {
        currentPage++;
        loadMovies(currentPage);
    });

    // Cargar la primera página al iniciar
    loadMovies(currentPage);
});
