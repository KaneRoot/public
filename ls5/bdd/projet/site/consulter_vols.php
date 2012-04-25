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

/* choix du classement */

/* À FINIR TODO */
if(isset($_GET['classement']))
{
	$classement = "ORDER BY ";
	if(strcmp($_GET['classement'], "prix" ))
		$classement .= ;
}

/* requête un peu complexe */
$query = 
"select 
	V.idVol as idvol, 
	C.nomCompagnie as compagnie, 
	X.nomVille as vdepart, Y.nomVille as varrivee, 
	to_char(V.dateDepart, 'yyyy/mm/dd hh24:mi:ss') as datedepart, 
	to_char(V.dateArrivee, 'yyyy/mm/dd hh24:mi:ss') as datearrivee,
	trunc((V.dateArrivee - V.dateDepart)*24) as dureeh,
	trunc( MOD(( (V.dateArrivee - V.dateDepart)*24*60),60)) as dureem,
	V.idCompagnie as idcompagnie,
	nb_billets_reserve(V.idVol, V.idCompagnie) as billetsreserves,
	nb_billets_achetes(V.idVol, V.idCompagnie) as billetsachetes,
	nb_billets_restants(V.idVol, V.idCompagnie) as billetsrestants
from VOL V 
JOIN COMPAGNIE C ON V.idCompagnie=C.idCompagnie
JOIN VILLE X ON X.idVille=V.idVilleDepart
JOIN VILLE Y ON Y.idVille=V.idVilleArrivee
where V.dateDepart > SYSDATE
";

if(isset($classement))
	$query .= $classement;

$stmt = oci_parse($conn, $query);
if(! oci_execute($stmt))
	die("Il y a eu une erreur lors de la recherche des vols. ");

?>
	<p> Classer : 
	<a href"?classement=prix" >par prix</a> 
	<a href"?classement=date_de_depart" >par date de départ</a> 
	<a href"?classement=nb_escales" >par nombre d'escales</a>.
	</p>
	<table>
		<thead>
			<tr>
				<th>id</th>
				<th>Compagnie</th>
				<th>Ville de départ</th>
				<th>Ville d'arrivée</th>
				<th>Date de départ</th>
				<th>Date d'arrivée</th>
				<th>Durée</th>
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
		"<td>" . $row['DUREEH'] .":". $row['DUREEM'] . " </td> " . 
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
