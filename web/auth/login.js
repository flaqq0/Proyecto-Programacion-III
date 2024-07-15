document.addEventListener('DOMContentLoaded', () => {
    const form = document.getElementById('loginForm');

    form.addEventListener('submit', (event) => {
        event.preventDefault();
        const email = document.getElementById('emailInput').value;
        const password = document.getElementById('passwordInput').value;

        // Lógica de autenticación aquí
        if (email && password) {
            // Simula la redirección después de un login exitoso
            window.location.href = '/browse'; // Reemplaza con la ruta deseada
        } else {
            alert('Por favor, completa todos los campos.');
        }
    });
});
