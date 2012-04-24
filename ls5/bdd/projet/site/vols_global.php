<?php 

session_start();

include("co.php");
include("fonctions.php");


/* on s'assure que la personne est connectée et gestionnaire */
estGestionnaire();

$compagnie = getCompagnie();

$_TITRE_PAGE="BDD - vols de la compagnie";
include("includes/in_entete"); 

?>
	<!-- container -->
	<div class="container">

		<?php include("includes/in_haut"); ?>

		<div class="row">
			<div class="twelve columns panel">
			<h5>Visuel sur l'ensemble de nos vols.</h5>
<?php

/* requête un peu complexe */
$query = 
"select 
	V.idVol as idvol, 
	C.nomCompagnie as compagnie, 
	X.nomVille as vdepart, Y.nomVille as varrivee, 
	V.dateDepart, V.dateArrivee,
	V.idCompagnie as idcompagnie,
	nb_billets_reserve(V.idVol, V.idCompagnie) as billetsreserves,
	nb_billets_achetes(V.idVol, V.idCompagnie) as billetsachetes,
	nb_billets_restants(V.idVol, V.idCompagnie) as billetsrestants
from VOL V 
JOIN COMPAGNIE C ON V.idCompagnie=C.idCompagnie
JOIN VILLE X ON X.idVille=V.idVilleDepart
JOIN VILLE Y ON Y.idVille=V.idVilleArrivee
where V.idCompagnie=$compagnie";

$stmt = oci_parse($conn, $query);
if(! oci_execute($stmt))
	die("Il y a eu une erreur lors de la recherche des vols. ");

echo "<p>idVol | Compagnie | Ville de départ | Ville d'arrivée | date de départ | date d'arrivée </p><br />";

echo "<p>";
while($row = oci_fetch_assoc($stmt))
{
	echo "<a href=modifier_vols.php?idvol=" . $row['IDVOL'] . ">";

	echo	$row['IDVOL'] . " | " .
			$row['COMPAGNIE'] . " | " .
			$row['VDEPART'] . " | " .
			$row['VARRIVEE'] . " | " .
			$row['DATEDEPART'] . " | " .
			$row['DATEARRIVEE'] . " | " . 
			$row['BILLETSRESERVES'] . " | " . 
			$row['BILLETSACHETES'] . " | " .
			$row['BILLETSRESTANTS']
			
			. "</a><br />\n";
}
echo "</p>";

?>
			</div>
		</div>
	</div>
<?php include("includes/in_pied"); ?>
