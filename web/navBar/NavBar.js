document.addEventListener('DOMContentLoaded', function () {
    const searchButton = document.getElementById('search-button');
    const searchInput = document.querySelector('.search-container input');

    searchButton.addEventListener('click', () => {
        const query = searchInput.value;
        if (query) {
            window.location.href = `/search?query=${query}`;
        }
    });

    searchInput.addEventListener('keypress', (e) => {
        if (e.key === 'Enter') {
            searchButton.click();
        }
    });
});
