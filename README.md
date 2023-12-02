# LABORATORIO 2

## Implemenacion y diseño del algorirmo

Hablando como funciona el juego, en un principio el jugador cuando elije su respuesta es guardada dentro de un "estado" y para que la IA responda a la jugada del jugador se crea un arbol completo y dependiendo de la dificultad va ser la profundidad del arbol,asi con el algoritmo minimax es mas preciso al ver la mejor alternativa.

No se creo solo arbol debido a que la profundidad que deberia tener el arbol era demasiado grande y por lo menos para mi, al momento de ejucutar me ocurria un error en ejecucion, debido a que la profundidad del arbol es de FILAS*COLUMNAS y me llevó a problemas de gestión de memoria, que prodia haber sido por mi computadora.



## RESULTADOS DE PRUEBAS 

En la implementacion del algoritmo minimax, que alfinal solo es un evaluador de jugadas y trata de encontrar el mejor valor. Debido a esto dentro de este juego cuando se ocupo minimax sin poda tiene una complejidad temporal exponencial. Esto significa que la cantidad de nodos que deben ser evaluados aumenta exponencialmente con la profundidad del árbol de juego.

<img src="https://users.dcc.uchile.cl/~jegger/memoria/images/minimax.gif" alt="minimax">


En cambio cuando se Implemento el agotirmo imcluyendo poda alfa-beta realiza "poda" en los nodos inutiles,osea, si  encuentra un nodo que no afectará la elección del mejor movimiento, dejará de explorar sus nodos hijos, reduciendo así la cantidad total de nodos evaluados. Esto claramente mejora el tiempo de ejecucion del programa siendo mas eficiente que hacerlo sin esta implementacón.

<img src="https://upload.wikimedia.org/wikipedia/commons/thumb/9/91/AB_pruning.svg/1920px-AB_pruning.svg.png" alt="minimax poda alfa-beta">