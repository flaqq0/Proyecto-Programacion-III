// scripts/script.js

document.addEventListener('DOMContentLoaded', function() {
    const form = document.getElementById('emailForm');
    const emailInput = document.getElementById('emailInput');

    form.addEventListener('submit', function(event) {
        event.preventDefault();

        const email = emailInput.value;

        if (email) {
            console.log('Email enviado:', email);
            // Redirigir al usuario a la página de registro
            window.location.href = '/auth/register';
        } else {
            alert('Por favor, ingresa una dirección de email válida.');
        }
    });
});
