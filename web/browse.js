document.addEventListener('DOMContentLoaded', function () {
    const moviesContainer = document.getElementById('movies-container');
    const searchButton = document.getElementById('search-button');
    const searchInput = document.getElementById('search-input');
    const loadMoreButton = document.getElementById('load-more-button');
    let movies = [];
    let likedMovies = JSON.parse(localStorage.getItem('likedMovies')) || [];
    let laterMovies = JSON.parse(localStorage.getItem('laterMovies')) || [];
    let currentIndex = 0;
    const pageSize = 5;

    async function fetchMovies(query) {
        const response = await fetch(`/search?query=${encodeURIComponent(query)}`);
        const result = await response.json();
        console.log("Fetched movies:", result); // Añadir este log
        return result;
    }

    function displayMovies() {
        const nextIndex = Math.min(currentIndex + pageSize, movies.length);
        for (let i = currentIndex; i < nextIndex; i++) {
            const movie = movies[i];
            const movieElement = document.createElement('div');
            movieElement.className = 'movie';
            movieElement.innerHTML = `
                <h2>${movie.title}</h2>
                <p>${movie.plot_synopsis}</p>
                <button class="like-button">Me gusta</button>
                <button class="later-button">Ver más tarde</button>
            `;
            movieElement.querySelector('.like-button').addEventListener('click', () => addToLiked(movie));
            movieElement.querySelector('.later-button').addEventListener('click', () => addToLater(movie));
            moviesContainer.appendChild(movieElement);
        }
        currentIndex = nextIndex;
        if (currentIndex >= movies.length) {
            loadMoreButton.style.display = 'none';
        } else {
            loadMoreButton.style.display = 'block';
        }
    }

    function addToLiked(movie) {
        if (!likedMovies.some(m => m.imdb_id === movie.imdb_id)) {
            likedMovies.push(movie);
            localStorage.setItem('likedMovies', JSON.stringify(likedMovies));
        }
    }

    function addToLater(movie) {
        if (!laterMovies.some(m => m.imdb_id === movie.imdb_id)) {
            laterMovies.push(movie);
            localStorage.setItem('laterMovies', JSON.stringify(laterMovies));
        }
    }

    searchButton.addEventListener('click', async function () {
        const query = searchInput.value;
        movies = await fetchMovies(query);
        currentIndex = 0;
        moviesContainer.innerHTML = '';
        displayMovies();
    });

    loadMoreButton.addEventListener('click', function () {
        displayMovies();
    });
});