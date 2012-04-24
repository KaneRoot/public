<?php 

session_start();

include("co.php");
include("fonctions.php");

$_TITRE_PAGE="BDD - consultation vols";
include("includes/in_entete"); 

?>
	<!-- container -->
	<div class="container">

		<?php include("includes/in_haut"); ?>

		<div class="row">
			<div class="twelve columns panel">
			<h5>Visuel sur l'ensemble des vols.</h5>
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
";

$stmt = oci_parse($conn, $query);
if(! oci_execute($stmt))
	die("Il y a eu une erreur lors de la recherche des vols. ");

?>

	<table>
		<thead>
			<tr>
				<th>id</th>
				<th>Compagnie</th>
				<th>Ville de départ</th>
				<th>Ville d'arrivée</th>
				<th>Date de départ</th>
				<th>Date d'arrivée</th>
				<th>Nb billets réservés</th>
				<th>Nb billets achetés</th>
				<th>Nb billets restants</th>
			</tr>
		</thead>

<?php
while($row = oci_fetch_assoc($stmt))
{
	echo "<tr>";
	echo	"<td>" . $row['IDVOL'] . "</td>" .
		"<td>" . $row['COMPAGNIE'] . " </td> " .
		"<td>" . $row['VDEPART'] . " </td> " .
		"<td>" . $row['VARRIVEE'] . " </td> " .
		"<td>" . $row['DATEDEPART'] . " </td> " .
		"<td>" . $row['DATEARRIVEE'] . " </td> " . 
		"<td>" . $row['BILLETSRESERVES'] . " </td> " . 
		"<td>" . $row['BILLETSACHETES'] . " </td> " .
		"<td>" . $row['BILLETSRESTANTS'] . "</td>";

	echo "</tr>\n";
}

?>
	</table>
			</div>
		</div>
	</div>
<?php include("includes/in_pied"); ?>
