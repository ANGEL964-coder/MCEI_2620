---------------------------------------------
Resultados - Primera función
---------------------------------------------
|Método | raíz | iteraciones | Observaciones |
|-------|------|-------------|---------------|
|Bisección | 0.20164 | 29 | Alta cantidad de iteraciones y buena precisión.|
|Brent | 0.20164 | 6 | Pocas iteraciones, comparado con todos los métodos que no usan la función FDF, el mejor en ejecucición.
|Falsepos | 0.20164 | 8 | Pocas iteraciones, sin embargo no es comparable con brent, ya que tiene una mayor precisión decimal en cada iteración.|
|Newton | 0.20164 | 4 | Se necesita definición de la función FDF para manejar el método, entre todos los metodos presenta la menor cantidad de iteraciones.|
|Secant | 0.20164 | 5 | Presenta la misma cantidad de iteraciones que el método de steffensen y la misma precisión que todos los métodos.|
|Steffensen | 0.20164 | 5 | Misma cantidad de iteraciones que el método de la secante.|


---------------------------------------------
Resultados - Segunda función
---------------------------------------------
|Método | raíz | iteraciones |
|-------|------|-------------|
|Bisección | 0.567143 | 28 |
|Brent | 0.567143| 6 |
|Falsepos | 0.567143| 7 |
|Newton | 0.567143 | 4 | 
|Secant | 0.567143 | 4 |
|Steffensen | 0.567143 | 4 |


---------------------------------------------
Preguntas de Discusión
---------------------------------------------

1. ¿Qué método converge en menos iteraciones? El método que menos iteraciones realizó fue el método de newton con tan solo 4 iteraciones en total.
2. ¿Qué método presenta mayor robustez? Los métodos que presentan la mayor robustez son la bisección y brent, debido a que son métodos cerrados en un intervalo que sin importar la complejidad de la función y a pesar de presentar mayor cantidad de iteraciones se tiene la certeza de que convergen.
3. ¿Qué ocurre cuando el valor inicial está lejos de la raíz? Cuando el valor incial esta lejos de la raiz, en el caso de los métodos abiertos como newton, secant y steffensen, se presenta la misma precisión pero una mayor cantidad de iteraciones para llegar a dicho resultado. En el caso de los cerrados como brent y bisección, el método debe concer el intervalo donde esta la raiz debido a que si existen muchos cambios de signo en el intervalo seleccionado no es capaz de converger.
4. ¿Cuál método recomendaría para problemas de ingeniería? Dependiendo si la función o señal que se va a analizar su derivada tiene un bajo o alto gasto computacional. En casos como señales electricas como el audio u convertidores DC, sería mejor un método como brent donde se presenta una mayor robustez y no es necesario calcular la derivada que para el caso de estas señales puede ser altamente costoso en terminos de recursos de computación. Para casos sencillos como funciones trigonometricas o señales electricas que no sean complejas, recomendaria el método cerrado de newton debido a su baja cantidad de iteraciones.
5. ¿Existe una relación entre costo computacional y velocidad de convergencia? Si, la relación entre la velocidad de convergencia y el costo computacional se evidencia en métodos como la bisección y newton. En el caso de la bisección el costo computacional de cada iteración no es costoso debido a la simpleza del método, sin embargo en el caso de newton o los métodos abiertos donde se usa la función derivada, se requiere mucho costo computacional para poder trabajar de manera simultanea tanto la función base como su derivada. Por ende, a pesar de presentar menos iteraciones presentan un mayor costo computacional que métodos cerrados como brent, bisección o falsepos. 