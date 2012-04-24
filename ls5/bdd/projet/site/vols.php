<?php 

session_start();

include("co.php");
include("fonctions.php");

$_TITRE_PAGE="BDD - vols - réservation";
include("includes/in_entete"); 

if( isset($_GET['restart']))
{
	unset($_SESSION['ville_depart'], $_SESSION['ville_arrivee'], $_SESSION['vol']);
}

if( isset($_POST['ville_depart']) )
{
	$_SESSION['ville_depart'] = $_POST['ville_depart'];
}
if( isset($_SESSION['ville_depart']))
	echo "Ville de départ : " . $_SESSION['ville_depart'];

if( isset($_POST['ville_arrivee']) )
	$_SESSION['ville_arrivee'] = $_POST['ville_arrivee'];

?>
	<!-- container -->
	<div class="container">

		<?php include("includes/in_haut"); ?>

		<div class="row">
			<div class="three columns panel">
			<h5>Les vols</h5>
			<p>Voici la page où vous pouvez sélectionner le vol que vous allez prendre !</p>
			<hr />
			<p><a href="vols.php?restart=oui">Oubliez mes choix ! </a></p>
			</div>
			<div class="eight columns panel">

<?php

/* si l'utilisateur n'a encore rien choisi */

if(! isset($_SESSION['ville_depart']) && ! isset($_SESSION['ville_arrivee']))
{
	?>
			<form class="nice" action="vols.php" method="POST" >
				<fieldset>
				<h5>Choisissez la ville de départ</h5>
				<p>Généralement c'est pas un vrai choix ça.</p>

				<select id="ville_depart" name="ville_depart">

	<?php
		/* c'est ici qu'on va afficher les vols */
	$query = "select idVille, nomVille from VILLE where idVille in 
	(select distinct idVilleDepart from VOL)";
	$stmt = oci_parse($conn, $query);
	if(! oci_execute($stmt))
		die("Il y a eu une erreur lors de la recherche des villes de départ");

	while($row = oci_fetch_assoc($stmt))
	{
		echo "<option value='" . $row['IDVILLE'] . "' >" .
			$row['NOMVILLE']. "</option>\n";
	}

	?>
				</select>
				<input type="submit" value="Go !" />
			</form>
	<?php
}
else if( ! isset($_SESSION['ville_arrivee']) )
{
	?>
			<form class="nice" action="vols.php" method="POST" >
				<fieldset>
				<h5>Choisissez la ville d'arrivée</h5>
				<p>Généralement ça c'est un vrai choix.</p>

				<select id="ville_arrivee" name="ville_arrivee">

	<?php
	$idVilleDepart = $_POST['ville_depart'];

		/* c'est ici qu'on va afficher les vols */
	$query = "select idVille, nomVille from VILLE where idVille in
	(select idVilleArrivee from VOL where idVilleDepart=$idVilleDepart)";
	$stmt = oci_parse($conn, $query);
	if(! oci_execute($stmt))
		die("Il y a eu une erreur lors de la recherche des villes de départ");

	while($row = oci_fetch_assoc($stmt))
	{
		echo "<option value='" . $row['IDVILLE'] . "' >" .
			$row['NOMVILLE']. "</option>\n";
	}

	?>
				</select>
				<input type="submit" value="Go !" />
			</form>
	<?php
}
else if(! isset($_SESSION['date_depart']) && isset($_SESSION['ville_depart'], $_SESSION['ville_arrivee']))
{
	?>
		<h5>Choisissez votre date et horraire de départ.</h5>
		<form class="nice" action="vols.php" method="POST" >
			<fieldset>
			<select id="date_depart" name="date_depart">
<?php 

$query = "select V.idVol as idvol, V.idCompagnie as idcompagnie, C.nomCompagnie as nomcompagnie, 
to_char(V.dateDepart, 'yyyy/mm/dd hh24:mi/ss') as ledatedepart,
to_char(V.dateArrivee, 'yyyy/mm/dd hh24:mi/ss') as ledatearrivee 
from VOL V JOIN COMPAGNIE C ON V.idCompagnie = C.idCompagnie
where V.idVilleDepart=" . $_SESSION['ville_depart'] . 
" and V.idVilleArrivee= " . $_SESSION['ville_arrivee'] . " and SYSDATE < V.dateDepart";

$stmt = oci_parse($conn, $query);
if(! oci_execute($stmt))
	die("Il y a eu une erreur lors de la recherche des villes de départ");

while($row = oci_fetch_assoc($stmt))
{
	echo "<option value='" . $row['IDVOL'] . "_" . $row['IDCOMPAGNIE'] . "' >" . 
		$row['NOMCOMPAGNIE']. ". Date de départ : " .$row['LEDATEDEPART'] . " Date d'arrivée : " . $row['LEDATEARRIVEE'] . " </option>\n";
}
?>
			</select>
			<input type="submit" value="Go !" />
		</form>

<?php
}
?>
			</div>
		</div>
	</div>
<?php include("includes/in_pied"); ?>
