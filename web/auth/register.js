// register.js

document.addEventListener('DOMContentLoaded', function() {
    const form = document.getElementById('registerForm');

    form.addEventListener('submit', function(event) {
        event.preventDefault();

        // Simulando el registro con éxito
        const email = document.getElementById('emailInput').value;
        const password = document.getElementById('passwordInput').value;

        console.log('Registrando usuario con email:', email, ' y contraseña:', password);

        // Redireccionar a la página de login
        window.location.href = '/auth/login';
    });
});
