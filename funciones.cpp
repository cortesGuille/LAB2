// Función principal del algoritmo minimax con ajuste de dificultad
int minimax(EstadoTablero& tablero, int profundidad, int alpha, int beta, bool esMaximizando, int nivelDificultad) {
    if (profundidad == 0 || juegoTerminado(tablero)) {
        return evaluacion(tablero);
    }

    if (nivelDificultad == FACIL && !esMaximizando) {
        // En modo fácil, la IA toma decisiones más rápidas
        return 0;
    }

    if (esMaximizando) {
        int mejorValor = INFINITO_NEGATIVO;
        for (int jugada : jugadasPosibles(tablero)) {
            // Implementa la función para realizar la jugada en el tablero
            // EstadoTablero nuevoTablero = realizarJugada(tablero, jugada);
            int valor = minimax(nuevoTablero, profundidad - 1, alpha, beta, false, nivelDificultad);
            mejorValor = std::max(mejorValor, valor);
            alpha = std::max(alpha, mejorValor);
            if (beta <= alpha) {
                break; // Poda alfa-beta
            }
        }
        return mejorValor;
    } else {
        int mejorValor = INFINITO_POSITIVO;
        for (int jugada : jugadasPosibles(tablero)) {
            // Implementa la función para realizar la jugada en el tablero
            // EstadoTablero nuevoTablero = realizarJugada(tablero, jugada);
            int valor = minimax(nuevoTablero, profundidad - 1, alpha, beta, true, nivelDificultad);
            mejorValor = std::min(mejorValor, valor);
            beta = std::min(beta, mejorValor);
            if (beta <= alpha) {
                break; // Poda alfa-beta
            }
        }
        return mejorValor;
    }
}