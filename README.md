1. Comment se comporte UCB en fonction de K ?

> Je constate que plus la valeur de K est elevée plus l'algorithme UCB prendra la décision d'explorer (+ de risque), plus la valeur de K se rapproche de zéro plus il reste sur la même machine (- de risque)

2. Dans quel(s) cas la stratégie gloutonne est la meilleure ?

> Quand le K est petit, la stratégie UCB à le même comportement que l'algorithme glouton
> 
> Quand K est élevé, la stratégie UCB à le même comportement que l'algorithme aléatoire

3. Dans quel(s) cas la stratégie UCB est la meilleure ?

> Il faut un juste milieu pour la valeur de K, ni trop d'exploration ni trop d'exploitation.