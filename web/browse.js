document.addEventListener('DOMContentLoaded', function () {
    const moviesContainer = document.getElementById('movies-container');
    const loadMoreButton = document.getElementById('load-more-button');
    const searchButton = document.getElementById('search-button');
    const searchInput = document.querySelector('.search-container input');
    let movies = [];
    let currentPage = 1;
    const pageSize = 5; // Cantidad de películas por página

    async function fetchMovies(query) {
        try {
            const response = await fetch(`/search?query=${query}`);
            if (!response.ok) {
                throw new Error('Network response was not ok');
            }
            const data = await response.json();
            movies = data;
            currentPage = 1;
            displayMovies();
        } catch (error) {
            console.error('Error fetching movies:', error);
        }
    }

    function displayMovies() {
        const startIndex = (currentPage - 1) * pageSize;
        const endIndex = startIndex + pageSize;
        const moviesToShow = movies.slice(startIndex, endIndex);

        moviesContainer.innerHTML = moviesToShow.map(movie => `
            <div class="movie">
                <h2>${movie.title}</h2>
                <p>${movie.plot_synopsis}</p>
            </div>
        `).join('');

        if (endIndex < movies.length) {
            loadMoreButton.style.display = 'block';
        } else {
            loadMoreButton.style.display = 'none';
        }
    }

    searchButton.addEventListener('click', () => {
        const query = searchInput.value.trim();
        if (query) {
            fetchMovies(query);
        }
    });

    loadMoreButton.addEventListener('click', () => {
        currentPage++;
        displayMovies();
    });
});
