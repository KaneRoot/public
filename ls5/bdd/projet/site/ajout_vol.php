<?php 
	session_start();
	$_TITRE_PAGE="BDD - ajout vol";
	include("includes/in_entete"); 
	include("co.php");
	include("fonctions.php");

$compagnie = getCompagnie();

if(isset($_POST['idvol']) && $_POST['idvol'] > 0 &&
		isset($_POST['idvilledepart'], $_POST['idvillearrivee'], 
			$_POST['datedepart'], $_POST['datearrivee']))
{
	$idvol = $_POST['idvol'];
	$idvilledepart = $_POST['idvilledepart'];
	$idvillearrivee = $_POST['idvillearrivee'];
	$datedepart = "'". $_POST['datedepart'] . "'";
	$datearrivee = "'" . $_POST['datearrivee'] . "'";

	$query = "INSERT INTO VOL VALUES( " .
		$idvol . ", " .  $compagnie . ", " .
		$idvilledepart . ", " . $idvillearrivee . ", " . 
		"to_date(" . $datedepart . ", 'yyyy/mm/dd hh24:mi:ss'), 
		to_date(" . $datearrivee . ", 'yyyy/mm/dd hh24:mi:ss'))
	";
	$stmt = oci_parse($conn, $query);
	if(! oci_execute($stmt))
		die("Il y a eu une erreur à l'ajout du vol : <br />\n  $query");
}

$prochainidvol = get_prochain_idvol($conn);

?>
	<!-- container -->
	<div class="container">

		<?php include("includes/in_haut"); ?>
	
		<div class="row">
			<h5>Ajout d'un vol</h5>
			<form class="nice" action="" method="POST" >
			<div class="six columns">
					<fieldset>
					<h5>L'identifiant du vol</h5>
					<p>Pour les dates c'est au format 'yyyy/mm/dd hh24:mi:ss' </p>
					<label for='idvol' class="green radius label" >L'identifiant (idVol) .</label><br />
					<input id='idvol' name='idvol' type="text" class="input-text" value="<?php echo $prochainidvol; ?>" />
					</fieldset>

			</div>
			<div class="six columns">
					<fieldset>
					<h5>Les villes de départ et d'arrivée </h5>
					<select id="idvilledepart" name="idvilledepart">
<?php

$query = "select * from VILLE";
$stmt = oci_parse($conn, $query);
if(! oci_execute($stmt))
	die("Il y a eu une erreur durant la recherche des villes." );

/* et voici une technique de haut vol pour pas me retaper la requête */
$options = "";

while($row = oci_fetch_assoc($stmt))
	$options .= "<option value='" . $row['IDVILLE'] . "' >" .
	$row['NOMVILLE'] . "</option>\n";

echo $options;
?>

					</select>
					<select id="idvillearrivee" name="idvillearrivee">
<?php echo $options ; ?>
					</select>
<input id='datedepart' name='datedepart' type="text" placeholder="Date depart" class="input-text" />
<input id='datearrivee' name='datearrivee' type="text" placeholder="Date arrivée" class="input-text" />
					</fieldset>
					<input type="submit" value="Ajouter le vol" />
					<input type="reset" value="Oublier ça" />
				</form>
			</div>
		</div>
		<div class="row">
			<div class="twelve columns">
			<hr />
				<h5>Les vols déjà présents</h5>
<?php
/* Pour voir arranger les résultats rapidement */
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
where V.dateDepart > SYSDATE and V.idCompagnie=$compagnie
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

?>
			</div>
		</div>

	</div>
<?php 
	include("includes/in_pied"); 
?>
