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
afficher_les_vols($conn);

?>

			</div>
		</div>
	</div>
<?php include("includes/in_pied"); ?>
