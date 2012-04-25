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
	if(strcmp($_GET['classement'], "duree" ) == 0)
		$classement .= "dureeh ASC, dureem ASC";
	else if(strcmp($_GET['classement'], "nb_escales") == 0)
		$classement .= "escales ASC";
	else if(strcmp($_GET['classement'], "date_de_depart") == 0)
		$classement .= "datedepart ASC";
	else if(strcmp($_GET['classement'], "prix") == 0)
		$classement .= "prix ASC";
}
/* requête un peu complexe */
/* TODO ajouter le nombre d'escales, le prix du billet le moins cher */
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
	nb_billets_restants(V.idVol, V.idCompagnie) as billetsrestants,
	nb_escales(V.idVol, V.idCompagnie) as escales,
	prixmin(V.idVol, V.idCompagnie) as prix
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
	<table>
		<thead>
			<tr>
				<th>id</th>
				<th>Compagnie</th>
				<th>Ville de départ</th>
				<th>Ville d'arrivée</th>
				<th><a href="?classement=date_de_depart" >Date de départ</a></th>
				<th>Date d'arrivée</th>
				<th><a href="?classement=duree">Durée</a></th>
				<th>Billets réservés</th>
				<th>Billets achetés</th>
				<th>Billets restants</th>
				<th><a href="?classement=prix" >Prix</a></th>
				<th><a href="?classement=nb_escales" >Nb d'escales</a></th>
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
		"<td>" . $row['BILLETSRESTANTS'] . "</td>" .
		"<td>" . $row['PRIX'] . "</td>" .
		"<td>" . $row['ESCALES'] . "</td>";

	echo "</tr>\n";
}

?>
	</table>
			</div>
		</div>
	</div>
<?php include("includes/in_pied"); ?>
