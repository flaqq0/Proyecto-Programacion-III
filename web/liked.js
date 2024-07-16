document.addEventListener('DOMContentLoaded', function () {
    const likedMoviesContainer = document.getElementById('liked-movies-container');
    const likedMovies = JSON.parse(localStorage.getItem('likedMovies')) || [];

    function displayLikedMovies() {
        likedMovies.forEach(movie => {
            const movieElement = document.createElement('div');
            movieElement.className = 'movie';
            movieElement.innerHTML = `
                <h2>${movie.title}</h2>
                <p>${movie.plot_synopsis}</p>
            `;
            likedMoviesContainer.appendChild(movieElement);
        });
    }

    displayLikedMovies();
});