<?php 

session_start();

include("co.php");

$_TITRE_PAGE="BDD - vols";
include("includes/in_entete"); 

?>
	<!-- container -->
	<div class="container">

		<?php include("includes/in_haut"); ?>

		<div class="row">
			<div class="eight columns panel">

<?php

if(! isset($_POST['ville_depart'], $_POST['ville_arrivee']))
{
	?>
			<form class="nice" action="" method="POST" >
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
else
{
	?>
			<form class="nice" action="" method="POST" >
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
?>
			</div>
			<div class="three columns panel">
			<h5>Les vols</h5>
			<p>Voici la page où vous pouvez sélectionner le vol que vous allez prendre !</p>

			</div>
		</div>
	</div>
<?php include("includes/in_pied"); ?>
