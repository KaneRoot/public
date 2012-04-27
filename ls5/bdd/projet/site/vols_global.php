<?php 

session_start();

include("co.php");
include("fonctions.php");


/* on s'assure que la personne est connectée et gestionnaire */
verifier_est_gestionnaire();

$compagnie = getCompagnie();

$_TITRE_PAGE="BDD - vols de la compagnie";
include("includes/in_entete"); 

?>
	<!-- container -->
	<div class="container">

		<?php include("includes/in_haut"); ?>

		<div class="row">
			<h5>Visuel sur l'ensemble de nos vols.</h5>
			<div class="twelve columns panel">
<?php
afficher_les_vols($conn);
?>
			</div>
		</div>
	</div>
<?php include("includes/in_pied"); ?>
