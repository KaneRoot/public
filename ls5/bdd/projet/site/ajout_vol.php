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
<input id='idvol' name='idvol' type="text" placeholder="id vol" class="input-text" />
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

/* on va rechercher l'ensemble des vols appartenant à la compagnie */
$query = 
"select 
	V.idVol as idvol, 
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

echo "<p>idVol | Ville de départ | Ville d'arrivée | date de départ | date d'arrivée </p><br />";

echo "<p>";
while($row = oci_fetch_assoc($stmt))
{
	echo	$row['IDVOL'] . " | " .
			$row['VDEPART'] . " | " .
			$row['VARRIVEE'] . " | " .
			$row['DATEDEPART'] . " | " .
			$row['DATEARRIVEE'] . " | " . 
			$row['BILLETSRESERVES'] . " | " . 
			$row['BILLETSACHETES'] . " | " .
			$row['BILLETSRESTANTS']
			
			. "<br />\n";
}
echo "</p>";

?>
			</div>
		</div>

	</div>
<?php 
	include("includes/in_pied"); 
?>
