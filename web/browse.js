document.addEventListener('DOMContentLoaded', function () {
    const moviesContainer = document.getElementById('movies-container');
    const prevButton = document.getElementById('prev-button');
    const nextButton = document.getElementById('next-button');
    let currentPage = 1;
    const pageSize = 10; // Cantidad de películas por página

    function loadMovies(query, page) {
        fetch(`/search?query=${query}&page=${page}&page_size=${pageSize}`)
            .then(response => response.json())
            .then(data => {
                moviesContainer.innerHTML = '';
                data.forEach(movie => {
                    const movieCard = document.createElement('div');
                    movieCard.classList.add('movie-card');
                    movieCard.textContent = `${movie.title} - ${movie.tags}`;
                    moviesContainer.appendChild(movieCard);
                });
            })
            .catch(error => {
                console.error('Error al cargar películas:', error);
            });
    }

    function goToPage(page) {
        if (page < 1) page = 1;
        currentPage = page;
        loadMovies('', currentPage);
    }

    prevButton.addEventListener('click', () => goToPage(currentPage - 1));
    nextButton.addEventListener('click', () => goToPage(currentPage + 1));

    // Cargar películas en la página inicial
    loadMovies('', currentPage);
});
