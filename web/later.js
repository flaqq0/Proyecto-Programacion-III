document.addEventListener('DOMContentLoaded', function () {
    const laterMoviesContainer = document.getElementById('later-movies-container');
    const laterMovies = JSON.parse(localStorage.getItem('laterMovies')) || [];

    function displayLaterMovies() {
        laterMovies.forEach(movie => {
            const movieElement = document.createElement('div');
            movieElement.className = 'movie';
            movieElement.innerHTML = `
                <h2>${movie.title}</h2>
                <p>${movie.plot_synopsis}</p>
            `;
            laterMoviesContainer.appendChild(movieElement);
        });
    }

    displayLaterMovies();
});
