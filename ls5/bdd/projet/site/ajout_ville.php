<?php 
	session_start();
	$_TITRE_PAGE="BDD - ajout ville";
	include("includes/in_entete"); 
	include("co.php");

if(isset($_POST['addville']) && strlen($_POST['addville']) > 0)
{
	$ville = "'" . $_POST['addville'] . "'";
	$query = "insert INTO VILLE VALUES(seq_ville.nextVal , $ville )";
	$stmt = oci_parse($conn, $query);
	if(! oci_execute($stmt))
		die("Il y a eu une erreur à l'ajout de la ville $ville .");
}

?>
	<!-- container -->
	<div class="container">

		<?php include("includes/in_haut"); ?>
	
		<div class="row">
			<div class="six columns">
				<form class="nice" action="" method="POST" >
					<fieldset>
					<h5>Ajout d'une ville</h5>
					<p>Il faut vérifier qu'on ne l'a pas déjà !</p>
					<input id='addville' name='addville' type="text" placeholder="Ville" class="input-text" />
					</fieldset>
					<input type="submit" value="Ajouter la ville" />
					<input type="reset" value="Oublier ça" />
				</form>
			</div>
			<div class="six columns">
				<h5>Les villes déjà présentes</h5>
<?php

$query = "select idVille, nomVille from VILLE";
$stmt = oci_parse($conn, $query);
if( ! oci_execute($stmt))
	die("Il y a eu une erreur durant la recherche des villes.");

echo "<p>";
while($row = oci_fetch_assoc($stmt))
{
	echo $row['IDVILLE'] . " :: " . $row['NOMVILLE'] . " <br />";
}
echo "</p>";

?>
			</div>
		</div>

	</div>
<?php 
	include("includes/in_pied"); 
?>
