document.addEventListener('DOMContentLoaded', () => {
    const form = document.querySelector('form');

    form.addEventListener('submit', (event) => {
        event.preventDefault(); // Evita la acción por defecto del formulario
        window.location.href = form.action; // Redirige a la URL especificada en action
    });
});
