Les programmes client et serveur sont des solutions de l'exercice.

La fonction de multiplication se déroule normalement.
La fonction d'addition ne répond pas immédiatement (sleep(t)).
Entretemps, le client relance un appel rpc au serveur (voir affichage au niveau du serveur), ce qui met en avant le timeout et la ré-émission de la demande).

On peut également observer que :
si t <= 5 : pas de ré-émission
si 5 < t <= 25 : réémissions toutes les 5 secondes
si 25 < t : timeout définitif et échec de l'appel RPC

